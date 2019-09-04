#ifndef _LOG_INFO_H
#define _LOG_INFO_H
#include <stdarg.h>

enum
{
	NULL_REASON = 0,
	/*************** Reg Hazard Related ****************/
	GPR_HAZARD_NI,
	GPR_HAZARD_MR,
	SACC_HAZARD,
	STAB_HAZARD,
	CPRED_HAZARD,
	IRET_HAZARD,
	ISR_HAZARD,
	AREG_HAZARD,
	AMACC_HAZARD,
	/*************** BANK CONF Related ****************/
	BLK_PORT_CLOSED,
	RD_NOT_DONE,
	BANK_CONF,
	SLOT_CONF,
	BUS_CONF,
	MAX_STALL_REASON
};

enum FLUSH_REASON
{
	INT_OCCUR,
	IRET_FLUSH,
};


//-----------------------------------------------------------------------------------
bool InitLogForECS();
bool  ClrDbgInfo();
bool ResetSHFTab();
bool LogDMemOnIRET();

#ifdef STALL_REASON_LOG
	bool LogPipeStall(DSPU32 p_u32Reason, DSPU32 p_u32SrcPC, DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32Phase);
	bool LogBankConf(bool p_bolRead, DSPU32 p_u32Reason, DSPU32 p_u32Blk, DSPU32 p_u32Bank);
#endif
#ifdef MEM_CE_TESTING
	bool LogMemCE();
#endif


/************************* ISSStepCycle *************************/
#ifdef LOG_STEP_TESTING
	bool LogAddrRegs();
	bool  LogGenRegs();
	bool  LogALUReg0();
	bool  LogALUReg1();
	bool  LogSPURegs();
	bool  LogSHFRegs();
	bool  LogMULRegs();
	bool LogFlagRegs();
	bool LogSpecRegs();
	bool  LogImafr();
	void LogMemForUVWTest(DSPU32 addr, int length);
	bool LogDMACRegs();
	void LogSHFTAB();
#endif
#ifdef LOG_PXP
	bool LogPipePC_PXP();
	bool  LogGenRegs_PXP();
	bool  LogAddrRegs_PXP();
	bool LogALUReg_PXP();
	bool LogMULRegs_PXP();
	bool  LogSHFRegs_PXP();
#endif
#ifdef BWSIM_LOG_INFO
	bool LogINTRegs();
	void  LogDbgInfo();
	bool  LogDBGRegs();
	bool LogPipePC();
	
	bool LogCFG_Info();

	bool LogDBGPR();

	bool LogTimerRegs();
	
	bool LogPRComp();
	bool  LogData1Comp();
#endif
#ifdef BWSIM_CMP_100_104
	bool  LogGenRegs_100_104(unsigned int p_u32PC_WB);
#endif
#ifdef DECODER_TESTING
	bool  log_res_use_info_new(DSPU32 p_u32SlotNum, unsigned int *p_pSLKIdxs, unsigned int *p_pSlot);
	void LogBusTest(DSPU32 p_u32SlotNum, unsigned int *p_pSLKIdxs, unsigned int *p_pSlot);
#endif
#ifdef INTERRUPT_TESTING
	bool LogIRQTestGREG();
	bool LogIRQTestAREG();
#endif
#ifdef PIPE_FE_TESTING
	bool LogIAB();
#endif


/************************* May not use *************************/
bool LogSLKElem(DSPU32 p_u32SLKIdx);
bool LogALUACC();


#endif
