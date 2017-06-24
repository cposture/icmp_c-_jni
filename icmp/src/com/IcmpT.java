package com;

import com.icmp.IcmpPacket;
import com.icmp.IcmpSocket;
import com.icmp.factroy.FactoryManger;
import com.icmp.factroy.IcmpSocketFactory;


public class IcmpT {

	/**
	 * @param args
	 */
	public static void main(String[] args) { 
		IcmpSocketFactory factory = FactoryManger.getDefaultFactory();
		IcmpSocket icmpSocket = factory.createIcmpSocket();
		icmpSocket.init();

		IcmpPacket packet = null;
		for(int i = 0; i < 10000; i++){
			//icmpSocket.send("61.135.169.125");
			try {
				Thread.sleep(20);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			packet = icmpSocket.receive();
			if(packet.isNull() == false){
				if(packet.getType() ==0 && packet.getCode() == 0){
					System.out.println("来自: " + packet.srcIpToString());
				}
				//System.out.println("src: " + packet.srcIpToString() + "  dst: " + packet.dstIpToString());
			}
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		icmpSocket.uninit();
	}

}
