
/*-----------------------------------------------------------------------------
       1. Date:	2007-12-11 
          Author:	Yufenglin 
          Modification: add union RECI_F16, union RECI_F64_35, union RECI_F64,
                        union RECI_F64_18, union RECI_F32_18, union RECI_F32_8,
                        union RECI_F64_23, union RECI_F64_34, union RECI_F64_31
                        
       2. Date:	2007-12-11 
          Author:	Zhaoxiang 
          Modification: add union RECI_33to2, union RECI_34to19, union RECI_34to3                        

-----------------------------------------------------------------------------*/

#ifndef SPU_TYPE_H
#define SPU_TYPE_H

#include "dsptypes.h"

typedef union RECI_33to2	    //定点32位开方取结果用  
{
	DSPU64 u64Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u2src: 2;	  //不处理 
    	DSPU64    	u31X1: 32;	//结果（33-2） 
    	DSPU64    	u31X0: 30;	//不处理   	     	
  	} split_f32;
} RECI_33to2; 

typedef union RECI_34to19	     //sin、cos运算取16位结果用
{
	DSPU64 u64Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u19src: 19;	//不处理 
    	DSPU64    	u16X1: 16;	//结果 
    	DSPU64    	u29X0: 29;	//不处理   	     	
  	} split_f32;
} RECI_34to19;

typedef union RECI_34to3	   //sin运算取32位结果用
{
	DSPU64 u64Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u3src: 3;	  //不处理 
    	DSPU64    	u32X1: 32;	//结果 
    	DSPU64    	u29X0: 29;	//不处理   	     	
  	} split_f32;
} RECI_34to3;




//added by flyu for get reciprocal
typedef union RECI_F16	
{
	DSPU16 u64Value;
    struct SPLIT_F32 
    {
    	DSPU16    	u17src: 5;	//不处理 
    	DSPU16    	u18X1: 8;	//尾数 
    	DSPU16    	u29X0: 3;	//不处理   	     	
  	} split_f16;
} RECI_F16;

typedef union RECI_F64_35	
{
	DSPU64 u64Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u17src: 17;	//不处理 
    	DSPU64    	u18X1: 18;	//尾数 
    	DSPU64    	u29X0: 29;	//不处理   	     	
  	} split_f64;
} RECI_F64_35;

typedef union RECI_F64	
{
	DSPU64 u64Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u9src: 10;	//不处理 
    	DSPU64    	u23X1: 23;	//尾数 
    	DSPU64    	u8X0: 31;	//不处理   	     	
  	} split_f64;
} RECI_F64;

typedef union RECI_F64_18	
{
	DSPU64 u64Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u17src: 17;	//不处理 
    	DSPU64    	u17X1: 17;	//尾数 
    	DSPU64    	u1X1: 1;	//符号位 
    	DSPU64    	u8X0: 29;	//不处理   	     	
  	} split_f64;
} RECI_F64_18;

typedef union RECI_F32_18	
{
	DSPU32 u32Value;
    struct SPLIT_F32 
    {
    	DSPU32    	u18src: 18;	
    	DSPU32    	u14src: 14;	    	
  	} split_f32;
} RECI_F32_18;

typedef union RECI_F32_8	
{
	DSPU32 u32Value;
    struct SPLIT_F32 
    {
    	DSPU32    	u8src: 8;
		DSPU32    	u1Nega: 1;		
    	DSPU32    	u23src: 23;	    	
  	} split_f32;
} RECI_F32_8;

typedef union RECI_F64_23	
{
	DSPU64 u32Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u9src: 10;
		DSPU64    	u23src: 23;		
    	DSPU64    	u32src: 31;	    	
  	} split_f32;
} RECI_F64_23;

typedef union RECI_F64_34	
{
	DSPU64 u32Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u9src: 10;
		DSPU64    	u23src: 23;		
    	DSPU64    	u32src: 31;	    	
  	} split_f32;
} RECI_F64_34;

typedef union RECI_F64_31	
{
	DSPU64 u32Value;
    struct SPLIT_F32 
    {
    	DSPU64    	u8src: 9;
		DSPU64    	u23src: 23;		
    	DSPU64    	u33src: 32;	    	
  	} split_f32;
} RECI_F64_31;




#endif	


