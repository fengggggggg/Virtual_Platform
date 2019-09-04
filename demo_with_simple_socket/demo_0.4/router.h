/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 23:09
 * Update time   : 2019-05-27 18:53
 * Description   : 
 *	1.	修改targ_socket声明使其能够进行多Initiator通信
******************************************************/

#ifndef ROUTER_H_
#define ROUTER_H_

#include "common.h"


class Router
	: sc_core::sc_module
{

private:

	// size_t	m_inits;
	// size_t	m_targs;

protected:

	SC_HAS_PROCESS(Router);

public:

	vector<simple_target_socket_tagged<Router> *>				targ_socket;
	vector<simple_initiator_socket_tagged<Router> *>			init_socket;

	Router(sc_core::sc_module_name name);

	~Router() {}

	unsigned int decode_address( uint64	address,
								 uint64	&masked_address);

	uint64 compose_address( unsigned int	target_nr,
							uint64			address);

	tlm_sync_enum nb_transport_fw( int					id,
								   tlm_generic_payload	&trans, 
								   tlm_phase			&phase,
								   sc_time				&delay);
  
	tlm_sync_enum nb_transport_bw( int 					id, 
								   tlm_generic_payload	&trans, 
								   tlm_phase 			&phase,
								   sc_time				&delay );

};

#endif
