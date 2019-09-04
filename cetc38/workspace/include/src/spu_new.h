
#ifndef _SPU_H
#define _SPU_H

bool sin_cos_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool log_abs_f32_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool sqrt_abs_flo32_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool spufr_to_reg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool reg_to_spufr_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool arctg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool set_spec_reg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool read_spec_reg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool cpred_to_reg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool reg_to_cpred_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool save_cpred_bit_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool restore_cpred_bit_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);

bool set_spec_reg_cores_alufr_etc(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool read_spec_reg_cores_alufr_etc(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);

bool wr_spufr_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool rd_spufr_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);


#endif


