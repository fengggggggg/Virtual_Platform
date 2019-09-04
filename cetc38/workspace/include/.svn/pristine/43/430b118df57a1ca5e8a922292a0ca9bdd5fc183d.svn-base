/**********************************************************************************************
  Copyright (C), 
  File name:      DSPU80.h
  Author:       Version: 
                Date: 
  Description:    // 用于详细说明此程序文件完成的主要功能，与其他模块
                  // 或函数的接口，输出值、取值范围、含义及参数间的控
                  // 制、顺序、独立或依赖等关系
  Others:         // 其它内容的说明
  Function List:  // 主要函数列表，每条记录应包括函数名及功能简要说明
    1. ....
  History:        // 修改历史记录列表，每条修改记录应包括修改日期、修改
                  // 者及修改内容简述 
         1. Date:	2008-3-28
            Author:	zhaoxiang
            Modification: add USignExtend(), SetToMAX_usigned_80();
		 2. Date:	2008-3-28
            Author:	zhaoxiang
            Modification: "private" is instead of "public"
		 3. Date:	2008-3-28
            Author:	zhaoxiang
            Modification: modify SetToMAX_SN_80(), SetToMIN_SN_80() 
		    
**************************************************************************************************/

#ifndef DSPU80_H
#define DSPU80_H
#include "GlobleDef.h"


class DSPU80 
{
      public:
          DSPU80(){u64Low=0;u16High=0;};
          ~DSPU80(){};
          DSPU80(DSP_BIT80 pSrc);
		  DSPU80(DSPU16 uh,DSPU32 um, DSPU32 ul);
          void SignExtend();
          void USignExtend();        //无符号扩展 (乘累加中取80位累加寄存器结果,对于无符号数最高位若为1,扩展符号位为0)          add by zhaoxiang 2008.3.35
          void SetToMAX_SN_80(){u64Low = u64AllOne; u16High = 0x007f; };
          void SetToMIN_SN_80(){u64Low = u64AllZero; u16High = 0xff80; };
          void SetToMAX_UN_80(){u64Low = u64AllOne; u16High = 0xffff; };
          void SetToMAX_usigned_80(){u64Low = u64AllOne; u16High = 0x00ff; };        //add by zhaoxiang        2008.3.24
          DSPU80(DSPU64 pSrc);
          DSPU80(DSPU16 pHigh, DSPU64 pLow) { u16High = pHigh; u64Low = pLow; };
          DSPU80 operator+ (DSPU80 pSrc2);
		  DSPU80 operator- (DSPU80 pSrc2);
          DSPU80 operator+ (DSPU64 pSrc);
          bool operator== (DSPU80 pSrc2);
          bool u64LowSign() { return (u64Low & u64MSBMask) != 0; };
          bool Sign() { return (u16High & 0x8000) != 0; };
		  bool MACCSign() {return ((u16High & 0xff80)!=0);};
		  void MACCSExtend();
		  void MACCUExtend();
          bool IsZero() { return (u64Low == 0) && (u16High == 0); };
          DSP_BIT80 GetDSPBIT (){DSP_BIT80 x; x.u64Low = u64Low; x.u16High = u16High; return x; };
          void OverturnAll() { u64Low = ~u64Low; u16High = ~u16High; }; 
       
      public:
	      DSPU64 u64Low;				//低64位
	      DSPU16 u16High;				//高16位
};		

//---------------------------------------------------------------------------
#endif	//DSPU80_H
