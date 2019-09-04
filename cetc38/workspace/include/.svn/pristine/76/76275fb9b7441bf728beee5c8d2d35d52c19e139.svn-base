#ifndef ICACHE_MEMORY_H_
#define ICACHE_MEMORY_H_

#include "global.h"
#include <string.h>

namespace BWDSP104X{
struct insnLine512{
	unsigned int insnSlot[16];		//16 words of an instruction line
	
	void reset(){
		for(int i=0;i<16;i++){
			insnSlot[i] = 0x0;
		}
	}
	//assignment operation
	insnLine512& operator =(const insnLine512& lhs){		
		for(int j=0;j<16;j++){
			insnSlot[j] = lhs.insnSlot[j];
		}
		return *this;
	}
};

//struct dataRAM{
//	insnLine512 dataEntry[128];		//128 entries of instruction line
//	void reset(){
//		for(int i=0;i<128;i++){
//			dataEntry[i].reset();
//		}
//	}
//};

struct tagLine88{
	unsigned int valid[4];			//valid <1x4>, value can be [0..1]	1bit	x4
	//unsigned int lru[4];			//lru <2x4>, value can be [0..3]	2bits	x4
	unsigned char lru;				//8bits, only [0..2] is usable
	unsigned int tag[4];			//tag <19x4>, value can be [0..524287]	19bits x4

	void reset(){
		for(int i=0;i<4;i++){
			valid[i] = tag[i] = 0x0;
		}
		lru = 0;
	}
//	tagLine88& operator =(const tagLine88& rhs){
//		for(int i=0;i<4;i++){
//			valid[i] = rhs.valid[i];
//
//			tag[i] = rhs.tag[i];
//		}
//		lru = rhs.lru;
//		return *this;
//	}
};

//struct tagRAM{
//	tagLine88 tagEntry[128];		//128 entries of tag line
//
//	void reset(){
//		for(int i=0;i<128;i++)
//			tagEntry[i].reset();
//	}
//};

struct cacheLine2136{
	tagLine88 tagLine;
	insnLine512 dataLine[4];			//A cache line has 4 ways of data ram
	void reset(){
		tagLine.reset();
		for(int i=0;i<4;i++){
			dataLine[i].reset();
		}
	}
	//assignment operation
	cacheLine2136& operator =(const cacheLine2136& lhs){
//		for(int i=0;i<4;i++){
//			tagLine.valid[i] = lhs.tagLine.valid[i];
//			tagLine.tag[i] = lhs.tagLine.tag[i];
//			for(int j=0;j<16;j++){
//				dataLine[i].insnSlot[j] = lhs.dataLine[i].insnSlot[j];
//			}
//		}
//		tagLine.lru = lhs.tagLine.lru;
		memcpy(this,&lhs,sizeof(cacheLine2136));
		return *this;
	}
	//output stream operation
//	friend std::ostream& operator << (std::ostream& out, const cacheLine2136& rhs) {
//		out<<std::hex<<rhs.tagLine.tag[0];
//		return out;
//
//	}
};



//class icache_memory
//{
//public:
//	std::string name;
//	tagRAM tag_chunck[4];
//	dataRAM data_chunck[16];			//way0: [0..3]
//										//way1: [4..7]
//										//way2: [8..11]
//										//way3: [12..15]
//public:
//	icache_memory(){}
//	icache_memory(std::string nm);
//	~icache_memory(){}
//
//	void reset();
//	cacheLine2136 readCacheLine(unsigned int PCaddr);		//Attention: SRAM mode, no miss occurs
//	bool readCacheWord(unsigned int addr, unsigned int *p_value);	//return false when address is illegal
//	bool writeCacheWord(unsigned int addr,unsigned int value);	//return false when address is illegal
//};

}//end of namespace BWDSP104X
#endif
