/******************************************************************************
Copyright (C), CETE38
文件名  :    PackCommandID.h
作者    :    黄光红
版本    :    v0.0.1
完成日期:    2013-03-01
描述    :    PackCommandID.h定义通信数据包的命令标识，或称为信息标签。
                        每个信息标签用唯一码表示，对应唯一的命令请求包、应答包、通知包。
其它    :
历史记录:
1.
修改日期:
作者    :
修改内容:
2.
...
******************************************************************************/
#ifndef PACK_COMMANDID_H
#define PACK_COMMANDID_H
//连接请求包标识
const unsigned short CONNECT_REQUEST_PACK = 0X0001;
//断开请求包标识
const unsigned short DISCONNECT_REQUEST_PACK = 0X0002;
//通信链路测试请求包标识
const unsigned short LINKTEST_REQUEST_PACK = 0X0003;
//目标系统检查请求包标识
const unsigned short TARGET_CHECK_REQUEST_PACK = 0X0010;
//目标机选择请求包标识
const unsigned short TARGET_SELECT_REQUEST_PACK = 0X0011;
//单核周期单步
const unsigned short SINGLE_CORE_STEP_CYCLE=0x0020;
//单核指令单步
const unsigned short SINGLE_CORE_STEP_INST=0x0021;
//单核继续运行
const unsigned short SINGLE_CORE_RUN=0x0022;
//单核暂停
const unsigned short SINGLE_CORE_PAUSE=0x0023;
//单核复位
const unsigned short SINGLE_CORE_RESET=0x0024;
//单核JTAG复位
const unsigned short SINGLE_JTAG_RESET=0x0025;


//多核运行
const unsigned short MULTI_CORE_STEP_CYCLE=0x0030;
//多核运行
const unsigned short MULTI_CORE_RUN=0x0032;
//多核同步停止
const unsigned short MULTI_CORE_PAUSE=0x0033;
//多核同步复位
const unsigned short MULTI_CORE_RESET=0x0034;
//多核同步JTAG复位
const unsigned short MULTI_CORE_JTAG_RESET=0x0035;

//读寄存器
const unsigned short READ_REGISTER=0x0040;
//写寄存器
const unsigned short WRITE_REGISTER=0x0041;
//读存储器
const unsigned short READ_MEMORY=0x0042;
//写寄存器
const unsigned short WRITE_MEMORY=0x0043;
//读寄存器（离散）
const unsigned short READ_MEMORY_DISCRETE=0x0044;
//写存储器（离散）
const unsigned short WRITE_MEMORY_DISCRETE=0x0045;

//读JTAG寄存器
const unsigned short WRITE_JTAG_REGISTER=0x0050;
//写JTAG寄存器
const unsigned short READ_JTAG_REGISTER=0x0051;

//设置断点
const unsigned short BREAKPOINT_INSERT=0x0060;
//清除断点
const unsigned short CLEAR_BREAKPOINT=0x0061;
//设置观察点
const unsigned short WATCHPOINT_INSERT=0x0062;
//清除观察点
const unsigned short CLEAR_WATCHPOINT=0x0063;


//设置JTAG时钟频率
const unsigned short SET_JTAG_FREQUENCY=0x00E0;

//软件模拟器专用命令
const unsigned short SIMULATOR_SPEC_COMMAND=0xff;

//停止事件通知包标识
const unsigned short STOP_EVENT_NOTIFY_PACK = 0X00F0;



#endif//PACK_COMMANDID_H
