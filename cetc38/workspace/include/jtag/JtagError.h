/******************************************************************************
*Copyright (C), CETE38
*文件名  :    JtagError.h
*作者    :    林广栋
*版本    :    v0.0.1
*完成日期:    2013-03-26
*描述    :    JtagError.h定义系统错误码
*其它    :
*历史记录:
*1.
*修改日期:2013年3月30日
*作者    :林广栋
*修改内容:定义JTAG接口错误码
******************************************************************************/

#ifndef JTAG_ERROR_H
#define JTAG_ERROR_H

const int JTAG_OK=0x00;
const int JTAG_SUCCESS = 0X00;

/*----------------------------------调试连接服务端DCS错误码---------------------*/
//0x1001~0x10FF保留供调试连接服务端DCS使用

const int CORE_IS_RUNNING=0x81;
const int CORE_IS_NOT_RUNNING=0x82;
const int CORE_ID_NOT_FOUND=0x83;
const int CORE_GROUP_NO_ONE_FOUND=0x84;
const int READ_REG_ERROR=0x85;
const int WRITE_REG_ERROR=0x86;
const int BREAKPOINT_INSERT_ERROR=0x87;
const int WATCHPOINT_INSERT_ERROR=0x88;
const int CONNECT_CHECK_ERROR=0x89;
const int READ_MEMORY_ERROR=0x8a;
const int WRITE_MEMORY_ERROR=0x8b;
const int SERVER_ETHERNET_RECV_ERROR=0x8c;
const int SERVER_PACK_INFO_LENGTH_ERROR=0x8d;
const int SERVER_PACK_TEXT_LENGTH_ERROR=0x8e;
const int SERVER_ETHERNET_IPADDRESS_INVALID_ERROR=0x8f;
const int SERVER_ETHERNET_STARTUP_ERROR=0x90;
const int SERVER_ETHERNET_SEND_ERROR=0x91;
const int ONE_CORE_IS_RUNNING=0x92;
const int ONE_CORE_IS_NOT_RUNNING=0x93;
const int STATISTICS_MODE_OFF=0x94;
/*----------------------------------调试连接服务端DCS错误码---------------------*/




#endif//JTAG_ERROR_H





















