#include "com_icmp_ntv_NativeIcmpSocketImpl.h"
#include "icmpsocket.h"
#include <stdio.h>

IcmpSocket _icmpSocket;

jobject _icmp_obj = NULL;

jshort two_unsign_char_2_jshort(u_char _type,u_char _code)
{
	return (0xFF00 & _type << 8) | _code;
}

/*
 * Class:     com_icmp_ntv_NativeIcmpSocketImpl
 * Method:    nativeSend
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_icmp_ntv_NativeIcmpSocketImpl_nativeSend
  (JNIEnv *env, jobject _this, jstring _dst_ip)
{
	const char* _pDst_ip = env->GetStringUTFChars(_dst_ip,NULL);
	if(_pDst_ip == NULL)
	{
		return NULL;
	}
	int _result =  _icmpSocket.send((char*)_pDst_ip);
	env->ReleaseStringUTFChars(_dst_ip,_pDst_ip);
	return _result;
}


/*
 * Class:     com_icmp_ntv_NativeIcmpSocketImpl
 * Method:    nativeReceive
 * Signature: (Lcom/icmp/IcmpPacket;)V
 */
JNIEXPORT void JNICALL Java_com_icmp_ntv_NativeIcmpSocketImpl_nativeReceive
  (JNIEnv *_env, jobject _this, jobject _icmp_obj)
{
	if(_icmp_obj == NULL)
	{
		return;
	}

	//receive icmp packet.
	const icmp_packet *_icmp_packet = NULL;
	_icmp_packet = (const icmp_packet *)_icmpSocket.receive();
	if(_icmp_packet == NULL)
	{
		return;
	}

	//find packet class.
	static jclass _jicmp_packet_clazz = NULL;
	if(_jicmp_packet_clazz == NULL)
	{
		_jicmp_packet_clazz = _env->GetObjectClass(_icmp_obj);
		if(_jicmp_packet_clazz == NULL)
		{
			return;
		}
	}

	//find init method id.
	static jmethodID _icmp_init_method_id = NULL;
	if(_icmp_init_method_id == NULL)
	{
		_icmp_init_method_id = _env->GetMethodID(_jicmp_packet_clazz,"<init>","()V");
		if(_icmp_init_method_id == NULL)
		{
			return;
		}
	}
	
	//set icmp type method id.
	static jmethodID _icmp_type_method_id = NULL;
	if(_icmp_type_method_id == NULL)
	{
		_icmp_type_method_id = _env->GetMethodID(_jicmp_packet_clazz,"setType","(B)V");
		if(_icmp_type_method_id == NULL)
		{
			return;
		}
	}

	//set icmp code method id.
	static jmethodID _icmp_code_method_id = NULL;
	if(_icmp_code_method_id == NULL)
	{
		_icmp_code_method_id = _env->GetMethodID(_jicmp_packet_clazz,"setCode","(B)V");
		if(_icmp_code_method_id == NULL)
		{
			return;
		}
	}

	//set icmp source ip method id.
	static jmethodID _icmp_src_ip_method_id = NULL;
	if(_icmp_src_ip_method_id == NULL)
	{
		_icmp_src_ip_method_id = _env->GetMethodID(_jicmp_packet_clazz,"setSourceIp","(I)V");
		if(_icmp_src_ip_method_id == NULL)
		{
			return;
		}
	}

	//set icmp distination ip method id.
	static jmethodID _icmp_dst_ip_method_id = NULL;
	if(_icmp_dst_ip_method_id == NULL)
	{
		_icmp_dst_ip_method_id = _env->GetMethodID(_jicmp_packet_clazz,"setDestinationIp","(I)V");
		if(_icmp_dst_ip_method_id == NULL)
		{
			return;
		}
	}

	//set icmp isnull.
	static jmethodID _icmp_is_null_method_id = NULL;
	if(_icmp_is_null_method_id == NULL)
	{
		_icmp_is_null_method_id = _env->GetMethodID(_jicmp_packet_clazz,"setNull","(Z)V");
		if(_icmp_is_null_method_id == NULL)
		{
			return;
		}
	}

	icmp *_icmp_pt = NULL;
	_icmp_pt = (icmp *)&_icmp_packet->_icmp;

	//set packet parameters.
	_env->CallVoidMethod(_icmp_obj,_icmp_type_method_id,_icmp_pt->icmph.type);
	_env->CallVoidMethod(_icmp_obj,_icmp_code_method_id,_icmp_pt->icmph.code);
	_env->CallVoidMethod(_icmp_obj,_icmp_src_ip_method_id,_icmp_packet->iph.src_ip);
	_env->CallVoidMethod(_icmp_obj,_icmp_dst_ip_method_id,_icmp_packet->iph.dst_ip);
	_env->CallVoidMethod(_icmp_obj,_icmp_is_null_method_id,0);
}

/*
 * Class:     com_icmp_ntv_NativeIcmpSocketImpl
 * Method:    nativeInit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_icmp_ntv_NativeIcmpSocketImpl_nativeInit
  (JNIEnv *env, jobject _this)
{
	return _icmpSocket.Init();
}

/*
 * Class:     com_icmp_ntv_NativeIcmpSocketImpl
 * Method:    nativeUninit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_icmp_ntv_NativeIcmpSocketImpl_nativeUninit
  (JNIEnv *env, jobject _this)
{
	_icmpSocket.Uninit();
}