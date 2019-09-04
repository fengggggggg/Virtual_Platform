#ifndef DSPU10_H
#define DSPU10_H

//---------------------------------------------------------------------------
#include "dsptypes.h"

class DSPU10 
{
	  public:
          DSPU10(){ u10Data = 0; };
          ~DSPU10(){};
          DSPU10(DSPU16 pSrc){u10Data = pSrc & 0x000000ff; };
          DSPU10(DSPU32 pSrc){u10Data = pSrc & 0x000003ff; };
		  DSPU10(int pSrc){u10Data = pSrc & 0x000003ff; };
          
		  DSPU10(DSP_BIT20 pSrc){u10Data = (DSPU32)pSrc.u4High << 8 | (pSrc.u16Low & 0xff); };
          void SignExtend() { if (u10Data & 0x00000080) u10Data |= 0x00000f00; };
          
          void SetToMAX_SN_20(){ u10Data = 0x000001ff; }; //应余锋林要求修改20140327
          void SetToMIN_SN_20(){ u10Data = 0x00000200; }; //应余锋林要求修改20140327
          void SetToMAX_UN_20(){ u10Data = 0x000003ff; };
          void SetToZero(){ u10Data = 0x0; };


		  DSPU10 operator+ (DSPU10 pSrc2) {return this->u10Data + pSrc2.u10Data; };
		  
          DSPU10 operator+ (DSPU32 pSrc2) { DSPU10 Src2(pSrc2); return *this + Src2; };
          
		  bool operator== (DSPU10 pSrc2)  { return this->u10Data == pSrc2.u10Data; }; 
          bool Sign() { return (u10Data & 0x00000200) != 0; };  //bit19是符号位 
          bool IsZero() { return (u10Data == 0); };
          DSP_BIT20 GetDSPBIT () { DSP_BIT20 x; x.u4High = u10Data >> 8; x.u16Low = u10Data & 0xff; return x; };
          DSPU32 GetU32() { return u10Data; };
          void SetU32 (DSPU32 pSrc) { u10Data = pSrc & 0x000003ff; };
          void OverturnAll() { u10Data = ~u10Data; u10Data &= 0x000003ff; }; 
          
      //应余锋林要求添加该成员20140123
      DSP_BIT20 GetDSP10BIT () { DSP_BIT20 x; x.u4High = 0;; x.u16Low = u10Data & 0x3ff; return x; };
      private:
     	  DSPU32 u10Data :10 ;	
};

//---------------------------------------------------------------------------
#endif	//DSPU10_H
