#ifndef DSPU20_H
#define DSPU20_H

//---------------------------------------------------------------------------
#include "dsptypes.h"

class DSPU20 
{
      public:
          DSPU20(){ u20Data = 0; };
          ~DSPU20(){};
          DSPU20(DSPU16 pSrc){u20Data = pSrc & 0x0000ffff; };
          DSPU20(DSPU32 pSrc){u20Data = pSrc & 0x000fffff; };
          DSPU20(int pSrc){u20Data = pSrc & 0x000fffff; };
          DSPU20(DSP_BIT20 pSrc){u20Data = (DSPU32)pSrc.u4High << 16 | pSrc.u16Low; };
          void SignExtend() { if (u20Data & 0x00008000) u20Data |= 0x000f0000; };
          
          
          void SetToMAX_SN_20(){ u20Data = 0x0007ffff; };
          void SetToMIN_SN_20(){ u20Data = 0x00080000; };
          void SetToMAX_UN_20(){ u20Data = 0x000fffff; };
          void SetToZero(){ u20Data = 0x0; };
          
          DSPU20 operator+ (DSPU20 pSrc2) {return this->u20Data + pSrc2.u20Data; };
          DSPU20 operator+ (DSPU32 pSrc2) { DSPU20 Src2(pSrc2); return *this + Src2; };
          bool operator== (DSPU20 pSrc2)  { return this->u20Data == pSrc2.u20Data; }; 
          bool Sign() { return (u20Data & 0x00080000) != 0; };  //bit19ÊÇ·ûºÅÎ» 
          bool IsZero() { return (u20Data == 0); };
          DSP_BIT20 GetDSPBIT () { DSP_BIT20 x; x.u4High = u20Data >> 16; x.u16Low = u20Data; return x; };
          DSPU32 GetU32() { return u20Data; };
          void SetU32 (DSPU32 pSrc) { u20Data = pSrc & 0x000fffff; };
          void OverturnAll() { u20Data = ~u20Data; u20Data &= 0x000fffff; }; 
       
      private:
     	  DSPU32 u20Data :20 ;	
};		

//---------------------------------------------------------------------------
#endif	//DSPU20_H
