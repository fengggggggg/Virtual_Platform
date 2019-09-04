/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 09:32
 * Update time   : 2019-05-17 11:18
 * Description   :
 *	1.	target中定义fw函数，该函数由initiator(即router)调用
******************************************************/
#ifndef TARGET_H
#define TARGET_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include <string>

using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace tlm;
using namespace tlm_utils;


// Target module representing a simple memory
SC_MODULE(Memory)
{
public:
	// TLM-2 socket, defaults to 32-bits wide, base protocol
	simple_target_socket<Memory> targ_socket;

	enum { SIZE = 256 };
	const sc_time LATENCY;

	SC_CTOR(Memory)
	{
		// Register callbacks for incoming interface method calls
		targ_socket.register_nb_transport_fw( this, &Memory::nb_transport_fw);

		// Initialize memory with random data
		for (int i = 0; i < SIZE; i++)
			mem[i] = 0xAA000000 | (mem_nr << 20) | (rand() % 256);

		++mem_nr;
	}

	// TLM-2 blocking transport method
	virtual tlm_sync_enum nb_transport_fw (	tlm_generic_payload& trans, 
											tlm_phase& phase, 
											sc_time& delay )
	{
		tlm_command		cmd = trans.get_command();
		sc_dt::uint64   adr = trans.get_address() / 4;
		unsigned char*  ptr = trans.get_data_ptr();
		unsigned int    len = trans.get_data_length();
		unsigned char*  byt = trans.get_byte_enable_ptr();
		unsigned int    wid = trans.get_streaming_width();

		// Obliged to check address range and check for unsupported features,
		//   i.e. byte enables, streaming, and bursts
		// Can ignore extensions

		// Generate the appropriate error response
		if (adr >= SIZE) {
			trans.set_response_status( TLM_ADDRESS_ERROR_RESPONSE );
			 return TLM_ACCEPTED;
		}
		if (byt != 0) {
			trans.set_response_status( TLM_BYTE_ENABLE_ERROR_RESPONSE );
			return TLM_ACCEPTED;
		}
		if (len > 4 || wid < len) {
			trans.set_response_status( TLM_BURST_ERROR_RESPONSE );
			return TLM_ACCEPTED;
		}

		wait(delay);
		delay = SC_ZERO_TIME;

		// Obliged to implement read and write commands
		if ( cmd == TLM_READ_COMMAND )
			memcpy(ptr, &mem[adr], len);
		else if ( cmd == TLM_WRITE_COMMAND )
			memcpy(&mem[adr], ptr, len);

		// Obliged to set response status to indicate successful completion
		trans.set_response_status( TLM_OK_RESPONSE );

		// 输出模块名
		cout << "Targ=" << this->name() << ", ";
	}

	int mem[SIZE];
	static unsigned int mem_nr;
};

unsigned int Memory::mem_nr = 0;

#endif
