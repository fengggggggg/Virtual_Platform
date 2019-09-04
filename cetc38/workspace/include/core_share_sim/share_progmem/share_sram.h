/*
 * share_sram.h
 *
 * Created on: Jun 4, 2015
 * Author:		liugu
 */
#ifndef SHARE_SRAM_H_
#define SHARE_SRAM_H_

#include "protocol.h"
#include "extension.h"

using namespace tlm;
using namespace sc_core;
using namespace std;

class share_sram:
	public sc_module,
	public tlm_fw_transport_if<PROTOCOL_TYPE>
{
	public:
		//signals
		sc_in_clk		clk;			//module clock signal
		sc_module_name	name;			//module name
		//sockets
		tlm_target_socket<512, PROTOCOL_TYPE> target_socket_from_icache[2];
	
		//Address space: [0x0, 0x17FFF]
		#define SHARE_SRAM_DEFAULT_LOW_ADDRESS	0x0
		#define SHARE_SRAM_DEFAULT_SIZE			0x18000
		unsigned int share_sram_low_address;
		unsigned int share_sram_size;				//in word(32bits) default: 96K=6x16K

		//Memory space
		unsigned int *memory;

		//Internal variables
		#define FALSE_ADDR		0x5a5aa5a5
		#define PIPELINE_DEPTH	4
		unsigned int ack_pc[2];
		unsigned int ack_pc_next[2];
		unsigned int ack_counter[2];
		bool					ack_pc_ready[2];
		bool					ack_pc_next_ready[2];
		unsigned int irq_pc[2];
		bool					irq_plus_en[2];
		
		
		

		//SystemC and TLM functions
		SC_HAS_PROCESS(share_sram);
		share_sram(sc_module_name module_name);
		~share_sram();

		virtual tlm_sync_enum nb_transport_fw(
			tlm_generic_payload&trans,
			tlm_phase &phase,
			sc_time &t);
		virtual void b_transport(
			tlm_generic_payload &trans,
			sc_time &t){}
		virtual bool get_direct_mem_ptr(
			tlm_generic_payload &trans,
			tlm_dmi &dmi_data){return false;}
		virtual unsigned int transport_dbg(
			tlm_generic_payload &trans){return 0;}

		//Internal logic functions
		void clock_tick();
		void reset();
		void send_cache_line(unsigned int addr, unsigned int core_id);
		void NotifyShareSRAMLowAddr(unsigned int low_addr){ share_sram_low_address = low_addr;}
		void NotifyShareSRAMSize(unsigned int size){ share_sram_size = size;}

		//Interface for JTAG
		bool read_word(unsigned int addr, unsigned int &value);
		bool write_word(unsigned int addr, const unsigned int value);

		// #define DEBUG_out cerr<<"["<<sc_time_stamp()<<"]"<<name<<": "
};

#endif
