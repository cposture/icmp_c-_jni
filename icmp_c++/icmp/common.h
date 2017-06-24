#pragma once
#include <Windows.h>

#define SAFE_DELETE(pObject) if(pObject != NULL){delete pObject; pObject = NULL;}
#define SAFE_DELETE_ARRAY(pObject) if(pObject != NULL){delete[] pObject; pObject = NULL;}

const u_short _max_size = 65535;
const u_int _buffer_size = 128;

//ip��ַ
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;

}ip_address;

//ipЭ���ײ�
typedef struct ip_header
{
	u_char		vsn_hlen;			//4λ�汾��,4λ�ײ�����
	u_char		tos;				//8λ��������
	u_short		total_len;			//16λ�ܳ��ȣ��ֽ�����
	u_short		identification;		//16λ��ʶ
	u_short		flags_offset;       //3λ��־,13λƬƫ����
	u_char		time_to_live;		//8λ����ʱ��
	u_char		protocol;			//8λЭ��
	u_short		header_checksum;	//16λ�ײ������
	ip_address	src_ip;				//32λԴip��ַ
	ip_address	dst_ip;				//32λĿ��ip��ַ

	void set_vsn_hlen()
	{
		vsn_hlen = 5; //��4λ�ײ�����
		vsn_hlen = vsn_hlen | 64;//��4λ�汾��
	}

}ip_header;

//icmpЭ���ײ�
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

//icmp���ݰ�
typedef struct icmp_packet
{
	ip_header	iph;
	icmp _icmp;
}icmp_packet;
