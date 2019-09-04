#ifndef _PIPE_FE_REG_H
#define _PIPE_FE_REG_H

//--------------------------------------------------------------------------
typedef struct PIPE_FE_REG_CONTENT
{
		// the address of the instruction
   	unsigned int  u32_LinePC;

	// nest level
	// �˴���Ϊ�жϼ���+ 1�����Ƿ�ӳĿǰ���ڱ�������ж�Ƕ�������
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
		// ��ǰslot(slot0��slot4��slot8��slot12)��ָ����FE2�Ƿ񱻴����
  		bool  bol_SlotDone;
  		// retָ����FE2���з�֧Ԥ���Ŀ���ַ
		unsigned int  u32_RetBPC;
		// branch predicted taken
		bool bol_BPT;

	} arrFE2ActionInfo[4];  // �ֱ�洢slot0, slot4, slot8, slot12���ķ�ָ֧����FE2��ִ����Ϣ


  // retָ����FE2���з�֧Ԥ���Ŀ���ַ
	//unsigned int  u32_RetBPC;
	// branch predicted taken
	//bool bol_BPT;
	
	// ��һ��ָ�����к������ָ֧��ʱ��
	// ����PEX�׶���������һ����ָ֧��ִ���˷�֧Ԥ�⡣
	// in current instruction line, 1~16 means which slot was processed in FE2, 
	// 0 means no slot was processed
	//unsigned int  u32_SlotDoInFE2;
	

} PIPE_FE_REG_CONTENT;



#endif
