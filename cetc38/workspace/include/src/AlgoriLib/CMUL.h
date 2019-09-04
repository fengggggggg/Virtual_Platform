/*************************************************
  Copyright (C), 
  File name:      CMUL.h
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
                  
    1. Date:	2007-8-6
       Author:	GRui
       Modification: add MAC32(), MACD16(), MACF32(), MACC16(), MulAdd64(),
       					 MulSub64(), MulAddNeg64(), MULSqrAdd16()       
       
	  2. Date:	2007-9-7
       Author:	GRui
       Modification: add Mul16F32()
       
	  3. Date:	2007-9-29
       Author:	GRui
       Check: MulC16(), MulC16Conj(), MulC16DConj(), MULSqrAdd16(), Mul16F32()
       
    4. Date:	2008.3.20 
       Author:	ZhaoXiang 
       Modification:  modify Mul32(), MulSqrAdd16();
                             (内部函数: Mul16()); 
                      
    5. Date:	2008.3.21 
       Author:	ZhaoXiang 
       Modification: modify MACCTo32(), MACCToD16(), MAC32();
                            (内部函数: MACCTo16(), MAC16());
       
    6. Date:	2008.3.27 
       Author:	ZhaoXiang 
       Modification: modify MulC16(), MulC16Conj();
       
    7. Date:	2008.3.28 
       Author:	ZhaoXiang 
       Modification: modify MulF32();

    8. Date:	2008-6-3                                                
       Author:	GRui                                                  
       Modification: 为了模拟硬件对无符号数的乘累减，增加了MSubU32()。
       
    9. Date:	2008-9-13
       Author:	zhaoxiang
       Modification: 为累加截位32位输出增加了temp_MACCTo32()函数,还未经过验证，如经过验证后需替换函数MACCTo32()。
         
    10. Date:	2008-9-20
       Author:	zhaoxiang
       Modification: 修改了temp_MACCTo32()函数 和 MAC32()函数。 
       	
    11. Date:	2008-9-23
       Author:	zhaoxiang
       Modification: 按照汪灏要求修改了MAC32()函数 (对80位寄存器高8位的处理)。
       
    12. Date:	2008-10-19
       Author:	zhaoxiang
       Modification: 修改了temp_MACCTo32()函数,其中增加了无符号80位寄存器置高8位的限制。 
    
    13. Date:	2008-10-20
       Author:	zhaoxiang
       Modification: 修改了MSubU32()的函数定义,且修改了函数体。
                     修改了MACC16()函数.  
    
    14. Date:	2009-12-3
       Author:	zhaoxiang
       Modification: 删除原MACCTo32()函数，将函数temp_MACCTo32()改为MACCTo32()函数。
       
    15. Date:	2008-12-3
       Author:	zhaoxiang
       Modification: 添加函数C32MUL_1_2_Inst71()，改函数用于占多个乘法器的指令，将指令中不用的乘法器的标志位屏蔽。
    
    16.
       Date:	2012-7-18 
       Author:	GRui
       modify： 1) change DSPU32 MACCToD16(DSP_BIT80 p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, int p_intCutPos, bool p_bolUseCutPos);
                   to     DSPU32 MACCToD16(const DSP_BIT80 &p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, int p_intCutPos, bool p_bolUseCutPos);   
                2) change DSPU32 MACCToF32(DSP_BIT80 p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR); 
                   to     DSPU32 MACCToF32(const DSP_BIT80 &p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR);  
                3) change DSPU32 MACCTo32(DSP_BIT80 p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, int p_intCutPos, bool p_bolUseCutPos);
                   to     DSPU32 MACCTo32(const DSP_BIT80 &p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, int p_intCutPos, bool p_bolUseCutPos);
                
       Added:   在BWDSP1042标签下新增系列指令(14个)。
       
    17.
       Date:	2012-8-10 
       Author:	GRui
               
       删除：  1042标签下凡是没有标注"found"的函数待确认后均可能被删除（约2条）。
     
       
       新增：  MACC16MFix8(),MACNegC16MFix8(),LoadMACCD32(),LoadMACCQ8()
       
       修改参数：MACCToQ8(),HMACCTo32()
                         
       修改函数说明：
       
     18.
       Date:	2013-1-1 
       Author:	GRui            
       
       新增：   MulF64H(), MulF64L(), MulF64HL(), MACCToF64L(), MACCToF64H()
       
     19. 
       Date:	2013-4-11
       Author:	zhaoxiang
       新增:  MACC8() 
               
	   19. 
	   Date:	2013-12-31
	   Author:	linguangdong
	   新增:  MACD8Mult16() 、MACDC8MultC16()、LoadHOMACC()
	   修改：MACCToQ8(),LoadMACCQ8()、MACC8()、OMACCTo32()、OMACCToD16()、MACSigmaQ8()、MACQ8()
	   等8位操作的函数

	   20. 
	   Date:	2014-1-1
	   Author:	linguangdong
	   删除：LoadMACCHL32

	   21. 
	   Date:	2014-1-1
	   Author:	linguangdong
	   修改：所有以Load开头的函数、所有以MACCTo（HMACCTo）开头的函数，最后增加bool p_bolUseCutPos
	   参数，用以区分截位数据从立即数C来，还是从MULCR来。

	   22. 
	   Date:	2014-1-15
	   Author:	linguangdong
	   修改：LoadHOMACC、MACDC8MultC16、MACD8Mult16三个函数的第一参数改为以引用的方式
	   访问MACC。

	   23. 
	   Date:	2014-10-13
	   Author:	zhaoxiang
	   新增: AMACCF32()

    
***********************************************************/


//---------------------------------------------------------------------------
#ifndef UNIT_MULTIPLIER_H
#define UNIT_MULTIPLIER_H

//---------------------------------------------------------------------------
#include "dsptypes.h"


/******************************************************************
	函数名：		Mul32

	描述:			32位定点数据相乘。

	参数:			p_u32Src1 -- 源操作数1。
					p_u32Src2 -- 源操作数2。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern DSPU32 Mul32(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR);

/******************************************************************
	函数名：		MulD16

	描述:			输入数据的高低16位分别作定点数据相乘。

	参数:			p_u32Src1 -- 源操作数1，包含高低两个16位定点数据。
					p_u32Src2 -- 源操作数2，包含高低两个16位定点数据。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern DSPU32 MulD16(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR);

/******************************************************************
	函数名：		MulF32

	描述:			32位浮点数据相乘。

	参数:			p_u32Src1 -- 源操作数1。
					p_u32Src2 -- 源操作数2。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处

*******************************************************************/
extern DSPU32 MulF32(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR);

/******************************************************************
	函数名：		MulC16

	描述:			16位定点复数相乘：(a + bi) * (c + di)。

	参数:			p_CFix16Src1 -- 源操作数(a + bi)，16位定点复数。
					p_CFix16Src2 -- 源操作数(c + di)，16位定点复数。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位；16位定点复数乘法在一个乘法器内完成。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern DSP_CFix16 MulC16(DSP_CFix16 p_CFix16Src1, DSP_CFix16 p_CFix16Src2, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR);

/******************************************************************
	函数名：		MulC16Conj

	描述:			16位定点复数相乘：(a + bi) * conj(c + di)。

	参数:			p_CFix16Src1 -- 源操作数(a + bi)，16位定点复数。
					p_CFix16Src2 -- 源操作数(c + di)，16位定点复数。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern DSP_CFix16 MulC16Conj(DSP_CFix16 p_CFix16Src1, DSP_CFix16 p_CFix16Src2, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR);

/******************************************************************
	函数名：		MulC16DConj

	描述:			16位定点复数相乘：conj(a + bi) * conj(c + di)。

	参数:			p_CFix16Src1 -- 源操作数(a + bi)，16位定点复数。
					p_CFix16Src2 -- 源操作数(c + di)，16位定点复数。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern DSP_CFix16 MulC16DConj(DSP_CFix16 p_CFix16Src1, DSP_CFix16 p_CFix16Src2, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR);

/******************************************************************
	函数名：		MACCToD16

	描述:				乘累加结果寄存器MACC截位输出为高低16位定点数据。

	参数:				DSP_BIT80 -- 80位MACC。
							p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
							p_u32MULCR -- 乘法器控制寄存器。
							p_intCutPos -- 截位信息。
							p_bolUseCutPos -- 截位信号选择。true: 使用p_intCutPos作为截位信号；
					  									  false：使用p_u32MULCR中的截位信号。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位；
							根据p_bolUseCutPos选择截位信号来源。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern DSPU32 MACCToD16(const DSP_BIT80 &p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, int p_intCutPos, bool p_bolUseCutPos);


/******************************************************************
	函数名：		MAC32

	描述:			32位定点数据乘累加。

	参数:			p_u32Src1 -- 源操作数1。
					p_u32Src2 -- 源操作数2。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器，其中包含有无符号等控制信息。

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MAC32(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT80 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR);

/******************************************************************
	函数名：		MACD16

	描述:			高低16位定点数据乘累加。

	参数:			p_u32Src1 -- 源操作数1。
					p_u32Src2 -- 源操作数2。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器，其中包含有无符号等控制信息。

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACD16(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT80 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR); 


/******************************************************************
	函数名：		MACC16

	描述:			16位定点复数乘累加。

	参数:			p_u32Src1 -- 16位定点复数1。
					p_u32Src2 -- 16位定点复数2。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACC16(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT80 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR);

/******************************************************************
	函数名：		MULSqrAdd16

	描述:				求32位定点数据p_u32Src内部高低16位数据的平方和。

	参数:				p_u32Src -- 源操作数，包括高低16位定点数据。
							p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
							p_u32MULCR -- 乘法器控制寄存器。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern DSPU32 MULSqrAdd16(DSPU32 p_u32Src, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR); 


/******************************************************************
	函数名：		MACCTo32

	描述:			  乘累加结果寄存器MACC截位输出为32位定点数据。

	参数:			  DSP_BIT80 -- 80位MACC。
					    p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					    p_u32MULCR -- 乘法器控制寄存器。
					    p_intCutPos -- 截位信息。
					    p_bolUseCutPos -- 截位信号选择。true: 使用p_intCutPos作为截位信号；
					  									  false：使用p_u32MULCR中的截位信号。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位；
							根据p_bolUseCutPos选择截位信号来源。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern DSPU32 MACCTo32(const DSP_BIT80 &p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, int p_intCutPos, bool p_bolUseCutPos);

/*------------------------BWDSP1042------------------------*/
/*found*****************************************************************
	函数名：		MulS16
	
	对应指令形式: Rs=LHRm*LHRn 
	              Rs=HHRm*HHRn 
	              Rs=LHRm*HHRn 

	描述:			从两个通用寄存器中分别选择高16位或低16位作定点有符号数乘法。

	参数:		p_u32Src1 -- 源操作数1，对应Rm，包含高低两个16位定点数据。
					p_u32Src2 -- 源操作数2，对应Rn，包含高低两个16位定点数据。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Mode -- 模式选择
					    0 -- 选择Rm的低16位与Rn的低16位相乘
					    1 -- 选择Rm的高16位与Rn的高16位相乘
					    2 -- 选择Rm的低16位与Rn的高16位相乘

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern DSPU32 MulS16(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, DSPU32 p_u32Mode);

/*found*****************************************************************
	函数名：		LoadMACC32
	
	对应指令形式: MACCs=Rm(C)(z,s,p)                      // z, s, p必定3选1

	描述:			将32位Rm寄存器内容放置在MACC[(31+c):c]处。

	参数:		DSP_BIT80 -- 80位MACC。
					p_u32Src -- 源操作数，对应Rm。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Pos -- 放置起始位置，对应c。
					p_u32Mode -- 模式选择
					    0 -- 对于MACC中的其他位，高低位均补零，对应后缀z
					    1 -- 对于MACC中的其他位，高位进行符号位扩展，低位补零，对应后缀s
					    2 -- 对于MACC中的其他位，保持原值，对应后缀p

	返回值：		

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void LoadMACC32(DSP_BIT80 &p_u80MACC, DSPU32 p_u32Src, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, DSPU32 p_u32Pos, DSPU32 p_u32Mode, bool p_bolUseCutPos);

/*found*****************************************************************
	函数名：		LoadMACC64
	
	对应指令形式: MACCs=Rm+1:m(C)(z,s,p)

	描述:			将64位Rm+1:m寄存器内容放置在MACC[(63+c):c]处。

	参数:		DSP_BIT80 -- 80位MACC。
					p_Src -- 64位输入，p_Src.Low32对应Rm，p_Src.High32对应Rm+1。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Pos -- 放置起始位置，对应c。
					p_u32Mode -- 模式选择
					    0 -- 对于MACC中的其他位，高低位均补零，对应后缀z
					    1 -- 对于MACC中的其他位，高位进行符号位扩展，低位补零，对应后缀s
					    2 -- 对于MACC中的其他位，保持原值，对应后缀p

	返回值：	

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void LoadMACC64(DSP_BIT80 &p_u80MACC, DSP_BIT64 &p_Src, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, DSPU32 p_u32Pos, DSPU32 p_u32Mode,  bool p_bolUseCutPos);

/*found*****************************************************************
	函数名：		LoadMACCD16
	
	对应指令形式: HMACCs=HRm(C)(z,s,p)  

	描述:			将寄存器Rm分成高低16位，分别对应存入MACC的高低40位。放置起始位置为c和c+40，具体位置为[(16+c):c]，[(56+c):c+40]。

	参数:		DSP_BIT80 -- 80位MACC。
					p_u32Src -- 源操作数，对应Rm。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Pos -- 放置起始位置，对应c。
					p_u32Mode -- 模式选择
					    0 -- 对于MACC中的其他位，高低位均补零，对应后缀z
					    1 -- 对于MACC中的其他位，高位进行符号位扩展，低位补零，对应后缀s
					    2 -- 对于MACC中的其他位，保持原值，对应后缀p

	返回值：		

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void LoadMACCD16(DSP_BIT80 &p_u80MACC, DSPU32 p_u32Src, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, DSPU32 p_u32Pos, DSPU32 p_u32Mode,  bool p_bolUseCutPos);

/*found*****************************************************************
	函数名：		MACNeg32

	对应指令形式: MACCs-=Rm*Rn(U)
                MACCs-=Rm*Rn

	描述:			32位定点数据乘累减。

	参数:		p_u32Src1 -- 源操作数1，对应Rm。
					p_u32Src2 -- 源操作数2，对应Rn。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器，其第0位被算法库扩展用于表示源操作数是否为有符号数。
					    p_u32MULCR[0] == 1： 源操作数为有符号数
					    p_u32MULCR[0] == 0： 源操作数为无符号数

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACNeg32(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT80 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR);

/*found*****************************************************************
	函数名：		MACNegD16

	对应指令形式: HMACCs-=HRm*HRn(U)
                HMACCs-=HRm*HRn

	描述:			高低16位定点数据乘累减。

	参数:		p_u32Src1 -- 源操作数1，对应Rm。
					p_u32Src2 -- 源操作数2，对应Rn。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器，其第0位被算法库扩展用于表示源操作数是否为有符号数。
					    p_u32MULCR[0] == 1： 源操作数为有符号数
					    p_u32MULCR[0] == 0： 源操作数为无符号数

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACNegD16(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT80 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR); 

/*found*****************************************************************
	函数名：		MACQ8
	
	对应指令形式: OMACCs=ORm*ORn(U)
	              OMACCs+=ORm*ORn(U)
                OMACCs-=ORm*ORn(U)

	描述:			8位无符号定点数据乘累加或乘累减。

	参数:		p_u32Src1 -- 源操作数1，对应Rm。
					p_u32Src2 -- 源操作数2，对应Rn。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_bolIsAdd -- 累加或累减选择。
					    true -- 乘累加
					    false -- 乘累减

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACQ8(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT128 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, bool p_bolIsAdd); 

/*found*****************************************************************
	函数名：		MACSigmaQ8
	
	对应指令形式: LLOMACCs+=sigma(ORm*ORn(U)); LLOMACCs=sigma(ORm*ORn(U))                
                HLOMACCs+=sigma(ORm*ORn(U)); HLOMACCs=sigma(ORm*ORn(U))

	描述:			将Rm和Rn分别分成4个8bit无符号数据，分别对应相乘相加，并与LLOMACC/LHOMACC相加后再存入到LLOMACC或LHOMACC中。
	          MACC的其它位清零。

	参数:		p_u32Src1 -- 源操作数1，对应Rm。
					p_u32Src2 -- 源操作数2，对应Rn。
					p_pMACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Mode -- 模式选择
						0：LLOMACCs=sigma(ORm*ORn(U))
						1：LHOMACCs=sigma(ORm*ORn(U))
						2：LLOMACCs+=sigma(ORm*ORn(U))
						3：LHOMACCs+=sigma(ORm*ORn(U))
	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACSigmaQ8(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT128 *p_pMACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32Mode); 

/*found*****************************************************************
	函数名：		MACCToQ8
	
	对应指令形式: ORs=OMACCn(U,cut=C)
                ORs=OMACCn(cut=C)

	描述:				乘累加结果寄存器MACC截位输出为4个8位定点数据。

	参数:				DSP_BIT80 -- 80位MACC。
							p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
							p_u32MULCR -- 乘法器控制寄存器。
							p_intCutPos -- 截位信息。
							p_bolUseCutPos -- 截位信号选择。
							    true: 使用p_intCutPos作为截位信号；
					  			false：使用p_u32MULCR中的截位信号。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位；
							根据p_bolUseCutPos选择截位信号来源。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern DSPU32 MACCToQ8(const DSP_BIT128 &p_u128MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, int p_intCutPos, bool p_bolUseCutPos);

/*found*****************************************************************
	函数名：		HMACCTo32
	
	对应指令形式: Rs=LHMACCn(U,cut=C)
	              Rs=LHMACCn(cut=C)
                Rs=HHMACCn(U,cut=C)                
                Rs=HHMACCn(cut=C)

	描述:				将累加结果寄存器MACC[39:0]或MACC[79:40]按照截位控制截位后输出至目的寄存器Rs，

	参数:				DSP_BIT80 -- 80位MACC。
							p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
							p_u32MULCR -- 乘法器控制寄存器，其第0位被算法库扩展用于表示源操作数是否为有符号数。
					        p_u32MULCR[0] == 1： 源操作数为有符号数
					        p_u32MULCR[0] == 0： 源操作数为无符号数
							p_bolIsHigh -- MACC高低位选择
							    true -- 将MACC[79:40]按照截位控制截位后输出
							    false -- 将MACC[39:0]按照截位控制截位后输出
							p_intCutPos -- 截位信息。
							p_bolUseCutPos -- 截位信号选择。
							    true: 使用p_intCutPos作为截位信号；
					  			false：使用p_u32MULCR中的截位信号。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位；
							根据p_bolUseCutPos选择截位信号来源。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern DSPU32 HMACCTo32(const DSP_BIT80 &p_u80MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, bool p_bolIsHigh, int p_intCutPos, bool p_bolUseCutPos);

/*found*****************************************************************
	函数名：		OMACCToD16
	
	对应指令形式: HRs=HOMACCn(U,cut=C)
                HRs=LOMACCn(U,cut=C)

	描述:				将累加结果寄存器MACC[79:60]、MACC[59:40](或MACC[39:20]、MACC[19:0])分别按照截位控制截位后输出至目的寄存器Rs[31:16]和Rs[15:0]，
	            如果不满16位则高位补零，如果截取后超过16位，则进行饱和处理，并对溢出标志位置位，

	参数:				DSP_BIT80 -- 80位MACC。
							p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
							p_u32MULCR -- 乘法器控制寄存器。
							p_bolIsHigh -- MACC高低位选择
							    true -- 将MACC[79:60]、MACC[59:40]按照截位控制截位后输出
							    false -- 将MACC[39:20]、MACC[19:0]按照截位控制截位后输出
							p_intCutPos -- 截位信息。
							p_bolUseCutPos -- 截位信号选择。
							    true: 使用p_intCutPos作为截位信号；
					  			false：使用p_u32MULCR中的截位信号。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位；
							根据p_bolUseCutPos选择截位信号来源。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern DSPU32 OMACCToD16(const DSP_BIT128 &p_u128MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, bool p_bolIsHigh, int p_intCutPos, bool p_bolUseCutPos);

/*found*****************************************************************
	函数名：		OMACCTo32
	
	对应指令形式: Rs=LLOMACCn(U,cut=C)
                Rs=LHOMACCn(U,cut=C)
                Rs=HLOMACCn(U,cut=C)
                Rs=HHOMACCn(U,cut=C)

	描述:				将累加结果寄存器MACC[19:0]或MACC[39:20]或MACC[59:40]或MACC[79:60]按照截位控制截位后输出至目的寄存器Rs，如果不满32位，则高位补零。

	参数:				DSP_BIT80 -- 80位MACC。
							p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
							p_u32MULCR -- 乘法器控制寄存器。
							p_u32PartSel -- 源操作数位置选择
							    0 -- 将MACC[19:0]按照截位控制截位后输出
							    1 -- 将MACC[39:20]按照截位控制截位后输出
							    2 -- 将MACC[59:40]按照截位控制截位后输出
							    3 -- 将MACC[79:60]按照截位控制截位后输出
							p_intCutPos -- 截位信息。
							p_bolUseCutPos -- 截位信号选择。
							    true: 使用p_intCutPos作为截位信号；
					  			false：使用p_u32MULCR中的截位信号。

	返回值：		计算结果。

	注意事项:		根据计算结果设置相关标志位；
							根据p_bolUseCutPos选择截位信号来源。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern DSPU32 OMACCTo32(const DSP_BIT128 &p_u128MACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, DSPU32 p_u32PartSel, int p_intCutPos, bool p_bolUseCutPos);


/*found*****************************************************************
	函数名：		MACC16MFix8
	
	对应指令形式: CHMACCs=CHRm*LLORn
                CHMACCs=CHRm*HLORn
                CHMACCs=CHRm*LHORn
                CHMACCs=CHRm*HHORn
                CHMACCs+=CHRm*LLORn
                CHMACCs+=CHRm*HLORn
                CHMACCs+=CHRm*LHORn
                CHMACCs+=CHRm*HHORn

	描述:			16位定点复数和8位实数的乘法累加，占用一个乘法器，乘法结果输出实部/虚部到MACCs。

	参数:		p_u32Rm -- 16位定点复数，对应Rm。
					p_u32Rn -- 16位定点复数2，对应Rn。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Mode -- 模式选择。
							0 -- CHMACCs+=CHRm*LLORn
							1 -- CHMACCs+=CHRm*HLORn
							2 -- CHMACCs+=CHRm*LHORn
							3 -- CHMACCs+=CHRm*HHORn

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACC16MFix8(DSPU32 p_u32Rm, DSPU32 p_u32Rn, DSP_BIT80 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32Mode);

/*found*****************************************************************
	函数名：		MACNegC16MFix8
	
	对应指令形式: CHMACCs-=CHRm*LLORn
                CHMACCs-=CHRm*HLORn
                CHMACCs-=CHRm*LHORn
                CHMACCs-=CHRm*HHORn

	描述:			16位定点复数和8位实数的乘法累减，占用一个乘法器，乘法结果输出实部/虚部到MACCs。

	参数:		p_u32Rm -- 16位定点复数，对应Rm。
					p_u32Rn -- 16位定点复数2，对应Rn。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Mode -- 模式选择。
							0 -- CHMACCs-=CHRm*LLORn
							1 -- CHMACCs-=CHRm*HLORn
							2 -- CHMACCs-=CHRm*LHORn
							3 -- CHMACCs-=CHRm*HHORn

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACNegC16MFix8(DSPU32 p_u32Rm, DSPU32 p_u32Rn, DSP_BIT80 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32Mode);

/*found*****************************************************************
	函数名：		LoadMACCD32
	
	对应指令形式: HMACCs=DRm(C)(z,s,p)

	描述:			将寄存器Rm中的32位数据同时存入MACC的高低40位，起始位置为c和c+40。

	参数:		DSP_BIT80 -- 80位MACC。
					p_u32Src -- 源操作数，对应Rm。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Pos -- 放置起始位置，对应c。
					p_u32Mode -- 模式选择
					    0 -- 对于MACC中的其他位，高低位均补零，对应后缀z
					    1 -- 对于MACC中的其他位，高位进行符号位扩展，低位补零，对应后缀s
					    2 -- 对于MACC中的其他位，保持原值，对应后缀p

	返回值：		

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void LoadMACCD32(DSP_BIT80 &p_u80MACC, DSPU32 p_u32Src, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, DSPU32 p_u32Pos, DSPU32 p_u32Mode,  bool p_bolUseCutPos);

/*found*****************************************************************
	函数名：		LoadMACCQ8
	
	对应指令形式: OMACCs=ORm(C)(z,s,p) (U) 

	描述:			将寄存器Rm分成4个8位数，分别对应存入MACC的4个20位数据段。放置起始位置为c、c+20、c+40、c+60，
	          具体位置为[(7+c):c]、[(27+c):c+20]、[(47+c):c+40]、[(67+c):c+60]。

	参数:		DSP_BIT80 -- 80位MACC。
					p_u32Src -- 源操作数，对应Rm。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。
					p_u32Pos -- 放置起始位置，对应c。
					p_u32Mode -- 模式选择
					    0 -- 对于MACC中的其他位，高低位均补零，对应后缀z
					    1 -- 对于MACC中的其他位，高位进行符号位扩展，低位补零，对应后缀s
					    2 -- 对于MACC中的其他位，保持原值，对应后缀p

	返回值：		

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void LoadMACCQ8(DSP_BIT128 &p_u128MACC, DSPU32 p_u32Src, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, DSPU32 p_u32Pos, DSPU32 p_u32Mode,  bool p_bolUseCutPos);


/******************************************************************
	函数名：		MACC8

	描述:			COMACCs=CORm*CORn
					COMACCs+=CORm*CORn
					8位定点复数乘累加。

	参数:			p_u32Src1 -- Rm。
					p_u32Src2 -- Rn。
					p_pACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器。

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void MACC8(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT128 *p_pACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR);


/******************************************************************
	函数名：	  MulDF64

	对应指令形式: QMACCH=DFRm+1:m*DFRn+1:n
								QMACCL=DFRm+1:m*DFRn+1:n

	描述:		两个64位浮点数相乘。该指令用到四个乘法器，具体见指令集20130904版本。

	参数:		
					p_u80MACC -- 80位MACC结果。
					p_u64Src1 -- 高32位为Rm+1,低32位为Rm。
					p_u64Src2 -- 高32位为Rn+1,低32位为Rn。
					MULIdx -- 乘法器索引号，与结果相对应。如MULIdx=0，则输出的MACC为MUL0的MACC结果。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0，四个乘法器的标志寄存器结果一样。	
					p_u32MULCR -- 乘法器控制寄存器，四个乘法器的控制寄存器值一样。
					

	返回值：		无。

	注意事项:		根据计算结果设置标志寄存器中的相关标志位；					

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern void MulDF64(DSP_BIT80 &p_u80MACC, DSP_BIT64 p_u64Src1, DSP_BIT64 p_u64Src2, DSPU32 MULIdx, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR);

/******************************************************************
	函数名：	  QMACCToDF64

	对应指令形式: DFRs+1:s=QMACCH
								DFRs+1:s=QMACCL

	描述:		取出2个64位浮点数相乘的结果，存放于Rs+1和Rs中。该指令与QMACCH=DFRm+1:m*DFRn+1:n	QMACCL=DFRm+1:m*DFRn+1:n配对使用，用到四个乘法器，具体见指令集20130904版本。

	参数:		
					p_u64Res -- 输出的结果，高32位对应指令的Rs+1，低32位对应指令的Rs。
					p_u80MACC0 -- 该指令用到的第0个乘法器的MACC。
					p_u80MACC1 -- 该指令用到的第1个乘法器的MACC。
					p_u80MACC2 -- 该指令用到的第2个乘法器的MACC。
					p_u80MACC3 -- 该指令用到的第3个乘法器的MACC。		
					p_pStatReg0 -- 乘法器0的标志寄存器结果,指向标志寄存器输出缓存的指针，所指内存区域初始为0。	
					p_pStatReg1 -- 乘法器1的标志寄存器结果,指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_pStatReg2 -- 乘法器2的标志寄存器结果,指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_pStatReg3 -- 乘法器3的标志寄存器结果,指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器，四个乘法器的控制寄存器值一样。
					

	返回值：		无。

	注意事项:		根据计算结果设置标志寄存器中的相关标志位；					

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern void QMACCToDF64(DSP_BIT64 &p_u64Res, DSP_BIT80 p_u80MACC0, DSP_BIT80 p_u80MACC1, DSP_BIT80 p_u80MACC2, DSP_BIT80 p_u80MACC3, DSPU32 *p_pStatReg0, DSPU32 *p_pStatReg1, DSPU32 *p_pStatReg2, DSPU32 *p_pStatReg3, DSPU32 p_u32MULCR);

/******************************************************************
	函数名：	  MAC8Mult16

	对应指令形式: 
	OMACC+=ORm*HHRn(U)
	OMACC+=ORm*HHRn

	OMACC+=ORm*LHRn(U)
	OMACC+=ORm*LHRn

	OMACCs=ORm*LHRn(U)
	OMACCs=ORm*LHRn

	OMACC=ORm*HHRn(U)
	OMACC=ORm*HHRn

	描述:		8位数与16位数相加，累加到MACC中。对于向MACC中赋值的指令，先把
	MACC清零，再调用本函数，把数据累加到MACC中。MULCR第[0]位为0时，表示无符号数，
	第[0]位为1时，表示有符号数。p_HLSel为true时，表示8位数据p_u32Src1与p_u32Src2的低16位相乘，
	为false时，表示8位数据p_u32Src1与p_u32Src2的高16位相乘。


	参数:		p_HLSel		p_HLSel为true时，表示8位数据p_u32Src1与p_u32Src2的低16位相乘，
							为false时，表示8位数据p_u32Src1与p_u32Src2的高16位相乘。
				p_u32Src1	代表Rm
				p_u32Src2	代表Rn

	返回值：		无。

	注意事项:		根据计算结果设置标志寄存器中的相关标志位；					

	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern void MACD8Mult16(DSP_BIT128 &p_OMACC, DSPU32 p_u32Src1, DSPU32 p_u32Src2,DSPU32 p_u32MULCR, DSPU32 *p_pStatReg, bool p_HLSel);


/******************************************************************
	函数名：	  MACDC8MultC16

	对应指令形式: 
	COMACC=CORm*CHRn
	COMACC+=CORm*CHRn

	描述:		8位复数与16位复数相加，累加到MACC中。对于向MACC中赋值的指令，先把
				MACC清零，再调用本函数，把数据累加到MACC中。

	参数:		p_u32Src1	代表Rm
				p_u32Src2	代表Rn
	返回值：		无。
	注意事项:		根据计算结果设置标志寄存器中的相关标志位；					
	修改记录
	--------------------------------------
	日期			作者			修改处
	
	*******************************************************************/
extern void MACDC8MultC16(DSP_BIT128 &p_OMACC, DSPU32 p_u32Src1, DSPU32 p_u32Src2,DSPU32 p_u32MULCR, DSPU32 *p_pStatReg);

/******************************************************************
	函数名：	  LoadHOMACC

	对应指令形式: 
	HOMACCs=Rm(C,p)
	HOMACCs=Rm+1:m(C,p)

	描述:		把32位或64位数据存入到MACC[127:64]位中。

	参数:		p_u32Src1	代表Rm
				p_u32Src2	代表Rm+1
				p_u32Pos	立即数截位信息，代表指令中的立即数C
				p_bol32 为true时表示把p_u32Src1放入MACC中，对应HOMACCs=Rm(C,p)
				p_bol32 为false时表示把p_u32Src1、p_u32Src2放入MACC中，
				对应HOMACCs=Rm+1:m(C,p)，其中p_u32Src2放高位,p_u32Src1放低位。

				p_bolUseCutPos为true时，使用p_u32Pos截位信息
				p_bolUseCutPos为false时，使用MULCR中的[24:20]位作为截位信息。
	返回值：		无。
	注意事项:		根据计算结果设置标志寄存器中的相关标志位；
	修改记录
	--------------------------------------
	日期			作者			修改处
	*******************************************************************/
extern void LoadHOMACC(DSP_BIT128 &p_OMACC, DSPU32 p_u32Src1, DSPU32 p_u32Src2,DSPU32 p_u32MULCR, DSPU32 p_u32MULCUTR, DSPU32 *p_pStatReg,DSPU32 p_u32Pos,bool p_bol32,bool p_bolUseCutPos);

/******************************************************************
	函数名：		AMACCF32

	描述:			两个32位浮点数相乘，结果存在40位AMACC中。
	                AMACCs=FRm*FRn

	参数:			p_u32Src1 -- 源操作数Rm。
					p_u32Src2 -- 源操作数Rn。
					p_pAMACC -- 指向80位乘累加结果寄存器的指针。
					p_pStatReg -- 指向标志寄存器输出缓存的指针，所指内存区域初始为0。
					p_u32MULCR -- 乘法器控制寄存器，其中包含有无符号等控制信息。

	返回值：		无。

	注意事项:		根据计算结果设置相关标志位。

	修改记录
	--------------------------------------
	日期			作者			修改处
	
*******************************************************************/
extern void AMACCF32(DSPU32 p_u32Src1, DSPU32 p_u32Src2, DSP_BIT40 *p_pAMACC, DSPU32 *p_pStatReg, DSPU32 p_u32MULCR);

#endif

