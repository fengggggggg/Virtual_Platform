#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace tlm_utils;
using namespace tlm;

// *********************************************
// Generic payload non-blocking transport router
// *********************************************

template<unsigned int N_TARGETS>
//template<unsigned int N_INIT>

SC_MODULE(Router)
{
	// TLM-2 socket, defaults to 32-bits wide, base protocol
	// 此处改为使用tagged以及数组
	simple_target_socket<Router>		target_socket;

	// *********************************************
	// Use tagged sockets to be able to distinguish incoming backward path calls
	// *********************************************

	simple_initiator_socket_tagged<Router>*	initiator_socket[N_TARGETS];

	SC_CTOR(Router)
	: target_socket("target_socket")
	{
		// Register callbacks for incoming interface method calls
		target_socket.register_nb_transport_fw( this, &Router::nb_transport_fw);

		for (unsigned int i = 0; i < N_TARGETS; i++)
		{
			char txt[30];
			sprintf(txt, "init_socket_%d", i);
			initiator_socket[i] = new simple_initiator_socket_tagged<Router>(txt);

			// *********************************************
			// Register callbacks for incoming interface method calls, including tags
			// *********************************************
			initiator_socket[i]->register_nb_transport_bw(this, &Router::nb_transport_bw, i);
		}
	}

	// ****************
	// FORWARD PATH
	// ****************

	// TLM-2 non blocking transport_fw method
	virtual tlm_sync_enum nb_transport_fw( tlm_generic_payload& trans, 
										   tlm_phase &phase, sc_time& delay )
	{
		uint64 address = trans.get_address();
		uint64 masked_address;
		unsigned int target_nr = decode_address( address, masked_address);

		// Modify address within transaction
		trans.set_address( masked_address );

		// Forward transaction to appropriate target
		( *initiator_socket[target_nr] )->nb_transport_fw( trans, phase, delay );
		return tlm::TLM_ACCEPTED;
	}
  
	// ****************
	// BACKWARD PATH
	// ****************
	virtual tlm_sync_enum nb_transport_bw(	int id, 
											tlm_generic_payload& trans, 
											tlm_phase &phase, sc_time& delay )
	{
		// Backward transaction to initiator
		target_socket->nb_transport_bw( trans, phase, delay );
		return tlm::TLM_ACCEPTED;
	}

	// ****************
	// ROUTER INTERNALS
	// ****************

	// Simple fixed address decoding
	inline unsigned int decode_address(uint64 address, uint64& masked_address )
	{
		unsigned int target_nr = static_cast<unsigned int>( (address >> 8) & 0x3 );
		masked_address = address & 0xFF;
		return target_nr;
	}

	inline uint64 compose_address( unsigned int target_nr, uint64 address)
	{
		return (target_nr << 8) | (address & 0xFF);
	}
};

#endif
