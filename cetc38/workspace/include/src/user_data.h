
#ifndef _USER_DATA_H
#define _USER_DATA_H

//---------------------------------------------------------------------

DSPU32 u32_data_mem[BLK_NUM_PERCORE][INNER_DATA_BLK_SIZE];

//---------------------------------------------------------------------
	CPipeLineEX  PIPE_EX;
	//CPipeLineFE  PIPE_FE;
//-------------------------------- GPR -------------------------------
DSPU32 u32ri_R[GP_REG_NUM];
DSPU32 u32ro_R[GP_REG_NUM];
//---------------------------------- BPB ---------------------------------
DSPU32  u2ri_BPB[2048];
DSPU32  u2ro_BPB[2048];
//------------------------------ ALU Flag ---------------------------------
DSPU32 u32ri_ALUFR[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
DSPU32 u32ro_ALUFR[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
//---------------------------------------------------------------------

#ifdef PIPE_FE_TESTING
	DSPU32 m_arrEmittedLine[20];
#endif

//--------------------------------------------------------------------------------------------------
GREGISTER<DSPU64> u64r_INTReg0;
GREGISTER<DSPU64> u64r_INTReg1;
GREGISTER<DSPU64> u64r_PMASK;  // ������ʽ,��ʾ��Щ�ж��Ѿ�����Ӧ�����ڴ����С�

GREGISTER<DSPU64> u64r_SameINT;	// ͬ�����ȼ��жϽ�����ˮ��(ILAT=1, PMASK=1)

GREGISTER<bool> bolr_TestEnd;          // indicate to the end of a testbench (only for run testbench)
GREGISTER<bool> bolr_UseCustomINT;
GREGISTER<bool> bolr_UseRealINT;
GREGISTER<bool> bolr_UseRTLINT;
//---------------------------------------------------------------------
GREGISTER<DSPU32> u32r_CyclesL;	
GREGISTER<DSPU32> u32r_CyclesH;	
GREGISTER<DSPU32> u32r_FPC;
GREGISTER<DSPU32> u32r_EPC;
GREGISTER<DSPU32> u32r_EX_NPC;
GREGISTER<DSPU32> u32r_CoreID; // GRQ here
GREGISTER<DSPU32> u32r_SITR; // store strap code ����жϴ����Ĵ���  ��ַ0x1201114 12λ��ַ0x514
GREGISTER<DSPU32> u32r_IMACR;  //��䴫��ӷ������ƼĴ���
GREGISTER<DSPU32> u32r_IMAFR;  //��䴫��ӷ�����־�Ĵ���
GREGISTER<DSPU32> u32r_CINF;  //�ں���Ϣ�Ĵ���
GREGISTER<DSPU32> u32r_CIDR;  // Chip ID Register
GREGISTER<DSPU32> u32r_REGFS;
GREGISTER<DSPU32> u32r_NestLvlAftIRET_AC_EX; // ִ��iret�󣬷���Ŀ��ָ���Ӧ���ж�Ƕ�׼���
GREGISTER<DSPU32> u32r_SavedBranchPC;      // ����cache æ���Ĵ�ķ�֧��Ϣ
GREGISTER<DSPU32> u32r_SavedBranchINTLvl;   // ����cache æ���Ĵ�ķ�֧��Ϣ
GREGISTER<bool> bolr_SavedBranchValid;       // ����cache æ���Ĵ�ķ�֧��Ϣ

GREGISTER<bool> bolr_FpcUsedISRFlushed;
GREGISTER<bool> bolr_CacheBusyISRFlushed;
GREGISTER<DSPU32> u32r_CacheBusySavedPC;
GREGISTER<bool> bolr_ISRFlushedOnce;

GREGISTER<DSPU32> u32r_CBTgtAddr;			// Us = Um CB Un	
GREGISTER<bool> bolr_CBEn;


GREGISTER<DSPU32> u32r_CFGCE[5];
GREGISTER<DSPU32> u32r_DMRWCFR_ACEX[3][9];
GREGISTER<DSPU32> u32r_DMRWCFR_EXWB[3][9];

//----------------------------------------------------------------
	GREGISTER<DSPU32>  u32r_SeqCounter_EMIT;
	GREGISTER<DSPU32>  u32r_SeqCounter_DC1;
	GREGISTER<DSPU32>  u32r_SeqCounter_DC2;
	GREGISTER<DSPU32>  u32r_SeqCounter_DC3;
	GREGISTER<DSPU32>  u32r_SeqCounter_DC4;
	GREGISTER<DSPU32>  u32r_SeqCounter_AC;
	GREGISTER<DSPU32>  u32r_SeqCounter_EX;
	GREGISTER<DSPU32>  u32r_SeqCounter_WB;
//------------------ALU registers and signals------------------	
	//GREGISTER<DSPU32> u32r_ALUA_AC[NUM_OF_UNITS][ALU_NUM_OF_UNIT];    // ALU Input A in AC/EX
	//GREGISTER<DSPU32> u32r_ALUB_AC[NUM_OF_UNITS][ALU_NUM_OF_UNIT];     // ALU Input B in AC/EX
	//GREGISTER<DSPU32> u32r_ALUCR_AC[NUM_OF_UNITS][ALU_NUM_OF_UNIT];  // ALU Input CR in AC/EX
	GREGISTER<DSPU32> u32r_ALUCON_AC[NUM_OF_UNITS][ALU_NUM_OF_UNIT];  // ALU CON in AC/EX
	GREGISTER<DSPU32> u32r_ALUA_EX[NUM_OF_UNITS][ALU_NUM_OF_UNIT];    // ALU Input A in EX/WB
	GREGISTER<DSPU32> u32r_ALUB_EX[NUM_OF_UNITS][ALU_NUM_OF_UNIT];     // ALU Input B in EX/WB
	GREGISTER<DSPU32> u32r_ALUCR_EX[NUM_OF_UNITS][ALU_NUM_OF_UNIT];  // ALU Input CR in EX/WB
	GREGISTER<DSPU32> u32r_ALUFR_EX[NUM_OF_UNITS][ALU_NUM_OF_UNIT];  // ALU generated FR in EX/WB
	GREGISTER<DSPU32> u32r_ALU_ACF[NUM_OF_UNITS][ALU_NUM_OF_UNIT];     // ACF register of ALU in x,y,z,t units

	GREGISTER<DSPU32> u32r_ALU_BKFlag[NUM_OF_UNITS];
	GREGISTER<DSPU32> u32r_ALUFAR[NUM_OF_UNITS];
	GREGISTER<DSPU32> u32r_ALUFOR[NUM_OF_UNITS];
//------------------MUL registers------------------	
	//GREGISTER<DSPU32> u32r_MULA_AC[NUM_OF_UNITS][MUL_NUM_OF_UNIT];    // MUL Input A in AC/EX
	//GREGISTER<DSPU32> u32r_MULB_AC[NUM_OF_UNITS][MUL_NUM_OF_UNIT];		// MUL Input B in AC/EX
	//GREGISTER<DSPU32> u32r_MULCR_AC[NUM_OF_UNITS][MUL_NUM_OF_UNIT];  // MUL Input CR in AC/EX
	GREGISTER<DSPU32> u32r_MULA_EX[NUM_OF_UNITS][MUL_NUM_OF_UNIT];    // MUL Input A in EX/WB
	GREGISTER<DSPU32> u32r_MULB_EX[NUM_OF_UNITS][MUL_NUM_OF_UNIT];		// MUL Input B in EX/WB
	GREGISTER<DSPU32> u32r_MULCR_EX[NUM_OF_UNITS][MUL_NUM_OF_UNIT];  // MUL Input CR in EX/WB
	GREGISTER<DSPU32> u32r_MULFR_EX[NUM_OF_UNITS][MUL_NUM_OF_UNIT];  // MUL generated FR in EX/WB
	
	GREGISTER<DSPU32> u32r_MULFAR[NUM_OF_UNITS];
	GREGISTER<DSPU32> u32r_MULFOR[NUM_OF_UNITS];
	GREGISTER<DSPU32> u32r_MULCUTR[NUM_OF_UNITS];
//------------------SHF registers------------------	
	GREGISTER<DSPU32> u32r_SHFA_AC[NUM_OF_UNITS][SHF_NUM_OF_UNIT];    // SHF Input A in AC/EX
	GREGISTER<DSPU32> u32r_SHFB_AC[NUM_OF_UNITS][SHF_NUM_OF_UNIT];    // SHF Input B in AC/EX
	GREGISTER<DSPU32> u32r_SHFCR_AC[NUM_OF_UNITS][SHF_NUM_OF_UNIT];  // SHF Input CR in AC/EX
	GREGISTER<DSPU32> u32r_SHFA_EX[NUM_OF_UNITS][SHF_NUM_OF_UNIT];    // SHF Input A in EX/WB
	GREGISTER<DSPU32> u32r_SHFB_EX[NUM_OF_UNITS][SHF_NUM_OF_UNIT];		// SHF Input B in EX/WB
	GREGISTER<DSPU32> u32r_SHFCR_EX[NUM_OF_UNITS][SHF_NUM_OF_UNIT];  // SHF Input CR in EX/WB
	GREGISTER<DSPU32> u32_SHF_SCF[NUM_OF_UNITS][SHF_NUM_OF_UNIT]; 
	GREGISTER<DSPU32> u32r_SHF_SLTAR[NUM_OF_UNITS][SHF_NUM_OF_UNIT]; 
	GREGISTER<DSPU32> u32r_SHFER[NUM_OF_UNITS][SHF_NUM_OF_UNIT];
	
	GREGISTER<DSPU32> u32r_SHF_BKFlag[NUM_OF_UNITS];	
	GREGISTER<DSPU32> u32r_SHFFAR[NUM_OF_UNITS];
	GREGISTER<DSPU32> u32r_SHFFOR[NUM_OF_UNITS];
	GREGISTER<DSPU32> u32r_SHFCUTR[NUM_OF_UNITS];

	//------------------SPU registers------------------	
	GREGISTER<DSPU32> u32r_SPUA_AC[NUM_OF_UNITS];    // SPU Input A in AC/EX
	GREGISTER<DSPU32> u32r_SPUB_AC[NUM_OF_UNITS];		// SPU Input B in AC/EX
	GREGISTER<DSPU32> u32r_SPUCR_AC[NUM_OF_UNITS];  // SPU Input CR in AC/EX
	GREGISTER<DSPU32> u32r_SPUA_EX[NUM_OF_UNITS];    // SPU Input A in EX/WB
	GREGISTER<DSPU32> u32r_SPUB_EX[NUM_OF_UNITS];    // SPU Input B in EX/WB
	GREGISTER<DSPU32> u32r_SPUCR_EX[NUM_OF_UNITS];  // SPU Input CR in EX/WB		


	//------------------ALU registers and signals------------------	
	// ACC(48 bits) register of ALU in x,y,z,t units
	DSP_BIT40  u40ri_ALU_ACC[NUM_OF_UNITS][ALU_NUM_OF_UNIT];          // low 40 bits of ACC
	DSP_BIT40  u40ro_ALU_ACC[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
	DSPU8  u8ri_ALU_EXP[NUM_OF_UNITS][ALU_NUM_OF_UNIT];                       // high 8 bits of ACC
	DSPU8  u8ro_ALU_EXP[NUM_OF_UNITS][ALU_NUM_OF_UNIT];

	DSPU32 u32ri_ALU_CA[NUM_OF_UNITS][ALU_NUM_OF_UNIT];                //ALU CAFR
	DSPU32 u32ro_ALU_CA[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
	DSPU32 u32ri_ALU_DFER[NUM_OF_UNITS][ALU_NUM_OF_UNIT];           //ALUDFER 32ָ���Ĵ���
	DSPU32 u32ro_ALU_DFER[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
	DSP_BIT64 u64ri_ALU_DFMR[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
	DSP_BIT64 u64ro_ALU_DFMR[NUM_OF_UNITS][ALU_NUM_OF_UNIT];

	//------------------MUL registers------------------	
	DSPU32 u32ri_MULFR[NUM_OF_UNITS][MUL_NUM_OF_UNIT];			// MUL Flag Registers
	DSPU32 u32ro_MULFR[NUM_OF_UNITS][MUL_NUM_OF_UNIT];
	//------------------SHF registers------------------	
	DSPU32 u32ri_SHFFR[NUM_OF_UNITS][SHF_NUM_OF_UNIT];         // SHF Flag Registers
	DSPU32 u32ro_SHFFR[NUM_OF_UNITS][SHF_NUM_OF_UNIT];


	DSP_BIT64  u64ri_SHF_SACC[NUM_OF_UNITS][SHF_NUM_OF_UNIT];   //SHF SACC
	DSP_BIT64  u64ro_SHF_SACC[NUM_OF_UNITS][SHF_NUM_OF_UNIT];   //SHF SACC
	//DSPU32		u32_SHF_SCF[NUM_OF_UNITS][SHF_NUM_OF_UNIT]; 
	//DSPU32		u32_SHF_SC[NUM_OF_UNITS][SHF_NUM_OF_UNIT]; 
	SHF_RAM	u32_SHF_TAB[NUM_OF_UNITS][SHF_NUM_OF_UNIT];

	//------------------SPU registers------------------	
	DSPU32 u32ri_SPUFR[NUM_OF_UNITS];           // SPU Flag Registers
	DSPU32 u32ro_SPUFR[NUM_OF_UNITS];    

	DSPU32  u32ri_ExcpPC, u32ro_ExcpPC;        // �쳣PC
	DSPU32  u32ri_ExcpCode, u32ro_ExcpCode;    // �쳣��
	//----------------------------------------------------------------	
	NEW_DSP_BIT80  u80ri_MUL_MACC[NUM_OF_UNITS][MUL_NUM_OF_UNIT];      // MACC register of MUL in x,y,z,t units
	NEW_DSP_BIT80  u80ro_MUL_MACC[NUM_OF_UNITS][MUL_NUM_OF_UNIT];

	DSP_BIT128 u128ri_MUL_MACC[NUM_OF_UNITS][MUL_NUM_OF_UNIT];  
	DSP_BIT128 u128ro_MUL_MACC[NUM_OF_UNITS][MUL_NUM_OF_UNIT];

	DSPU32 EvtSrc2Int_Map[MAX_EVT_NUM];

	// attention for reseting time
	/*------------------------------------------ Signals -----------------------------------------*/	
	/*------------------------------------------ Group 1  ----------------------------------------*/	
#ifdef ECS_RES_STAT
	bool m_bolStatEn;			// ECS enable resource statistics
	DSPU32 m_u32BMCCnt;
	DSPU32 m_arrALUStat[NUM_OF_UNITS * ALU_NUM_OF_UNIT + 1];
	DSPU32 m_arrMULStat[NUM_OF_UNITS * MUL_NUM_OF_UNIT + 1];
	DSPU32 m_arrSHFStat[NUM_OF_UNITS * SHF_NUM_OF_UNIT + 1];
	DSPU32 m_arrSPUStat[NUM_OF_UNITS * SPU_NUM_OF_UNIT + 1];
	
	DSPU32 m_arrBMCStat[13];		// 0 ~12 channels
	DSPU32 m_arrRdStat[17];		// 0 ~ 16 words
	DSPU32 m_arrWrStat[17];
#endif
	DSPU32 m_u32BRCnt;
	DSPU32 m_u32MPCnt;
	DSPU32 m_u32RTLINTs;
	bool bolStartDump;
	bool bolDMemDumped;	

	bool bolFirstWB;
	bool bolFirstEX;
//	DSPU32 m_u32CBTgtAddr;			// Us = Um CB Un	
	DSPU32 m_u32BPMask;			// BreakPoints Mask
	DSPU32 m_u32WPMask;			// WatchPoints Mask

	DSPU64 m_u64WastedCycles;
	DSPU64 m_u64MemStallCycles;
	DSPU64 m_u64HzdStallCycles;
	DSPU64 m_u64InstNum_WB;
	
	bool m_bolLogRegsDetail;
	DSPU32  m_u32LogMode;
	DSPU32  m_u32TestMode;

	DSPU32 m_u32CyclesL, m_u32CyclesH;
	// attention: these registers are not pipeline registers.
	// the ninth registers are used to store PC and flag.
	DSPU32 m_arrJTAGPipePC[10];
	bool m_bolRTrap4Valid, m_bolShutINT;
	bool m_bolUseWrMemLog;
	bool m_bolUseCustomPath;
	DSPU32 m_arrSLKIdx_AC[16];
	bool g_bolDoShfReg;
	bool m_bolMemLogged;  // just for debug use

	DSPU32 m_u32AppINT, m_u32GateCycles;
	bool m_bolLogOnStrap, m_bolLimitRtrap10, m_bolOnlyOutINT;
	bool m_bolJTAGStopped;

	bool m_bolFileLoaded;

	// �������쳣��ָ���EX/WB�������ʱ,����쳣
	// ����⵽�쳣, ��stall EX/WB
	bool  m_bolFatalExcp;

	bool m_bolDmaRdWrConflict, m_bolDmaRdWrConflictSticky;
	
	// about phase done
	bool m_bolFE1Done;
	// [addr] array
	// �˽ṹ�Ƿ�������Ҫȡ���ڼĴ��������Ƿ��ܿء�
	// ��ˮ�߼Ĵ������ʺϲ��ô˽ṹ����Ϊ�����Ƿ����
	// ��ȡ���ڿ����ź�
	//DSPU32 m_arrSpecReg0_L[1024]; // eC104+�ں˿���/״̬�Ĵ���
	//DSPU32 m_arrSpecReg0_R[1024];
	
	DSPU32 m_u32NestLvl_FE1;
	bool    m_bolSimEnd;
	bool m_bolMemExcp_AC;
	bool m_bolUsingCache;  // cache related
	
	// IAB1 --> IAB0
	// IAB[0~15]: һ��ȡָ�е�16��ָ����
	// IAB[16]: u32_LinePC, ȡָ��PC
	// IAB[17]: 
	//		bit [0..7]: u32_NestLvl, 0 means normal app and 1 ~ 64 means interrupt. (�жϼ���)
	//		bit 8: bol_ISRFirstLn (first line of ISR)
	//
	// IAB[18]: u32_RetBPC, retָ����FE2���з�֧Ԥ���Ŀ���ַ (action info of slot0 in FE2)
	// IAB[19]:
	//      bit 0: bol_SlotDone, ��ǰslot��ָ����FE2�Ƿ񱻴����(action info of slot0 in FE2)
	//		bit 1: bol_BPT, Branch Perdict Taken flag ((action info of slot0 in FE2))

	// IAB[20]: u32_RetBPC, retָ����FE2���з�֧Ԥ���Ŀ���ַ (action info of slot4 in FE2)
	// IAB[21]:
	//      bit 0: bol_SlotDone, ��ǰslot��ָ����FE2�Ƿ񱻴����(action info of slot4 in FE2)
	//		bit 1: bol_BPT, Branch Perdict Taken flag ((action info of slot4 in FE2))

	// IAB[22]: u32_RetBPC, retָ����FE2���з�֧Ԥ���Ŀ���ַ (action info of slot8 in FE2)
	// IAB[23]:
	//      bit 0: bol_SlotDone, ��ǰslot��ָ����FE2�Ƿ񱻴����(action info of slot8 in FE2)
	//		bit 1: bol_BPT, Branch Perdict Taken flag ((action info of slot8 in FE2))

	// IAB[24]: u32_RetBPC, retָ����FE2���з�֧Ԥ���Ŀ���ַ (action info of slot12 in FE2)
	// IAB[25]:
	//      bit 0: bol_SlotDone, ��ǰslot��ָ����FE2�Ƿ񱻴����(action info of slot12 in FE2)
	//		bit 1: bol_BPT, Branch Perdict Taken flag ((action info of slot12 in FE2))
	DSPU32 m_arrIABP1In[IAB_WIDTH];
	DSPU32 m_arrIABP1Out[IAB_WIDTH];
	DSPU32 m_arrIABP0In[IAB_WIDTH];
	DSPU32 m_arrIABP0Out[IAB_WIDTH];
	

	bool m_bolStateDiffer; //�жϷ��غ����״̬��ͬ��true�����ڵ������鿴
	bool m_bolABIChkEn;
	bool m_bolABIChkFromECS;
	DSPU32 m_u32ABIMask;
	DSPU32 m_u32ABIBase;
	DSPU32 m_u32ABITop;
	DSPU32 m_u32MainAddr;

	DSPU32 m_u32IdleTick;
	DSPU32 m_u32CustomINTIdx;

	DSPU32 m_u32DumpCntDown;
	bool m_bolDMemDumped;
	bool m_bolStartDump;
	DSPU32 m_u32TraceState;
	DSPU32 m_u32TraceCase1;
	DSPU32 m_u32TraceCase3;
	DSPU32 m_u32TraceBasePC;
	DSPU32 m_u32TraceBaseTime;
	DSPU32 m_arrDeltaPC[4];
	DSPU32 m_arrDeltaTime[4];
	#ifdef LOG_PXP
	char log_pxp_msg[2048];
	#endif
	/*------------------------------------------ Group 2  -----------------------------------------*/	
	/**************************** Reset these signals at each cycle *******************************/
#ifdef ECS_RES_STAT
	DSPU32 m_u32RdMemCnt;
	DSPU32 m_u32WrMemCnt;
#endif
#ifdef LOG_PXP
	DSPU64 m_u64ARegWMask;
#endif
	bool m_arrFWDValid[NUM_OF_PAGES][NUM_OF_UNITS][REG_NUM_OF_UNIT];
	DSPU32 m_arrFWDValue[NUM_OF_PAGES][NUM_OF_UNITS][REG_NUM_OF_UNIT];

	bool m_bolWrEn;	// for PXP log
	bool m_bolStepInsn;
	
	bool m_bolAbandon_AC;
	
	bool m_bolLogBankConf;
	
	bool m_bolUpdateBPB;
	DSPU32 m_u32BPBIdx;
	DSPU32 m_u32BPTrigReg;
	DSPU32 m_u32WPTrigReg;
	
	DSPU32 m_u32MPReqIdx;  // for memory access in pipeline

	bool m_bolHit;
	bool m_bolWrSTDR;
	bool m_bolSetCGCRBit12;
	
	bool m_EX_bolMeetNest;  // ��EX�������flush���������ж�Ƕ��
	bool m_AC_bolMeetNest;  // ��AC�������flush���������ж�Ƕ��
	
	// IAB1 stall signals
	bool m_PEX_bolStallIABP1;    // idle or fatal excp or branch in PEX	
	// IAB0 stall signals	
	bool m_PEX_bolStallIABP0;    // idle or fatal excp or branch in PEX	
	
	DSPU32  m_u32ExcpMask_AC, m_u32ExcpMask_EX;
	
	// ��Ϊ�����ж϶����ɵ�flush�ź�
	bool m_INT_bolFlush_DC3DC4;  //��DC3_DC4�������
	bool m_INT_bolFlush_DC2DC3;  //��DC2_DC3�������
	bool m_INT_bolFlush_DC1DC2;  //��DC1_DC2�������
	bool m_INT_bolFlush_EMITDC1;  //��EMIT_DC1�������
	bool m_INT_bolFlushIABP0;      //��IAB0
	bool m_INT_bolFlushIABP1;      //��IAB1

	// AC�������ɵ�flush�ź�
	// ����ԭ��:�жϷ����һ��ָ���⵽��ȫ���ж�
	bool m_AC_bolFlush_ACEX;    //AC�����ɣ���AC_EX�������
	bool m_AC_bolFlush_DC4AC;   //AC�����ɣ���DC4_AC�������
	bool m_AC_bolFlush_DC3DC4;  //AC�����ɣ���DC3_DC4�������
	bool m_AC_bolFlush_DC2DC3;  //AC�����ɣ���DC2_DC3�������
	bool m_AC_bolFlush_DC1DC2;  //AC�����ɣ���DC1_DC2�������
	bool m_AC_bolFlush_EMITDC1;  //AC�����ɣ���EMIT_DC1�������
	bool m_AC_bolFlushIABP0;      //AC�����ɣ���IAB0
	bool m_AC_bolFlushIABP1;      //AC�����ɣ���IAB1

	// EX�������ɵ�flush�ź�
	// ����ԭ��:����쳣ָ��strap; ���ֳ���ת��ָ��
	bool m_EX_bolFlush_ACEX;    //EX�����ɣ���AC_EX�������
	bool m_EX_bolFlush_DC4AC;   //EX�����ɣ���DC4_AC�������
	bool m_EX_bolFlush_DC3DC4;  //EX�����ɣ���DC3_DC4�������
	bool m_EX_bolFlush_DC2DC3;  //EX�����ɣ���DC2_DC3�������
	bool m_EX_bolFlush_DC1DC2;  //EX�����ɣ���DC1_DC2�������
	bool m_EX_bolFlush_EMITDC1;  //EX�����ɣ���EMIT_DC1�������
	bool m_EX_bolFlushIABP0;      //EX�����ɣ���IAB0
	bool m_EX_bolFlushIABP1;      //EX�����ɣ���IAB1

	// ��Ϊ(Us=Um CB Un)ָ���������flush�ź�
	bool m_CB_bolFlush_DC2DC3;		// ��DC2_DC3�����
	bool m_CB_bolFlush_DC1DC2;		// ��DC1_DC2�����
	bool m_CB_bolFlush_EMITDC1;	// ��EMIT_DC1�����
	bool m_CB_bolFlushIABP0;		// ��IAB0
	bool m_CB_bolFlushIABP1;		// ��IAB1
	
	// ��ˮ�߸������յ�flush�ź�
	bool m_bolFlush_ACEX;    //��ʾAC_EX������౻flush
	bool m_bolFlush_DC4AC;   //��ʾDC4_AC������౻flush
	bool m_bolFlush_DC3DC4;  //��ʾDC3_DC4������౻flush
	bool m_bolFlush_DC2DC3;  //��ʾDC2_DC3������౻flush
	bool m_bolFlush_DC1DC2;  //��ʾDC1_DC2������౻flush
	bool m_bolFlush_EMITDC1; //��ʾEMIT_DC1������౻flush
	bool m_bolFlushIABP0;        // ��ʾIAB0������༰����౻����
	bool m_bolFlushIABP1;        // ��ʾIAB1������༰����౻����

	DSPU32 m_u32INTLvlToCache;  // ��m_bolFlushIABP1Ϊtrueʱ�����ݸ�cache ���жϼ�����Ϣ
	// PIPE_EX stall signals
	// ��DC2�γɵ�stall�ź�
	// ԭ��: ��ַ�Ĵ������
	bool m_DC2_bolStall_DC2DC3;

	// PIPE_EX stall signals
	// �ô�ָ����DC4�γɵ�stall�ź�
	// ԭ��: �ô��ͻ
	bool m_DC4_bolMemStall_DC4AC;

	// PIPE_EX stall signals
	// ��DC4�γɵ�stall�ź�
	// ԭ��: IRETָ��ǰ����һ����ָ֧��
	bool m_DC4_bolIRETStall_DC4AC;   

	// PIPE_EX stall signals
	// ��DC4�γɵ�stall�ź�
	// ԭ��: �жϷ�������һ��ָ��
	bool m_DC4_bolISRStall_DC4AC;    

	// PIPE_EX stall signals
	// ��DC4�γɵ�stall�ź�
	// ԭ��: CPred�Ĵ�������Գ�ͻ�γɵ�stall�ź�
	bool m_DC4_bolCPredStall_DC4AC;

	// PIPE_EX stall signals
	// ��AC�γɵ�stall�ź�
	bool m_AC_bolHazardStall_ACEX;   // AC����������������ɵ�PEX��stall�ź�
	bool m_AC_bolInsnOutMemStall_ACEX; // AC�����ڷ��ʺ���洢�����ɵ�PEX��stall�ź�

	// added by liuyu:
	// stall at ac stage for ICMA
	bool m_AC_bolICMAStall_ACEX;
	
	bool m_AC_bolDMACStall_ACEX;
	
	// ��ˮ�߸������յ�stall�ź�
	bool m_bolStall_EXWB;      //��ʾEX_WB����stall
	bool m_bolStall_ACEX;      //��ʾAC_EX����stall
	bool m_bolStall_DC4AC;     //��ʾDC4_AC����stall
	bool m_bolStall_DC3DC4;    //��ʾDC3_DC4����stall
	bool m_bolStall_DC2DC3;    //��ʾDC2_DC3����stall
	bool m_bolStall_DC1DC2;    //��ʾDC1_DC2����stall
	bool m_bolStall_EMITDC1;   //��ʾEMIT_DC1����stall
	bool m_bolStallIABP0;      // ��ʾIAB0����stall
	bool m_bolStallIABP1;      // ��ʾIAB1����stall

	bool m_WB_bolFreeWBInRes;

	bool m_bolFPCUsed; // cache�ڵ�FPC�Ĵ����Ƿ���Ա�����
	bool m_bolIABCanBeUpdate;  // IAB�������Ƿ���Ա�����

	// signals for branch
	bool m_bolFE2BraTaken;        // ��֧Ԥ����ɵĳ���ת��
	bool m_bolACBraTaken;         // first line of ISR in AC found global HW INT is disabled	
	bool m_bolEXBraTaken;

	bool m_bolCondBraTaken;		// Us = Um CB Un	
	
	DSPU32 m_u32FE2TgtAddr ;  	
	DSPU32 m_u32ACTgtAddr ;  	
  	DSPU32 m_u32EXTgtAddr ;
	DSPU32 m_u32FE2INTLvl;
	bool m_bolIsFE2FrmL2;
	bool m_bolEXIsIRET;
	bool m_bolEXIsExcp;

	//bool m_bolFE2Done;
	bool m_bolEMITDone;
	bool m_bolDC2Done;
	bool m_bolDC3Done;
	bool m_bolDC4Done;
	bool m_bolACDone;
	bool m_bolACPostDone;
	bool m_bolEXDone;
	bool m_bolWBDone;

#ifdef INTERRUPT_TESTING
	DSPU32 m_u32WBPC;         // ͨ��WB����ִ���е�PC
	DSPU32 m_u32WBNestLvl;		// ͨ��WB����ִ���е��жϼ���

	DSPU32 m_u32ACPostPC;         // ͨ��AC����ִ���е�PC
	DSPU32 m_u32ACPostNestLvl;		// ͨ��AC����ִ���е��жϼ���
#endif	

	// about interruption
	// bool m_bolINTOccur;
	// DSPU32 m_u32INTLvl;	// range of m_u32INTLvl: 0 ~ 63
	DSPU64 m_u64ILATSet, m_u64ILATClr;		// reset at UpdateILAT()
	DSPU64 m_u64PMASKSet, m_u64PMASKClr;	

	DSPU64 m_u64SameINTSet, m_u64SameINTClr;


	// for BCond in EX use
	bool m_bolEX_BCond;
	DSPU32 m_u32EX_BCondAddr;	

	// variable for PIPE_EX.EMIT use
	DSPU32  m_u32SlotNum_EMIT;
	DSPU32  m_u32slot_EMIT[16];

	DSPU32 m_arrALU_BKFlag[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
	bool m_arrChgBKF[NUM_OF_UNITS];

	DSPU32 m_arrSHF_BKFlag[NUM_OF_UNITS][SHF_NUM_OF_UNIT];
	bool m_arrChgBKF_SHF[NUM_OF_UNITS];

	/*------------------------------------------ AC_EX -----------------------------------------*/	
	/**************************** Update these variables at each cycle *******************************/
	// idle �Ĵ���λ��AC/EX, ��EX�����bolro_Idle, ��bolro_IdleΪtrue, ��stall EX/WB
	bool bolri_Idle;
	bool bolro_Idle;
	// ����ԭ�ӷô�
	bool bolri_AtomO;
	bool bolro_AtomO;

	DSPU32 u32ri_IVT[MAX_INT_LVL + 1];        // �ж������Ĵ���(ISR��ڵ�ַ)
	DSPU32 u32ro_IVT[MAX_INT_LVL + 1];
	DSPU32 u32ri_IRA[MAX_INT_LVL + 1];         // �жϷ��ص�ַ�Ĵ���
	DSPU32 u32ro_IRA[MAX_INT_LVL + 1];

	DSPU32 u32ri_ALUCR[NUM_OF_UNITS];                                    // ALU Control Registers
	DSPU32 u32ro_ALUCR[NUM_OF_UNITS];
	DSPU32 u32ri_MULCR[NUM_OF_UNITS];                                                     // MUL Control Registers
	DSPU32 u32ro_MULCR[NUM_OF_UNITS];
	DSPU32 u32ri_SHFCR[NUM_OF_UNITS];                                  // SHF Control Registers
	DSPU32 u32ro_SHFCR[NUM_OF_UNITS];
	DSPU32 u32ri_SPUCR[NUM_OF_UNITS];           // SPU Control Registers
	DSPU32 u32ro_SPUCR[NUM_OF_UNITS];
	// ��������ִ�У�ÿ����һ������AC��д��DC4/AC����
	DSPU32 u32ri_CPredReg[NUM_OF_UNITS];
	DSPU32 u32ro_CPredReg[NUM_OF_UNITS];
	DSPU32 u32ri_GPLYR[NUM_OF_UNITS];  //٤�޻�ϵ��
	DSPU32 u32ro_GPLYR[NUM_OF_UNITS];  
	//------------------------------------------------------
	DSPU32 u32ri_LC[4];     // zero-overhead loop counter register
	DSPU32 u32ro_LC[4];
	
	DSPU32 u32ri_ALU_CON[NUM_OF_UNITS][ALU_NUM_OF_UNIT];                       // CON register of ALU in x,y,z,t units
	DSPU32 u32ro_ALU_CON[NUM_OF_UNITS][ALU_NUM_OF_UNIT];

	//-------------------------------- UVW -------------------------------
	DSPU32 u32ri_U[REG_NUM_OF_ADDRUNIT];
	DSPU32 u32ro_U[REG_NUM_OF_ADDRUNIT];
	DSPU32 u32ri_V[REG_NUM_OF_ADDRUNIT];
	DSPU32 u32ro_V[REG_NUM_OF_ADDRUNIT];
	DSPU32 u32ri_W[REG_NUM_OF_ADDRUNIT];
	DSPU32 u32ro_W[REG_NUM_OF_ADDRUNIT];
	//------------------------ Global Control Status Register -----------------------
	DSPU32 u32ri_CGCR;
	DSPU32 u32ro_CGCR;
	DSPU32 u32ri_GCSR;
	DSPU32 u32ro_GCSR;
	//--------------------------------for interrupt----------------------------------
	DSPU64  u64ri_ILAT;          // ������ʽ,�ж�����Ĵ���
	DSPU64  u64ro_ILAT;
	DSPU64  u64ri_IMASK;        // ������ʽ,�ж����μĴ���
	DSPU64  u64ro_IMASK;
	DSPU64  u64ri_ICTLR;           // ������ʽ,�жϿ��ƼĴ���,��ʾ��ƽ�����������ش���
	DSPU64  u64ro_ICTLR;          // BWDSP100�в�δʹ��

	DSPU64 u32ri_ITMRl;
	DSPU64 u32ro_ITMRl;
	DSPU64 u32ri_ITMRh;
	DSPU64 u32ro_ITMRh;
	DSPU32 u32ri_INTSrc[31];
	DSPU32 u32ro_INTSrc[31];
	
	bool bolri_INTOccur;
	bool bolro_INTOccur;
	int i32ri_INTLvl;	// range of m_u32INTLvl: 0 ~ 63
	int i32ro_INTLvl;

	//------------------------------------------------------	
	DSPU32 u32ri_CJMP;            // contain return address of call
	DSPU32 u32ro_CJMP;
	DSPU32 u32ri_SRP;
	DSPU32 u32ro_SRP;
	DSPU32 u32ri_BAR;
	DSPU32 u32ro_BAR;	
	DSPU32 u32ri_IINT_TxEN;
	DSPU32 u32ro_IINT_TxEN;
	DSPU32 u32ri_IINTN_Tx;
	DSPU32 u32ro_IINTN_Tx;
	DSPU32 u32ri_IINTN_Rx[8];
	DSPU32 u32ro_IINTN_Rx[8];
	
	DSPU32 u32ri_IRET_ADDR_ACEX;       // ��AC����ȡ��Я����EX��ʹ�õ��жϷ��ص�ַ
	DSPU32 u32ro_IRET_ADDR_ACEX;

	DSP_BIT64 u64ri_ALU_DFIRR[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
	DSP_BIT64 u64ro_ALU_DFIRR[NUM_OF_UNITS][ALU_NUM_OF_UNIT];	

//---------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void ShiftGREGs();
int ShiftCustomRegs();
void ShiftIABP0();
void ShiftIABP1();
void ShiftFlags();
void ShiftRegs_ACEX();
void ShiftRegs_EXWB();
DSPU32 RdALUFAR(DSPU32 p_u32MacroIdx);
void WrALUFAR(DSPU32 p_u32MacroIdx, DSPU32 p_u32Value);
DSPU32 RdALUFOR(DSPU32 p_u32MacroIdx);
void WrALUFOR(DSPU32 p_u32MacroIdx, DSPU32 p_u32Value);
DSPU32 RdSHFFAR(DSPU32 p_u32MacroIdx);
void WrSHFFAR(DSPU32 p_u32MacroIdx, DSPU32 p_u32Value);
DSPU32 RdSHFFOR(DSPU32 p_u32MacroIdx);
void WrSHFFOR(DSPU32 p_u32MacroIdx, DSPU32 p_u32Value);
DSPU32 RdMULFAR(DSPU32 p_u32MacroIdx);
void WrMULFAR(DSPU32 p_u32MacroIdx, DSPU32 p_u32Value);
DSPU32 RdMULFOR(DSPU32 p_u32MacroIdx);
void WrMULFOR(DSPU32 p_u32MacroIdx, DSPU32 p_u32Value);
DSPU32 ReadALUCR(DSPU32  p_u32MacroIdx);
void WriteALUCR(DSPU32  p_u32MacroIdx, DSPU32 p_u32Value, bool p_bolIsInOut);
DSP_BIT128  ReadMACC(DSPU32  p_u32UnitIdx, DSPU32  p_u32MULIdx);
bool  WriteMACC(DSPU32  p_u32UnitIdx, DSPU32  p_u32MULIdx, DSP_BIT128  p_xu128Value);
void  ReadACC_48(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSP_BIT48 &p_ACCValue);
DSP_BIT40  ReadACC(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx);
bool  WriteACC_48(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, const DSP_BIT48  &p_b48ACC);
bool  WriteACC(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSP_BIT40  p_xu40Value);
DSPU8 ReadACCExp(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx);
bool WriteACCExp(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSPU8 p_u8Value);
DSPU32 ReadCON(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx);
bool WriteCON(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSPU32 p_u32Value);
DSPU32 ReadSPUCR(DSPU32  p_u32UnitIdx);
bool WriteSPUCR(DSPU32  p_u32UnitIdx, DSPU32 p_u32Value, bool p_bolIsInOut);
DSPU32 ReadSHFCR(DSPU32  p_u32UnitIdx);
bool WriteSHFCR(DSPU32  p_u32UnitIdx, DSPU32 p_u32Value, bool p_bolIsInOut);
DSPU32 ReadMULCR(DSPU32  p_u32UnitIdx);
bool WriteMULCR(DSPU32  p_u32UnitIdx, DSPU32 p_u32Value, bool p_bolIsInOut);
bool WriteALUBKFlag(DSPU32  p_u32UnitIdx, DSPU32 p_u32Value);
bool WriteSHFBKFlag(DSPU32  p_u32UnitIdx, DSPU32 p_u32Value);

DSPU32 ReadALUCA(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx);
bool WriteALUCA(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSPU32 p_u32Value);
DSPU32 ReadALUDFER(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx);
bool WriteALUDFER(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSPU32 p_u32Value);
DSP_BIT64 ReadALUDFIRR(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx);
bool WriteALUDFIRR(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSPU32 p_u32Value, bool IsHigh);
DSP_BIT64 ReadALUDFMR(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx);
bool WriteALUDFMR(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSPU32 p_u32Value, bool IsHigh);
void  ReadDFACC_80(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSP_BIT80 &p_FACCValue);
bool  WriteDFACC_80(DSPU32  p_u32UnitIdx, DSPU32  p_u32ALUIdx, DSP_BIT80  p_FACC);
DSPU32 ReadGPLYR(DSPU32  p_u32UnitIdx);
bool WriteGPLYR(DSPU32  p_u32UnitIdx, DSPU32 p_u32Value, bool p_bolIsInOut);

bool SetIRA(DSPU32 p_u32IntLvl, DSPU32 p_u32Addr);
DSPU32 ReadIRA(DSPU32 p_u32IntLvl);
DSPU32 rd_u32r_IVT(DSPU32  p_u32IVTIdx);
bool wr_u32r_IVT(DSPU32 p_u32IVTIdx, DSPU32 p_u32Value, bool p_bolIsInOut);
DSPU32 rd_u32r_IRA(DSPU32  p_u32IVTIdx);
bool wr_u32r_IRA(DSPU32 p_u32IVTIdx, DSPU32 p_u32Value, bool p_bolIsInOut);

#ifdef CHG_PAGE_IDX
DSPU32 ReadGPR_SLK(DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32SLKIdx);
bool WriteGPR_SLK(DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32Value, DSPU32 p_u32SLKIdx);
DSPU32 ReadGPR_Page(DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32PageIdx);
bool WriteGPR_Page(DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32Value, DSPU32 p_u32PageIdx);

#define rd_u32r_R_new(U, R, P) ReadGPR_SLK((U), (R), p_u32SLKIdx)
#define wr_u32r_R_new(U, R, V, P) WriteGPR_SLK((U), (R), (V), p_u32SLKIdx)
#else
DSPU32 rd_u32r_R_new(DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32PageIdx);
bool wr_u32r_R_new(DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32Value, DSPU32 p_u32PageIdx);
#endif

bool WriteGPR_JTAG(DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32Value, DSPU32 p_u32PageIdx);
DSPU32 ReadGPR_JTAG(DSPU32 p_u32UnitIdx, DSPU32 p_u32RegIdx, DSPU32 p_u32PageIdx);
DSPU32 rd_u32r_UVW_JTAG(DSPU32 p_u32UVWTp, DSPU32 p_u32RegIdx);
DSPU32  rd_u32r_UVW(DSPU32 p_u32UVWTp, DSPU32  p_u32RegIdx);
bool wr_u32r_UVW(DSPU32 p_u32UVWTp, DSPU32 p_u32RegIdx, DSPU32 p_u32Value);
bool wr_u32r_UVW_JTAG(DSPU32 p_u32UVWTp, DSPU32 p_u32RegIdx, DSPU32 p_u32Value);
DSPU32 rd_SHF_Tab(DSPU32 p_u32UnitIdx, DSPU32 p_u32SHFIdx, DSPU32 n, DSPU32 d);
bool wr_SHF_Tab(DSPU32 p_u32UnitIdx, DSPU32 p_u32SHFIdx, DSPU32 n, DSPU32 d, DSPU32 p_Mode, DSPU32 p_u32Value);

void WrCGCR(DSPU32 p_u32Value, bool p_bolWrInOut);
void SetChipID(DSPU32 p_u32ChipID);
void WrIMASK(DSPU32 p_u32Value, bool p_bolWrInOut, bool p_LowHalf);
void WrCJMP(DSPU32 p_u32Value, bool p_bolWrInOut);
void WrFPC(DSPU32 p_u32Value);

#endif


