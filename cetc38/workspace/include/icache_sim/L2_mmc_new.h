#ifndef L2_MMC_NEW_H_
#define L2_MMC_NEW_H_

#include "global.h"
#include "register32.h"
#include <stdlib.h>

//using std::string;

namespace BWDSP104X{
	class L2_mmc_new{
	public:
		std::string name;
		
		//Input signals
		bool L2_irq;
		unsigned int L2_irq_pc;
		//Output signals
		bool L2_ack;
		unsigned int L2_ack_pc;
		insnLine512 L2_ack_insn;
		//Internal storage
		register_basic<ictype_bool> reg_L2_ack;			
		register32 reg_L2_ack_pc;
		register_basic<insnLine512> reg_L2_ack_insn;
		register32 reg_L2_irq_pc;

		register_basic<ictype_bool> inProcessing;
#define  L2_DEFAULT_LATENCY 4
		register32 reg_L2_counter;
		//L2 Memory
		enum L2_mode{L2_INVALID,L2_NOP_MEM,L2_INTERNAL_MEM,L2_EXTERN_MEM};
		L2_mode mode;
#define L2_INTERNAL_MEM_DEFAULT_SIZE 0x200000
#define L2_INTERNAL_MEM_DEFAULT_LOW_ADDR 0x0
#define L2_INTERNAL_MEM_DEFAULT_HIGH_ADDR 0x1fffff
		DSPU32 *internalMem;	//Internal memory space is 2M words, address=[0x00_0000~0x1f_ffff]
		DSPU32 internalMem_lowspace;	//lower space of internal memory, default is 0x0
		DSPU32 *externalMem;			//External memory pointer
		DSPU32 externalMem_size;		//size of external memory
		DSPU32 externalMem_lowspace;	//lower space of external memory
	public:
		L2_mmc_new(){};

		~L2_mmc_new(){};
		//External interface
		void reset();
		void setMode(L2_mode m, DSPU32 p_u32MemSize,DSPU32 p_u32LowAddr);
		void evaluate();
		void update();
		insnLine512 getInsnLineFromMem();
		bool LoadInnerMem();

		void gatherInputSignals(bool p_L2_irq, unsigned int p_L2_irq_pc);
		void emitOutputSignals(bool *p_L2_ack, unsigned int *p_L2_ack_pc, insnLine512 *p_L2_ack_insn);

		void setExternalMem(unsigned int * ptr_ext_mem){
			externalMem = ptr_ext_mem;
		}
	};
}

#endif
