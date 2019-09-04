
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
// �ô��ͻ��Ϊ���ࣺ
// 1. DC4����дָ��λ��ͬһָ�����ҷ���BLK��ͻ��������
DSPU32 m_u32WrBlockMask;
// 2. WB��д������DC4���Ϸ�����������BLK��ͻ��д����
DSPU32 m_u32RdBlockMask;
// 3. DC4����������֮����ٲã����ۺϷ����
DSPU32 m_u32VBlockMask;
// 4. DC4/AC/EX����д���������Ժ���ķô��������BLK��ͻ������д��������
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


