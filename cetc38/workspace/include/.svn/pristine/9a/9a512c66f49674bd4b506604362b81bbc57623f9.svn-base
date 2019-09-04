
#ifndef _WATCH_POINT_H
#define _WATCH_POINT_H

/*------------------------------------------- define -------------------------------------------*/
#define WP_NUM  16

/*------------------------------------------ typedef ------------------------------------------*/
typedef struct  _WP_ELEM_INFO
{
    DSPU32  u32StartAddr;
	DSPU32  u32EndAddr;
	DSPU32  u32NegCount;
	DSPU32  u32Type;             // 1(read), 2(write), 3(read/write)

//	bool bolTriggered;
//   bool bolEmpty;

} WP_ELEM_INFO;

/*----------------------------------- data declarations ----------------------------------*/
WP_ELEM_INFO g_arrWPs[WP_NUM];
DSPU32  g_u32WPSetNum; // 0 ~ 32, means number of WP set

/*-------------------------------------- implimention -------------------------------------*/
void InitWPs();
bool HasWPRes();
bool IsWPOverlap(DSPU32 p_u32StartAddr, DSPU32 p_u32EndAddr);
bool IsWPAddrValid(DSPU32 p_u32StartAddr, DSPU32 p_u32EndAddr);
void TriggerWP(DSPU32 p_u32Addr, bool p_bolIsWr);
void ISSClearWatchpoint();
DSPU32 ISSGetWPTriggerReg();
bool ISSInsertWatchpoint(DSPU32 p_u32StartAddr, DSPU32 p_u32EndAddr, DSPU32 p_u32NegCnt, DSPU8 p_u8Type);


#endif


