/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 23:09
 * Update time   : 2019-05-27 18:53
 * Description   : 
 *	1.	修改targ_socket声明使其能够进行多Initiator通信
******************************************************/

#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "common.h"


class Router
	: sc_core::sc_module
{
private:

	unsigned int decode_address( uint64	address,
								 uint64	&masked_address)
	{
		unsigned int target_nr = static_cast<unsigned int>( (address >> 8) & 0x3 );
		masked_address = address & 0xFF;
		return target_nr;
	}

	uint64 compose_address( unsigned int	target_nr,
							uint64			address)
	{
		return (target_nr << 8) | (address & 0xFF);
	}

	tlm_sync_enum nb_transport_fw( tlm_generic_payload	&trans, 
								   tlm_phase			&phase,
								   sc_time				&delay)
	{
		uint64 address = trans.get_address();
		uint64 masked_address;
		unsigned int target_nr = decode_address( address, masked_address);

		// Modify address within transaction
		trans.set_address( masked_address );

		// Forward transaction to appropriate target
		( *init_socket[target_nr] )->nb_transport_fw( trans, phase, delay );
		return tlm::TLM_ACCEPTED;
	}
  
	tlm_sync_enum nb_transport_bw( int 					id, 
								   tlm_generic_payload	&trans, 
								   tlm_phase 			&phase,
								   sc_time				&delay )
	{
		for (int i = 0; i < N_INIT; i++)
			targ_socket[i]->nb_transport_bw(trans, phase, delay);
		return tlm::TLM_ACCEPTED;
	}

protected:

	SC_HAS_PROCESS(Router);

public:

	// tlm_utils::simple_target_socket_tagged<Router>*			targ_socket[N_INIT];
	tlm_utils::simple_target_socket<Router>					targ_socket[N_INIT];
	tlm_utils::simple_initiator_socket_tagged<Router>*		init_socket[N_TARG];

	Router(sc_core::sc_module_name name)
	{
		for (unsigned int i = 0; i < N_INIT; i++)
		{
			// char socket_name[30];
			// sprintf(socket_name, "targ_socket_%d", i);
			// targ_socket[i] = new simple_target_socket_tagged<Router>(socket_name);

			targ_socket[i].register_nb_transport_fw(this, &Router::nb_transport_fw);
		}

		for (unsigned int i = 0; i < N_TARG; i++)
		{
			char socket_name[30];
			sprintf(socket_name, "init_socket_%d", i);
			init_socket[i] = new simple_initiator_socket_tagged<Router>(socket_name);

			init_socket[i]->register_nb_transport_bw(this, &Router::nb_transport_bw, i);
		}
	}

	~Router() {}
};

#endif
