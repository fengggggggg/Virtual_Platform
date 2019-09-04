
#ifndef _MULTI_CORE_H
#define _MULTI_CORE_H

#define PADDR_START			0x200000U
#define PADDR_END			0x1200000U

#define JTAG_ADDR_START		0xE01800U
#define JTAG_ADDR_END		0xE01C00U
#define INSN_ADDR_START		0xE20000U
#define INSN_ADDR_END		0xE30000U

#define DATA_BLK_SIZE			0x200000U		// 2M words
#define BLK_SIZE_PER_CORE		0x1000000U		// 16M words

#define GADDR_START			0x1200000U
#define GADDR_END				0x3200000U

/*
#define TYPE_BLK_MASK 			0x70000U
#define TYPE_FAULT_MASK		0x700U
#define TYPE_ATTR_MASK			0xFU
*/

#define TYPE_FAULT_CODE(T)		( ( (T) >> 8U ) & 0x7U )
#define TYPE_ATTR_CODE(T)		( (T) & 0xFU )
#define TYPE_BLK_IDX(T)			( ( (T) >> 16U ) & 0x7U )
#define ADDR_BLK_IDX(A)			( ( (A) >> 21U ) - 1U )

#define IS_LOCAL_REQ(T)		( GIsBitSet(T, 0) || GIsBitSet(T, 1) )
#define IS_ICMA_REQ(T)		GIsBitSet(T, 2)
#define IS_DMAC_REQ(T)		GIsBitSet(T, 3)

// ---------------------------------------------------
// PIPE_EX.DC2_DC3.m_left.u32RWMask:
// RD(0~15): 0(LOCAL), 1(ICMA), 2(DMAC)
// WR(16~31): 16(LOACL), 17(ICMA), 18(DMAC)
//
#define HAS_LOCAL_REQ(M)	( GIsBitSet(M, 0) || GIsBitSet(M, 16) )
#define HAS_ICMA_REQ(M)	( GIsBitSet(M, 1) || GIsBitSet(M, 17) )
#define HAS_DMAC_REQ(M)	( GIsBitSet(M, 2) || GIsBitSet(M, 18) )

#define HAS_LOCAL_RD_REQ(M)	GIsBitSet(M, 0)
#define HAS_ICMA_RD_REQ(M)		GIsBitSet(M, 1)
#define HAS_DMAC_RD_REQ(M)	GIsBitSet(M, 2)

#define HAS_LOCAL_WR_REQ(M)	GIsBitSet(M, 16)
#define HAS_ICMA_WR_REQ(M)	GIsBitSet(M, 17)
#define HAS_DMAC_WR_REQ(M)	GIsBitSet(M, 18)

bool IsPAddr(DSPU32 p_u32Addr);
bool IsGAddr(DSPU32 p_u32Addr);


bool IsValidPAddr(DSPU32 p_u32MemAddr);
bool PAddrToGAddr(DSPU32 p_u32PAddr, DSPU32 p_u32CoreID, DSPU32 &p_u32GAddr);
bool GAddrToPAddr(DSPU32 p_u32GAddr, DSPU32 &p_u32CoreID, DSPU32 &p_u32PAddr);
bool ToCurrentCorePAddr(DSPU32 p_u32MemAddr, DSPU32 &p_u32PAddr);
void SrvMemReq_DC4();
void SrvMemReq_WB();
//bool GetAtomIMask();


DSPU32 GetReqType(DSPU32 &p_u32MemAddr);
DSPU32 GetAddrType(DSPU32 p_u32SLKIdx);
bool IsSameAddrType(DSPU32 p_u32Type1, DSPU32 p_u32Type2);
bool IsSameAddr_Insn(DSPU32 *p_pAddrs, DSPU32 p_u32AddrMask);
bool IsSameAddr_Line(DSPU32 *p_pAddrs1, DSPU32 p_u32AddrMask1, DSPU32 *p_pAddrs2, DSPU32 p_u32AddrMask2);

#if 0
typedef struct {
	DSPU32 u32CurrentCoreBlkNum;		// 用于掩码计数
	DSPU32 u32OtherCoreMaskNum;		// 用于掩码计数
	DSPU32 u32OutCoreDevNum;			// 用于掩码计数
	
	DSPU32 u32CurrentCoreBlks;			// 低6位是代表当前核内不同block的掩码
	DSPU32 u32OtherCoreBlks;			// 高16位是代表芯片内不同core的掩码
										// 低6位是代表当前核内不同block的掩码			
	DSPU32 u32OutCoreDevs;			// 掩码，每一位代表核外一个连续的地址范围
	DSPU32 u32AddrType;
	DSPU32 u32Result;
} BLK_INFO;

bool SrvWrReq_DC4();
bool PermitWr_DC4();
bool PermitRd_DC4();
bool SrvRdReq_DC4(bool p_bolAtom);

DSPU32 GetAddrType(DSPU32 p_u32SLKIdx);
void getType(DSPU32 p_u32AddrNum, DSPU32 p_u32Addr, BLK_INFO &p_blkinfo);
bool IsSameAddrFound(DSPU32 *p_pAddrs, DSPU32 p_u32AddrMask);
bool IsCurrentCoreAddr(DSPU32 p_u32Addr);
bool IsPAddr(DSPU32 p_u32Addr);
bool IsSpecificCoreDAddr(DSPU32 p_u32MemAddr, DSPU32 p_u32CoreID, DSPU32 &p_u32PAddr);
bool IsOutCoreDAddr(DSPU32 p_u32MemAddr, DSPU32 *p_pMask);
bool IsCurrentCoreValidDAddr(DSPU32 p_u32MemAddr, DSPU32 *p_pBlkMask);
bool IsOtherCoreValidDAddr(DSPU32 p_u32MemAddr, DSPU32 *p_pMask);
#endif


#endif


