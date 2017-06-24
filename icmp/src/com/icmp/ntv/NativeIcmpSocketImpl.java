package com.icmp.ntv;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import com.icmp.IcmpPacket;
import com.icmp.IcmpSocket;

/**
 * icmp socket 用c++实现icmp数据包的接收和发送 
 * @author Administrator
 *
 */
public class NativeIcmpSocketImpl implements IcmpSocket {
	
	/**
	 * 数据接收缓存区
	 */
	private static IcmpPacket icmpPacket = new IcmpPacket();
	
	/**
	 * 标识icmp.dll是否已经加载。
	 */
	private static boolean dllIsLoad = false;
	
	//加载icmp.dll链接库
	static{
		String tempdll = System.getProperty("java.io.tmpdir");
		String osname = System.getProperty("os.name");
		String dllName = "icmp";
		if(osname.toLowerCase().startsWith("window")){
			dllName += ".dll";
		}else if(osname.toLowerCase().startsWith("linux")){
			dllName += ".so";
		}else if(osname.toLowerCase().startsWith("unix")){
			dllName += ".so";
		}
		tempdll += dllName;
		
		//生成icmp.dll临时文件
		File file = new File(tempdll);
		boolean canLoadIcmpDll = false;
		if(!file.exists()){
			String icmpdllPath = NativeIcmpSocketImpl.class.getPackage().getName().replace(".", "/") + "/" + dllName;
			InputStream in = Thread.currentThread().getContextClassLoader().getResourceAsStream(icmpdllPath);
			if(in != null){
				try {
					OutputStream os = new FileOutputStream(file);
					byte[] b = new byte[1024];
					int readSize = 0;
					while((readSize = in.read(b)) != -1){
						os.write(b, 0, readSize);
						os.flush();
					}
					os.close();
					canLoadIcmpDll = true;
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				}finally{
					try {
						in.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		}else{
			canLoadIcmpDll = true;
		}
		
		if(canLoadIcmpDll){
			System.load(file.getAbsolutePath());
			dllIsLoad = true;
		}
	}
	@Override
	public int send(String targetIp) {
		if(dllIsLoad){
			return this.nativeSend(targetIp);
		}
		return 0;
	}

	@Override
	public IcmpPacket receive() {
		if(dllIsLoad){
			icmpPacket.setNull(true);
			this.nativeReceive(icmpPacket);
		}
		return icmpPacket;
	}
	
	@Override
	public int init() {
		if(dllIsLoad){
			return this.nativeInit();
		}
		return 0;
	}

	@Override
	public void uninit() {
		if(dllIsLoad){
			this.nativeUninit();
		}
	}

	@Override
	protected void finalize() throws Throwable {
		if(dllIsLoad){
			this.nativeUninit();
		}
	}
	
	private native int nativeSend(String targetIp);
	private native void nativeReceive(IcmpPacket icmpPacket);
	private native int nativeInit();
	private native void nativeUninit();
}
