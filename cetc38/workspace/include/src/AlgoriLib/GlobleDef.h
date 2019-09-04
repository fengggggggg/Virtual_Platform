//---------------------------------------------------------------------------
#ifndef Globle_Def_H
#define Globle_Def_H

#include "dsptypes.h"

//---------------------------------------------------------------------------
// bit define of ALU  Ctl registers
#define ALU_Ctl_Signed          0
#define ALU_Ctl_Saturation      1

//---------------------------------------------------------------------------
// bit define of Mul Ctl registers
#define Mul_Ctl_Signed          0
#define Mul_Ctl_Saturation      1
#define Mul_Ctl_16CutNum        4
#define Mul_Ctl_32CutNum        12
#define Mul_Ctl_8CutNum			20
#define Test_Mul_Ctl_16CutNum(MulCtl)  ((MulCtl >>  4) & 0x0000001f)  //4-8位 共5位        
#define Test_Mul_Ctl_32CutNum(MulCtl)  ((MulCtl >> 12) & 0x0000003f)  //12-17位 共6位  

#define Test_Mul_Ctl_8CutNum(MulCtl)  (((MulCtl) >> Mul_Ctl_8CutNum) & 0x0000001f)  //20-24位 共5位  

//---------------------------------------------------------------------------
// bit define of SPU Ctl registers
#define SPU_Ctl_Saturation 1

//---------------------------------------------------------------------------
// bit define of ALU Flag registers
//to be updated later
#define ALU_Zero            33
#define ALU_Nega            33
#define ALU_Carry           33

#define ALU_OverFlow         0
#define ALU_FOverFlow        1
#define ALU_UnderFlow        2
#define ALU_Invalid          3

#define ALU_AOS              8
#define ALU_AVS              9
#define ALU_AUS             10
#define ALU_AIS             11

//---------------------------------------------------------------------------
// bit define of Mul Flag registers
#define Mult_Zero           33
#define Mult_Nega           33
#define Mult_OverFlow        0  //Multiplier fixed-pt, overflow,
#define Mult_FOverFlow       1
#define Mult_UnderFlow       2
#define Mult_Invalid         3

#define Mult_MOS             8    //Multiplier fixed-pt, overflow, sticky
#define Mult_MVS             9    //Multiplier floating-pt, overflow, sticky
#define Mult_MUS            10    //Multiplier floating-pt, underflow, sticky
#define Mult_MIS            11    //Multiplier floating-pt, invalid op., sticky

#define Mult_8_OverFlow 4
#define Mult_16_OverFlow 5
#define Mult_32_OverFlow 6

#define Mult_8_OverFlow_S 12
#define Mult_16_OverFlow_S 13
#define Mult_32_OverFlow_S 14

//---------------------------------------------------------------------------
// bit define of Shifter Ctl registers
#define SHF_Ctl_Signed          0
#define SHF_Ctl_Saturation      1

//--------------------------------------------------------------------------
// bit define of Shifter Flag registers
#define SHF_Zero        33
#define SHF_Nega        33
//#define SHF_OverFlow    0
//#define SHF_SSHO        8

#define SHF_OverFlow    0
#define SHF_FOverFlow   1   //baohua 2013.3.13
#define SHF_FUnderFlow  2	//baohua 2013.3.13
#define SHF_FInvalid    3	//baohua 2013.3.13
#define SHF_OverFlow8Bit     4//baohua 2013.3.13
#define SHF_OverFlow16Bit     5//baohua 2013.3.13
#define SHF_OverFlow32Bit     6//baohua 2013.3.13


#define SHF_SOVS        8
#define SHF_SFVS      9	//baohua 2013.3.13
#define SHF_SFUS     10	//baohua 2013.3.13
#define SHF_SFIS   11	//baohua 2013.3.13
#define SHF_OV8BitS     12//baohua 2013.3.13
#define SHF_OV16BitS     13//baohua 2013.3.13
#define SHF_OV32BitS     14//baohua 2013.3.13

//---------------------------------------------------------------------------
// bit define of SPU Flag registers
#define SPU_SZ          33
#define SPU_SN          33
#define SPU_SO          0
#define SPU_SFO         1
#define SPU_SFU         2 //特定单元浮点下溢标志
#define SPU_SI          3

#define SPU_SSO         8      //spu静态浮点无效操作
#define SPU_SSFO        9      //spu静态浮点上溢
#define SPU_SSFU        10     //spu静态浮点下溢
#define SPU_SSI         11     //spu静态浮点下溢

//---------------------------------------------------------------------------
#define MAX_SN_32 0x7fffffff
#define MIN_SN_32 0x80000000
#define MAX_UN_32 0xffffffff

#define MAX_SN_16 0x7fff
#define MIN_SN_16 0x8000
#define MAX_UN_16 0xffff

#define N_A_N 0xffffffff
#define POS_INF  0x7f800000
#define NEG_INF  0xff800000
#define MAX_NORM 0x7f7fffff
#define MIN_NORM 0xff7fffff

#define NEG_ZERO 0x80000000
#define POS_ZERO 0x00000000

//---------------------------------------------------------------------------
#define MAX_SN(x)          (( ~(1 << (x - 1)) ))
#define MIN_SN(x)          ((  (1 << (x - 1)) ))
#define MAX_UN(x)          (( ~(1 << x) ))

//---------------------------------------------------------------------------
//截断方式 
#define md_to_zero          0     
#define md_to_nearest       1     

//---------------------------------------------------------------------------

#define BIT(y)             ((1 << (y)))         

#define SetFlag(x, y)      ((x) = ((x) | (1 << (y))))   
#define ClearFlag(x, y)    ((x) = ((x) & ~(1 << (y))))   

#define SetBit(x, y)      ((x) = ((x) | (1 << (y))))   
#define ClearBit(x, y)    ((x) = ((x) & ~(1 << (y))))   

#define TestFlag(x, y)      ((((x) & (1 << (y)))) != 0)
#define TestBit(x, y)       ((((x) & (1 << (y)))) != 0)

//---------------------------------------------------------------------------
// mode of saturation management
#define BaoHe_none          (BIT(ALU_Ctl_Signed))
#define BaoHe_none_unsigned (0)
#define BaoHe_signed        (BIT(ALU_Ctl_Saturation) | BIT(ALU_Ctl_Signed)) 
#define BaoHe_unsigned      (BIT(ALU_Ctl_Saturation))

//---------------------------------------------------------------------------
//为支持跨平台，对不跨平台的常数均使用以下定义
#ifdef DSP_WIN32	//data types in windows VC 6.0
	const DSPU64 u64AllZero = 0x0;
	const DSPU64 u64AllOne  = 0xffffffffffffffff;  
	const DSPU64 u64MSBMask = 0x8000000000000000;
	const DSPU64 u40AllOne = 0xffffffffff;
	const DSPU64 u40SignedMin = 0x8000000000;
	const DSPU64 u40SignedMax = 0x7fffffffff;
#else 
#ifdef 	DSP_LINUX			//data types in linux
	const DSPU64 u64AllZero = 0x0ull;
	const DSPU64 u64AllOne  = 0xffffffffffffffffull;  
	const DSPU64 u64MSBMask = 0x8000000000000000ull;
	const DSPU64 u40AllOne = 0xffffffffffull;
	const DSPU64 u40SignedMin = 0x8000000000ull;
	const DSPU64 u40SignedMax = 0x7fffffffffull;
#endif
#endif

#endif	//Globle_Def_H