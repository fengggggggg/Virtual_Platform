/******************************************************************************
Copyright (C), CETE38
文件名  :    CommProtocol.h
作者    :    黄光红      
版本    :    v0.0.1       
完成日期:    2013-03-01
描述    :    CommProtocol.h定义CommProtocol类，
                        描述通信协议，包含一个接收线程自动接收DCS的数据包。将接收到的应答包存储在所有者的respPackList；
                        将接收到的通知包存储在所有者的notifyPackList，并通知事件模块处理。并以可通过它发送数据包。
其它    :          
历史记录:       
1. 
修改日期:
作者    :
修改内容:
2. 
...
******************************************************************************/

#ifndef RECV_DATA_PACK_THREAD_H
#define RECV_DATA_PACK_THREAD_H

//#define BOOST_THREAD_NO_LIB
//#define BOOST_DATE_TIME_SOURCE
#include "IRemoteComm.h"

#include <vector>
#include <map>
#include <string>

//使用boost的线程库需要的头文件
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>


using namespace std;
using namespace boost;


//DCS调试连接服务端simulator类型
const unsigned char DCS_Type_SIMULATOR = 1;

//同步字符
const char PACK_SYNC_HEAD[4] = {0X5A, 0XA5, 0X7B, 0XB7};
//最大包长度
const unsigned short MAX_PACK_LENGTH = 4096;
//包头长度
const unsigned short PACK_HEAD_LENGTH = 8;
//最大包信息长度，包括包头、正文、校验和三部分
const unsigned short MAX_PACK_INFO_LENGTH = MAX_PACK_LENGTH - 4;//4092
//最小包信息长度
const unsigned short MIN_PACK_INFO_LENGTH = PACK_HEAD_LENGTH + 1;//9
//最大包正文长度
const unsigned short MAX_PACK_TEXT_LENGTH = MAX_PACK_LENGTH - 4 - 1 -8;//4083
//最小包正文长度
const unsigned short MIN_PACK_TEXT_LENGTH = 0;

/*DataPackPrePart表示数据包头部分*/
typedef union DataPackHeadTag
{
    struct _header
    {
        unsigned short infoLength;//包信息长度，信息长度＝包头＋正文＋校验和
        unsigned char deviceID;//设备标识
        unsigned char reserve0;//保留信息
        unsigned char chipID;//处理器标识
        unsigned char reserve1;//保留信息
        unsigned short packSN;//包序号
    }header;
    unsigned char head[PACK_HEAD_LENGTH];
}DataPackHead;

/*DataPackPostPart表示数据包正文部分*/
typedef union DataPackTextTag
{
    struct _reqsPack
    {
        unsigned short commandID;//命令标识
        unsigned char subInfo;//设附加信息
        //请求包部分参数，最大为4080
        unsigned char reqsPara[MAX_PACK_TEXT_LENGTH - 3];
    }reqsPack;
    struct _respPack
    {
        unsigned short commandID;//命令标识
        unsigned char subInfo;//设附加信息
        unsigned char result;//执行结果
        //应答包部分参数，最大为4079
        unsigned char respPara[MAX_PACK_TEXT_LENGTH - 4];
    }respPack;
    unsigned char text[MAX_PACK_TEXT_LENGTH];
}DataPackText;

/*DataPack表示数据包*/
typedef struct DataPackTag
{
    //数据包包头
    boost::shared_ptr<DataPackHead> headPart;
    //数据包正文长度
    unsigned short textLength;
    //数据包正文
    boost::shared_ptr<DataPackText> textPart;
    //校验和
    unsigned char checkSum;
}DataPack;


//class IRemoteComm;
//class SimDebugProtocol;


/******************************************************************************
类名    :    CommProtocol
描述    :    CommProtocol定义通信协议，包含一个接收线程自动接收DCS的数据包。将接收到的应答包存储在所有者的
         respPackList； 将接收到的通知包存储在所有者的notifyPackList，并通知事件模块处理。
                         并以可通过它发送数据包。
其它    :
******************************************************************************/
class CommProtocol
{
private:

    //物理通信通道
    IRemoteComm *remoteComm;
    _ConnectType CommType;
    //boost线程类,接收数据包
    boost::thread *recvThread;

public:
   boost::mutex reqtPackListMutex;  //互斥访问reqtPackList
   vector<DataPack> reqtPackList;//应答包列表

   boost::mutex sendMutex;

   boost::mutex stopThreadMutex;  //互斥访问stopThreadFlag
   //bool stopThreadFlag;//停止接收包线程标志
private:
	unsigned int ntfyPackSN;
	map<unsigned short, string> commandInfo;

public:
//	void setCommPort(unsigned int port){remoteComm->setCommPort(port);};

    /******************************************************************************
    *函数名称:    getRemoteComm
    *描述    :    获取物理通信通道
    *输入参数:    无
    *输出参数:    无
    *返回值  :    物理通信通道
    *其它    :
    ******************************************************************************/
    IRemoteComm *getRemoteComm();

    /******************************************************************************
    函数名称:    CommProtocol
    描述    :    构造函数
    输入参数:    owner指定所属调试器
    输出参数:    无
    返回值  :    无      
    其它    :    
    ******************************************************************************/
    CommProtocol();

	void initCommandInfo();

    /******************************************************************************
    函数名称:    CommProtocol
    描述    :    析构函数
    输入参数:    无
    输出参数:    无
    返回值  :    无      
    其它    :    
    ******************************************************************************/
    ~CommProtocol();

    /******************************************************************************
        函数名称:    openComm
        描述    :    打开通信
        输入参数:    无
        输出参数:    无
        返回值  :    空
        其它    :
        ******************************************************************************/
    int openComm();

    /******************************************************************************
        函数名称:    closeComm
        描述    :    关闭通信
        输入参数:    无
        输出参数:    无
        返回值  :    空
        其它    :
        ******************************************************************************/
    void closeComm();

    /******************************************************************************
    函数名称:    startupThread
    描述    :    启动接收线程
    输入参数:    无
    输出参数:    无
    返回值  :    空
    其它    :
    ******************************************************************************/
    void startupThread();

    /******************************************************************************
    函数名称:    stopThread
    描述    :    停止接收线程
    输入参数:    无
    输出参数:    无
    返回值  :    空
    其它    :
    ******************************************************************************/
    void stopThread();

private:
    /******************************************************************************
    函数名称:    searchSyncHead
    描述    :    搜素数据包同步字头。
    输入参数:    无
    输出参数:    无
    返回值  :    成功返回0，失败返回错误码
    其它    :
    ******************************************************************************/
    int searchSyncHead();

    /******************************************************************************
         函数名称:    getCheckSum
         描述    :    计算数据包的校验和
         输入参数:   dataPack为数据包，具有包头和正文信息。
         输出参数:   无
         返回值  :    返回校验和
         其它    :
    ******************************************************************************/
    unsigned char getCheckSum(DataPack &dataPack);

public:
    /******************************************************************************
    函数名称:    testCheckSum
    描述    :    检查数据包的校验和是否正确
    输入参数:   dataPack为数据包，具有包头和正文信息。
    输出参数:   无
    返回值  :    返回校验和检查是否正确
    其它    :
    ******************************************************************************/
	bool testCheckSum(DataPack &dataPack);

    /******************************************************************************
       函数名称:    waitReqtPack
       描述    :    等待包。等待直到reptPackList中有包才返回。
       输入参数:    无
       输出参数:    若等到应答包，reptPack返回应答包。
       返回值  :    无
       其它    :
     ******************************************************************************/
    void waitReqtPack(DataPack &respPack);

    /******************************************************************************
           函数名称:    createReqsPack
           描述    :    创建请求包
           输入参数:   commandID指定请求命令标识；para指定请求包参数
           输出参数:   connectPack为创建的请求包
           返回值  :    成功返回０；失败返回非０错误码
           其它    :
     ******************************************************************************/
    int createRespPack(DataPack &connectPack, const unsigned short commandID,
            unsigned short packSN,vector<char> *reqsPara);

   /******************************************************************************
           函数名称:    createReqsPack
           描述    :    创建请求包
           输入参数:   commandID指定请求命令标识；para指定请求包参数
           输出参数:   connectPack为创建的请求包
           返回值  :    成功返回０；失败返回非０错误码
           其它    :
     ******************************************************************************/
    int createNtfyPack(DataPack &connectPack, const unsigned short commandID,
         vector<char> *ntfyPara);

    /******************************************************************************
             函数名称:    printReqsDataPack
             描述    :    打印请求数据包。
             输入参数:   reqsDataPack为请求数据包
             输出参数:   无
             返回值  :   无
             其它    :
    ******************************************************************************/
    void printReqsDataPack(DataPack &reqsDataPack);

    /******************************************************************************
                 函数名称:    printRespDataPack
                 描述    :    打印应答数据包。
                 输入参数:   reqsDataPack为应答数据包
                 输出参数:   无
                 返回值  :   无
                 其它    :
    ******************************************************************************/
    void printRespDataPack(DataPack &respDataPack);

    /******************************************************************************
                 函数名称:    printNtfyDataPack
                 描述    :    打印异步上报数据包。
                 输入参数:   ntfyDataPack为异步上报数据包
                 输出参数:   无
                 返回值  :   无
                 其它    :
    ******************************************************************************/
    void printNtfyDataPack(DataPack &ntfyDataPack);


    /******************************************************************************
    函数名称:    recvDataPack
    描述    :    接收数据包。接受到一个完整数据包才返回。
    输入参数:    无
    输出参数:    无
    返回值  :    成功返回0，失败返回错误码
    其它    :    若接收到应答包存放在应答包列表；若接收到通知包存放在通知包列表。
    ******************************************************************************/
    int recvDataPack();

    /******************************************************************************
    函数名称:    sendDataPack
    描述    :    发送数据包
    输入参数:    dataPack为数据包
    输出参数:    无
    返回值  :    成功返回0，失败返回错误码
    其它    :
    ******************************************************************************/
    int sendDataPack(DataPack *pack);



};//End class CommProtocol define



#endif//RECV_DATA_PACK_THREAD_H





