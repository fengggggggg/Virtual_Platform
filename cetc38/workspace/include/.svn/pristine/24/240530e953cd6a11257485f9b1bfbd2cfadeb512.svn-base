
#ifndef _ISS_DMAC_H
#define _ISS_DMAC_H

#define DMAC_WIDTH 8


//-------------------------------------------
// 通过DMAC方式访问本核存储器
typedef struct 
{
	bool bolInUse;				// 该结构体是否正在被使用(内容是否有效)
	bool bolInServe;			// 为true表示该消息已经被成功发送给目的核
	//bool arrDelayServed[2];		// 该结构体所包含的访问请求是否已经被服务
	bool bolri_Served;
	bool bolro_Served;
	DMAC_MEM dmac_mem;
	DSPU32 arrMacroIdx[24];
	DSPU32 arrRegIdx[24];
	DSPU32 arrPageIdx[24];
	DSPU32 u32SpecWrMask;
} DMAC_REQ_T;

//--------------------------------------------------------------

typedef struct
{
	bool		bolInUse;
	bool		bolServed;		// 该结构体所包含的访问请求是否已经被服务
	DSPU32	u32DelaySrv;	// 利用request_update()执行减1操作。
	DSPU32	u32DelayResp;
//	DSPU32	u32ChanIdx;		
	DSPU32	u32ElemNum;	// 当前还未被服务的请求数
	DMAC_MEM dmac_mem;
	DSPU32	u32Block;		// burst方式只能访问一个确定的block
	OUT_RESP_BANK arrBanks[BANK_NUM_PERBLK];	// 访存请求中的访存地址可能分布于确定block内的8个bank上
} DMAC_RESP_T;


DMAC_RESP_T m_dmac_resp[DMAC_MAX_CHANNELS];
DMAC_REQ_T m_dmac_req;


/************************************ Declaration ************************************************/
//tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_core::sc_time &delay);
//tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_core::sc_time &delay);
void reset_dmac_req();
void reset_dmac_resp();
bool reset_dmac();
bool send_resp_dmac(DMAC_MEM* p_dmac_mem);
bool send_req_dmac(DMAC_MEM* p_dmac_mem);
void dmac_resp_delay_countdown();
bool fill_dmac_rd_req(DSPU32 p_u32GAddr, DSPU32 p_u32RdBus, DSPU32 p_u32RdIdx);
bool fill_dmac_wr_req(DSPU32 p_u32GAddr, DSPU32 p_u32Value, DSPU32 p_u32PageIdx, DSPU32 p_u32MacroIdx, DSPU32 p_u32SrcRegIdx, DSPU32 p_u32WrBus, DSPU32 p_u32WrIdx, bool p_bolSpecWr);


void PutDMACReq_AC();
void SrvDMACReq_AC();

void GenDMACStall();
bool SrvDMACH_DC4(DMAC_RESP_T *p_dmac_resp);


bool rd_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 *p_pValue);
bool wr_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 p_pValue);

bool jtag_rd_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 *p_pValue);
bool jtag_wr_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 p_pValue);


#if 0
void DelElemIdx_DMAC(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 p_u32ElemIdx);
void SelMinAddr(DMAC_MEM *p_dmac_mem, DSPU32 &p_u32Addr, DSPU32 &p_u32ReqIdx);
bool SelChanIdx_DMAC(DSPU32 &p_u32ChanIdx, DSPU32 p_u32Block);
bool SelReqIdx_DMAC(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 &p_u32ReqIdx, DSPU32 &p_u32ElemIdx, DSPU32 p_u32ChanIdx);
/*------------------------------------------ typedef ------------------------------------------*/
// 本核以指令方式访问核外存储器

// 在保持与DMAC间通信接口(MSG_INSN_RW_MEM)不变的条件下，
// 为便于内核使用而对MSG_INSN_RW_MEM进行封装形成MSG_INSN_RW_MEM_ISS。

typedef struct
{
	// 一条访存指令的访存地址位于同一bank的同一深度(即地址相同)的最大数量为4
	DSPU32 arrAddr[4];   // 访存地址
	DSPU32 arrAddrIdx[4]; // 在一条指令的8个访存地址中的序号: 0 ~ 7
	DSPU32 u32ElemNum; // 访存请求个数

} INSN_RW_MEM_ELEM;

typedef struct
{
	// 一条访存指令的访存地址最多使bank的深度为4
	INSN_RW_MEM_ELEM arrDepth[4];
	DSPU32 u32BankDepth;   // bank深度信息，即当前bank上的bank冲突解决需要的cycle数 
	                      // 0 表示当前Bank中无元素

} INSN_RW_MEM_BANK;

typedef struct
{
	// 每个block含8个bank.
	INSN_RW_MEM_BANK arrBanks[8];

} INSN_RW_MEM_BLOCK;

typedef struct msg_insn_rw_mem_iss
{
	bool bolInUse;   // 该结构体是否正在被使用
	bool bolInServe; // 为true表示该消息已经被成功发送给DMAC
	bool bolServed;  // 该结构体所包含的访问请求是否已经被服务
	MSG_INSN_RW_MEM msg_insn_rw_mem;

	// 对于写操作，内核在恰当的时机根据下列信息
    // 读通用寄存器作为源操作数
	DSPU32 arrMacroIdx[24];
	DSPU32 arrRegIdx[24];

	// 四条访存总线的bank冲突信息
	// arrBusInfo[0]：read_bus_0
    // arrBusInfo[1]：read_bus_1
    // arrBusInfo[2]：write_bus_0
    // arrBusInfo[3]：write_bus_1
	INSN_RW_MEM_BLOCK arrBusBankConfInfo[4];

} MSG_INSN_RW_MEM_ISS;

//--------------------------------------------------
// 核外以指令方式访问本核存储器

// 在保持与DMAC间通信接口(MSG_INSN_RW_MEM)不变的条件下，
// 为便于内核使用而对MSG_INSN_RW_MEM进行封装形成MSG_INSN_RW_CORE_MEM_ISS。

typedef struct
{
	DSPU32 u32Index;             // 在MSG_INSN_RW_CORE_MEM_ISS.msg_insn_rw_mem.arrInsnsRWInfo[]中的索引号
	bool bolInUse;                 // Is there valid info in this structure?
	bool bolServed;               // 是否已被服务

} INSN_RW_CORE_MEM_ELEM;

typedef struct
{
	// the maximum number of request for each bank from on instr line is 24
	// the maximum number of RW instructions in one execution line is 3
	// 三条指令可能同时访问一个bank
	INSN_RW_CORE_MEM_ELEM arrElems[24];
	DSPU32 u32ElemNum;                // 当前bank还未被服务的请求数

} INSN_RW_CORE_MEM_BANK;

typedef struct
{
	// 每个block含8个bank.
	INSN_RW_CORE_MEM_BANK arrBanks[8];
	DSPU32 u32ElemNum;                // 当前block还未被服务的请求数

} INSN_RW_CORE_MEM_BLOCK;

typedef struct msg_insn_rw_core_mem_iss
{
	bool bolInUse;   // 该结构体是否正在被使用
	bool bolServed;  // 该结构体所包含的访问请求是否已经被服务
	DSPU32 u32CountDown;  // 利用request_update()执行减1操作。
	MSG_INSN_RW_MEM msg_insn_rw_mem;

	// 核内数据存储器包括6个block
	// 此数据结构用于提供对msg_insn_rw_mem.arrInsnsRWInfo[]的索引
	INSN_RW_CORE_MEM_BLOCK arrBlocks[6];
	DSPU32 u32ElemNum;  // 当前还未被服务的请求数

} MSG_INSN_RW_CORE_MEM_ISS;

//--------------------------------------------------
// 以burst方式访问本核存储器

// 在保持与DMAC间通信接口(MSG_RW_CORE_MEM)不变的条件下，
// 为便于内核使用而对MSG_RW_CORE_MEM进行封装形成MSG_BURST_RW_CORE_MEM_ISS。

typedef struct
{
	DSPU32 u32Index;             // 在MSG_BURST_RW_CORE_MEM_ISS.msg_rw_core_mem.arrRWElems[]中的索引号
	bool bolInUse;                 // Is there valid info in this structure?
	bool bolServed;               // 是否已被服务

} BURST_RW_CORE_MEM_ELEM;

typedef struct
{
	// burst方式访存请求中最多包含8个访存地址
	BURST_RW_CORE_MEM_ELEM arrElems[8];
	DSPU32 u32ElemNum;                // 当前bank还未被服务的请求数

} BURST_RW_CORE_MEM_BANK;

typedef struct msg_burst_rw_core_mem_iss
{
	bool bolInUse;   // 该结构体是否正在被使用
	bool bolServed;  // 该结构体所包含的访问请求是否已经被服务
	bool bolIsRead;  // 用于区分读操作还是写操作
	DSPU32 u32CountDown;  // 利用request_update()执行减1操作。
	MSG_RW_CORE_MEM msg_rw_core_mem;	

	DSPU32 u32BlockIdx;    // burst方式只能访问一个确定的block
	// 访存请求中的访存地址可能分布于确定block内的8个bank上
	BURST_RW_CORE_MEM_BANK arrBanks[8];
	DSPU32 u32ElemNum;   // 当前还未被服务的请求数

} MSG_BURST_RW_CORE_MEM_ISS;

//--------------------------------------------------
typedef struct
{
	// u32ElemMask: addr_f addr_e ...... addr_b addr_a(LSB)
	
	DSPU32 u32ElemMask0;  // 冲突解决的第1个周期服务请求的掩码
	DSPU32 u32ElemMask1;  // 冲突解决的第2个周期服务请求的掩码
	DSPU32 u32ElemMask2;  // 冲突解决的第3个周期服务请求的掩码
	DSPU32 u32ElemMask3;  // 冲突解决的第4个周期服务请求的掩码
	bool bolSingleWord;      // 是否是单字访存指令
	bool bolIsDM8;          // 是否是双模8指令
	
	DSPU32 u32ConfNum;    // 冲突解决周期数
	DSPU32 u32ConfState;   // 冲突状态码	

} BANK_CONFLICT_TBL_LINE;

/*----------------------------------- data declarations ----------------------------------*/
MSG_INSN_RW_MEM_ISS m_msg_insn_rw_mem_iss;  // 本核以指令方式访问核外存储器

MSG_INSN_RW_CORE_MEM_ISS m_msg_insn_rw_core_mem_iss;  // 核外以指令方式访问本核存储器
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_wr_ch00_iss;     // 256bit数据写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rd_ch00_iss;     // 256bit数据读
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch1_iss;     // 128bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch2_iss;     // 64bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch3_iss;     // 64bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch4_iss;     // 64bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch5_iss;     // 64bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch6_iss;     // 64bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch7_iss;     // 64bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch8_iss;     // 64bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch9_iss;     // 64bit数据读写
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_cha_iss;     // 32bit数据读写

// bank冲突信息表
BANK_CONFLICT_TBL_LINE m_bank_conflict_tbl[24];  // GRQ: 为什么有24项?

/*-------------------------------------- implimention -------------------------------------*/

void reset_mem_req_frm_out_core();
void memreq_frmout_countdown();
void reset_msg_insn_rw_mem_iss();
bool add_insn_rd_mem_elem(DSPU32 p_u32GAddr, DSPU32 p_u32Slot, MSG_INSN_RW_MEM_ISS &p_msg_insn_rw_mem_iss, bool p_bolAtom, bool p_bolSingleWord, bool p_bolIsDM8, DSPU32 p_u32AddrIdx);
bool add_insn_wr_mem_elem(DSPU32 p_u32GAddr, DSPU32 p_u32Value, DSPU32 p_u32MacroIdx, DSPU32 p_u32SrcRegIdx, DSPU32 p_u32Slot, MSG_INSN_RW_MEM_ISS &p_msg_insn_rw_mem_iss, bool p_bolAtom, bool p_bolSingleWord, bool p_bolIsDM8, DSPU32 p_u32AddrIdx, bool p_bolSpecWr);
DSPU32 get_insn_rd_mem_result(DSPU32 p_u32GAddr, MSG_INSN_RW_MEM_ISS &p_msg_insn_rw_mem_iss);
void init_bank_conflict_tbl();
bool lookup_bank_conflict_tbl(BANK_CONFLICT_TBL_LINE *p_pTableLine, DSPU32 *p_pMemAddr);
bool prepare_lookup_paras(DSPU32 p_u32Bus, MSG_INSN_RW_MEM_ISS *p_p_msg_insn_rw_mem_iss, BANK_CONFLICT_TBL_LINE *p_pTableLine, DSPU32 *p_pMemAddr);
tlm::tlm_sync_enum nb_transport_bw_dmac( tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay );
tlm::tlm_sync_enum nb_transport_fw_dmac( tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay );

// 从MSG_RW_CORE_MEM.arrRWElems[]结构中找出地址最小的单元
void GetMinAddr(MSG_RW_CORE_MEM *p_pMsgRWCoreMem, DSPU32 &p_u32Addr, DSPU32 &p_u32Index);

// 将MSG_INSN_RW_MEM.MSG_INSN_RW_MEM_ELEM.u32Bus由slot序号转变为bus序号
// 核外通信时该数据项被定义为bus序号
// 但是由于代码遗留问题，内核将该数据项理解为slot序号
void InBusToOutBus(MSG_INSN_RW_MEM *p_p_msg_insn_rw_mem);
// 将MSG_INSN_RW_MEM.MSG_INSN_RW_MEM_ELEM.u32Bus由bus序号转变为slot序号
void OutBusToInBus(MSG_INSN_RW_MEM *p_p_msg_insn_rw_mem);

//bool RdSharedMem(DSPU32 p_u32Addr, DSPU32 *p_pValue);
//bool WrSharedMem(DSPU32 p_u32Addr, DSPU32 p_u32Value);


// 当完成核外以burst方式访问核内存储器请求后
// 内核使用该接口通知DMAC
bool send_resp_brust_rw_core_mem(MSG_RW_CORE_MEM *p_p_msg_rw_core_mem, bool p_bolIsRead);
// 当完成核外以指令方式访问核内存储器请求后
// 内核使用该接口通知DMAC
bool send_resp_insn_rw_core_mem(MSG_INSN_RW_MEM *p_p_msg_insn_rw_mem);
// 当内核需要以指令方式访问核外存储器时
// 使用该接口通知DMAC
bool send_req_insn_rw_out_mem(MSG_INSN_RW_MEM_ISS *p_p_msg_insn_rw_mem_iss);
// 当内核需要读DMAC寄存器时
// 使用该接口通知DMAC
bool rd_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 *p_pValue);
// 当内核需要写DMAC寄存器时
// 使用该接口通知DMAC
bool wr_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 p_u32Value);
// 内核复位DMAC
bool reset_dmac();

bool SrvOutInsnReq_DC4(bool p_bolAtom);
bool GetOutInsnRWElemIdx(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 *p_pElemIdx, DSPU32 *p_pIdxOfIdx, DSPU32 p_u32CurrBus, MSG_INSN_RW_CORE_MEM_ISS &p_INST_RW_REQ);
bool GetOutInstrReqCurrBlock(DSPU32 *p_pBusNum, DSPU32 p_u32Block, MSG_INSN_RW_CORE_MEM_ISS &p_OUT_INST_RW_REQ);
void DelOutInsnRWReq(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 p_u32ElemIdx, MSG_INSN_RW_CORE_MEM_ISS &p_INST_RW_REQ);

bool SrvCHxxReq_DC4(DSPU32 p_u32CHIdx, DSPU32 p_u32Mode);
bool GetBurstElemOnBank(DSPU32 p_u32Bank, DSPU32 *p_pElemIdx, MSG_BURST_RW_CORE_MEM_ISS &p_Burst_RW_REQ);
void DelBurstRWReq(DSPU32 p_u32Bank, DSPU32 p_u32ElemIdx, MSG_BURST_RW_CORE_MEM_ISS &p_BURST_RW_REQ);

void PutOutCoreMemReq_AC();
void GetRdOutCoreResult_AC_POST();
void SrvOutMemReq_AC();
void GenOutCoreMemStall();

#endif

#endif


