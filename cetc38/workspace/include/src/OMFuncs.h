
//---------------------------------------------------------------------------
#ifndef OM_FUNCS_H
#define OM_FUNCS_H

/*---------------------------Include Files-------------------------*/

//extern bool RdIRQsFile(string p_strFileName, int *p_intIRQs);
extern bool  RdNewIRQsFile(string p_strFileName, DSPU64 *p_u64IRQs);
//extern bool OpenLogFile(string p_strFileName);
//extern bool WrValueToLog(DSPU32 p_u32Content);
//extern bool WrSpaceToLog();
//extern bool WrEndlToLog();
//extern void CloseLogFile();
//void TestDLL();
extern void TestDLL();
extern bool comp_svct_call_ret(string p_strIOPath,  int  p_intType);

#endif	//OM_FUNCS_H



