package com.icmp;

import com.icmp.util.IPUtil;

public class IcmpPacket {

	/**
	 * 源IP
	 */
	private int sourceIp;

	/**
	 * 目的IP
	 */
	private int destinationIp;

	/**
	 * 8位类型
	 */
	private byte type;

	/**
	 * 8位code
	 */
	private byte code;

	/**
	 * 标识是否为空数据包
	 */
	private boolean isNull;

	public byte getType() {
		return type;
	}

	public void setType(byte type) {
		this.type = type;
	}

	public byte getCode() {
		return code;
	}

	public void setCode(byte code) {
		this.code = code;
	}

	public int getSourceIp() {
		return sourceIp;
	}

	public void setSourceIp(int sourceIp) {
		this.sourceIp = sourceIp;
	}

	public int getDestinationIp() {
		return destinationIp;
	}

	public void setDestinationIp(int destinationIp) {
		this.destinationIp = destinationIp;
	}

	public String srcIpToString() {
		return IPUtil.toStr(sourceIp);
	}

	public String dstIpToString() {
		return IPUtil.toStr(destinationIp);
	}

	public boolean isNull() {
		return isNull;
	}

	public void setNull(boolean isNull) {
		this.isNull = isNull;
	}

}
