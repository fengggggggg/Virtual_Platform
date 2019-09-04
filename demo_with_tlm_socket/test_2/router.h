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
	, public tlm::tlm_bw_transport_if<>
	, public tlm::tlm_fw_transport_if<>
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

	//simple_target_socket<Router>		targ_socket;
	//simple_initiator_socket<Router>		init_socket;
	tlm::tlm_target_socket<32>		targ_socket;
	tlm::tlm_initiator_socket<32>	init_socket;

	Router(sc_module_name name)
	{
		//targ_socket.register_nb_transport_fw(this, &Router::nb_transport_fw);
		targ_socket.bind(*this);

		// init_socket注册会报错
		//init_socket.register_nb_transport_bw(this, &Router::nb_transport_bw);
		init_socket.bind(*this);
	}

	~Router() {}

	// ****************
	// FORWARD PATH
	// ****************

	// TLM-2 non blocking transport_fw method
	virtual tlm_sync_enum nb_transport_fw( tlm_generic_payload	&trans, 
										   tlm_phase			&phase,
										   sc_time				&delay )
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
	virtual tlm_sync_enum nb_transport_bw(tlm_generic_payload	&trans, 
										  tlm_phase 			&phase, 
										  sc_time				&delay )
	{
		// Backward transaction to initiator
		targ_socket->nb_transport_bw(trans, phase, delay);

		return tlm::TLM_ACCEPTED;
	}

	virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
										   sc_dt::uint64 end_range) {}

	virtual void b_transport(tlm::tlm_generic_payload	&trans,
							 sc_core::sc_time			&delay) {}

	virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload	&trans,
									tlm::tlm_dmi				&dmi_data)
	{
		return false;
	}

	virtual unsigned int transport_dbg(tlm::tlm_generic_payload	&trans)
	{
		return 0;
	}

};

#endif
