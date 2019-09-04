/******************************************************************************
*Copyright (C), CETE38
*文件名  :    jtag.h
*作者    :    林广栋
*版本    :    v0.0.1
*完成日期:    2013-3-29
*描述    :    jtag接口定义
*其它    :
*历史记录:
*1.
*修改日期:2013-3-29
*作者    :林广栋
*修改内容:创建
******************************************************************************/



#ifndef JTAG_H
#define JTAG_H
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include "JTAGLog.h"
#include "../src/AlgoriLib/dsptypes.h"
#define RUNNING_STATE 1
#define STOP_STATE 0
#include "LoadELFFile.h"
#include <queue>
using namespace std;

typedef union tag_NetworkShort
{
	unsigned short st;
	unsigned char Buf[2];
}NetworkShort;

typedef union tag_NetworkInt
{
	unsigned int i;
	unsigned char Buf[4];
}NetworkInt;


#define JtagTestBit(x,y) ((x)&(1<<(y)))


/*TargetType表示目标机类型*/
enum _TargetType{
    BWDSP100 = 0,
    BWDSP1041,
    BWDSP1042,
    BWDSP1044,
    BWDSP1048,
    BWDSP200A,
    TargetNull
};

/*ConnectType表示远程通信连接类型*/
enum _ConnectType{
    Ethernet_TCP = 1,
    USB
};

#define STEP_CYCLE_END 0
#define STEP_INST_END 1
#define BP_HIT 2
#define WP_TRIGGER 3
#define PAUSE_COMMAND 4
#define CORE_EXCEPTION 5

#define JTAG_CHECK_INTERVAL 20//轮询目标机状态时间间隔

#define VIRTUAL_ABI_CHECK_REG_MAIN_ADDR 0x9020000
#define VIRTUAL_ABI_CHECK_REG_EXIT_ADDR 0x9020001

extern boost::mutex jtagMutex;
extern boost::mutex ntfyMutex;
typedef struct _ntfyMsg
{
	char coreIdx;
	unsigned int stopRsn;
	unsigned int pc;
	unsigned int wp;
}ntfyMsg;

extern queue<ntfyMsg> ntfyMsgQ;


extern void jtag_accept_thread(void *pTop);
extern void jtag_notify_thread();
extern void gateway_accept_thread();
extern bool bTerminateSelf;
extern bool bCommSetup;
extern bool bCodeCoverTest;
extern string CodeCoverDir;
extern string ABICheckDir;
extern unsigned int jtagPort;
extern string jtagIPAdr;

#endif


