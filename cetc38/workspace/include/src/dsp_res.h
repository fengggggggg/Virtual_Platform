
#ifndef _DSP_RES_H
#define _DSP_RES_H

//----------------------------------------------------------
typedef struct
{		
	DSPU32 mopcode;
	DSPU32 mopcodeH;
	DSPU32 slotnum;
	DSPU32 en;
	DSPU32 num;
	DSPU32 slotnum_debug;
} RES_DISTRIBUTE;

RES_DISTRIBUTE ResALU[NUM_OF_UNITS][ALU_NUM_OF_UNIT];
RES_DISTRIBUTE ResMUL[NUM_OF_UNITS][MUL_NUM_OF_UNIT];
RES_DISTRIBUTE ResSHF[NUM_OF_UNITS][SHF_NUM_OF_UNIT];
RES_DISTRIBUTE ResSPU[NUM_OF_UNITS][SPU_NUM_OF_UNIT];
int dis_line_num;


/*------------------------------------------ typedef ------------------------------------------*/
typedef struct
{
	// '1' means corresponding resource is in use

	//Resource: ALU (8 ALUs each unit)
	DSPU8 arrALU[NUM_OF_UNITS];
	
	//Resource: Multiplier (8 MULs each unit)
	DSPU8 arrMUL[NUM_OF_UNITS];
	
	//Resource: Shifter (4 SHFs each unit)
	DSPU8 arrSHF[NUM_OF_UNITS];
	
	//Resource: SPU (1 SPU each unit)
	DSPU8 arrSPU[NUM_OF_UNITS];

	//-----------译码器资源(通道)分配测试相关-----------

	// 数据读总线掩码
	DSPU32 u32InnerRdBusRes;  // u32InnerRdBusRes[0]: 数据读总线0
	                          // u32InnerRdBusRes[1]: 数据读总线1
	
	// 数据写总线掩码
	DSPU32 u32InnerWrBusRes;  // u32InnerWrBusRes[0]: 数据写总线0
                              // u32InnerWrBusRes[1]: 数据写总线1

	// 地址寄存器读通道掩码                    
	DSPU32 u32AddrRegRdBusRes;  // u32AddrRegRdBusRes[0]: X宏读通道0
								// u32AddrRegRdBusRes[1]: X宏读通道1
								// u32AddrRegRdBusRes[2]: Y宏读通道0
								// u32AddrRegRdBusRes[3]: Y宏读通道1
								// u32AddrRegRdBusRes[4]: Z宏读通道0
								// u32AddrRegRdBusRes[5]: Z宏读通道1
								// u32AddrRegRdBusRes[6]: T宏读通道0
								// u32AddrRegRdBusRes[7]: T宏读通道1
                              
	// 地址寄存器写通道掩码                             
	DSPU32 u32AddrRegWrBusRes;  // u32AddrRegWrBusRes[0]: X宏写通道0
								// u32AddrRegWrBusRes[1]: X宏写通道1
								// u32AddrRegWrBusRes[2]: Y宏写通道0
								// u32AddrRegWrBusRes[3]: Y宏写通道1
								// u32AddrRegWrBusRes[4]: Z宏写通道0
								// u32AddrRegWrBusRes[5]: Z宏写通道1
								// u32AddrRegWrBusRes[6]: T宏写通道0
								// u32AddrRegWrBusRes[7]: T宏写通道1

	// ABFPR读通道掩码
	DSPU32 u32ABFPRRdBusRes;   // u32ABFPRRdBusRes[0]: X宏ABFPR 读通道
								// u32ABFPRRdBusRes[1]: Y宏ABFPR 读通道
								// u32ABFPRRdBusRes[2]: Z宏ABFPR 读通道
								// u32ABFPRRdBusRes[3]: T宏ABFPR 读通道

	// ABFPR写通道掩码
	DSPU32 u32ABFPRWrBusRes;  // u32ABFPRWrBusRes[0]: X宏ABFPR 写通道
								// u32ABFPRWrBusRes[1]: Y宏ABFPR 写通道
								// u32ABFPRWrBusRes[2]: Z宏ABFPR 写通道
								// u32ABFPRWrBusRes[3]: T宏ABFPR 写通道

	// SBFPR读通道掩码
	DSPU32 u32SBFPRRdBusRes;    // bolSBFPRRdBusRes[0]: X宏SBFPR 读通道
								// bolSBFPRRdBusRes[1]: Y宏SBFPR 读通道
								// bolSBFPRRdBusRes[2]: Z宏SBFPR 读通道
								// bolSBFPRRdBusRes[3]: T宏SBFPR 读通道

	// SBFPR写通道掩码
	DSPU32 u32SBFPRWrBusRes;   // bolSBFPRWrBusRes[0]: X宏SBFPR 写通道
								// bolSBFPRWrBusRes[1]: Y宏SBFPR 写通道
								// bolSBFPRWrBusRes[2]: Z宏SBFPR 写通道
								// bolSBFPRWrBusRes[3]: T宏SBFPR 写通道
								
	//add by zx UVW立即数通道掩码
	DSPU32 u32UVWImm;       //[3:0]表示4个立即数通道3~0

	//add by zx UVW中加法器/移位器部件
	DSPU32 u32UVWADD;

} DSP_RES_TBL;
//--------------------------------------------------------------------
typedef struct
{
	bool bolInUse;     // if this element is in use
	// Which slot of instruction line before is in hazard
	DSPU8 u8Slot;    // 0 ~ 15

	// Info of current line
	DSPU8 u8Unit;        // 0 ~ 3  (X, Y, Z, T)
	DSPU8 u8RegIdx;    // 0 ~ 63

} GEN_REG_HAZD;

//--------------------------------------------------------------------
typedef struct
{
	bool bolInUse;
	DSPU8 u8Unit;   
	DSPU8 u8RegIdx;       	
	DSPU32 u32Value;

} REG_RESULT;
//--------------------------------------------------------------------
typedef struct
{		
	bool bolRead;
	DSPU32 u32AddrMask;
	DSPU32 arrAddrs[NUM_OF_UNITS][2];

} MEM_INSTR_DETAIL;
//--------------------------------------------------------------------
typedef struct
{
	DSPU8 u8UnitsUseCalc;
	DSPU8 u8ALUs[NUM_OF_UNITS];             // each bit indicate the index of ALUs
	DSPU8 u8MULs[NUM_OF_UNITS];            // each bit indicate the index of Muls
	DSPU8 u8SHFs[NUM_OF_UNITS];            // each bit indicate the index of Shifters
	DSPU8 u8SPUs[NUM_OF_UNITS];             // each bit indicate the index of SPU

	// data hazard detect
	//每个宏有64个寄存器，用64位掩码表示相关性。
	DSPU64 arrSrcGenRegs[NUM_OF_UNITS];
	DSPU64 arrDestGenRegs[NUM_OF_UNITS];
	
	DSPU32 u32FwdFlag;

	//----------------------------------------------------
	// below is for memory access instructions
	bool bolMemAcs;
	bool bolRead;
	DSPU32 u32AddrType;	// 该指令所形成访存地址的类型。	                   					    
						// bit0:		This addr belongs to Private space(use local addr)
						// bit1:		This addr belongs to Private space(use global addr)
						// bit2:		This addr belongs to ICMA space
						// bit3:		This addr belongs to DMA space
						// bit4~7:		RSV for addr attribute code
						//
						// bit8:		地址越界/跨界(越界是指访问保留空间，跨界是指单条访存指令的多个地址跨Block)
						// bit9:		地址冲突(单条写指令)
						// bit10: 		地址冲突(两条写指令)
						// bit11~15:	RSV for addr fault code
						//
						// bit16~18:	Block Index of this insn
						// bit19~31:	RSV
						//	                   
	// format of u32AddrMask: ......T1 T0 Z1 Z0 Y1 Y0 X1 X0(LSB)	
	DSPU32 u32AddrMask; // 当前指令访存地址序号掩码
	// format of u32BlkMask: ......BLK5 BLK4 BLK3 BLK2 BLK1 BLK0(LSB)					   
	// DSPU32 u32BlkMask;  // 当前指令访存block序号掩码
	
	DSPU32 arrAddrs[NUM_OF_UNITS][2];
	DSPU32 arrValues[NUM_OF_UNITS][2];  // for write memory (or for other use)

	DSPU32 arrMemDestReg[NUM_OF_UNITS];    // 访存目的寄存器索引(双字则取较低的寄存器序号)
	DSPU32 arrMemSrcReg[NUM_OF_UNITS];     // 访存源寄存器索引(双字则取较低的寄存器序号)
	bool bolSingleWord;         // 是否为单字访存指令
	bool bolIsDM8;             // 是否为双模8访存指令
	//----------------------------------------------------
	// for {x,y,z,t}swap(Rs,Rm,Un) use
	bool bolAtom;			// 是否为原字指令
	DSPU32 u32AtomAddr;
	DSPU32 u32AtomWrVal;
	DSPU32 u32AtomRdVal;
	DSPU32 u32AtomUnit;
	DSPU32 u32AtomSrcIdx;

	//----------------------------------------------------
	// for [Um+=C] = Un+1:n use
	bool bolSpecWr;
//	DSPU32 arrUVWAddrs[2];
//	DSPU32 arrUVWValues[2];
	//----------------------------------------------------
	bool bolDestHL;  // for data hazard when dest reg is HL
	bool bolareg_is_greg;  // for data hazard when areg_is_greg

	DSPU32 u32SrcCPred, u32DestCPred;

	// below is for AddrReg data hazard detect
	DSPU32 u32SrcU, u32SrcV, u32SrcW;
	DSPU32 u32DestU, u32DestV, u32DestW;

	// read addr_reg in the last cycle of DC2, these value will be used in AC
	DSPU32 u32AddrRegN, u32AddrRegM, u32AddrRegK;

	// 宏间传输指令会指定源/目的寄存器页面
	bool bolUseSpecificPage;
	DSPU32 u32SrcPageIdx, u32DestPageIdx;

	// SACC相关性检测
	bool bolRdSACC;  // 当前指令读SACC
	bool bolWrSACC;  // 当前指令写SACC

	// STAB相关性检测
	bool bolRdSTAB;  // 当前指令读STAB
	bool bolWrSTAB_AC;  // 当前指令写STAB
	bool bolWrSTAB_EX;
	DSPU32 u32STABMask;  // 每个移位器中的STAB表分为4块
	                     // 相关性检测是以块为单位进行的
	                     // [3..0]分别对应block3 ~ block0

	// SC相关性检测
	bool bolRdSC;  // 当前指令读SC寄存器
	bool bolWrSC;  // 当前指令写SC寄存器

	// AMACC相关性检测
	DSPU32 u32RdAMACCMask;
	DSPU32 u32WrAMACCMask;

	//-----------译码器资源(通道)分配测试相关-----------

	// 数据读总线掩码
	DSPU32 u32InnerRdBusMask;  // u32InnerRdBusMask[0]: 数据读总线0
	                          // u32InnerRdBusMask[1]: 数据读总线1
	
	// 数据写总线掩码
	DSPU32 u32InnerWrBusMask;  // u32InnerWrBusMask[0]: 数据写总线0
                              // u32InnerWrBusMask[1]: 数据写总线1

	// 地址寄存器读通道掩码                    
	DSPU32 u32AddrRegRdBusMask;  // u32AddrRegRdBusMask[0]: X宏读通道0
								// u32AddrRegRdBusMask[1]: X宏读通道1
								// u32AddrRegRdBusMask[2]: Y宏读通道0
								// u32AddrRegRdBusMask[3]: Y宏读通道1
								// u32AddrRegRdBusMask[4]: Z宏读通道0
								// u32AddrRegRdBusMask[5]: Z宏读通道1
								// u32AddrRegRdBusMask[6]: T宏读通道0
								// u32AddrRegRdBusMask[7]: T宏读通道1
                              
	// 地址寄存器写通道掩码                             
	DSPU32 u32AddrRegWrBusMask;  // u32AddrRegWrBusMask[0]: X宏写通道0
								// u32AddrRegWrBusMask[1]: X宏写通道1
								// u32AddrRegWrBusMask[2]: Y宏写通道0
								// u32AddrRegWrBusMask[3]: Y宏写通道1
								// u32AddrRegWrBusMask[4]: Z宏写通道0
								// u32AddrRegWrBusMask[5]: Z宏写通道1
								// u32AddrRegWrBusMask[6]: T宏写通道0
								// u32AddrRegWrBusMask[7]: T宏写通道1

	// ABFPR读通道掩码
	DSPU32 u32ABFPRRdBusMask;   // u32ABFPRRdBusMask[0]: X宏ABFPR 读通道
								// u32ABFPRRdBusMask[1]: Y宏ABFPR 读通道
								// u32ABFPRRdBusMask[2]: Z宏ABFPR 读通道
								// u32ABFPRRdBusMask[3]: T宏ABFPR 读通道

	// ABFPR写通道掩码
	DSPU32 u32ABFPRWrBusMask;  // u32ABFPRWrBusMask[0]: X宏ABFPR 写通道
								// u32ABFPRWrBusMask[1]: Y宏ABFPR 写通道
								// u32ABFPRWrBusMask[2]: Z宏ABFPR 写通道
								// u32ABFPRWrBusMask[3]: T宏ABFPR 写通道

	// SBFPR读通道掩码
	DSPU32 u32SBFPRRdBusMask;    // u32SBFPRRdBusMask[0]: X宏SBFPR 读通道
								// u32SBFPRRdBusMask[1]: Y宏SBFPR 读通道
								// u32SBFPRRdBusMask[2]: Z宏SBFPR 读通道
								// u32SBFPRRdBusMask[3]: T宏SBFPR 读通道

	// SBFPR写通道掩码
	DSPU32 u32SBFPRWrBusMask;   // u32SBFPRWrBusMask[0]: X宏SBFPR 写通道
								// u32SBFPRWrBusMask[1]: Y宏SBFPR 写通道
								// u32SBFPRWrBusMask[2]: Z宏SBFPR 写通道
								// u32SBFPRWrBusMask[3]: T宏SBFPR 写通道
								
	//add by zx UVW立即数通道掩码
	DSPU32 u32UVWImm;       //[3:0]表示4个立即数通道3~0

	//add by zx宏间传输通道共四个
	//BMRC--Between Macro Read Channel
	//这三个变量只用于配合硬件测试分配
	DSPU32 u32BMRCSrc;    //0:X宏,1:Y宏,2:Z宏,3:T宏
	DSPU32 u32BMRCDest;   //[3:0]从低到高每位分别表示xyzt宏
	DSP_BIT64 u64Reg;    //宏间传输通道64位

} SLOT_RES_USED;

//--------------------------------------------------------------------
typedef struct
{
	DSPU8 u8UnitsUseCalc;                // bit mask showing which units are involved

	bool bolUseSpecCalc;                   // 是否使用指定的计算部件资源

	// 当bolUseSpecCalc = true时，使用以下数据项以掩码方式说明使用到的资源
	DSPU8 u8ALUs;                            // each bit indicate the index of ALUs
	DSPU8 u8MULs;                           // each bit indicate the index of Muls
	DSPU8 u8SHFs;                           // each bit indicate the index of Shifters
	DSPU8 u8SPUs;                           // each bit indicate the index of SPUs

	// 当bolUseSpecCalc = false时，使用以下数据项说明使用到的资源
	// 当bolUseSpecCalc = true时，以下变量不需要设置。
	DSPI32 i32ALUNum;                      // Number of ALU to be used, not specified condition
	DSPI32 i32MULNum;                     // Number of Multiplier to be used, not specified condition
	DSPI32 i32SHFNum;                     // Number of Shifter to be used, not specified condition
	DSPI32 i32SPUNum;                     // Number of SPU to be used, not specified condition
	
	// below is for instruction "Rs = Rm * Rm + Rn * Rn"
	bool bolSpecOptional;
	DSPU8 u8MULsOptional;

	// one ALU or one SHF is needed, such as "Rs = Rm + Rn"
	// 使用一个ALU或SHF
	bool bolOneALUOrSHF;

	//使用一个ALU或SHF的指令是否已被分配 为1表示已分配
	DSPU8 IsAssigned;

	// a group of MUL is needed, 2 MULs in each group.
	// 使用配对的2个MUL
	bool bolGrp2MUL;

	// a group of MUL is needed, 4 MULs in each group.
	// 使用配对的4个MUL
	bool bolGrp4MUL;

	//-----------译码器资源(通道)分配测试相关-----------

	// need to read ABFPR
	// ABFPR读通道
	bool bolABFPRRdBus;

	// need to write ABFPR
	// ABFPR写通道
	bool bolABFPRWrBus;

	// need to read SHFBFPR
	// SHFBFPR读通道
	//bool bolSBFPRRdBus;

	// need to write SHFBFPR
	// SHFBFPR写通道
	//bool bolSBFPRWrBus;

	// memory access instruction
	bool bolInnerRdBus;  // 1条数据读总线
	bool bolInnerWrBus;  // 1条数据写总线

	// like "xRs = Un" or "Un = xRs"
	bool bolAddrRegRdBus;  // 1条地址寄存器读通道
	bool bolAddrRegWrBus;  // 1条地址寄存器写通道

	//从译码器到地址产生器共4个立即数通道
	//只用于Un=C Vn=C Wn=C指令
	bool bolUVWImmBus;

	//地址产生器的“加法/移位”部件
	//用于非运算类指令1~6
	bool bolUAdd;
	bool bolVAdd;
	bool bolWAdd;
} SLOT_RES_NEEDED;

//--------------------------------------------------------------------
typedef struct
{
	SLOT_RES_USED  slot_res_used;
	
	DSPU32 u32DecodeInfo[JIT_MAX_PARA_NUM];

	// 20120823 added
	// in one macro(unit), the maximum number of calc res needed by an instruction is 4
	// each calc res has two src input(SrcA and SrcB)
	DSPU32 arrSrcA[NUM_OF_UNITS][4];
	DSPU32 arrSrcB[NUM_OF_UNITS][4];
	DSPU32 arrCtrlWord[NUM_OF_UNITS][4];
	DSPU32 arrCtrlWord1[NUM_OF_UNITS][4]; // added by yzhu for MULCUTR
	DSPU32 arrDestL[NUM_OF_UNITS][4];
	DSPU32 arrDestH[NUM_OF_UNITS][4];
	DSPU32 arrFlag[NUM_OF_UNITS][4];
	
	// Added by liuyu
	//=================== Conditionla Do Related Info ====================
	COND_DO_INFO cond_do_info;
	DSPU32 u32InstrIdx;	// [0, 15]
	bool bolIsMacroInstr; // 是否是宏内指令，用于支持两种类型条件执行指令的实现
					   // 只能写在第一个SLOT的指令必然不受条件控制，此数据项无意义
					   // 对于除情况1之外的其他指令
					   			// 1. 都接受If Um[Un]==C do 类条件控制
					   			// 2. 其中bolIsMacroInstr为true的指令还接受If {x,y,z,t}CPred[d]do类条件控制
	
	//============================================================
	bool bolInUse;  // whether this elem is in use
	bool bolHoldInfo;  // whether this elem hold valid info  (2009-3-7)
	DSPU32 u32Next;       // point to next elem

} RES_SLK_ELEM;

/*----------------------------------- data declarations ----------------------------------*/

//resource table of dsp
DSP_RES_TBL m_dsp_res_tbl;

//resource static link list
RES_SLK_ELEM  m_arrResSLK[RES_SLK_SIZE];

SLOT_RES_NEEDED  m_arrDCResNeeded[MAX_INUM_LINE];

REG_RESULT m_arrWBGenRegInfo[MAX_INUM_LINE][HZD_GEN_BUFF_LEN];          // filled in WB
//REG_RESULT m_arrWBAddrRegInfo[16][HZD_ADDR_BUFF_LEN];       // filled in WB

DSPU32  m_arrLogResUse[NUM_OF_UNITS][MAX_INUM_LINE];

//---------------------------------------------------------------------------
void InitResSLK();
DSPU32 GetResSLKNumInUse();
DSPU32 MallocResSLK();
bool FreeResSLK(DSPU32 p_u32SLKIdx);
bool FreeSlotCalcRes(DSPU32 p_u32SLKIdx);
bool ClrSLKElem(DSPU32 p_u32SLKIdx);
bool SetGenRegIdx(DSPU32 p_u32RegIdx, DSPU64 &p_u64RegMask);
bool SetCalcResIdx(DSPU32 p_u32CalcResIdx, DSPU8 &p_u8CalcResMask);
bool IsCalcResIdxSet(DSPU32 p_u32CalcResIdx, DSPU8 p_u8CalcResMask);
bool malloc_alu_or_shf(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_abfpr_wr_bus(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_abfpr_rd_bus(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_areg_rd_bus(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_areg_wr_bus(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_inner_rd_bus(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_inner_wr_bus(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_calc_res(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_spec_calc_res(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);
bool malloc_calc_res_ALUSHF_SHF(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);

void RstDCResNeeded();
void RstResTbl();
void RstWBRegResult();
bool malloc_res_needed(DSPU32 p_u32SlotNum, unsigned int *p_pSLKIdxs);
DSPU32 GetALUIdx(char p_chrALUMask, int p_intTheNum);
int GetMULIdx(char p_chrMULMask, int p_intTheNum);
int GetSHFIdx(char p_chrSHFMask, int p_intTheNum);
DSPU32 SetALUCFlags(DSPU32 p_u32OrigStat, DSPU32 p_u32NewStat);
DSPU32 SetALUFlags(DSPU32 p_u32OrigStat, DSPU32 p_u32NewStat);
DSPU32 SetMULCFlags(DSPU32 p_u32OrigStat, DSPU32 p_u32NewStat);
DSPU32 SetMULFlags(DSPU32 p_u32OrigStat, DSPU32 p_u32NewStat);
DSPU32 SetSHFCFlags(DSPU32 p_u32OrigStat, DSPU32 p_u32NewStat);
DSPU32 SetSHFFlags(DSPU32 p_u32OrigStat, DSPU32 p_u32NewStat);
DSPU32 SetSPUFlags(DSPU32 p_u32OrigStat, DSPU32 p_u32NewStat);
void UpdateOAFlags();

bool DetectAddrRegHazard_DC2(DSPU32 p_u32SlotNum, DSPU32 *p_pSLKIdx, DSPU32 *p_pSrcRegs, DSPU32 *p_pDregsIDX, DSPU32 p_u32SrcLvl, DSPU32 p_u32Phase);
/*
bool IsSTABHazard(unsigned int *p_pSLKIdxCurr, DSPU32 p_u32SlotNumCurr, unsigned int *p_pSLKIdxBef, DSPU32 p_u32SlotNumBef, DSPU32 p_u32Phase);
bool IsSACCHazard(unsigned int *p_pSLKIdxCurr, DSPU32 p_u32SlotNumCurr, unsigned int *p_pSLKIdxBef, DSPU32 p_u32SlotNumBef, DSPU32 p_u32Phase);
*/
bool GetGenRegHazardMode1(
	unsigned int p_u32MPSLKIdx,
	unsigned int *p_pSlotBef, unsigned int *p_pSLKIdxBef, DSPU32 p_u32SlotNumBef, 
	DSPU32 *p_pSrcPageIdx, DSPU32 *p_pDestPageIdx, DSPU32 p_u32Phase);

bool GetGenRegHazardMode2(
	unsigned int *p_pSlotsCurr, unsigned int *p_pSLKIdxCurr, DSPU32 p_u32SlotNumCurr, 
	unsigned int *p_pSlotsBef, unsigned int *p_pSLKIdxBef, DSPU32 p_u32SlotNumBef,
	DSPU32 *p_pSrcPageIdx, DSPU32 *p_pDestPageIdx, DSPU32 p_u32Phase);

DSPU32 GetGPRHzdMode(DSPU32 *p_pSlotCurr, DSPU32 *p_pSLKIdxCurr, DSPU32 p_u32SlotNumCurr, 
	DSPU32 *p_pSlotBef, DSPU32 *p_pSLKIdxBef, DSPU32 p_u32SlotNumBef,
	DSPU32 *p_pSrcPageIdx, DSPU32 *p_pDestPageIdx);
	
bool GenRegForward(DSPU32 &p_u32Result, DSPU32 p_u32SLKIdx, DSPU32 p_u32Unit, DSPU32 p_u32RegIdx);
bool SetWBGenRegInfo(DSPU32 p_u32Slot, DSPU32 p_u32ElemIdx, DSPU8 p_u8Unit, DSPU8 p_u8RegIdx, DSPU32 p_u32Value);
DSPU32 GetAddrBlkMask(DSPU32 p_u32MemAddr);

//----------------------------------------------------------
bool malloc_UVW_Imm_bus(SLOT_RES_NEEDED &p_sResNeeded, DSPU32 p_u32SLKIdx);

bool DetectHzd_DC2(DSPU32 *p_pSLKIdx, DSPU32 p_u32SlotNum, DSPU32 *p_arrSrcRegs, DSPU32 p_u32Phase);

#if 0
DSPU32 IsSCHazard(unsigned int *p_pSLKIdxCurr, DSPU32 p_u32SlotNumCurr, unsigned int *p_pSLKIdxBef, DSPU32 p_u32SlotNumBef);
#endif

#endif


