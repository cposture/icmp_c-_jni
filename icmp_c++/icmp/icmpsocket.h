#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mstcpip.h>
#include "common.h"

#pragma comment(lib,"WS2_32.lib")

class IcmpSocket
{
private:
	bool isInit;
	SOCKET _socket;
	char* buff;

	sockaddr_in _from_addr;
	int _from_addr_len;
public:
	IcmpSocket();
	~IcmpSocket();
	int Init();
	void Uninit();
	int send(char* pDst_ip);
	const char* receive();
protected:

};