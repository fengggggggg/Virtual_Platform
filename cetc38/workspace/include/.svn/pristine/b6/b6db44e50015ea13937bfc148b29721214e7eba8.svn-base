/*************************************************
  Copyright (C), 
  File name:      Cfloat.h
  Author:       
  Version: 
                
  Date: 
  Description:    // 对32位浮点数操作,取指数,取尾数,判断零,非数,规格化数 
 
  History:        // 修改历史记录列表，每条修改记录应包括修改日期、修改
                  // 者及修改内容简述  
    1. Date:	2007-12-11 
       Author:	Yufenglin 
       Modification: Cfloat32(DSPU32 pu32src) 
    
	2. Date:	2007-12-20 
       Author:	Yufenglin 
       Modification: add union RECI_F32
      
    3. Date:	2013-3-27 
       Author:	Yufenglin 
       Modification: Isf64NAN(),Isf64INF(),Isf64DNORM()
       
***********************************************************/


#ifndef Cfloat32_H
#define Cfloat32_H

#include "dsptypes.h"

//added by flyu for get reciprocal
typedef union RECI_F32	//32位浮点数据类型(DSP浮点数据类型)
{
	DSPU32 u32Value;
    struct SPLIT_F32 
    {
    	DSPU32    	u6src: 6;	//不处理 
    	DSPU32    	u9X1: 9;	//x1
    	DSPU32    	u8X0: 8;	//x0
    	DSPU32    	u8Exp: 8;		//指数
    	DSPU32   	u1Nega: 1;		//符号位    	     	
  	} split_f32;
} RECI_F32;


class Cfloat32
{
      public:
        Cfloat32(){};
        ~Cfloat32(){};
        Cfloat32(DSPU32 pu32src); 
        Cfloat32(float pf32src);
        DSPU32 GetNega() {return cf32value.split_f32.u1Nega;};
        DSPU8  GetExp() {return cf32value.split_f32.u8Exp;};
        DSPU32 GetFrac() {return cf32value.split_f32.u23Frac;}; 
        DSPU32 GetU32() ; 
        void SetZero();
        void SetNeg(){cf32value.split_f32.u1Nega = ~cf32value.split_f32.u1Nega; };
        void SetExp(DSPU32 pu32Exp) {cf32value.split_f32.u8Exp = pu32Exp;};
        void SetFrac(DSPU32 pu32Frac) {cf32value.split_f32.u23Frac = pu32Frac;};
        void SetU32(DSPU32 pu32src);
        float GetF32();
        bool IsZero() {return ((cf32value.split_f32.u8Exp == 0) && (cf32value.split_f32.u23Frac == 0)); };  
        bool IsNega() {return (cf32value.split_f32.u1Nega == true); };  
        bool IsNAN() {return ((cf32value.split_f32.u8Exp == 0xff) && ( cf32value.split_f32.u23Frac != 0)); };  //非数 
        bool IsINF() {return ((cf32value.split_f32.u8Exp == 0xff) && ( cf32value.split_f32.u23Frac == 0)); }; //无穷大 
        bool IsDNORM() {return (cf32value.split_f32.u8Exp == 0 && cf32value.split_f32.u23Frac != 0); };      //非规格化数，内部当0处理 
        bool IsNORM() {return (cf32value.split_f32.u8Exp != 0 && cf32value.split_f32.u8Exp != 0xff); };     //正常数 
         
     
		bool Isf64NAN() {return ((cf32value.split_f32.u8Exp == 0xff) && ( (cf32value.split_f32.u23Frac >> 20) == 0x7) && ( (cf32value.split_f32.u23Frac & 0xfffff) != 0)); };  
		bool Isf64INF() {return ((cf32value.split_f32.u8Exp == 0xff) && ( (cf32value.split_f32.u23Frac >> 20) == 0x7) && ( (cf32value.split_f32.u23Frac & 0xfffff) == 0)); };  
		bool Isf64DNORM() {return ((cf32value.split_f32.u8Exp == 0x0) && ( (cf32value.split_f32.u23Frac >> 20) == 0x0) && ( (cf32value.split_f32.u23Frac & 0xfffff) != 0)); };  

     
      //private:
      public:
      			CUSTOM_F32 cf32value;
		  		RECI_F32 rf32value;                            //add by yufenglin 2007.12.11
};

//---------------------------------------------------------------------------
#endif	//Cfloat32_H
