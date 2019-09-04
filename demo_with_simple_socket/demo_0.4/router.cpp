#include "router.h"

Router::Router(sc_core::sc_module_name name)
{
    for (unsigned int i = 0; i < N_INIT; i++)
	{
		char socket_name[30];
		sprintf(socket_name, "targ_socket_%d", i);
		targ_socket.push_back(new simple_target_socket_tagged<Router>(socket_name));

		targ_socket[i]->register_nb_transport_fw(this, &Router::nb_transport_fw, i);
	}

	for (unsigned int i = 0; i < N_TARG; i++)
	{
		char socket_name[30];
		sprintf(socket_name, "init_socket_%d", i);
		init_socket.push_back(new simple_initiator_socket_tagged<Router>(socket_name));

		init_socket[i]->register_nb_transport_bw(this, &Router::nb_transport_bw, i);
	}
}

tlm_sync_enum Router::nb_transport_fw( int					id,
							           tlm_generic_payload	&trans,
                                       tlm_phase			&phase,
                                       sc_time				&delay)
{
	cout << name() << " receive COMMAND from init" << id << endl;

	uint64 address = trans.get_address();
	uint64 masked_address;
	unsigned int target_nr = decode_address( address, masked_address);

	// Modify address within transaction
	trans.set_address( masked_address );

	// Forward transaction to appropriate target
	( *init_socket[target_nr] )->nb_transport_fw(trans, phase, delay );
	// return tlm::TLM_COMPLETED;
	return tlm::TLM_ACCEPTED;
}

tlm_sync_enum Router::nb_transport_bw( int 					id,
                                       tlm_generic_payload	&trans,
                                       tlm_phase 			&phase,
							           sc_time				&delay )
{
	cout << name() << "receive RESPONSE from target" << id << endl;

	for (unsigned int i = 0; i < N_INIT; i++)
		(*targ_socket[i])->nb_transport_bw(trans, phase, delay);
	return tlm::TLM_ACCEPTED;
}

unsigned int Router::decode_address( uint64	address,
							         uint64	&masked_address)
{
	unsigned int target_nr = static_cast<unsigned int>( (address >> 8) & 0x3 );
	masked_address = address & 0xFF;
	return target_nr;
}

uint64 Router::compose_address( unsigned int	target_nr,
						        uint64			address)
{
	return (target_nr << 8) | (address & 0xFF);
}