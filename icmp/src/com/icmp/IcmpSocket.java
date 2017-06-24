package com.icmp;

public interface IcmpSocket {
	int init();
	void uninit();
	int send(String targetIp);
	IcmpPacket receive();
}
