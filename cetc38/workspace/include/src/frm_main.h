
#ifndef _FRM_MAIN_H
#define _FRM_MAIN_H

void EMIT_ACTION();
void UpdateIAB();
void GenIABHalt();
void DC2_ACTION();
void DC2_POST_ACT();
void ChkMemReqAddr_DC2_POST();

//void CondClrHzd_DC2_POST();
void SetRWMask_DC2_POST(DSPU32 p_u32AddrType, bool p_bolIsRead);

void DC3_POST_ACT();
void DC4_ACTION();
void PutCoreMemReq_DC4();
void DC4_POST_ACT();
void AC_ACTION();
// void CondClrHzd_AC();
void AC_POST_ACT();
void EX_ACTION();
// void GetRdCoreMemResult_EX();
// void GetRdResult_INSN(DSPU32 u32Phase);
// void GetRdResult_AC_POST();
// void GetRdResult_EX();
void GetRdResult_INSN(DSPU32 u32Phase);

void WB_ACTION();
void ManageDataHazard();

void ManageDataHzdBefDC4();

bool DetectCPredHzd_DC4();
bool DetectISRHzd_DC4();
bool DetectIRETHzd_DC4();

void FillHzdMask_AC();

bool DetectDataHzd_AC();
bool AccessSameBank(DSPU32 p_u32MemAddr0, DSPU32 p_u32MemAddr1);

bool DetectDataHzd_DC2();

void DetectINT();
void DetectFatalExcp();
void PutFlushInfoToCache();

void UpdateFPC();
DSPU32 GetIntLvlInServ(DSPU64 p_u64ILAT, DSPU64 p_u64PMASK);
void FlushOnCB_PEX();
void FlushOnCB_IAB();
void FlushOnINT_PEX();
void FlushOnINT_IAB();
void FlushOnExcp_PEX();
void FlushOnExExcp_IAB();
void FlushOnEXB_PEX();
void FlushOnEXB_IAB();

void GenPipeEXFlushBefDC4();
void GenPipeEXFlush();
void GenPipeEXStallBefDC4();
void GenPipeEXStall();
bool IsBInstInEX(DSPU32 p_u32InstrWord0, DSPU32 p_u32InstrWord1);
bool IsIRET(DSPU32 p_u32InstrWord);
void GenIABFlush();
void NotifyCacheUpdatefpc();
void UpdateEPC();
void DSP_Flush_IABP0();
void DSP_Flush_IABP1();
void DSP_Flush_EMIT_DC1();
void DSP_Flush_DC1_DC2();
void DSP_Flush_DC2_DC3();
void DSP_Flush_DC3_DC4();
void DSP_Flush_DC4_AC();
void DSP_Flush_AC_EX();
void Reset_PIPE_EX();
void DSP_Stall();
void DSP_Flush();
void DSP_PEX_POST_EXE_BEF_DC4();
void DSP_PEX_POST_EXE();
void DSP_PEX_EXE();
void FlushOnACB_PEX();
void FlushOnACB_IAB();
void FreeWBSLKRes();

void DetectGINTEnable_AC();
void INTRelated_AC_POST();
bool IsFlushed(DSPU32 p_u32Phase);
bool PermitRW_DC4();

void fill_wr_bus(WR_BUS_T *p_wrBus, DSPU32 p_u32Addr, DSPU32 p_u32Value, DSPU32 p_u32RegUnit, DSPU32 p_u32RegIdx);
void fill_rd_bus(RD_BUS_T *p_rdBus, DSPU32 p_u32Addr);
void SrvCoreMem_DC4();
void SrvRdBus_DC4(DSPU32 p_rdBusID);
void SrvWrBus_DC4(DSPU32 p_wrBusID, DSPU32 &p_u32MPSLKIdx);
void SrvDMAC_DC4();

void SetGenRegFwd(unsigned int *p_pSlots,unsigned int *p_pSlotsRes,DSPU32 p_u32SlotNum);

bool send_swi_req();

#if 0
void emit_when_iab0_empty();
void emit_when_iab0_not_empty();
DSPU32 getAtomAddrType(DSPU32 p_u32AtomAddr);

void FillPipePageIdxInfo();

void FindExeLineIn32Words(int p_intFirstPos, unsigned int *p_u32IAB);
void FindExeLineIn16Words(int p_intFirstPos, unsigned int *p_u32IAB);
#endif

#endif


