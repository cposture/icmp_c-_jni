#include "icmpsocket.h"
#include <stdio.h>

void main()
{
	IcmpSocket _icmpsocket;
	_icmpsocket.Init();
	
	const icmp_packet *_icmp_packet = NULL;
	const char* buff = NULL;
	while(true)
	{
		_icmpsocket.send("192.168.1.1");
		//Sleep(100);
		buff = _icmpsocket.receive();
		if(buff != NULL)
		{
			_icmp_packet = (icmp_packet *)buff;
			if(_icmp_packet->_icmp.icmph.code == 0 && _icmp_packet->_icmp.icmph.type == 0)
			{
				printf("icmp response: %d.%d.%d.%d\n",
					_icmp_packet->iph.src_ip.byte1,
					_icmp_packet->iph.src_ip.byte2,
					_icmp_packet->iph.src_ip.byte3,
					_icmp_packet->iph.src_ip.byte4);
			}

			printf("src ip: %d.%d.%d.%d\n",
				_icmp_packet->iph.src_ip.byte1,
				_icmp_packet->iph.src_ip.byte2,
				_icmp_packet->iph.src_ip.byte3,
				_icmp_packet->iph.src_ip.byte4);
		}

		Sleep(1000);
	}
	_icmpsocket.Uninit();

}