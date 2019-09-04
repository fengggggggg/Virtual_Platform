
#ifndef _BUS_ARBITR_H
#define _BUS_ARBITR_H

typedef struct
{
	DSPU32 u32Data;
	DSPU32 u32Addr;
	bool bolNotCE;
	bool bolEN;	
} MEM_CE_INFO;

MEM_CE_INFO g_arrMemCE[BLK_NUM_PERCORE][BANK_NUM_PERBLK];

//===========================================================
// 访存冲突分为三类：
// 1. DC4级读写指令位于同一指令行且发生BLK冲突：读优先
DSPU32 m_u32WrBlockMask;
// 2. WB级写操作与DC4级合法读操作发生BLK冲突：写优先
DSPU32 m_u32RdBlockMask;
// 3. DC4两个读操作之间的仲裁，无论合法与否
DSPU32 m_u32VBlockMask;
// 4. DC4/AC/EX三级写操作与来自核外的访存操作发生BLK冲突：核内写操作优先
DSPU32 m_u32OutReqBlockMask;

#define CloseVPort(B) 		( m_u32VBlockMask = GSetBit(m_u32VBlockMask, (B)) )
#define CloseRdPort(B)		( m_u32RdBlockMask = GSetBit(m_u32RdBlockMask, (B)) )
#define CloseWrPort(B)	( m_u32WrBlockMask = GSetBit(m_u32WrBlockMask, (B)) )
#define CloseOutPort(B)	( m_u32OutReqBlockMask = GSetBit(m_u32OutReqBlockMask, (B)) )

#define IsVPortValid(B)	( !GIsBitSet(m_u32VBlockMask, (B)) )
#define IsRdPortValid(B)	( !GIsBitSet(m_u32RdBlockMask, (B)) )
#define IsWrPortValid(B)	( !GIsBitSet(m_u32WrBlockMask, (B)) )
#define IsOutPortValid(B)	( !GIsBitSet(m_u32OutReqBlockMask, (B)) )

void RstBlkPortMask();

#endif


