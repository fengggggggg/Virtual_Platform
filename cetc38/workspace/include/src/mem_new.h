
#ifndef _MEM_H
#define _MEM_H

bool like_rd_u_dw_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool like_rd_u_sw_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool like_wr_u_dw_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool like_wr_u_sw_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool greg_is_areg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool areg_is_greg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool reg_trans_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ima_sigma_add_32(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ima_sigma_add_64(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool ima_sigma_add_q16(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool imafr_is_reg_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool wr_addr_sw_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);
bool rd_addr_sw_cores(DSPU32 p_u32InstrWord, DSPU32 p_u32SLKIdx, DSPU32 p_u32Slot, DSPU32 p_u32Phase, DSPU32 p_u32JITIdx, DSPU32 p_u32Opcode);


#endif


