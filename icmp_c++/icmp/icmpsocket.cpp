#include "icmpsocket.h"

u_short checknum(u_short *buffer,int size);

IcmpSocket::IcmpSocket()
{
	isInit = false;
	buff = NULL;
	_from_addr_len = 0;
	_from_addr_len = sizeof(_from_addr);
	memset(&_from_addr,0,_from_addr_len);
}

IcmpSocket::~IcmpSocket()
{
	SAFE_DELETE(buff);
}

int IcmpSocket::Init()
{
	int _result = 0;
	if(isInit == true)
	{
		return _result;
	}
	WSADATA _wsaData;
	_result = WSAStartup(MAKEWORD(2,2),&_wsaData);
	if(_result == SOCKET_ERROR)
	{
		return SOCKET_ERROR;
	}
	
	_socket = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
	if(_socket == SOCKET_ERROR)
	{
		closesocket(_socket);
		WSACleanup();
		return SOCKET_ERROR;
	}

	char _host_name[255];
	memset(_host_name,0,sizeof(_host_name));

	_result = gethostname(_host_name,sizeof(_host_name));
    if(_result == SOCKET_ERROR)
	{
		closesocket(_socket);
		WSACleanup();
		return SOCKET_ERROR;
	}	

	hostent* _pHost = NULL;
	_pHost = gethostbyname(_host_name);
	if(_pHost == NULL)
	{
		closesocket(_socket);
		WSACleanup();
		return SOCKET_ERROR;
	}

	sockaddr_in _host_addr;
	_host_addr.sin_family = AF_INET;
	_host_addr.sin_port = 0;
	memcpy(&_host_addr.sin_addr.S_un.S_addr,_pHost->h_addr_list[0],_pHost->h_length);

	_result = bind(_socket,(sockaddr*)&_host_addr,sizeof(_host_addr));
	if(_result == SOCKET_ERROR)
	{
		closesocket(_socket);
		WSACleanup();
		return SOCKET_ERROR;
	}

	DWORD dwBufferLen[10];
	DWORD dwBufferInLen = 1;
	DWORD dwBytesReturned = 0;
	_result = WSAIoctl(_socket, SIO_RCVALL, &dwBufferInLen, sizeof(dwBufferInLen), 
		&dwBufferLen, sizeof(dwBufferLen), &dwBytesReturned, NULL, NULL);
	if(_result == SOCKET_ERROR)
	{
		closesocket(_socket);
		WSACleanup();
		return SOCKET_ERROR;
	}

	//初始化数据接收缓存区
	SAFE_DELETE(buff);
	buff = new char[_buffer_size];
	if(buff == NULL)
	{
		for(int i = 0; i <= 2; i++)
		{
			buff = new char[_buffer_size];
			if(buff != NULL)
			{
				break;
			}
		}
		if(buff == NULL)
		{
			closesocket(_socket);
			WSACleanup();
			return SOCKET_ERROR;
		}
	}
	memset(buff,0,sizeof(buff));

	isInit = true;
	return _result;
}

void IcmpSocket::Uninit()
{
	if(isInit == false)
	{
		return;
	}
	isInit = false;
	SAFE_DELETE(buff);
	closesocket(_socket);
	WSACleanup();
}

int IcmpSocket::send(char* pDst_ip)
{
	if(isInit == false)
	{
		return SOCKET_ERROR;
	}

	//icmp请求数据包
	icmp _icmp;
	memset(&_icmp,0,sizeof(_icmp));
	_icmp.icmph.type = 0x08;
	_icmp.icmph.code = 0;
	memset(&_icmp.data,1,sizeof(_icmp.data));
	_icmp.icmph.checksum = checknum((u_short*)&_icmp,sizeof(_icmp));

	//目标IP地址
	sockaddr_in _dst_addr;
	_dst_addr.sin_family = AF_INET;
	_dst_addr.sin_port = 0;
	_dst_addr.sin_addr.S_un.S_addr = inet_addr(pDst_ip);

	return sendto(_socket,(char*)&_icmp,sizeof(_icmp),0,(sockaddr*)&_dst_addr,sizeof(_dst_addr));
}

const char* IcmpSocket::receive()
{
	if(isInit == false || buff == NULL)
	{
		return NULL;
	}
	int _result = 0;
	memset(buff,0,sizeof(buff));
	_result = recvfrom(_socket,buff,_buffer_size,0,(sockaddr*)&_from_addr,&_from_addr_len);
	if(_result == SOCKET_ERROR)
	{
		return NULL;
	}
	return buff;
}

//icmp首部校验和
u_short checknum(u_short *buffer,int size)
{
     unsigned long cksum=0;

     while(size > 1)
	 {
	     cksum += *buffer++;
	     size -= sizeof(u_short);
	 }

     if(size)
     {
	      cksum += *(u_char *)buffer;
	 }
     cksum=(cksum >> 16) + (cksum & 0xffff);
     cksum+=(cksum >> 16);
     return(u_short) (~cksum);
 }