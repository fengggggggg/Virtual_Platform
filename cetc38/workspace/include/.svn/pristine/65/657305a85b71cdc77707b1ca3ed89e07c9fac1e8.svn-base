
#ifndef _FUNCS_H
#define _FUNCS_H


enum ABI_CHK_MASK
{
	CALLEE_SAVED_CHK = 0x1,			// callee save寄存器使用合法性检查
	CALL_STACK_CHK = 0x2,			// 函数调用栈访存合法性检查
	STACK_POINTER_CHK1 = 0x4,		// 栈指针(U8)调整合法性检查
	STACK_POINTER_CHK2 = 0x8		// 栈帧指针(U8, U9)数值合法性检查
};

/*------------------------------ typedef ------------------------------*/
typedef struct
{
	// the address of the instruction line
	DSPU32  u32PC;
	
	// instruction words
	DSPU32  u32InstrSlots[16];

} PIPELINE_REGS;

typedef struct
{
	// 当前指令是当前指令行中的第几条指令
	// 用于支持指令的条件执行
	DSPU32 u32InstrIdx;	// [0, 15]
	DSPU32 u32PC;
	DSPU32 u32CondDoN;// If xx do N
	bool bolIsMacroInstr; // 是否是宏内指令，用于支持两种类型条件执行指令的实现
					   // 只能写在第一个SLOT的指令必然不受条件控制，此数据项无意义
					   // 对于除情况1之外的其他指令
					   			// 1. 都接受If Um[Un]==C do 类条件控制
					   			// 2. 其中bolIsMacroInstr为true的指令还接受If {x,y,z,t}CPred[d]do类条件控制
	bool bolNotDoByUVW1;
	bool bolNotDoByUVW2;
	bool bolNotDoByCPred1[NUM_OF_UNITS];
	bool bolNotDoByCPred2[NUM_OF_UNITS];
	DSPU32 u32UnitMask; // this instruction belongs to which macro

	bool bolNotDo;

} COND_DO_INFO;

//------------------------------------------------------------------------
#define SetAddrMaskBit(p_u32AddrMask, p_u32UnitIdx, p_u32AddrIdx) \
	GSetBit((p_u32AddrMask), ((p_u32UnitIdx) * 2 + (p_u32AddrIdx)))

#define GSetBit(p_u32Value, p_u32BitIdx) \
	((p_u32Value) | (0x1U << (p_u32BitIdx)))

#define GClrBit(p_u32Value, p_u32BitIdx) \
	((p_u32Value) &  (~(0x1U << (p_u32BitIdx))))

#define GIsBitSet(p_u32Value, p_u32BitIdx) \
	( ((p_u32Value) & (0x1U << (p_u32BitIdx))) != 0 )

#define GSetBit64(p_u64Value, p_u32BitIdx) \
	(p_u64Value | (0x1ULL << (p_u32BitIdx)))

#define GClrBit64(p_u64Value, p_u32BitIdx) \
	((p_u64Value) &  (~(0x1ULL << (p_u32BitIdx))))

#define GIsBitSet64(p_u64Value, p_u32BitIdx) \
	( ((p_u64Value) & (0x1ULL << (p_u32BitIdx))) != 0 )

#define GIsSomeBitSet64(p_u64Value, p_u64BitMask) \
	( ((p_u64Value) & (p_u64BitMask)) != 0 )

// Note: BegIdx = [0, 31], EndIdx = [0, 31], BegIdx <= EndIdx
// 0b'0...01...10...0 | value
#define GSetBitsRange(p_u32Value, p_u32BegIdx, p_u32EndIdx) \
	((p_u32Value) | ((0x1ULL << (p_u32EndIdx + 1)) - (0x1ULL << (p_u32BegIdx))))

#define GClrBitsRange(p_u32Value, p_u32BegIdx, p_u32EndIdx) \
	((p_u32Value) & (~(((0x1ULL << (p_u32EndIdx + 1)) - (0x1ULL << (p_u32BegIdx))))))

//-------------------------------------------------------------------------------------------------------
#define IncSeqCounter(p_u32SeqCounter) \
	( ((DSPU32)(p_u32SeqCounter))%7U + 1U )

// Note: Caller assures that startbit is [0, 31], bitlen is [1, 32]
#define ExtractBinStr(p_u32BinStr, p_u32StartBit, p_u32BitLen) \
	( ((p_u32BinStr)>>(p_u32StartBit)) & ((0xffffffffU)>>(32-(p_u32BitLen))) )

#define IsExtFirstWord(p_u32IWord) \
	( (ExtractBinStr((p_u32IWord), 25U, 2U)) == 3U && (!GIsBitSet(p_u32IWord, 31)) )

#define IsExtSecondWord(p_u32IWord) \
	( (ExtractBinStr((p_u32IWord), 25U, 2U)) == 2U )

#define IsInstNoCalc(p_u32IWord) \
	( (ExtractBinStr((p_u32IWord), 26U, 5U)) == 0U )

#define IsCondDo_UVW(p_u32IWord) \
	( (GetOpcodeExt(p_u32IWord)==op_ext_cond_do_etc_c) && (ExtractBinStr(p_u32IWord, 18U, 3U) == 1U) )

#define IsCondDo_CPred(p_u32IWord) \
	( (GetOpcodeExt(p_u32IWord)==op_ext_cond_do_etc_c) && (ExtractBinStr(p_u32IWord, 18U, 3U) == 2U) )

#define IsCondDoInst(p_u32IWord) \
	(IsCondDo_UVW(p_u32IWord) || IsCondDo_CPred(p_u32IWord))

#define IsHwINTLvl(p_u32IntLvl) \
	( (p_u32IntLvl) < EXCP_INT_LVL )

#define IsExcpINTLvl(p_u32IntLvl) \
	( (p_u32IntLvl) == EXCP_INT_LVL )

#define IsMemExcp(p_u32ExcpMask) \
	( ((p_u32ExcpMask)&0x2U) != 0U )
//	( ((p_u32ExcpMask)&0x3E0U) != 0U )

#define IS_CHPG_INSN(I) ( GIsBitSet(I, 31) && GIsBitSet(I, 26) && GIsBitSet(I, 25) )

#define GetOpcodeExt(p_u32IWord) \
	(ExtractBinStr((p_u32IWord), 21U, 4U))

#define GetOpcodeNoCalc(p_u32IWord) \
	(ExtractBinStr((p_u32IWord), 18U, 5U))

#define GetOpcode(p_u32IWord) \
	(ExtractBinStr((p_u32IWord), 18U, 8U))

#define GenDSPU64(p_u32HighWord, p_u32LowWord) \
	( ((DSPU64)(p_u32HighWord)<<32U) | (p_u32LowWord) )

//#define GenILATMask()	0xA7FFF4FFFE33F28ULL //0x2A7FFF4FFFE33F28ULL
#define GenILATMask()	0x1fffffffffffffffULL //0x2A7FFF4FFFE33F28ULL

#define GenICTLRMask()	0x103C000000000000ULL
	
//-------------------------------------------------------------------------------------------------------------------------------
void ResetSignals();
void RstGenRegs();
void RstAddrRegs();
void RstALURegs();
void RstMULRegs();
void RstSHFRegs();
void RstSPURegs();
void ResetRegs();
void RstSeqCounter();
void ResetIABP0();
void ResetIABP1();
void RstModelPass();
void SetModelPass(DSPU32 p_u32Input, DSPU32 p_u32Output);
bool SetIVT(DSPU32 p_u32ISRAddr, DSPU32 p_u32INTLvl);

bool ClrINTReq(DSPU32 p_u32INTLvl);
bool ClrPMASKBit(DSPU32 p_u32INTLvl);
DSPU32 GetNestLvlAftIRET(DSPU64 p_u64PMASK, DSPU32 p_u32INTLvl);
bool TrigINT(DSPU32 p_u32INTLvl);
bool SetILAT(DSPU32 p_u32INTLvl);
void UseCustomINT();
void UseRealINT();

bool InitINTI();
void UseRTLINT();

void UpdateINTReg();
void UpdateILAT();
void UpdateBKFlags();
void UpdateECR(DSPU32 p_u32ExcpMaskLow, DSPU32 p_u32ExcpMaskHigh, DSPU32 p_u32ExcpPC);
bool CompStates(int p_intType);


bool FillCondDoInfo(DSPU32 *p_pSlots, DSPU32 *p_pSlotsRes, DSPU32 p_u32SlotNum, DSPU32 p_u32Phase);
void CondClrHzd_DC4_POST(DSPU32 p_u32SLKIdx, DSPU32 p_u32UnitIdx);


bool GetAddr12FromAddr32(DSPU32 p_addr32, DSPU32 *p_addr12, DSPU32 *p_units);
int GetMSB_64(DSPU64 p_u64Value);
int GetLSB_64(DSPU64 p_u64Value);
int GetLSB_32(DSPU32 p_u32Value);
int GetMSB_32(DSPU32 p_u32Value);

DSPU32 GetNestLvl(DSPU64 p_u64PMASK);
DSPU64 GetPMASK_R(DSPU64 p_u64PMASK);
DSPU32 GenModelPass(DSPU32 p_u32Input);
DSPU32 GAShift32(DSPU32 p_u32Value, int p_i32ShfCtrl);
DSPU32 GSignExtend(DSPU32 p_u32Src, int p_intSrcLen);

DSPU64 g_arrNewIRQs[2048];  // New INT signals
char g_arrIOPath[110];
char g_arrFileName[140];
char g_arrLisaMsg[100];

char g_arrABIPath[110];

DSPU32 g_arrRTLINTId[64];
DSPU32 g_arrRTLINTCnt[64];

void SetDefaultPath();
void PrintToCout(const char *p_pMsg);
void PrintToCerr(char *p_pMsg, ...);

bool ClrTestResult();
void SimService(DSPU32 p_u32TrapCode, DSPU32 p_u32R50, DSPU32 p_u32R51, DSPU32 p_u32R52);
/************************* SimService Log *************************/
bool InitNewIntSignals();
bool LogTraceCases();
bool LogTestResult(DSPU32 p_u32Addr, DSPU32 p_u32Num, DSPU32 p_u32Columns);
bool  LogDataMem();
bool  LogPIOMem();
bool  LogDulPIOMem();
bool  LogStateOnCall();
bool  LogStateOnRet();
bool  LogStateOnCall_ForLib();
bool  LogStateOnRet_ForLib();

bool  LogStateForISR(FILE *p_fp);
bool  LogStateForISR_Enter();
bool  ModelLogFrameInfo(char *p_pFrameInfo);
bool  LogStateForISR_Leave();
/************************* AC_POST_ACT *************************/
bool  LogOnStrap(DSPU32 p_u32StartAddr, DSPU32 p_u32WordsNum);


bool IsFlagReg(DSPU32 p_u32SpecRegIdx);
char GetMacroName(int macroIdx);
char GetUVWName(DSPU32 p_u32UVWIdx);

DSPU32 U4toU32Mask(DSPU32 u4Mask);

void ISSResStat();

/***************************** For LIB-TEST ************************************/
#ifdef LIBTEST
typedef struct{
	unsigned long StartAddr;
	unsigned long EndAddr;
}AreaAddr;
typedef struct{
	unsigned long PC;
	unsigned long AddrU8;
	unsigned long AddrU9;
	unsigned long WriteAddr;
}WrtStackError;
typedef struct{
	unsigned long PC;
	unsigned long Addr;
}RWAddrError;
typedef struct{
	//输入
	string Vendor;
	string module;
	string identify;
	int StackSize;  //栈大小
	int IntTime;    //中断屏蔽时间
	unsigned long MallocAddr;
	unsigned long INTLockAddr;
	unsigned long INTUnLockAddr;
	//list<AreaAddr> InStaticData;
	list<AreaAddr> InParaMemList;
	list<AreaAddr> DataPagList;
}TestCaseForLib;
typedef struct{
	unsigned long FunStartTime;
	unsigned long FunEndTime;
	unsigned long INTStartTime;
	unsigned long INTEndTime;
	unsigned long StackStartAddr;
	unsigned long StackEndAddr;
	unsigned long StackSize;
	int FuncUseTime;
	int IntTime;
	list<WrtStackError> ReadIllegalAddr;
	list<WrtStackError> WriteIllegalAddr;
	list<RWAddrError> WriteIllegalDataPagAddr;
	list<RWAddrError> ReadExtAddr;
	list<RWAddrError> WriteExtAddr;
	
	bool UseMalloc;  //true--Use
}TestStatusForLib;
bool m_bolTestForLib;  //用于算法性能测试 true表示正在测试，false表示测试结束
TestCaseForLib m_TestLibInput;
TestStatusForLib m_TestLibOutput;
bool GetFuncInfoFromFile();
void GetAccessStackStatus();
void PrintTestStatus();
#endif


/*********************************************************************/
//函数性能测试，提交给贾光帅使用
//使用宏定义 TEST_FUN_STATUS
typedef struct{
	unsigned long InstPC; //call 指令所对应的PC
	unsigned long JumpAddr; //跳转地址
	unsigned long RetAddr;  //Call指令返回地址
	unsigned long BeginCycle;
	unsigned long EndCycle;
	unsigned long Cycles;

}TestFunStatus;

TestFunStatus CurFunStatus;
stack<TestFunStatus> FunStatusBuf0;
stack<TestFunStatus> FunStatusBuf1;
void InitCurFunStatus();
void PrintFunStatus();

/*********************************************************************/

typedef struct
{
	DSPU32 GPRX[24];		// R40~R63
	DSPU32 GPRY[24];
	DSPU32 GPRZ[24];
	DSPU32 GPRT[24];
	DSPU32 AddrU[6];		// U10~U15
	DSPU32 AddrV[8];		// V8~V15
	DSPU32 AddrW[8];		// W8~W15
	DSPU32 LC2;
	DSPU32 LC3;
	DSPU32 ALUCR[NUM_OF_UNITS];
	DSPU32 MULCR[NUM_OF_UNITS];
	DSPU32 SHFCR[NUM_OF_UNITS];
	DSPU32 SPUCR[NUM_OF_UNITS];
	DSPU32 SHFCUTR[NUM_OF_UNITS];
	DSPU32 MULCUTR[NUM_OF_UNITS];
	DSPU32 IMACR;
} CalleeSavedRegs;

deque<CalleeSavedRegs> CalleeRegsBuf;
void SaveRegs();
bool CheckRegs();

void TrigEvent(DSPU32 u32EvtSrc, bool bolPosEdge);
void DetectTINT();
#if 0
bool IsHwINTLvl(DSPU32 p_u32IntLvl);
bool IsExcpINTLvl(DSPU32 p_u32IntLvl);
bool IsMemExcp(DSPU32  p_u32ExcpMask);
DSPU64 GenILATMask();
DSPU64 GenICTLRMask();

DSPU64 GenDSPU64(DSPU32 p_u32HighWord, DSPU32 p_u32LowWord);

bool IsCondDoInst(DSPU32 p_u32IWord);
bool IsCondDo_UVW(DSPU32 p_u32IWord);
bool IsCondDo_CPred(DSPU32 p_u32IWord);
DSPU32 ExtractBinStr(DSPU32 p_u32BinStr, DSPU32 p_u32StartBit, DSPU32 p_u32BitLen);
DSPU32 IncSeqCounter(DSPU32 p_u32SeqCounter);
DSPU32 BinStrToHex(DSPU32 p_u32BinStr);
DSPU32  RdDMRWCFR(DSPU32 p_u32BlkIdx, DSPU32 p_u32BankIdx, DSPU32 p_u32Type);
void WrSRP(DSPU32 p_u32Value, bool p_bolWrInOut);
void WrBAR(DSPU32 p_u32Value, bool p_bolWrInOut);
void SetRealINTFlag();
void WrICTLR(DSPU32 p_u32Value, bool p_bolWrInOut, bool p_LowHalf);

void DoTestDLL();
bool IsExcpDected();
DSPU32  ReadLogMode();
DSPU32 rd_u32r_ALUA_EX(DSPU32 p_u32UnitIdx, DSPU32 p_u32ALUIdx);
bool wr_u32r_ALUA_EX(DSPU32 p_u32UnitIdx, DSPU32 p_u32ALUIdx, DSPU32 p_u32Value);
DSPU32 rd_u32r_ALUB_EX(DSPU32 p_u32UnitIdx, DSPU32 p_u32ALUIdx);
bool wr_u32r_ALUB_EX(DSPU32 p_u32UnitIdx, DSPU32 p_u32ALUIdx, DSPU32 p_u32Value);
DSPU32 rd_u32r_ALUCR_EX(DSPU32 p_u32UnitIdx, DSPU32 p_u32ALUIdx);
bool wr_u32r_ALUCR_EX(DSPU32 p_u32UnitIdx, DSPU32 p_u32ALUIdx, DSPU32 p_u32Value);
void WrGCSR(DSPU32 p_u32Value, bool p_bolWrInOut);
DSPU32 ReadAppINT();
void SetLogOnStrap( bool p_bolLogOnStrap );
void SetLimitRtrap10( bool p_bolLimitRtrap10 );
void SetOnlyOutINT( bool p_bolOnlyOutINT );
void SetGateCycles( unsigned int p_u32GateCycles );
void SetRTrap4Invalid();
bool SimRTrap4();
DSPU32 RdINTReg0Low();
DSPU32 RdINTReg0High();
DSPU32 RdINTReg1Low();
DSPU32 RdINTReg1High();
void ReadExcpInfo(DSPU32 *p_pExcpCode, DSPU32 *p_pExcpPC);
void ResetIABP1In();

/*
DSPU32 SetAddrMaskBit(DSPU32 p_u32AddrMask, DSPU32 p_u32UnitIdx, DSPU32 p_u32AddrIdx);
DSPU32 GSetBit(DSPU32 p_u32Value, DSPU32 p_u32BitIdx);
DSPU32 GClrBit(DSPU32 p_u32Value, DSPU32 p_u32BitIdx);
bool GIsBitSet(DSPU32 p_u32Value, DSPU32 p_u32BitIdx);
DSPU64 GSetBit64(DSPU64 p_u64Value, DSPU32 p_u32BitIdx);
DSPU64 GClrBit64(DSPU64 p_u64Value, DSPU32 p_u32BitIdx);
bool GIsBitSet64(DSPU64 p_u64Value, DSPU32 p_u32BitIdx);
bool GIsSomeBitSet64(DSPU64 p_u64Value, DSPU64 p_u64BitMask);
*/

bool DoActually(bool p_bolNotDoByUVW, bool p_bolNotDoByCPred, DSPU32 p_u32InstrNumCondDo, DSPU32 p_u32CurrentInstrNum, bool p_bolIsMacroInstr);
DSPU32 GetValueOnMask(DSPU32 p_u32Value, DSPU32 p_u32Mask);
bool ConditionalDo(DSPU32 p_u32SLKIdx, DSPU32 p_Units, DSPU32 p_u32Phase, bool p_bolIsMacroInstr);
bool RdPipeNotDoByUVW(DSPU32 p_u32Phase);
DSPU32 RdPipeInstrNumCondDo(DSPU32 p_u32Phase);
void cond_do_uvw_dc2();
#endif


#endif


