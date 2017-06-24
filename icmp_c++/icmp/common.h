#pragma once
#include <Windows.h>

#define SAFE_DELETE(pObject) if(pObject != NULL){delete pObject; pObject = NULL;}
#define SAFE_DELETE_ARRAY(pObject) if(pObject != NULL){delete[] pObject; pObject = NULL;}

const u_short _max_size = 65535;
const u_int _buffer_size = 128;

//ip地址
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;

}ip_address;

//ip协议首部
typedef struct ip_header
{
	u_char		vsn_hlen;			//4位版本号,4位首部长度
	u_char		tos;				//8位服务类型
	u_short		total_len;			//16位总长度（字节数）
	u_short		identification;		//16位标识
	u_short		flags_offset;       //3位标志,13位片偏移量
	u_char		time_to_live;		//8位生存时间
	u_char		protocol;			//8位协议
	u_short		header_checksum;	//16位首部检验和
	ip_address	src_ip;				//32位源ip地址
	ip_address	dst_ip;				//32位目的ip地址

	void set_vsn_hlen()
	{
		vsn_hlen = 5; //低4位首部长度
		vsn_hlen = vsn_hlen | 64;//高4位版本号
	}

}ip_header;

//icmp协议首部
typedef struct icmp_header
{
	u_char	type;
	u_char	code;
	u_short checksum; 

}icmp_header;

typedef struct icmp
{
	icmp_header icmph;
	u_char data[5];
} icmp;

//icmp数据包
typedef struct icmp_packet
{
	ip_header	iph;
	icmp _icmp;
}icmp_packet;
