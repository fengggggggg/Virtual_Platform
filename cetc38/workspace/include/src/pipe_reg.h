
#ifndef _PIPE_REG_H
#define _PIPE_REG_H

#include <string.h>
#include "defines.h"
#include "../pipe_fe_reg.h"

enum FWD_FLAG
{
	NO_FWD = 0,
	SHF_FWD = 0x1,
	ALU_FWD = 0x2,
	MUL_FWD = 0x4
};

//--------------------------------------------------------------------------
typedef struct
{
	DSPU32 u32MemAddr;  // source address
	DSPU32 u32Value;        // value read

} PIPE_RD_RESULT_ELEM;

typedef struct
{
	// one instruction line can access (BANK_NUM_PERBLK * 2) words at most
	PIPE_RD_RESULT_ELEM  arrRdResultElems[BANK_NUM_PERBLK * 2];
	DSPU32 u32ResultNum;               // the number of result

} PIPE_RD_RESULT;

typedef struct
{
	// 0--1--2--3--4--5--6--7
	// xA-yA-zA-tA-xB-yB-zB-tB
	DSPU64 arrSrcRegMask[NUM_OF_UNITS * 2];
	DSPU64 arrDestRegMask[NUM_OF_UNITS * 2];

	DSPU64 arrSrcRegMask_SHF[NUM_OF_UNITS * 2];
	DSPU64 arrSrcRegMask_ALU[NUM_OF_UNITS * 2];
	DSPU64 arrSrcRegMask_MUL[NUM_OF_UNITS * 2];
	DSPU64 arrSrcRegMask_NUL[NUM_OF_UNITS * 2];
	DSPU64 arrDestRegMask_SHF[NUM_OF_UNITS * 2];
	DSPU64 arrDestRegMask_ALU[NUM_OF_UNITS * 2];
	DSPU64 arrDestRegMask_MUL[NUM_OF_UNITS * 2];
	DSPU64 arrDestRegMask_NUL[NUM_OF_UNITS * 2];
	// SACC��SHFIFT(8SHF x 4UNITS)Ϊ��λ�����
	// tSHF7~tSHF0--zSHF7~zSHF0--ySHF7~ySHF0--xSHF7~xSHF0
	DSPU32 u32RdSACC;
	DSPU32 u32WrSACC;

	// STAB�Կ�(8 SHF x 4 BLK x 4 UNITS)Ϊ��λ�����
	// (x, shf, blk)
	// (7,3,3)~(7,3,0)--(7,2,3)~(7,2,0)--...
	DSPU32 u32RdSTAB[NUM_OF_UNITS];
	DSPU32 u32WrSTAB[NUM_OF_UNITS];

	// EX��д��AC��д��SHFΪ��λ�ж�
	DSPU32 u32WrSTAB_AC[NUM_OF_UNITS];
	DSPU32 u32WrSTAB_EX[NUM_OF_UNITS];

	DSPU32 u32RdAMACCMask;
	DSPU32 u32WrAMACCMask;
	
	bool bolFilled;
} HZD_MASK_T;

/*
* write at AC stage, read at EX stage: 
* BA/LC/SER/SRP
*/	
enum ENUM_BREGS
{
	BREG_BEGIN = 0,
	BREG_BA,
	BREG_LC0,
	BREG_LC1,
	BREG_LC2,
	BREG_LC3,
	BREG_SER,
	BREG_SRP,
	BREG_NUM
};

//--------------------------------------------------------------------------
typedef struct PIPE_EX_REG_CONTENT
{
	// the address of the instruction
	unsigned int  uint32r_pc;
	//  nest level
	//	range of current nest level
	//�ж�Ƕ�׼���
	unsigned int  u32_NestLvl;
	// retָ����FE2���з�֧Ԥ���Ŀ���ַ
	unsigned int  u32r_RetBPC;
	// slot number of current instruction line
	//ִ�����а�������32λ��
	unsigned int  u32r_SlotNum;    // 1 ~ 16  (attention)
	// instruction words
	//���ִ���е�32λ��
	unsigned int  uint32r_slot[MAX_INUM_LINE];
	// malloced space to hold resource info
	//��ž�̬�����������
	unsigned int  u32r_slot_res[MAX_INUM_LINE];
	// branch predicted taken
	//Ԥ���Ƿ�����֧ 1Ϊ������֧��0Ϊ������
	bool bolr_BPT;
	// if hazard with instruction before
	//��ʾ�Ƿ���ǰ���ָ������������ ��
	bool bolr_DataHazard;
	// about exception
	//��64λ����ʾ�쳣
	//��ʾ�����쳣���ͣ���ô��ַԽ��
	unsigned int  u32_ExcpMask;
	unsigned int  u32_ExcpMaskHigh;
	// first instruction line of ISR
	//��ʾ��ִ�����Ƿ����жϷ������ĵ�һ��ִ����
	bool bol_ISRFirstLn;
	// whether this is a valid execute line
	bool bol_InstValid;
	// SLK index for memory access in pipeline
	//����д�ô�ָ�Я��д�ô���Ϣ��WBִ��д
	//��ž�̬�����������
	unsigned int u32_MPSLKIdx;
	// active signal
	//ѭ������������������ǰ������ָ����ʽ��ͬ��ָ��
	unsigned int  u32_SeqCounter;
	// whether this execution line was processed in FE2
	//��ʾ��ִ�����Ƿ���FE2���Ƿ񱻴����
	bool bol_Processed;

	//����Я�����ô�Ľ����WB��д��ͨ�üĴ���
	PIPE_RD_RESULT  INST_LINE_RD_RESULT;          // for memory access instruction

	// 0 --> x
	// 1 --> y
	// 2 --> z
	// 3 --> t
	unsigned int arrSrcPageIdx[NUM_OF_UNITS];
	unsigned int arrDestPageIdx[NUM_OF_UNITS];

	// ��Ӳ�������,��һ��ִ��������һ��ԭ�ӷô����,
	// ���ִ�����е����зô����������Ϊ��ԭ�ӵġ�(�����ֶ�д)
	bool bolAtom;                // ��ִ�����Ƿ�ԭ�ӷô����
	DSPU32 u32BlksInUseOrig;      // ���룬��ʾ��ִ���зô�ָ������ʵ�block
                         		// ���������ô�Ľ��ж��ı�

	DSPU32 arrBPValue[NUM_OF_ADDR_UNITS][REG_NUM_OF_ADDRUNIT];
	bool arrBPValid[NUM_OF_ADDR_UNITS][REG_NUM_OF_ADDRUNIT];

	DSPU32 arrCondRegsValue[BREG_NUM];
	bool arrCondRegsValid[BREG_NUM];

	// Us = Um CB Un
	DSPU32 u32CB_NPC;
	// ---------------------------------------------------
	// PIPE_EX.DC2_DC3.m_left.u32RWMask:
	// RD(0~15): 0(LOCAL), 1(ICMA), 2(DMAC)
	// WR(16~31): 16(LOCAL), 17(ICMA), 18(DMAC)
	//	
	DSPU32 u32RWMask;	

	HZD_MASK_T hzd_mask;
	
	DSPU32 u32InstrNum;

} PIPE_EX_REG_CONTENT;

//--------------------------------------------------------------------------
template <class T> class CPipeLineReg
{
	public:
		T m_left, m_right;
		bool m_bolStalled;

		CPipeLineReg (void)
		{
			memset(&m_left, 0, sizeof(m_left));
			memset(&m_right, 0, sizeof(m_right));
			m_bolStalled = false;
		}

		void shift()
		{
			if ( !m_bolStalled )
			{
				memcpy(&m_right, &m_left, sizeof(m_right));
				memset(&m_left, 0, sizeof(m_left));
			}
		}

		void flush_left()
		{
			memset(&m_left, 0, sizeof(T));
		}

		void flush_right()
		{
			memset(&m_right, 0, sizeof(T));
		}

		void stall()
		{
			m_bolStalled = true;
		}

		void clr_stall()
		{
			m_bolStalled = false;
		}

};

//--------------------------------------------------------------------------
class CPipeLineFE
{
	public:
		CPipeLineReg<PIPE_FE_REG_CONTENT> FE1_FE2;

		CPipeLineFE (void)
		{

		}			

		void shift()
		{		
			if ( !FE1_FE2.m_bolStalled )
			{
				FE1_FE2.shift();
			}

			FE1_FE2.clr_stall();
		}

		void flush()
		{
			FE1_FE2.flush_left();
			FE1_FE2.flush_right();
		}

		void stall()
		{
			FE1_FE2.stall();
		}

};

//--------------------------------------------------------------------------
class CPipeLineEX
{
	public:
		CPipeLineReg<PIPE_EX_REG_CONTENT> EMIT_DC1, DC1_DC2, DC2_DC3, DC3_DC4, DC4_AC, AC_EX, EX_WB;

		CPipeLineEX (void)
		{

		}

		void shift()
		{
			memset(&EX_WB.m_right, 0, sizeof(PIPE_EX_REG_CONTENT));

			if ( !EX_WB.m_bolStalled )
			{
				EX_WB.shift();
				memset(&AC_EX.m_right, 0, sizeof(PIPE_EX_REG_CONTENT));
			}			

			if ( !AC_EX.m_bolStalled )
			{
				AC_EX.shift();
				memset(&DC4_AC.m_right, 0, sizeof(PIPE_EX_REG_CONTENT));
				memcpy(&EX_WB.m_left, &AC_EX.m_right, sizeof(PIPE_EX_REG_CONTENT));
			}

			if ( !DC4_AC.m_bolStalled )
			{
				DC4_AC.shift();
				memset(&DC3_DC4.m_right, 0, sizeof(PIPE_EX_REG_CONTENT));
				memcpy(&AC_EX.m_left, &DC4_AC.m_right, sizeof(PIPE_EX_REG_CONTENT));
			}

			if ( !DC3_DC4.m_bolStalled )
			{
				DC3_DC4.shift();
				memset(&DC2_DC3.m_right, 0, sizeof(PIPE_EX_REG_CONTENT));
				memcpy(&DC4_AC.m_left, &DC3_DC4.m_right, sizeof(PIPE_EX_REG_CONTENT));
			}			

			if ( !DC2_DC3.m_bolStalled )
			{
				DC2_DC3.shift();
				memset(&DC1_DC2.m_right, 0, sizeof(PIPE_EX_REG_CONTENT));
				memcpy(&DC3_DC4.m_left, &DC2_DC3.m_right, sizeof(PIPE_EX_REG_CONTENT));
			}

			if ( !DC1_DC2.m_bolStalled )
			{
				DC1_DC2.shift();
				memset(&EMIT_DC1.m_right, 0, sizeof(PIPE_EX_REG_CONTENT));
				memcpy(&DC2_DC3.m_left, &DC1_DC2.m_right, sizeof(PIPE_EX_REG_CONTENT));
			}

			if ( !EMIT_DC1.m_bolStalled )
			{
				EMIT_DC1.shift();
				memcpy(&DC1_DC2.m_left, &EMIT_DC1.m_right, sizeof(PIPE_EX_REG_CONTENT));
			}
			
			EX_WB.clr_stall();
			AC_EX.clr_stall();
			DC4_AC.clr_stall();
			DC3_DC4.clr_stall();
			DC2_DC3.clr_stall();
			DC1_DC2.clr_stall();
			EMIT_DC1.clr_stall();
		}

		void flush()
		{
			EMIT_DC1.flush_left();
			EMIT_DC1.flush_right();
		
			DC1_DC2.flush_left();
			DC1_DC2.flush_right();

			DC2_DC3.flush_left();
			DC2_DC3.flush_right();

			DC3_DC4.flush_left();
			DC3_DC4.flush_right();

			DC4_AC.flush_left();
			DC4_AC.flush_right();

			AC_EX.flush_left();
			AC_EX.flush_right();

			EX_WB.flush_left();
			EX_WB.flush_right();
		}

		void stall()
		{
			EMIT_DC1.stall();
			DC1_DC2.stall();
			DC2_DC3.stall();
			DC3_DC4.stall();
			DC4_AC.stall();
			AC_EX.stall();
			EX_WB.stall();
		}		

};


#endif


