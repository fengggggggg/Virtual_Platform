/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 23:09
 * Update time   : 2019-06-09 17:09
 * Description   : 
 *	
******************************************************/

#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "common.h"
#include "centralized_buffer.h"


class Router
	: sc_core::sc_module
{

private:
	//////////////////////////////////////////////////////
	// Member Variables
	//////////////////////////////////////////////////////
	
	size_t								m_inits;			// number of initiators
	size_t								m_targs;			// number of targets

	soclib::tlmdt::centralized_buffer	m_central_buffer;	// input fifos

	sc_core::sc_event					m_cmd_received;		// any command received

	//////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////
	
	void execLoop();

	void route( size_t						from,
				tlm::tlm_generic_payload	&payload,
				tlm::tlm_phase				&phase,
				sc_core::sc_time			&time);

	unsigned int decode_address( uint64		address,
								 uint64		&masked_address);

	uint64 compose_address( unsigned int	target_nr,
							uint64			address);

	tlm_sync_enum nb_transport_fw( int					id,
								   tlm_generic_payload	&payload, 
								   tlm_phase			&phase,
								   sc_time				&time);
  
	tlm_sync_enum nb_transport_bw( int 					id, 
								   tlm_generic_payload	&payload, 
								   tlm_phase 			&phase,
								   sc_time				&time);

protected:

	SC_HAS_PROCESS(Router);

public:

	vector<simple_target_socket_tagged<Router> *>		targ_socket;
	vector<simple_initiator_socket_tagged<Router> *>	init_socket;

	Router( sc_core::sc_module_name		name,
			const size_t				n_inits,
			const size_t				n_targs);

	~Router() {}

};

#endif
