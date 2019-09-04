
/****************************************************************************
  1. Date:	2007-11-10
       Author:	baohua
       Modification:add  DSP_BIT40,add  DSPU8  u8Exp;  
       
***************************************************************************/

#ifndef DSPU40_H
#define DSPU40_H
/*---------------------------Include Files-------------------------*/
#include "dsptypes.h" 

class DSPU40 
{
      public:
          DSPU40(){};
          ~DSPU40(){};
          DSPU40(DSP_BIT40 pSrc);
          void SignExtend();
          void SetToMAX_SN_40(){ u8High = 0x7f; u32Low = 0xffffffff; };
          void SetToMIN_SN_40(){ u8High = 0x80; u32Low = 0x00000000; };  // 
          void SetToMAX_UN_40(){ u8High = 0xff; u32Low = 0xffffffff; };
          void SetToMAX_SN_32(){ u8High = 0x00; u32Low = 0x7fffffff; };
          void SetToMIN_SN_32(){ u8High = 0xff; u32Low = 0x80000000; };
          void SetToMAX_UN_32(){ u8High = 0x00; u32Low = 0xffffffff; };          
          DSPU40(DSPU32 pSrc) { u32Low = pSrc; u8High = 0; };
          DSPU40(DSPU8 pHigh, DSPU32 pLow) { u8High = pHigh; u32Low = pLow; };
          DSPU40 operator+ (DSPU40 pSrc2);
          DSPU40 operator+ (DSPU32 pSrc);
          bool operator== (DSPU40 pSrc2);
          bool u32LowSign() { return u32Low & 0x80000000; };
          bool Sign() { return u8High & 0x80; };
          bool IsZero() { return (u32Low == 0) && (u8High == 0); };
          bool IsOverflow()  { return ((u8High & 0x01) == 0x0 ) &&  this->u32LowSign(); };
          bool IsUnderflow() { return ((u8High & 0x01) == 0x1 ) && !this->u32LowSign(); };
          DSP_BIT40 GetDSPBIT (){DSP_BIT40 x; x.u32Low = u32Low; x.u8High = u8High; return x; };
          void OverturnAll() { u32Low = ~u32Low; u8High = ~u8High; }; 
          
          
       
      public:
          
          DSPU32 u32Low;				//µÍ32Î»
          DSPU8  u8High;                //¸ß8Î»  
         
         
          
};		

//---------------------------------------------------------------------------
#endif	//DSPU40_H
