
#ifndef _MEM_ACS_REQ_H
#define _MEM_ACS_REQ_H

#define ICMA_RD_DONE() (m_icma_resp.icma_mem.icma_rbus[RD_BUS0].u32ElemNum == 0 && m_icma_resp.icma_mem.icma_rbus[RD_BUS1].u32ElemNum == 0)
#define ICMA_WR_DONE() (m_icma_resp.icma_mem.icma_wbus[WR_BUS0].u32ElemNum == 0 && m_icma_resp.icma_mem.icma_wbus[WR_BUS1].u32ElemNum == 0)
#define MEM_RD_DONE() ( m_RdBus[RD_BUS0].u32ElemNum == 0 && m_RdBus[RD_BUS1].u32ElemNum == 0 )
#define MEM_WR_DONE() ( m_WrBus[WR_BUS0].u32ElemNum == 0 && m_WrBus[WR_BUS1].u32ElemNum == 0 )

/*----------------------------------------------------------------------------------------*/
typedef struct
{
	DSPU32 u32MemAddr;     // dest address
	DSPU32 u32Value;           // value to write
	DSPU32 u32RegUnit;       // source reg belong to which macro?
	DSPU32 u32RegIdx;         // the index of source reg
	DSPU32 u32PageIdx;
	DSPU32 u32Slot;             // slot index of the instruction initiating memory access
	bool bolInUse;                 // Is there valid info in this structure?

	bool bolIllegal;                 // 该地址非法，不产生访存效果，
	                             // 但参与bank冲突解决(即影响访存时序)

} WR_REQ_ELEM;

typedef struct
{
	// the maximum number of request for each bank from on instr line is 16
	// the maximum number of write instructions in one execution line is 2
	// 两条指令可能同时访问一个bank
	WR_REQ_ELEM arrReqElem[16];
	DSPU32 u32ElemNum;                // the number of request for each bank.
	
	// added by liuyu: for [Um +=C] = Un use
	DSPU32 u32SpecWrMask;	// one instruction line has 2 write insns at most, which means 16(8+8) reqs is enough

} WR_REQ_BANK;

typedef struct
{
	// request for each bank (totally BANK_NUM_PERBLK banks each block)
	WR_REQ_BANK arrReqBank[BANK_NUM_PERBLK];
	bool bolInUse;                             // Is there valid info in this structure?

} WR_REQ_BLOCK;

typedef struct
{
	// request for each block (totally BLK_NUM_PERCORE blocks each core)
	// 20130813: 增加一个虚拟块(block 6)以支持RTL设计方案调整
	WR_REQ_BLOCK arrReqBlock[BLK_NUM_PERCORE + 1]; // 支持虚拟block
	bool bolInUse;                                // Is there valid info in this structure?

	// 在硬件设计中,若一个执行行中有一个原子访存操作,
	// 则该执行行中的所有访存操作都被认为是原子的。(不区分读写)
	bool bolAtom;               // 本执行行是否含原子访存操作

	DSPU32 u32BlksInUseOrig;  // 掩码，表示初始WR_REQ_DSP需访问的block
	                       // 该数据项不随访存的进行而改变
	DSPU32 u32BlkMask;
} WR_REQ_DSP;

//-------------------------------------------------
typedef struct
{
	DSPU32 u32MemAddr;  // source address
	DSPU32 u32Slot;           // slot index of the instruction initiating memory access
	bool bolInUse;               // Is there valid info in this structure?

	bool bolIllegal;                 // 该地址非法，不产生访存效果，
	                             // 但参与bank冲突解决(即影响访存时序)
/*
	DSPU32 u32Value;        // value read
	DSPU32 u32RegUnit;    // dest reg belong to which macro?
	DSPU32 u32RegIdx;      // the index of dest reg
	bool bolValueFilled;       // Is the read operation completed?	
*/

} RD_REQ_ELEM;

typedef struct
{
	// the maximum number of request for each bank from on instr line is 16
	// the maximum number of read instructions in one execution line is 2
	// 两条指令可能同时访问一个bank
	RD_REQ_ELEM arrReqElem[16];
	DSPU32 u32ElemNum;  // the number of request for each bank.

} RD_REQ_BANK;

typedef struct
{
	// request for each bank (totally BANK_NUM_PERBLK banks each block)
	RD_REQ_BANK arrReqBank[BANK_NUM_PERBLK];
	bool bolInUse;

} RD_REQ_BLOCK;

typedef struct
{
	// request for each block (totally BLK_NUM_PERCORE blocks each core)
	// 20130813: 增加一个虚拟块(block 6)以支持RTL设计方案调整
	RD_REQ_BLOCK arrReqBlock[BLK_NUM_PERCORE + 1]; // 支持虚拟block
	bool bolInUse;

	// 在硬件设计中,若一个执行行中有一个原子访存操作,
	// 则该执行行中的所有访存操作都被认为是原子的。(不区分读写)
	bool bolAtom;               // 本执行行是否含原子访存操作
	DSPU32 u32BlksInUseOrig;    // 掩码，表示初始WR_REQ_DSP需访问的block
	                         // 该数据项不随访存的进行而改变
	
	DSPU32 u32BlkMask;
} RD_REQ_DSP;

/*----------------------------------- data declarations ----------------------------------*/
WR_REQ_DSP m_WrReq_DC4;          // filled and used in DC4
RD_REQ_DSP m_RdReq_DC4;          // filled and used in DC4

//------------------------------------------------------------------------------

enum WR_BUS_ID
{
	WR_BUS0,
	WR_BUS1,
	WR_BUS_MAX
};
enum RD_BUS_ID
{
	RD_BUS0,
	RD_BUS1,
	RD_BUS_MAX	
};

typedef struct
{
	DSPU32 u32MemAddr;
	DSPU32 u32Value;
	DSPU32 u32RegUnit;
	DSPU32 u32RegIdx;
	bool bolInUse;
} WR_BUS_ELEM;

typedef struct
{
	WR_BUS_ELEM arrElems[8];
	DSPU32 u32ElemNum;
} WR_BUS_BANK;

typedef struct
{
	WR_BUS_BANK arrBanks[BANK_NUM_PERBLK];
	DSPU32 u32ElemNum;
	DSPU32 u32Block;
	DSPU32 u32PageIdx;
	bool bolAtom;
	bool bolIllegal;
	bool bolInUse;
	// added by liuyu: for [Um +=C] = Un use
	bool bolIsSpecWr;
} WR_BUS_T;

typedef struct
{
	DSPU32 u32MemAddr;
	DSPU32 u32Value;
	bool bolInUse;
} RD_BUS_ELEM;

typedef struct
{
	RD_BUS_ELEM arrElems[8];
	DSPU32 u32ElemNum;
} RD_BUS_BANK;

typedef struct
{
	RD_BUS_BANK arrBanks[BANK_NUM_PERBLK];
	DSPU32 u32ElemNum;
	DSPU32 u32Block;
	bool bolInUse;
	bool bolIllegal;
	bool bolAtom;
} RD_BUS_T;

WR_BUS_T m_WrBus[WR_BUS_MAX];
RD_BUS_T m_RdBus[RD_BUS_MAX];

//--------------------------------------------------
// 核外以指令方式访问本核存储器，本核的响应结构
// 以block和bank方式组织
typedef struct
{
	DSPU32 u32ReqIdx;			// 在ICMA_REQ.ICMA_MEM.arrInsnsRWInfo[]中的索引号
	bool bolInUse;				// Is there valid info in this structure?
	bool bolServed;				// 是否已被服务
} OUT_RESP_ELEM;

typedef struct
{
	OUT_RESP_ELEM arrElems[24];
	DSPU32 u32ElemNum;			// 当前bank还未被服务的请求数
} OUT_RESP_BANK;

typedef struct
{
	OUT_RESP_BANK arrBanks[BANK_NUM_PERBLK];
	DSPU32 u32ElemNum;			// 当前block还未被服务的请求数
} OUT_RESP_BLOCK;


//-----------------------------------------------------------------------------------------
bool GetBlockIdx(DSPU32 p_u32PAddr, DSPU32 *p_pu32Block);
bool GetBankIdx(DSPU32 p_u32PAddr, DSPU32 *p_pu32Bank);
void RstMemReqs_DC4();
void SrvMemReq_AC_POST();


bool get_core_rd_result(DSPU32 p_u32MemAddr, DSPU32 &p_u32Value);
bool get_icma_rd_result(DSPU32 p_u32GAddr, DSPU32 &p_u32Value);
bool get_dmac_rd_result(DSPU32 p_u32GAddr, DSPU32 &p_u32Value);

bool PutReqResult(DSPU32 p_u32MemAddr, DSPU32 p_u32Value, PIPE_RD_RESULT &p_INST_LINE_RD_RESULT);
bool RdDataFrmPipe(DSPU32 p_u32MemAddr, DSPU32 *p_pValue, DSPU32 p_u32MPSLKIdx);

bool ReadCoreDataMem(DSPU32 p_u32MemAddr, DSPU32 *p_pValue);
bool WriteCoreDataMem(DSPU32 p_u32MemAddr, DSPU32 p_u32Value);
bool CheckAddrValid_DC4(DSPU32 p_u32MemAddr, bool p_bolIsRead);

#if 0
bool GetWrReqElemIdx(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 *p_pu32ElemIdx, DSPU32 p_u32CurrSlot);
bool GetRdReqElemIdx(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 *p_pu32ElemIdx, DSPU32 p_u32CurrSlot);
bool GetRdReqCurrSlot(DSPU32 *p_pSlotNum, DSPU32 p_u32Block);
bool GetWrReqCurrSlot(DSPU32 *p_pSlotNum, DSPU32 p_u32Block);
bool DelWrReq(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 p_u32ElemIdx);
bool PutWrReq(DSPU32 p_u32MemAddr, DSPU32 p_u32Value, DSPU32 p_u32RegUnit, DSPU32 p_u32RegIdx, DSPU32 p_u32Slot, bool p_bolAtom, bool p_bolAddrIllegal, DSPU32 p_u32BlkIdx, bool p_bolSpecWr, DSPU32 p_u32PageIdx);
bool DelRdReq(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 p_u32ElemIdx);
bool PutRdReq(DSPU32 p_u32MemAddr, DSPU32 p_u32Slot, bool p_bolAtom, bool p_bolAddrIllegal, DSPU32 p_u32BlkIdx);
bool IsOutMemAddr(DSPU32 p_u32MemAddr);
int GetSlotAddrUnit(DSPU32 p_u32SlotIdx);
#endif

#endif


