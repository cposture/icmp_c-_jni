package com.icmp.ntv;

import com.icmp.IcmpSocket;
import com.icmp.factroy.IcmpSocketFactory;

public class NativeIcmpSocketFactoryImpl implements IcmpSocketFactory {

	@Override
	public IcmpSocket createIcmpSocket() {
		return new NativeIcmpSocketImpl();
	}

}
