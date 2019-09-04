
#ifndef _DEFINES_H
#define _DEFINES_H

#define IAB_WIDTH		 26

#define EXCP_INT_LVL     61
#define MAX_INT_LVL      63          // range of INT level is 0 ~ 63

#define BWSIM_PUB_MODE                    // whether this is a publish version
//#define BWSIM_SUPPORT_IO

#define ICMA_TESTING	// Inter-Core Memory Access testing
#define DMAC_TESTING	// DMAC testing mode

#ifndef BWSIM_PUB_MODE
	#define BWSIM_LOG_INFO
	//#define BWSIM_CMP_100_104
	//#define DSP_DBG_COUT
	#define DSP_DBG_CERR
	//#define CMP_WITH_BW100
	//#define DECODER_TESTING    //分配验证开关
	//#define PIPE_FE_TESTING  // IAB发射验证开关

//	#define INTERRUPT_TESTING // 中断验证开关

	#define CUSTOM_ASSERT
//	#define MEM_CE_TESTING

//	#define STALL_REASON_LOG

	#define LOG_STEP_TESTING		// ISSStepCycle
//	#define LOG_PXP
#endif


//#define ECS_LOG2

#define CHG_PAGE_IDX

//#define GPR_FWD

#define NEW_ADD_INSNS

#define ECS_RES_STAT

//#define TEST_FUN_STATUS
#define LIBTEST  //用于算法库标准测试
//#define LIBTESTCODE //用于算法测试的代码覆盖率统计

//=============================
#define IMAFR_RSV_BITS 0xffff9e9eU
//=============================

#define DSP_PROG_ENTRY 0		// the start address of program memory in virtual address space 

enum {
	PHASE_FE = 0, 
	PHASE_DC2, 
	PHASE_DC2_POST, 
	PHASE_DC3,
	PHASE_DC3_POST,
	PHASE_DC4, 
	PHASE_DC4_POST, 
	PHASE_AC, 
	PHASE_AC_POST, 
	PHASE_EX,
	PHASE_WB,
	PHASE_MAX
	};

//-----------------------------------------------------------------------
#define NUM_OF_PAGES		2 // A, B
#define NUM_OF_UNITS                       4          //x, y, z, t
#define NUM_OF_ADDR_UNITS                  3          //U, V, W
#define REG_NUM_OF_UNIT                    64
#define REG_NUM_OF_ADDRUNIT                16
#define ALU_NUM_OF_UNIT                    8
#define MUL_NUM_OF_UNIT                    8  // 4
#define SHF_NUM_OF_UNIT                    4  // 2
#define SPU_NUM_OF_UNIT                    1
#define GP_REG_NUM                         512 // REG_NUM_OF_UNIT * NUM_OF_UNITS * 2(page)

#define MAX_INUM_LINE                      16

// maximum valid parameter after decode should be no more than JIT_MAX_PARA_NUM
#define JIT_MAX_PARA_NUM 15

// size of static link list (attention: one elem is reserved for the head of SLK)
// GRQ: 3 or 4? 3 isn't enough.
// for example, after one cycle, DC/AC, AC/EX, EX/WB are all full, then in next cycle, SLK will be not enough for malloc.
// attention that in one cycle, free action is after malloc action.
// DC1/DC2, DC2/DC3, DC3/DC, DC/AC, AC/EX, EX/WB
#define RES_SLK_SIZE          (7 * MAX_INUM_LINE + 1)

// eg.   cfr1:0_3:2 = cfr1:0 +/- cfr3:2
#define HZD_GEN_BUFF_LEN			16
//#define HZD_ADDR_BUFF_LEN			8

#define BLK_NUM_PERCORE      6
#define BANK_NUM_PERBLK      8

#define BANK_DEPTH		4
//-----------------------------------------------------------------------
// valid bits mask  (exclude software exception)
#define    ILAT_BIT_MASK                    0x1FBFFF00FF00C07C
#define    ICTLR_BIT_MASK                   0x103C000000000000

#define	MAX_EVT_NUM 		128
#define	INT_SRC_REG_START	0xE01141U
#define	INT_SRC_REG_END		0xE0115FU
#define	INT_SRC_MASK		0x7F007FU

#define SRAM_START_ADDR		0xE20000

//-----------------------------------------------------------------------
#define GRP0_SPEC_REG_GADDR 0x00E00000
#define GRP1_SPEC_REG_GADDR 0x00E01000
#define GRP2_SPEC_REG_GADDR 0x00E0b800
#define ALUCR_GADDR     0x00E00000
#define SPUCR_GADDR		0x00E002C0
#define SHFCR_GADDR		0x00E00200
#define MULCR_GADDR		0x00E00300
#define GPLYR_GADDR     0x00E00260    //伽罗华系数
#define INT_GADDR		0x00E01000
#define INTR_GADDR		0x00E01080
#define IINTN_Rx_GADDR  0x00E0110C 

#define UVW_GADDR       0x00E00B00
#define PIPEREG_GADDR   0x00E00B80
#define SACC_GADDR      0x00E00240
#define MACC_GADDR      0x00E0032C
#define SHFTABX0_GADDR    0x00E02000
#define SHFTABX1_GADDR    0x00E02400
#define SHFTABX2_GADDR    0x00E02800
#define SHFTABX3_GADDR    0x00E02C00
#define SHFTABY0_GADDR    0x00E03000
#define SHFTABY1_GADDR    0x00E03400
#define SHFTABY2_GADDR    0x00E03800
#define SHFTABY3_GADDR    0x00E03C00
#define SHFTABZ0_GADDR    0x00E04000
#define SHFTABZ1_GADDR    0x00E04400
#define SHFTABZ2_GADDR    0x00E04800
#define SHFTABZ3_GADDR    0x00E04C00
#define SHFTABT0_GADDR    0x00E05000
#define SHFTABT1_GADDR    0x00E05400
#define SHFTABT2_GADDR    0x00E05800
#define SHFTABT3_GADDR    0x00E05C00

// 以下[addr]型寄存器以内存方式实现
#define ALUFAR_GADDR    0x00E00004
#define ALUFOR_GADDR    0x00E00008
#define ALUCPred_GADDR  0x00E00130
#define SHFFAR_GADDR    0x00E00204
#define SHFFOR_GADDR    0x00E00208
#define SHFCUTR_GADDR   0x00E00274
#define MULFAR_GADDR    0x00E00304
#define MULFOR_GADDR    0x00E00308
#define MULCUTR_GADDR   0x00E003ac


//-----------------------------------------------------------------------
// shared program memory
#define    SHARED_PROG_MEM_SIZE    0x200000
#define SHARED_PROG_LOW_ADDR       0                     
#define SHARED_PROG_HIGH_ADDR      0x17FFF

// cache memory address in SRAM mode
#define CACHE_RAM_LOW_ADDR       0x00E0A000
#define CACHE_RAM_HIGH_ADDR       0x00E1FFFF

#define INNER_DATA_BLK_SIZE  0x40000
#define BLK0_LOW_ADDR        0x200000       // Data memory 0
#define BLK0_HIGH_ADDR       0x23FFFF
#define BLK1_LOW_ADDR        0x400000       // Data memory 1
#define BLK1_HIGH_ADDR       0x43FFFF
#define BLK2_LOW_ADDR        0x600000       // Data memory 2
#define BLK2_HIGH_ADDR       0x63FFFF
#define BLK3_LOW_ADDR        0x800000       // Data memory 3
#define BLK3_HIGH_ADDR       0x83FFFF
#define BLK4_LOW_ADDR        0xA00000       // Data memory 4
#define BLK4_HIGH_ADDR       0xA3FFFF
#define BLK5_LOW_ADDR        0xC00000       // Data memory 5
#define BLK5_HIGH_ADDR       0xC3FFFF


// below are to be update
#define MMR_LOW_ADDR         0x7F0000       // Memory map regs
#define MMR_HIGH_ADDR        0x7FFFFF
#define GRMM_LOW_ADDR        0x00E00800    // General purpose memory map regs
#define GRMM_HIGH_ADDR       0x00E009FF
//#define DMA_REGS_BASE_ADDR   0x1201180

// Local Timer Regs
#define LOCAL_TIMER_ADDR		0xE30A00
#define LOCAL_TIMER_OFFSET		0x16

#define DMAC_REG_START		0xE01200
#define DMAC_REG_LAST		0xE0133F
#define DMAC_REG_END		0xE017FF

//-----------------------opcode in C-----------------------
#define    op_add_32_c				0		//0		//0
#define    op_sub_32_c				1       //1
#define    op_add_16_c				2       //2
#define    op_sub_16_c				3		//3		//3
#define    op_addhalf_32_c			4		//4		//6
#define    op_subhalf_32_c			5		//5		//7
#define    op_addhalf_16_c			6		//6		//8
#define    op_subhalf_16_c			7		//7		//9
#define    op_c_add_16_c            8		//12		//34
#define    op_c_sub_16_c            9		//13		//35
#define    op_cj_add_16_c           10	//14		//38
#define    op_cj_sub_16_c           11	//15		//39
#define    op_cj_addhalf_16_c       12	//18	//50
#define    op_cj_subhalf_16_c       13	//19	//51
#define    op_add_8_c				14
#define	   op_sub_8_c				15
#define    op_add_flo32_c           16	//8		//16
#define    op_sub_flo32_c           17	//9		//17
#define    op_addhalf_flo32_c       18	//10  	//19
#define    op_subhalf_flo32_c       19	//11 	//20
#define    op_add_32_u_c			20	//20	//104
#define    op_sub_32_u_c			21	//21	//105
#define    op_add_16_u_c			22	//22		//106
#define    op_sub_16_u_c			23	//23		//107
#define    op_addhalf_32_u_c		24	//24		//108
#define    op_subhalf_32_u_c		25	//25		//109
#define    op_addhalf_16_u_c		26	//26		//110
#define    op_subhalf_16_u_c		27	//27		//111
#define   op_add_q8_c               28	//28
#define   op_sub_q8_c               29	//29
#define   op_add_abs_32_c           30	//30
#define   op_add_abs_f32_c          31	//31
#define    op_max_32_c              32	//33		//192
#define    op_max_16_c              33	//34		//193
#define    op_max_flo32_c           34	//35		//194
#define    op_min_32_c              35	//36		//195
#define    op_min_16_c              36	//37		//196
#define    op_min_flo32_c           37	//38		//197
#define    op_max_32_u_c            38	//39		//215
#define    op_max_16_u_c            39	//40		//216
#define    op_min_32_u_c            40	//41		//217
#define    op_min_16_u_c            41	//42		//218

#define    op_inc_imm_u_c           42	//43      //112
#define    op_dec_imm_u_c	        43	//44      //113
#define    op_inc_imm_c             44	//45      //11
#define    op_dec_imm_c	            45	//46      //12

#define    op_hl_add_sub_c          46	//47      //15
#define    op_max_min_hlreg_c       47	//48     //204


#define    op_shf_add_8_c           48


#define    op_c_add_32_c            49	//49     //32
#define    op_c_sub_32_c            50	//50     //33
#define    op_cj_add_32_c           51	//51     //36
#define    op_cj_sub_32_c           52	//52     //37
#define    op_c_addhalf_32_c        53	//53    //44
#define    op_c_subhalf_32_c        54	//54    //45
#define    op_cj_addhalf_32_c       55	//55    //48
#define    op_cj_subhalf_32_c       56	//56     //49
#define    op_c_add_flo32_c         57	//57     //52
#define    op_c_sub_flo32_c         58	//58     //53
#define    op_cj_add_flo32_c        59	//59     //54
#define    op_cj_sub_flo32_c        60	//60     //55
#define    op_c_addhalf_flo32_c     61	//61   //58
#define    op_c_subhalf_flo32_c     62	//62   //59
#define    op_cj_addhalf_flo32_c    63	//63    //60
#define    op_cj_subhalf_flo32_c    64	//64    //61
#define    op_max_min_32_c          65	//65    //198
#define    op_max_min_16_c          66	//66    //199
#define    op_max_min_flo32_c       67	//67    //200
#define    op_max_min_32_u_c        68	//68    //219
#define    op_max_min_16_u_c        69	//69    //220

#define    op_max_min_mn_c          70	//70    //201
#define    op_conj_c32_c            71	//71   //172

#define    op_like_addsub_32_c      72	//73   //4, 5, 18, 41, 43
#define    op_like_c_addsub_32_c    73	//74   //40, 42, 56, 57
#define	   op_oacc_8_c				74

#define    op_accum_32_c            75	//75  //26
#define    op_accum_16_c            76	//76  //27
#define    op_accum_32_u_c          77	//77 //102
#define    op_accum_16_u_c          78	//78 //103
#define    op_acc_add_q8_c          79	//79
#define    op_accum_flo32_c         80	//80 //28



#define    op_shf_add_8_u_c         81
#define	op_ht_c			82
#define	op_he_c			83
#define	   op_alu_sub16_to_32_c   84
#define	   op_alu_sub16_to_32_u_c   85
#define	   op_alu_sub8_to_16_c   86
#define	op_expand_c		87

#define    op_acf_is_ht_32_c        88	//88
#define    op_acf_is_ht_d16_c       89	//89
#define    op_acf_is_ht_f32_c       90	//90
#define    op_acc_addsub_d16_c      91	//91
#define    op_add_32_ca_c           92	//92
#define    op_acc_max_fix32_c       93	//93
#define    op_acc_max_4fix16_c      94	//94
#define    op_acc_max_reg_acc_c     95	//95

#define    op_acc_maxr_2fix32_MN_c  96
#define    op_acc_maxr_2fix16_c     97	//97
#define    op_acc_maxr_reg_acc_c    98	//98
#define    op_acc_fix16_manh_c      99	//99
#define    op_ht_hlreg_tohl_c       100	//100 //213, 214
#define    op_he_hlreg_tohl_c       101	//101 //211, 212
#define    op_is_eq_16_sz_c         102	//102
#define    op_reg_shf_acf_c         103	//103
#define    op_reg_is_acc_c          104	//104 //22, 23, 24

#define    op_rd_wr_acc_c		    105 //14
#define	op_sar_cpred_bit_c	106


#define    op_shf_add_16_c          107


#define    op_accum_c32_c           108	//108 //30
#define    op_accum_cflo32_c        109	//109 //31
#define    op_like_acc_is_zero_c    110	//110 //25, 63


#define    op_shf_add_16_u_c        111


#define    op_mul_32_c              112	//112 //64
#define    op_mul_32_u_c            113	//113 //100
#define    op_mul_16_c              114	//114 //65
#define    op_mul_16_u_c            115	//115 //101
#define    op_mul_flo32_c           116	//116 //66
#define    op_mul_s16_ll_c          117	//117
#define    op_mul_s16_HH_c          118	//118
#define    op_mul_s16_lH_c          119	//119
#define	   op_mul_c16_h16_c         120	//120 //68
#define	   op_mul_c16_l16_c         121	//121 //69
#define    op_mul_c16_c             122	//122 //74
#define    op_mul_c16_conj_c        123	//123 //75
#define	   op_mul_c16conj_c         124	//124 //76
#define    op_square_hl16_c         125	//125 //91
#define    op_mul_c32_32_c          126	//126 //67
#define    op_mul_cflo32_flo32_c    127	//127 //70
#define    op_square_32_c           128	//144 //90
#define    op_square_32_u_c         129	//145 //97
#define    op_mul_c32_c             130	//128 //71
#define	   op_mul_c32_conj_c        131	//129 //72
#define	   op_mul_c32conj_c         132	//130 //73
#define	   op_mul_cf32_etc_c        133	//131 //77, 80, 81, 93, 95, 83
#define    op_like_mulacc_32_c      134	//132 //84, 86
#define    op_like_mulacc_16_c      135	//133 //85, 87
#define    op_mulacc_8_etc_c        136	//134

#define		op_dfmul_c		        137 

#define    op_macc_c16_etc_c        138		//135 //92, 94
#define    op_mac_c16_m_fix8_c      139	//136
#define    op_mac_is_reg_etc_c      140	//137
#define    op_hmac_is_reg_etc_c     141	//138
#define    op_reg_is_macc_etc_c     142	//139 //88, 89
#define    op_hmacc_to_32_c         143	//140
#define    op_omacc_to_32_etc_c     144	//141
#define    op_mul_c8_16_c          145	//142 //99
#define    op_mulfr_to_reg_c        146	//143 //79
#define	   op_alu_sub8_to_16_u_c			147

#define    op_shiftr_32_c            148	//146 //128
#define	   op_arshift_32_c			 149
#define    op_shift0_32_c            150	//147 //129
#define	   op_lrshift_32_c			 151
#define    op_rot_32_c               152	//148 //130
#define	   op_rrot_32_c				 153
#define    op_shiftr_c16_c           154	//149 //132
#define    op_shift1_32_c            155	//150 //151
#define    op_minv_32_c              156	//151 //152
#define    op_mclr_32_c              157	//152 //154
#define    op_mset_32_c              158	//153 //155
#define    op_lxor_32_c              159	//154 //156
#define    op_rxor_32_c              160	//155 //157
#define    op_count0_32_c            161	//156 //170 (ALU)
#define    op_count0_16_c            162	//157 //171 (ALU)-
#define    op_onecount_reg_c         163	//158 //175 (ALU)
#define    op_onecount_hreg_c        164	//159 //176 (ALU)
#define    op_oneposi_reg_c          165	//160 //178 (ALU)
#define    op_oneposi_hreg_c         166	//161 //179 (ALU)
#define    op_and_32_c               167	//162 //182 (ALU)
#define    op_or_32_c                168	//163 //183 (ALU)
#define    op_nand_32_c              169	//164 //184 (ALU)
#define    op_nor_32_c               170	//165 //185 (ALU)
#define    op_xor_32_c               171	//166 //186 (ALU)
#define    op_not_32_c               172	//167 //187 (ALU)
#define    op_jlh_32_c               173	//168
#define    op_jlh_d16_c              174	//169
#define    op_jlh_q8_c                  175	//170
#define    op_shiftr_32_imm_c           176	//171 //133
#define    op_shift1_32_imm_c           177	//172 //134
#define    op_shift0_32_imm_c           178	//173 //135
#define    op_rot_32_imm_c              179	//174 //136
#define    op_expan_hhreg_etc_c         180	//175 // 138, 140, 141, 143, 145, 146
#define    op_cpat_creg_imm_c           181	//176 //144
#define    op_bclr_32_c                 182	//177 //148
#define    op_bset_32_c                 183	//178 //149
#define    op_binv_32_c                 184	//179 //150
#define    op_exp_is_imm_c              185	//180 //161
#define    op_like_h16_to_f32_c         186	//181 //167(ALU), 168(ALU)
#define    op_abs_c						187	//182 //13(ALU)
#define    op_conj_c16_c                188	//183 //173(ALU)
#define    op_oneposi_imm_c             189	//184 //177(ALU)
#define    op_zerocount_imm_c           190	//185 //180(ALU)
#define    op_onecount_imm_c            191	//186 //181(ALU)

#define    op_like_fix_flo32_c          192	//187 // 188(ALU), 190(ALU)
#define    op_get_exp_mant_c            193	//188 //162
#define    op_expan_chreg_c             194	//214 //142
#define    op_shiftr_c32_imm_c          195	//218 //137

#define    op_sigma_add_q16             196

#define    op_insert_to_sacc_c          197	//190
#define		op_abs2_sacc_c		198
#define		op_abs3_sacc_c		199
#define		op_sacc_xor_c		200

#define		op_sigma_b1_to_sacc_c		201
#define		op_sigma_b2_to_sacc_c		202
#define		op_sigma_b4h_to_sacc_c		203
#define		op_sigma_b4l_to_sacc_c		204
#define		op_sigma_b1_add_sacc_c		205
#define		op_sigma_b2_add_sacc_c		206
#define		op_sigma_b4h_add_sacc_c	    207
#define		op_sigma_b4l_add_sacc_c		208

#define		op_tab_to_reg_c	209
#define		op_tab_to_horeg_c	210
#define		op_reg_to_tab_c		211
#define		op_horeg_to_tab_c	212
#define		op_otab_add_const_c	213
#define		op_shift_sc_c		214
#define		op_vmin_c			215

#define     op_stab_add_c       216

#define		op_sigma_sc_c				 217
#define    op_shiftr_c32_c               218	//213 //131

#define    op_cpat_creg_c                219	//215 //147
#define    op_lxor_d32_c                 220	//216 //158
#define    op_rxor_d32_c                 221	//217 //159
#define    op_sin_cos_c          222	//74  // to sync
#define	op_arctg_c		223
#define    op_wr_addr_sw_c            224	//223 // 116, 117, 118
#define    op_rd_addr_sw_c		225	//227 //126, 127
#define    op_rd_u_dw_c            226	//228
#define    op_rd_u_sw_c            227	//229
#define    op_rd_u_dw_base_off_c   228	//230
#define    op_rd_u_sw_base_off_c   229	//231
#define    op_rd_v_dw_c            230	//232
#define    op_rd_v_sw_c            231	//233
#define    op_rd_v_dw_base_off_c   232	//234
#define    op_rd_v_sw_base_off_c   233	//235
#define    op_rd_w_dw_c            234	//236
#define    op_rd_w_sw_c            235	//237
#define    op_rd_w_dw_base_off_c   236	//238
#define    op_rd_w_sw_base_off_c   237	//239
#define    op_wr_u_dw_c            238	//240
#define    op_wr_u_sw_c            239	//241
#define    op_wr_u_dw_base_off_c   240	//242
#define    op_wr_u_sw_base_off_c   241	//243
#define    op_wr_v_dw_c            242	//244
#define    op_wr_v_sw_c            243	//245
#define    op_wr_v_dw_base_off_c   244	//246
#define    op_wr_v_sw_base_off_c   245	//247
#define    op_wr_w_dw_c            246	//248
#define    op_wr_w_sw_c            247	//249
#define    op_wr_w_dw_base_off_c   248	//250
#define    op_wr_w_sw_base_off_c   249	//251
#define    op_greg_is_areg_etc_c        250	//252 // 248, 249

#define    op_reg_trans_cores_c         251	//253 // 254, 255
#define    op_dreg_trans_cores_c        252
#define    op_sigma_reg_etc_cores_c     253

#define    op_set_spec_reg_c            254	//254 //165
#define    op_read_spec_reg_c           255	//255 //166

//-----------------------------------------------------------
// double words instruction below
#define    op_ext_sw_m8_etc_c          0 // 4, 5, new
#define    op_ext_br_dw_etc_c          1 // 9, 10, new
#define    op_ext_rd_sw_etc_c          2 // 11, 12, 13, 14, new
#define    op_ext_shf_64_etc_c         3 // 3, new
#define    op_dw_fext_ext_etc_c	       4
#define    op_ext_fext_etc_c           5
#define    op_ext_b_cmp_etc_c          6 // 6, new
#define    op_ext_b_on_bit_etc_c       7
#define    op_ext_cond_do_etc_c    8
#define    op_ext_bn_on_u_cmp_c        9
#define    op_ext_bn_on_v_cmp_c        10
#define    op_ext_bn_on_w_cmp_c        11
#define    op_ext_reg_is_fix_etc_c     12 // 7
#define    op_ext_maxmin_hlacc_etc_c   13
#define    op_ext_b_lbl_etc_c          14 // 16, 17, 21, 26, new
#define    op_ext_shf_c_add_32_c       15
//-----------------------------------------------------------
// no calc instruction below
#define    op_areg_add_sub_c        1	//1
#define    op_areg_add_imm_c        2	//2 //5
#define    op_areg_shf_imm_c        3	//3 //6
#define    op_areg_shf_reg_c        4	//4 //7
#define    op_areg_cb_reg_c         5	//5
#define    op_areg_abs_sub_c        6	//6
#define    op_padding_c         7	//7 // frm LG
#define    op_nop_c                 8	//8 //2
#define    op_idle_c                9	//9 //3
#define    op_id_to_reg_c           10

#define	op_swi_c		11

#define    op_clr_sf_c              12	//12 //8

#define    op_b_reg_c               15	//15 //20
#define    op_call_reg_c            16	//16 //15
#define    op_ret_c                 17	//17 //18
#define    op_iret_c                18	//18 //19
#define    op_strap_c               19	//19 //22  // GRQ: todo strap n
#define    op_etrap_c               20	//20 //23
#define    op_rtrap_c               21	//21 //25

#define	op_u_is_imm_c	23
#define	op_v_is_imm_c	24
#define	op_w_is_imm_c	25

#define	op_bn_label_c		26

#define	op_uvw_logical_c	27
#define	op_addr_is_uvw_c	28
#define	op_cmp_and_set_u_c	29
#define	op_cmp_and_set_v_c	30
#define	op_cmp_and_set_w_c	31


//------------------------opcode in lisa------------------------
#define    op_add_32				0b00000000 //0		//0
#define    op_sub_32				0b00000001 //1		//1
#define    op_add_16				0b00000010 //2		//2
#define    op_sub_16				0b00000011 //3		//3
#define    op_addhalf_32			0b00000100 //4		//6
#define    op_subhalf_32			0b00000101 //5		//7
#define    op_addhalf_16			0b00000110 //6		//8
#define    op_subhalf_16			0b00000111 //7		//9

#define    op_c_add_16              0b00001000 //8		//34
#define    op_c_sub_16              0b00001001 //9		//35
#define    op_cj_add_16             0b00001010 //10		//38
#define    op_cj_sub_16             0b00001011 //11		//39
#define    op_c_addhalf_16          0b00001100 //12	//46
#define    op_c_subhalf_16          0b00001101 //13	//47
#define    op_cj_addhalf_16         0b00001110 //14	//50
#define    op_cj_subhalf_16         0b00001111 //15	//51

#define    op_add_flo32             0b00010000 //16		//16
#define    op_sub_flo32             0b00010001 //17		//17
#define    op_addhalf_flo32         0b00010010 //18  	//19
#define    op_subhalf_flo32         0b00010011 //19 	//20

#define    op_add_32_u			    0b00010100 //20	//104
#define    op_sub_32_u			    0b00010101 //21	//105
#define    op_add_16_u			0b00010110 //22		//106
#define    op_sub_16_u			0b00010111 //23		//107
#define    op_addhalf_32_u		0b00011000 //24		//108
#define    op_subhalf_32_u		0b00011001 //25		//109
#define    op_addhalf_16_u		0b00011010 //26		//110
#define    op_subhalf_16_u		0b00011011 //27		//111
#define    op_add_q8            0b00011100 //28
#define    op_sub_q8            0b00011101 //29
#define    op_add_abs_32        0b00011110 //30
#define    op_add_abs_f32       0b00011111 //31

#define    op_max_32            0b00100000 //32		//192
#define    op_max_16            0b00100001 //33		//193
#define    op_max_flo32         0b00100010 //34		//194
#define    op_min_32            0b00100011 //35		//195
#define    op_min_16            0b00100100 //36		//196
#define    op_min_flo32         0b00100101 //37		//197
#define    op_max_32_u          0b00100110 //38		//215
#define    op_max_16_u          0b00100111 //39		//216
#define    op_min_32_u          0b00101000 //40		//217
#define    op_min_16_u          0b00101001 //41		//218
#define    op_inc_imm_u         0b00101010 //42      //112
#define    op_dec_imm_u	        0b00101011 //43      //113
#define    op_inc_imm           0b00101100 //44      //11
#define    op_dec_imm	        0b00101101 //45      //12
#define    op_hl_add_sub        0b00101110 //46      //15
#define    op_max_min_hlreg     0b00101111 //47     //204


#define    op_c_add_32          0b00110001 //49     //32
#define    op_c_sub_32          0b00110010 //50     //33
#define    op_cj_add_32         0b00110011 //51     //36
#define    op_cj_sub_32         0b00110100 //52     //37
#define    op_c_addhalf_32      0b00110101 //53    //44
#define    op_c_subhalf_32      0b00110110 //54    //45
#define    op_cj_addhalf_32     0b00110111 //55    //48
#define    op_cj_subhalf_32     0b00111000 //56     //49
#define    op_c_add_flo32       0b00111001 //57     //52
#define    op_c_sub_flo32       0b00111010 //58     //53
#define    op_cj_add_flo32      0b00111011 //59     //54
#define    op_cj_sub_flo32      0b00111100 //60     //55
#define    op_c_addhalf_flo32   0b00111101 //61   //58
#define    op_c_subhalf_flo32   0b00111110 //62   //59
#define    op_cj_addhalf_flo32  0b00111111 //63    //60
#define    op_cj_subhalf_flo32  0b01000000 //64    //61
#define    op_max_min_32        0b01000001 //65    //198
#define    op_max_min_16        0b01000010 //66    //199
#define    op_max_min_flo32     0b01000011 //67    //200
#define    op_max_min_32_u      0b01000100 //68    //219
#define    op_max_min_16_u      0b01000101 //69    //220
#define    op_max_min_mn        0b01000110 //70    //201
#define    op_conj_c32           0b01000111 //71   //172
//#define    op_conj_cflo32        0b01001000 //72   //174
#define    op_like_addsub_32	 0b01001000	//72 new added by LiuGu
#define    op_like_addsub_64     0b01001001 //73   //new added by LiuGu

//#define    op_like_c_addsub_32   0b01001010 //74   //40, 42, 56, 57 deleted
#define    op_cpred_do_n         0b01001010 //74 new added

#define    op_accum_32           0b01001011 //75  //26
#define    op_accum_16           0b01001100 //76  //27
#define    op_accum_32_u         0b01001101 //77 //102
#define    op_accum_16_u         0b01001110 //78 //103
#define    op_acc_add_q8         0b01001111 //79
#define    op_accum_flo32        0b01010000 //80 //28
#define    op_accum_c16          0b01010001 //81 //29
#define    op_ht_32              0b01010010 //82 //205
#define    op_ht_16              0b01010011 //83 //206
#define    op_ht_flo32           0b01010100 //84 //207
#define    op_he_32              0b01010101 //85 //208
#define    op_he_16              0b01010110 //86 //209
#define    op_he_flo32           0b01010111 //87 //210
#define    op_acf_is_ht_32       0b01011000 //88
#define    op_acf_is_ht_d16      0b01011001 //89
#define    op_acf_is_ht_f32      0b01011010 //90
#define    op_acc_addsub_d16     0b01011011 //91
#define    op_add_32_ca          0b01011100 //92
#define    op_acc_max_fix32      0b01011101 //93
#define    op_acc_max_4fix16     0b01011110 //94
#define    op_acc_max_reg_acc       0b01011111 //95
#define    op_acc_maxr_2fix32_MN    0b01100000 //96
#define    op_acc_maxr_2fix16       0b01100001 //97
#define    op_acc_maxr_reg_acc      0b01100010 //98
#define    op_acc_fix16_manh        0b01100011 //99
#define    op_ht_hlreg_tohl         0b01100100 //100 //213, 214
#define    op_he_hlreg_tohl         0b01100101 //101 //211, 212
#define    op_is_eq_16_sz           0b01100110 //102
#define    op_reg_shf_acf           0b01100111 //103
#define    op_reg_is_acc            0b01101000 //104 //22, 23, 24
//#define    op_con_is                0b01101001 //105 //62
#define    op_rd_wr_acc		    0b01101001 //105 //14
#define	   op_alufr_rd		    0b01101010 //106 //new added at 12-28
#define    op_alufr_wr		    0b01101011 //107 //new added at 12-28

//#define    op_reg_is_alufr          0b01101011 //107 //21
#define    op_accum_c32             0b01101100 //108 //30
#define    op_accum_cflo32          0b01101101 //109 //31
#define    op_like_acc_is_zero      0b01101110 //110 //25, 63
#define    op_rd_wr_bkfr            0b01101111 //111 //10
#define    op_mul_32                0b01110000 //112 //64
#define    op_mul_32_u              0b01110001 //113 //100
#define    op_mul_16                0b01110010 //114 //65
#define    op_mul_16_u              0b01110011 //115 //101
#define    op_mul_flo32             0b01110100 //116 //66
#define    op_mul_s16_ll            0b01110101 //117
#define    op_mul_s16_HH            0b01110110 //118
#define    op_mul_s16_lH            0b01110111 //119
#define	   op_mul_c16_h16           0b01111000 //120 //68
#define	   op_mul_c16_l16           0b01111001 //121 //69
#define    op_mul_c16               0b01111010 //122 //74
#define    op_mul_c16_conj          0b01111011 //123 //75
#define	   op_mul_c16conj           0b01111100 //124 //76
#define    op_square_hl16           0b01111101 //125 //91
#define    op_mul_c32_32            0b01111110 //126 //67
#define    op_mul_cflo32_flo32      0b01111111 //127 //70
#define    op_mul_c32               0b10000010 //130<=128 //71
#define	   op_mul_c32_conj          0b10000011 //131<=129 //72
#define	   op_mul_c32conj           0b10000100 //132<=130 //73
#define	   op_mul_cf32_etc          0b10000101 //133<=131 //77, 80, 81, 93, 95, 83
#define    op_like_mulacc_32        0b10000110 //134<=132 //84, 86
#define    op_like_mulacc_16        0b10000111 //135<=133 //85, 87
#define    op_mulacc_8_etc          0b10001000 //136<=134

#define    op_mul_dfloat64    	    0b10001001	//137<=135 new added

#define    op_macc_c16_etc          0b10001010 //138<=136 //92, 94  //new +1

#define    op_mac_c16_m_fix8        0b10001011 //139<=137 new +1
#define    op_mac_is_reg_etc        0b10001100 //140<=138 new +1
//#define    op_hmac_is_reg_etc      138
#define    op_hmacc_wr		    0b10001101 //141<=139 new added

//#define    op_omacc_wr		    0b10001100 //merged into 137<=140 new added

#define    op_reg_is_macc_etc       0b10001110 //142<=141 //88, 89 new +2
#define    op_hmacc_to_32           0b10001111 //143<=142  new +2
#define    op_omacc_to_32_etc       0b10010000 //144<=143 new +2
#define    op_rd_wr_macc            0b10010001 //145<=144 //99 new +2
#define    op_mulfr_to_reg          0b10010010 //146<=145 //79 new +2

#define    op_square_32             0b10000000 //128<=146 //90 new +2
#define    op_square_32_u           0b10000001 //129<=147 //97 new +2

#define    op_clr_macc		    0b10010011 //147 new added v20130116

//12-28 ends here.Look out the opcode should be added 2

#define    op_shiftr_32             0b10010100 //148 //128
#define    op_arshift_32	    0b10010101 //149  newadded v20130124
#define    op_shift0_32             0b10010110 //150<=149 //129
#define    op_rshift_32		    0b10010111 //151 new added v20130124
#define    op_rot_32                0b10011000 //152<=150 //130
#define    op_rrot_32		    0b10011001 //153 new added v20130124

#define    op_shiftr_c16            0b10011010 //154<=151 //132
#define    op_shift1_32             0b10011011 //155<=152 //151
#define    op_minv_32               0b10011100 //156<=153 //152
#define    op_mclr_32               0b10011101 //157<=154 //154
#define    op_mset_32                    0b10011110 //158<=155 //155
#define    op_lxor_32                    0b10011111 //159<=156 //156
#define    op_rxor_32                    0b10100000 //160<=157 //157
#define    op_count0_32                  0b10100001 //161<=158 //170 (ALU)
#define    op_count0_16                  0b10100010 //162<=159 //171 (ALU)-
#define    op_onecount_reg               0b10100011 //163<=160 //175 (ALU)
#define    op_onecount_hreg              0b10100100 //164<=161 //176 (ALU)
#define    op_oneposi_reg                0b10100101 //165<=162 //178 (ALU)
#define    op_oneposi_hreg               0b10100110 //166<=163 //179 (ALU)
#define    op_and_32                     0b10100111 //167<=164 //182 (ALU)
#define    op_or_32                      0b10101000 //168<=165 //183 (ALU)
#define    op_nand_32                    0b10101001 //169<=166 //184 (ALU)
#define    op_nor_32                     0b10101010 //170<=167 //185 (ALU)
#define    op_xor_32                     0b10101011 //171<=168 //186 (ALU)
#define    op_not_32                     0b10101100 //172<=169 //187 (ALU)
#define    op_jlh_32                     0b10101101 //173<=170
#define    op_jlh_d16                    0b10101110 //174<=171
#define    op_jlh_q8                     0b10101111 //175<=172
#define    op_shiftr_32_imm              0b10110000 //176<=173 //133
#define    op_shift1_32_imm              0b10110001 //177<=174 //134
#define    op_shift0_32_imm              0b10110010 //178<=175 //135
#define    op_rot_32_imm                 0b10110011 //179<=176 //136

#define    op_expan_hhreg_etc            0b10110100 //180<=177 // 138, 140, 141, 143, 145, 146


#define    op_cpat_creg_imm          0b10110101 //181<=178 //144
#define    op_bclr_32                0b10110110 //182<=179 //148
#define    op_bset_32                0b10110111 //183<=180 //149
#define    op_binv_32                0b10111000 //184<=181 //150
#define    op_exp_is_imm             0b10111001 //185<=182 //161

#define    op_like_h16_to_f32        0b10111010 //186<=183 //167(ALU), 168(ALU)
#define    op_abs		     0b10111011 //187<=184 //13(ALU)
#define    op_conj_c16               0b10111100 //188<=185 //173(ALU)
#define    op_oneposi_imm            0b10111101 //189<=186 //177(ALU)
#define    op_zerocount_imm          0b10111110 //190<=187 //180(ALU)
#define    op_onecount_imm           0b10111111 //191<=188 //181(ALU)
#define    op_like_fix_flo32         0b11000000 //192<=189 // 188(ALU), 190(ALU)
#define    op_get_exp_mant           0b11000001 //193<=190 //162

//#define    op_conv_64_to_32	     0b10111111 //191 new added
//#define    op_conv_32_to_64	     0b11000000	//192 new added
#define    op_expan_chreg            0b11000010 //194<=191<=215 //142 modified

#define    op_shiftr_c32_imm         0b11000011 //195<=192<=219 //137 modified

#define    op_expan_chreg_imm        0b11000001 //193<=220 //139 modified
#define    op_like_flo_c32           0b11000010 //194<=221 //189 modified
#define    op_c16_to_cf32            0b11000011 //195<=222 //169 modified



//#define    op_inv0_reg                189 // machine code is error
#define    op_sacc_ins_del	  0b11000101		//197<=193 // frm LG
#define    op_sacc_abs_2k	  0b11000110		//198<=194 // frm LG
#define    op_sacc_abs_3k	  0b11000111		//199<=195 // frm LG
#define    op_sacc_xor_sc	  0b11001000		//200<=196 // frm LG
//#define    op_sacc_reg		  0b11000101		//197 // frm LG
#define    op_sacc_sgm_s	  0b11001001		//201<=198 // frm LG
#define    op_sacc_sgm_b	  0b11001010		//202<=199 // frm LG
#define    op_sacc_sgm_qh	  0b11001011		//203<=200 // frm LG
#define    op_sacc_sgm_ql	  0b11001100		//204<=201 // frm LG
#define    op_sacc_sgm_sp	  0b11001101		//205<=202 // frm LG
#define    op_sacc_sgm_bp	  0b11001110		//206<=203 // frm LG
#define    op_sacc_sgm_qhp	  0b11001111		//207<=204 // frm LG
#define    op_sacc_sgm_qlp	  0b11010000		//208<=205 // frm LG
#define    op_ntabk_32		  0b11010001		//209<=206 // frm LG
#define    op_ntabk_16	 	  0b11010010		//210<=207 // frm LG
#define    op_ntabk_32_r	  0b11010011		//211<=208 // frm LG
#define    op_ntabk_16_r	  0b11010100		//212<=209 // frm LG
#define    op_ntabk_imm		  0b11010101		//213<=210 // frm LG

#define    op_new_211_pack        0b11010110		//214<=211 new added

//#define    op_shift_sck		  0b11010000		//208 // frm LG
//#define    op_sxor_sacc		  0b11010001		//209 // frm LG
//#define    op_starat_sacc	  0b11010010		//210 // frm LG


#define    op_vmin2_3		       	0b11010111 //215<=212// frm LG
#define    op_shffr_to_reg             	0b11011000 //216<=213 //153

#define    op_sacc_sigma		0b11011001 //217 new added v20130125

#define    op_shiftr_c32               	0b11011010 //218<=214 //131




#define    op_cpat_creg                	0b11011011 //219<=216 //147
#define    op_lxor_d32                 	0b11011100 //220<=217 //158
#define    op_rxor_d32                 	0b11011101 //221<=218 //159



#define    op_recip_flo32       0b11011111 //223 //115
#define    op_new_224		0b11100000 //224 new added

//#define    op_sin_cos           0b11011111 //223 // 116, 117, 118
//#define    op_log_abs_f32       0b11100000 //224 //121
//#define    op_sqrt_abs_flo32    0b11100001 //225 //124
//#define    op_spufr_to_reg      0b11100010 //226 //125
#define    op_arctg             0b11100001 //225 //126, 127

#define    op_rd_u_dw           0b11100010 //226
#define    op_rd_u_sw           0b11100011 //227
#define    op_rd_u_dw_base_off  0b11100100 //228
#define    op_rd_u_sw_base_off  0b11100101 //229
#define    op_rd_v_dw           0b11100110 //230
#define    op_rd_v_sw           0b11100111 //231
#define    op_rd_v_dw_base_off   0b11101000 //232
#define    op_rd_v_sw_base_off   0b11101001 //233
#define    op_rd_w_dw            0b11101010 //234
#define    op_rd_w_sw            0b11101011 //235
#define    op_rd_w_dw_base_off   0b11101100 //236
#define    op_rd_w_sw_base_off   0b11101101 //237
#define    op_wr_u_dw            0b11101110 //238
#define    op_wr_u_sw            0b11101111 //239
#define    op_wr_u_dw_base_off   0b11110000 //240
#define    op_wr_u_sw_base_off   0b11110001 //241
#define    op_wr_v_dw            0b11110010 //242
#define    op_wr_v_sw            0b11110011 //243
#define    op_wr_v_dw_base_off   0b11110100 //244
#define    op_wr_v_sw_base_off   0b11110101 //245
#define    op_wr_w_dw            0b11110110 //246
#define    op_wr_w_sw            0b11110111 //247
#define    op_wr_w_dw_base_off   0b11111000 //248
#define    op_wr_w_sw_base_off   0b11111001 //249

#define    op_greg_is_areg_etc        0b11111010 //250 // 248, 249

#define    op_reg_trans_etc_cores     0b11111011 //251 // 254, 255
#define    op_reg_trans_64bit	      0b11111100 //252
#define    op_reg_trans_sigma	      0b11111101 //253

#define    op_set_spec_reg            0b11111110 //254 //165
#define    op_read_spec_reg           0b11111111 //255 //166

//-----------------------------------------------------------
// double words instruction below
#define    op_ext_sw_m8_etc       0b0000 //0 // 4, 5, new
#define    op_ext_br_dw_etc       0b0001 //1 // 9, 10, new
#define    op_ext_rd_sw_etc       0b0010 //2 // 11, 12, 13, 14, new
#define    op_ext_fext_etc        0b0011 //3 // 3, new
#define    op_spell_extr		  0b0100	//4 // frm LG
#define	    op_ext_b_cmp_etc		      0b0101  //5
#define	    op_ext_cmp_do_etc		  0b0110	//6
#define    op_ext_reg_is_fix_etc  0b0111 //7
#define    op_maxmin_hacc		  0b1000	//8 // frm LG
#define    op_ext_b_lbl_etc           0b1001 //9 // 16, 17, 21, 26
#define    op_dword_shft		  0b1010	//10 // frm LG

#define    op_dword_complex	  0b1100	//12 new added 
// double words instruction v20130116
#define    op_dword_0		0b0000	//0
#define    op_dword_1		0b0001	//1
#define    op_dword_2		0b0010	//2
#define	   op_dword_3		0b0011	//3
#define    op_dword_4		0b0100	//4
#define    op_dword_5		0b0101	//5
#define    op_dword_6		0b0110	//6
#define	   op_dword_7		0b0111	//7
#define    op_dword_8		0b1000	//8
#define    op_dword_9		0b1001	//9
#define	   op_dword_10		0b1010	//10
#define	   op_dword_11		0b1011	//11
#define    op_dword_12		0b1100	//12
#define    op_dword_13		0b1101	//13
#define	   op_dword_14		0b1110	//14
#define	   op_dword_15		0b1111	//15



//-----------------------------------------------------------
// no calc instruction below
#define    op_areg_add_sub        0b00001 //1
#define    op_areg_add_imm        0b00010 //2 //5
#define    op_areg_shf_imm        0b00011 //3 //6
#define    op_areg_shf_reg        0b00100 //4 //7
#define    op_areg_cb_reg         0b00101 //5
#define    op_areg_abs_sub        0b00110  //6
#define    op_reg_hmp_sel		  0b00111    //7 // frm LG
#define    op_nop                 0b01000 //8 //2
#define    op_idle                0b01001 //9 //3
#define    op_getmid		      0b01010    //10 // frm LG
#define    op_swi			      0b01011    //11 // frm LG
#define    op_clr_sf              0b01100 //12 //8
#define    op_set_reg_bit         0b01101 //13 //9
#define    op_clr_reg_bit         0b01110 //14 //10
#define    op_b_reg               0b01111 //15 //20
#define    op_call_reg            0b10000 //16 //15
#define    op_ret                 0b10001 //17 //18
#define    op_iret                0b10010 //18 //19
#define    op_strap               0b10011 //19 //22  // GRQ: todo strap n
#define    op_etrap               0b10100 //20 //23
#define    op_rtrap               0b10101 //21 //25

// 控制寄存器12位编址
#define SPEC_ADDR_ABFPR 	0xd0c
#define SPEC_ADDR_ALUFR 	0xc10
#define SPEC_ADDR_ACF   	0xc30
#define SPEC_ADDR_CON   	0xc50
#define SPEC_ADDR_ALUCAFR	0xc70
#define SPEC_ADDR_ALUDFER	0xc90
#define SPEC_ADDR_ALUDFMR	0xcb0
#define SPEC_ADDR_ALUDFIRR	0xcf0
#define SPEC_ADDR_ACC		0xcc0
#define SPEC_ADDR_SHFFR		0xe10
#define SPEC_ADDR_SLTAR		0xe20
#define SPEC_ADDR_SCF		0xe30
#define SPEC_ADDR_SHFER		0xe64
#define	SPEC_ADDR_SPUFR		0XdC4
#define SPEC_ADDR_MULFR		0xf10
#endif



