#ifndef REGISTER32_H_
#define REGISTER32_H_

#include "global.h"
#include "icache_memory.h"

namespace BWDSP104X{
	class register32{
	public:
		std::string name;
	public:
		unsigned int val_in;		//The value write into the register
		unsigned int val_out;		//The value read from the register
	public:
		register32(){}
		register32(std::string nm);
		~register32(){}

		//External interface
		unsigned int read();
		void write(unsigned int v);
		void update();				//Attention: every cycle the instance must call update()
		void reset();
		void set(unsigned int v);
	};

//	class register_cacheline2136{
//	public:
//		std::string name;
//	private:
//		cacheLine2136 val_in;		//The value write into the register
//		cacheLine2136 val_out;		//The value read from the register
//	public:
//		register_cacheline2136(){}
//		register_cacheline2136(std::string nm);
//		~register_cacheline2136(){}
//
//		//External interface
//		cacheLine2136 read();
//		void write(cacheLine2136 v);
//		void update();				//Attention: every cycle the instance must call update()
//		void reset();
//	};

	template <class T> class register_basic{
		//Type template T should implement the following method:
		//1) operator =
		//2) reset()
	public:
		//std::string name;
	private:
		T val_in;		//The value write into the register
		T val_out;		//The value read from the register
	public:
		register_basic(){}
		//register_basic(std::string nm)
		//	:name(nm){};
		~register_basic(){}

		//External interface
		T read(){
			return val_out;
		}
		void write(T v){
			val_in = v;
			return;
		}
		void update(){
			//Attention: every cycle the instance must call update()
			val_out = val_in;
		}
		void reset(){
			val_in.reset();
			val_out.reset();
			return;
		}

		void set(T v){
			val_in = v;
			val_out = v;
		}
	};
}
#endif
