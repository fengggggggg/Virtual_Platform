
#ifndef _CUSTOM_INT_H
#define _CUSTOM_INT_H

/*------------------------------------------ typedef ------------------------------------------*/
typedef struct _IRQ_PARA
{
	unsigned int  u32BitMask;      // bit mask of specific INT
	unsigned int  u32MinCycle;
    unsigned int  u32MaxCycle;
    unsigned int  u32Offset;
    unsigned int  u32BeginLvl;     // 0 indicate low level and 1 indicate high level
    unsigned int  u32MaxCycleIRQ;  // u32MaxCycleIRQ.

} IRQ_PARA;

typedef struct _LVL_CHG_INFO
{
    unsigned int  u32NextChgCycle;
    unsigned int  u32CurrentLvl;

} LVL_CHG_INFO;

/*----------------------------------- data declarations ----------------------------------*/
IRQ_PARA      g_arrIRQParas[32];
LVL_CHG_INFO  g_arrLvlChgInfo[32];

//-----------------------------------------------------------------------------------------
void SelfInitIRQParas();
unsigned int GenRandNum(unsigned int p_u32Min, unsigned int p_u32Max);
void TestRand();


#endif


