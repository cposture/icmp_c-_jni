package com.icmp.util;

/**
 * int类型IP地址和String类型(xxx.xxx.xxx.xxx)IP地址相互转换
 * @author Administrator
 *
 */
public class IPUtil {
	
	/**
	 * String类型(xxx.xxx.xxx.xxx)IP地址转为int类型
	 * 最高8位表示最后一个'xxx'(从左往右),以此类推
	 * @param ip String类型(xxx.xxx.xxx.xxx)IP地址
	 * @return int 类型IP地址
	 */
	public static int toInt(String ip) throws IllegalArgumentException{
		if(ip == null || ip.isEmpty()){
			return 0;
		}
		String[] ipList = ip.split("\\.");
		if(ipList.length < 4){
			throw new IllegalArgumentException(ip + " isn't a valid ip address.");
		}

		return  (Integer.valueOf(ipList[3]) << 24 & 0xFF000000) 
			   |(Integer.valueOf(ipList[2]) << 16 & 0x00FF0000)
			   |(Integer.valueOf(ipList[1]) << 8 & 0x0000FF00)
			   |(Integer.valueOf(ipList[0]) & 0x000000FF);
	}
	
	public static String toStr(int ip){
		StringBuilder ipStr = new StringBuilder();
		ipStr.append((ip & 0xFF)).append(".");
		ipStr.append((ip >> 8 & 0xFF)).append(".");
		ipStr.append((ip >> 16 & 0xFF)).append(".");
		ipStr.append((ip >> 24 & 0xFF));
		return ipStr.toString();
	}
	
	public static void main(String[] args){
		int ip = toInt("192.168.1.12");
		System.out.println("int ip:" + ip);
		
		String ipStr = toStr(ip);
		System.out.println("str ip:" + ipStr);
	}
}
