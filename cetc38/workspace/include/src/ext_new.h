
#ifndef _EXT_H
#define _EXT_H

bool ext_like_rd_sw_m8_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_like_wr_sw_m8_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_like_rd_dw_m8_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_like_wr_dw_m8_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_like_rd_br_dw_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_like_wr_br_dw_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_rd_sw_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_rd_dw_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_wr_sw_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_wr_dw_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_fext_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_reg_is_fix_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_reg_is_flo32_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_uvw_is_imm_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_cond_to_cpred_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_maxmin_hlacc_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_fix16_is_on_cmp_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_shf_c_add_32_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_shf_64_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_sacc_insert_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_sigma_b1_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_fext_reg_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_like_append_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_compact_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_reg_mask_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_fix_reg_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_double_reg_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_fix_float_reg_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_compact_expand_cors(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_exchange_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_insert_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_ext_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_float64_to_fix(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_fix_to_float64(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_float_fix_c(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_Float32_Add_C_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_set_spec_reg_imm_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);

bool rd_wrt_onestab_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);

bool ext_fext_cores_new_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_like_append_cores_new_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_compact_cores_new_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_compact_expand_cors_new_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_reg_mask_cores_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);

#if 0
bool ext_atom_rd_sw_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_atom_wr_sw_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
//bool ext_fix_reg_cores_new_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
//bool ext_double_reg_cores_new_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
//bool ext_fix_float_reg_cores_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
#endif


bool ext_cmp_acf_reg_cores(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_exchange_cores_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_insert_cores_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_ext_cores_2(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_fext_cores_new(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_like_append_cores_new(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_compact_cores_new(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_fix_reg_cores_new(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_double_reg_cores_new(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ext_compact_expand_cors_new(DSPU32 p_u32IWordLow, DSPU32 p_u32IWordHigh, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);



#endif


