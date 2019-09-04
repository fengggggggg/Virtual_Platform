/*
 * icache_ram_new.h
 *
 *  Created on: Dec 25, 2013
 *      Author: liugu
 *      Abstract:This class is a replacement of original icache_ram.
 *      		Using a new organization of output registers to model i-cache ram.
 *      		A maxim of 4 read results can be buffered in this ram, and selected
 *      		by PCFE1 register in pipeline.
 *      Update: Jan 2, 2014: This class is renewed according to a single-port RAM model.
 *      			This model has 4 independent banks, each of which has only one r/w port.
 *      			A PC indicates the read or write address, and a r/w signals indicates
 *      			the type of operation. Output is only valid when read enabled, and it can
 *      			hold the value until next read enabled cycle. In other word, when write an
 *      			address PC, the output is not changed immediately.
 *      			The bank conflict checking and rewrite operation is controlled by the outside
 *      			logic. Rewrite is the most priority of all, and read of this cycle is not send
 *      			to the bank until next cycle. A register is used to buffer rewrite address and
 *      			instruction line.
 */

#ifndef ICACHE_RAM_NEW_H_
#define ICACHE_RAM_NEW_H_

#include "global.h"
#include "register32.h"
#include <vector>

namespace BWDSP104X{
	class icache_ram_new{
	public:
		//SRAM address space
		unsigned int lowAddr,highAddr;
		//Input signals
		unsigned int	readPC;		//AKA: pcFE0_w generated from FE0
		bool			readEn;		//AKA: pcFE0_en generated from FE0
		unsigned int	writePC;	//AKA: pcFE2_reg generated from FE2
		bool			writeEn;	//AKA: submitToIAB_w generated from FE2,
									//indicates the PC in FE2 is submitted to IAB this cycle
		cacheLine2136	writeLine;	//AKA: ReadSlotsToIAB_w generated from FE2
		//Output signals
		cacheLine2136	readLine[4];	//read buffer of 4 banks

		bool	 		icWbDelay_2nd_w;

		bool			in_flush_proc;

		//Internal memory
		register_basic<cacheLine2136>	cacheMem[4][128];		//4 banks, each has 128 entries
		register_basic<cacheLine2136>	readOutBuffer[4];		//4 read buffer of each bank
		register32 						wb_PC_reg;				//rewrite buffer
		register_basic<ictype_bool>		wb_En_reg;
		register_basic<cacheLine2136>	wb_Line_reg;

		//Internal signals
		bool							rwEn[4];				//only when rwEn==true, read and write is enabled
		bool							readOrWrite[4];			//0:read, 1:write
		unsigned int					PCAddress[4];			//One port address in a bank
		cacheLine2136					writeInput[4];			//Write line in each bank

		//write vector
		typedef struct{
			unsigned int bank_idx;
			unsigned int entry_idx;
			cacheLine2136 write_content;
		}write_elem;
		std::vector<write_elem> write_vector;					//record for write access in each cycle

		//write access trace
		unsigned int CC;	//which cycle counter when write happens
		unsigned int victim;	//which way is chosen as victim
		unsigned int victim_old;	//which way is chosen as victim for last line (wb)

	public:
		//External interface
		icache_ram_new();
		~icache_ram_new(){}
		void reset();
		void evaluate();
		void update();

		void gatherInputSignals(bool p_flush,unsigned int p_readPC,bool p_readEn,unsigned int p_writePC,bool p_writeEn,cacheLine2136 p_writeLine);
		void emitOutputSignals(cacheLine2136 p_readLine[4]);

		bool getWb2nd();
		//Internal functions
		unsigned int parseBankIdx(unsigned int PC);
		unsigned int parseEntryIdx(unsigned int PC);
		unsigned int parseOffsetIdx(unsigned int PC);
		unsigned int parseTagIdx(unsigned int PC);
		//SRAM mode interface
		bool set(unsigned int addr,unsigned int value);		//Addr is linear address. Return false if addr out of SRAM space
		bool get(unsigned int addr,unsigned int *value);
		void setSpaceAddr(unsigned int low);

		//Monitor functions
		void getUtilization(double *p_util);
		//void getMissRate(double *p_missRate);

		//New interface for write access trace
		void notifyCC(unsigned int p_CC){ CC = p_CC;}
		void notifyVictimWay(unsigned int p_victim){victim_old = victim; victim = p_victim;}

		//bool setTag(unsigned int bank_idx,unsigned int entry_idx,tagLine88 value){}
	};

}



#endif /* ICACHE_RAM_NEW_H_ */
