/******************************************************************************
*Copyright (C), CETE38
*�ļ���  :    JTAGLog.h
*����    :    �ֹ㶰 ���ƹ��
*�汾    :    v0.0.1
*�������:    2012-12-29
*����    :    ��־�ӿڶ���
*����    :
*��ʷ��¼:
*1.
*�޸�����:2012-12-29
*����    :�ֹ㶰
*�޸�����:����
******************************************************************************/

#ifndef JTAG_LOG_H_
#define JTAG_LOG_H_

//if define this, log to stdout
//if define this, log to file
//if not define all, do not log.
//#define LOG_CMD
//#define LOG_FILE

#ifdef LOG_CMD
#define JTAGLogStr(level, str) JTAGLog(level, str, 0)
#define JTAGLog(level,format,...) logPrintf(level,format,__VA_ARGS__)
#define JTAGOpenLogFile()
#define JTAGCloseLogFile()
#define JTAGSetLogFileDir(directory)
extern void logPrintf(int level, char *format, ...);
#elif defined(LOG_FILE)
#include <string>
#include <sstream>
#include <ctime>
using namespace std;
#define JTAGLogStr(level, str) JTAGLog(level, str, 0)
#define JTAGLog(level, format, ...) logFilePrintf(level, format, __VA_ARGS__)
#define JTAGOpenLogFile() openLogFile()
#define JTAGCloseLogFile() closeLogFile()
#define JTAGSetLogFileDir(directory) setLogFileDir(directory)
extern void logFilePrintf(int, char *, ...);
extern void openLogFile();
extern void closeLogFile();
extern void setLogFileDir(const char *directory);
#else
#define JTAGLogStr(level, str)
#define JTAGLog(level,format,...)
#define JTAGOpenLogFile()
#define JTAGCloseLogFile()
#define JTAGSetLogFileDir(directory)
#endif//#ifdef LOG_CMD

#endif//#ifndef JTAG_LOG_H_

