package com.icmp.factroy;

import com.icmp.ntv.NativeIcmpSocketFactoryImpl;

public class FactoryManger {
	
	private static IcmpSocketFactory defaultFactory;
	
	static{
		defaultFactory = new NativeIcmpSocketFactoryImpl();
	}
	
	public static IcmpSocketFactory getDefaultFactory(){
		return defaultFactory;
	}
}
