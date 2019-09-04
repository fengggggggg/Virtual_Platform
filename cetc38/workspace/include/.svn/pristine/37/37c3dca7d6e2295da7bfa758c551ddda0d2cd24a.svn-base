
#ifndef _MEM_PIPE_H
#define _MEM_PIPE_H

/*------------------------------------------ typedef ------------------------------------------*/
// SLK head, DC4/AC, AC/EX, EX/WB. simple testing show 3 is enough for the size. // GRQ
//#define MEM_PIPE_SLK_SIZE 5
#define MEM_PIPE_SLK_SIZE 10

//--------------------------------------------------------------------
typedef struct
{
	// 8 banks each block, DSP core can write two blocks at the same time
	DSPU32 arrWrAddr[BANK_NUM_PERBLK * 2];
	DSPU32 arrWrValue[BANK_NUM_PERBLK * 2];
	DSPU32 arrUnitIdx[BANK_NUM_PERBLK * 2];
	DSPU32 arrRegIdx[BANK_NUM_PERBLK * 2];
	DSPU32 arrSrcPageIdx[BANK_NUM_PERBLK * 2];

	DSPU32 arrBlkIdx[BANK_NUM_PERBLK * 2];
	bool arrAtom[BANK_NUM_PERBLK * 2];
	
	DSPU32 u32WrElemNum;

	bool bolInUse;  // whether this elem is in use
	DSPU32 u32Next;       // point to next elem

	// for special use(liuyu)
	DSPU32 u32SpecWrMask;
/*
	DSPU32 arrRdAddr[BANK_NUM_PERBLK * 2];
	DSPU32 arrRdValue[BANK_NUM_PERBLK * 2];
	DSPU32 arrRdBlkIdx[BANK_NUM_PERBLK * 2];
	bool arrRdAtom[BANK_NUM_PERBLK * 2];	
	DSPU32 u32RdElemNum;
	bool bolIsRead;
*/
} MEM_PIPE_SLK_ELEM;

/*----------------------------------- data declarations ----------------------------------*/
//static link list for memory access in pipeline
MEM_PIPE_SLK_ELEM  m_arrMemPipeSLK[MEM_PIPE_SLK_SIZE]; 

/*-------------------------------------- implimention -------------------------------------*/
void InitMPSLK();
DSPU32 MallocMPSLK();
bool FreeMPSLK(DSPU32 p_u32SLKIdx);
DSPU32 GetMPSLKNumInUse();

#endif


