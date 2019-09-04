
#ifndef _NO_CALC_H
#define _NO_CALC_H

bool areg_add_sub_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool like_areg_add_imm_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
//bool id_to_reg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool like_areg_shf_reg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool clr_sf_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase);
bool set_reg_bit_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool clr_reg_bit_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
//bool chg_page_idx_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool like_uvw_is_imm_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool uvw_logical_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool addr_is_uvw_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool like_cmp_and_set_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);



#endif


