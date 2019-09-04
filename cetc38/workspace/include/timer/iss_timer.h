#ifndef _TIMER_H_H_
#define _TIMER_H_H_

#include <systemc.h>
#include <iostream>
#include "../src/user_type.h"

typedef unsigned int DSPU32;
typedef unsigned long long DSPU64;

#define TIsBitSet(V, I) ( ((V) & (0x1U << (I))) != 0 )
#define TSetBit(V, I) ((V) | (0x1U << (I)))

#define TIMER_NUM				2

#define PULSE_BIT_LENGTH		9
#define MODE_SEL_BIT			31

#define LO_PUL_BIT				7
#define LO_OUT_CLK_BIT			6
#define LO_CLK_INV_BIT			5
#define LO_TM_RST_BIT			4
#define LO_TM_EN_BIT			3
#define LO_TM_OINV_BIT			2
#define LO_TM_EXRST_BIT			1
#define LO_TM_OM_BIT			0

#define HI_PUL_BIT				23
#define HI_OUT_CLK_BIT			22
#define HI_CLK_INV_BIT			21
#define HI_TM_RST_BIT			20
#define HI_TM_EN_BIT			19
#define HI_TM_OINV_BIT			18
#define HI_TM_EXRST_BIT			17
#define HI_TM_OM_BIT			16

enum TIMER_ENUM
{
	TIMER_HI,
	TIMER_LO,
	TIMER_HL,
	TIMER_END
};

class iss_timer: public sc_module
{
private:
	/*
	GREGISTER<DSPU32> u32r_TCR[TIMER_NUM];
	GREGISTER<DSPU32> u32r_THPR[TIMER_NUM];
	GREGISTER<DSPU32> u32r_TLPR[TIMER_NUM];
	GREGISTER<DSPU32> u32r_THCNT[TIMER_NUM];
	GREGISTER<DSPU32> u32r_TLCNT[TIMER_NUM];

	bool bolTINT_LO;
	bool bolTINT_HI;
	bool bolTINT_HL;
	*/
	GREGISTER<DSPU32> u32r_LTCR[TIMER_NUM];
	GREGISTER<DSPU32> u32r_LTCSR[TIMER_NUM];
	GREGISTER<DSPU32> u32r_LTCCR[TIMER_NUM];
	GREGISTER<DSPU32> u32r_LTPRLO[TIMER_NUM];
	GREGISTER<DSPU32> u32r_LTPRHI[TIMER_NUM];
	GREGISTER<DSPU32> u32r_LTCNTLO[TIMER_NUM];
	GREGISTER<DSPU32> u32r_LTCNTHI[TIMER_NUM];

	GREGISTER<bool> bolr_TMChg[TIMER_NUM];
	
	bool bolTINT_LO[TIMER_NUM];
	bool bolTINT_HI[TIMER_NUM];
	bool bolTINT_HL[TIMER_NUM];

	void DoTimer_32(DSPU32 u32TCR, DSPU32 u32TIDX);
	void DoTimer_64(DSPU32 u32TCR, DSPU32 u32TIDX);
	void RstTCNT(DSPU32 u32TIDX, TIMER_ENUM eHL);
	/*
	void SetTCR(DSPU32 TIDX, DSPU32 u32Val);
	void SetTPR(DSPU32 TIDX, DSPU32 u32Val, TIMER_ENUM eHL);
	void SetTCNT(DSPU32 TIDX, DSPU32 u32Val, TIMER_ENUM eHL);
	*/

public:
	sc_in_clk clk;

	SC_HAS_PROCESS(iss_timer);

	iss_timer(sc_module_name p_name, int p_intID)
	{
		for (int i = 0; i < TIMER_NUM; i++)
		{
			bolTINT_LO[i] = false;
			bolTINT_HI[i] = false;
			bolTINT_HL[i] = false;
			
			//u32r_LTCR[i] = 0U;
			u32r_LTCR[i].SetValue(0x00800080U);  //LTCR上电复位值为0x00800080U
			u32r_LTCSR[i].SetValue(0U);
			u32r_LTCCR[i].SetValue(0U);
			u32r_LTPRLO[i].SetValue(0U);
			u32r_LTPRHI[i].SetValue(0U);
			u32r_LTCNTLO[i].SetValue(0xffffffffU);
			u32r_LTCNTHI[i].SetValue(0xffffffffU);

			bolr_TMChg[i].SetValue(false);
		}
#ifdef TIMER_TB
		SC_METHOD(DoTimer);
		sensitive << clk.pos();
		dont_initialize();
#endif
	}
	void DoTimer();
	DSPU32 GetTINTMask();
	void ShiftRegs();

	bool RdTimerRegs(DSPU32 u32RegIdx, DSPU32 &u32Value);
	bool WrTimerRegs(DSPU32 u32RegIdx, DSPU32 u32Value);
	bool JTagRdTimerRegs(DSPU32 u32RegIdx, DSPU32 &u32Value);
	bool JTagWrTimerRegs(DSPU32 u32RegIdx, DSPU32 u32Value);

	DSPU32 GetTCR(DSPU32 TIDX);
	DSPU32 GetTPR(DSPU32 TIDX, TIMER_ENUM eHL);
	DSPU32 GetTCNT(DSPU32 TIDX, TIMER_ENUM eHL);
};


#endif
