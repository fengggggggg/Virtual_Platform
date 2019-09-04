
#ifndef _JIT_CACHE_H
#define _JIT_CACHE_H

/*------------------------------------------- define --------------------------------------*/
#define JIT_CACHE_SIZE  1024
#define JIT_IDX_MASK      0x3FF

/*------------------------------------------ typedef --------------------------------------*/
typedef struct
{	
	DSPU32 u32DecodeInfo[JIT_MAX_PARA_NUM];
	DSPU32 u32Inst0;
	DSPU32 u32Inst1;

} INST_DEC_INFO;


/*----------------------------------- data declarations ----------------------------------*/
INST_DEC_INFO g_arrJITCache[JIT_CACHE_SIZE];

/*-------------------------------------- implimention -------------------------------------*/
void InitJITCache();
DSPU32 PC2JITIdx(DSPU32 p_u32PC);



#endif


