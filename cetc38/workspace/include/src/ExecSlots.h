
#ifndef _EXEC_SLOTS_H
#define _EXEC_SLOTS_H

inline bool CondPermitted(DSPU32 p_u32SLKIdx)
{
	return (m_arrResSLK[p_u32SLKIdx].bolHoldInfo && !m_arrResSLK[p_u32SLKIdx].cond_do_info.bolNotDo);
}

bool do_slots(unsigned int *p_pSlots, unsigned int *p_pSlotsRes, DSPU32 p_u32LineAddr, DSPU32 p_u32SlotNum, DSPU32 p_u32Phase);
bool IsValidDWI(DSPU32 p_u32IWord0, DSPU32 p_u32IWord1);
bool do_inst(DSPU32 p_u32IWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32LineAddr, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx);
bool do_inst_ext(DSPU32 p_u32IWord0, DSPU32 p_u32IWord1, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx);

#if 0
bool IsExtFirstWord(DSPU32 p_u32IWord);
bool IsExtSecondWord(DSPU32 p_u32IWord);
bool IsInstNoCalc(DSPU32 p_u32IWord);
DSPU32 GetOpcodeExt(DSPU32 p_u32IWord);
DSPU32 GetOpcodeNoCalc(DSPU32 p_u32IWord);
DSPU32 GetOpcode(DSPU32 p_u32IWord);
#endif

#endif


