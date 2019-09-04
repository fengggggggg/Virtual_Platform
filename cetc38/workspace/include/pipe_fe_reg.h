#ifndef _PIPE_FE_REG_H
#define _PIPE_FE_REG_H

//--------------------------------------------------------------------------
typedef struct PIPE_FE_REG_CONTENT
{
		// the address of the instruction
   	unsigned int  u32_LinePC;

	// nest level
	// 此处即为中断级别+ 1，并非反映目前正在被服务的中断嵌套情况。
	//	range of nest level: 0 ~ 64
	//  0 means normal app and 1 ~ 64 means interrupt. 
	unsigned int  u32_NestLvl;
	// always 16, except in flush condition
	unsigned int  u32_SlotNum;
	// instruction words
	unsigned int  u32_slot[16];
	// first instruction line of ISR
	bool bol_ISRFirstLn;
	// active signal, 1 ~ 7 is valid, 0 means bubble
	unsigned int  u32_SeqCounter;

	struct PIPE_FE2_ACTION_INFO
	{
		// 当前slot(slot0或slot4或slot8或slot12)的指令在FE2是否被处理过
  		bool  bol_SlotDone;
  		// ret指令在FE2进行分支预测的目标地址
		unsigned int  u32_RetBPC;
		// branch predicted taken
		bool bol_BPT;

	} arrFE2ActionInfo[4];  // 分别存储slot0, slot4, slot8, slot12处的分支指令在FE2的执行信息


  // ret指令在FE2进行分支预测的目标地址
	//unsigned int  u32_RetBPC;
	// branch predicted taken
	//bool bol_BPT;
	
	// 当一个指令行中含多个分支指令时，
	// 用于PEX阶段区分是哪一个分支指令执行了分支预测。
	// in current instruction line, 1~16 means which slot was processed in FE2, 
	// 0 means no slot was processed
	//unsigned int  u32_SlotDoInFE2;
	

} PIPE_FE_REG_CONTENT;



#endif
