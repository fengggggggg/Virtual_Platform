
#ifndef _BREAK_POINT_H
#define _BREAK_POINT_H

/*------------------------------------------- define -------------------------------------------*/
#define BP_NUM  32

/*------------------------------------------ typedef ------------------------------------------*/
typedef struct  _BP_ELEM_INFO
{
    DSPU32  u32Addr;
	DSPU32  u32NegCount;

//	bool bolTriggered;
//   bool bolEmpty;

} BP_ELEM_INFO;

/*----------------------------------- data declarations ----------------------------------*/
BP_ELEM_INFO g_arrBPs[BP_NUM];
DSPU32  g_u32BPSetNum; // 0 ~ 32, means number of BP set

/*-------------------------------------- implimention -------------------------------------*/
void InitBPs();
bool HasBPRes();
bool IsBPAddrValid(DSPU32 p_u32Addr);
void TriggerBP(DSPU32 p_u32Addr);
void ISSClearBreakpoint();
/*
void ClrBPTrigerFlag();
*/
bool ISSIsBPHit();
bool ISSInsertBreakpoint(DSPU32 p_u32Addr, DSPU32 p_u32NegCnt);



#endif


