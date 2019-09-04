/******************************************************
 * Author        : fwj
 * Creation time : 2019-05-16 23:09
 * Update time   : 2019-05-23 18:53
 * Description   : 
 *	1.	修改targ_socket声明使其能够进行多Initiator通信
******************************************************/

#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "common.h"

// *********************************************
// Generic payload non-blocking transport router
// *********************************************

// template<unsigned int N_INIT, unsigned int N_TARG>

class Router
	: public sc_core::sc_module
{
private:

	unsigned int decode_address(uint64 address, uint64& masked_address )
	{
		unsigned int target_nr = static_cast<unsigned int>( (address >> 8) & 0x3 );
		masked_address = address & 0xFF;
		return target_nr;
	}

	uint64 compose_address( unsigned int target_nr, uint64 address)
	{
		return (target_nr << 8) | (address & 0xFF);
	}

protected:

	SC_HAS_PROCESS(Router);

public:

	simple_target_socket<Router>		targ_socket;
	simple_initiator_socket<Router>		init_socket;

	Router(sc_module_name name)
	{
		targ_socket.register_nb_transport_fw(this, &Router::nb_transport_fw);

		// init_socket注册会报错
		//init_socket.register_nb_transport_bw(this, &Router::nb_transport_bw);
	}

	~Router() {}

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

		init_socket->nb_transport_fw(trans, phase, delay);
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
		targ_socket->nb_transport_bw(trans, phase, delay);

		return tlm::TLM_ACCEPTED;
	}
};

#endif
