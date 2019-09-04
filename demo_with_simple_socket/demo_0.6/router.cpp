/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-05 09:38
 * Update time   : 2019-06-12 11:13
 * Description   : 
******************************************************************************/

#include "router.h"

Router::Router( sc_core::sc_module_name name,
				const size_t			n_inits,
				const size_t			n_targs)
	: sc_module(name)
	, m_inits(n_inits)
	, m_targs(n_targs)
	, m_central_buffer("central_buffer", n_inits)
{
    for (unsigned int i = 0; i < m_inits; i++)
	{
		char socket_name[30];
		sprintf(socket_name, "targ_socket_%d", i);
		targ_socket.push_back(new simple_target_socket_tagged<Router>(socket_name));

		targ_socket[i]->register_nb_transport_fw(this, &Router::nb_transport_fw, i);
	}

	for (unsigned int i = 0; i < m_targs; i++)
	{
		char socket_name[30];
		sprintf(socket_name, "init_socket_%d", i);
		init_socket.push_back(new simple_initiator_socket_tagged<Router>(socket_name));

		init_socket[i]->register_nb_transport_bw(this, &Router::nb_transport_bw, i);
	}

	// register thread process
	SC_THREAD(execLoop);
	// SC_METHOD(execLoop);
	// sensitive << m_cmd_received;
}

////////////////////////////////////////////////////////////
// 该函数实际上执行fw函数的功能。该函数根据payload的地址，将payload
// 发送到正确的target
////////////////////////////////////////////////////////////
void Router::route(	size_t						from,
					tlm::tlm_generic_payload	&payload,
					tlm::tlm_phase				&phase,
					sc_core::sc_time			&time)
{
	// tlm_command cmd = payload.get_command();
	uint64 address = payload.get_address();
	uint64 masked_address;
	unsigned int target_nr = decode_address(address, masked_address);

	payload.set_address(masked_address);

#ifdef DEBUG_MODULE
	cout << "    route  the  cmd to   targ" << target_nr << "  / time = " << (int)time.value()
		 << endl;
#endif

	(*init_socket[target_nr])->nb_transport_fw(payload, phase, time);
}


void Router::execLoop()
{
	cout << "launch execLoop" << endl;

	size_t						from;
	tlm::tlm_generic_payload*	payload_ptr;
	tlm::tlm_phase*				phase_ptr;
	sc_core::sc_time*			time_ptr;

	while(true)
	{
		while(m_central_buffer.pop(from, payload_ptr, phase_ptr, time_ptr))
		{
			route(from, *payload_ptr, *phase_ptr, *time_ptr);
		}

		cout << endl << "!!! No transaction available in buffer, waiting Initiator to send."
			 << endl;
		sc_core::wait(m_cmd_received);
		// sc_core::next_trigger(m_cmd_received);
	}
}


//////////////////////////////////////////////////////////////////
// 该函数由initiator执行，当initiator发出一个事务时调用router的fw方法，
// 并尝试将事务推送到buffer中
//////////////////////////////////////////////////////////////////
tlm_sync_enum Router::nb_transport_fw( int					id,
							           tlm_generic_payload	&payload,
                                       tlm_phase			&phase,
                                       sc_time				&time)
{	
#ifdef DEBUG_MODULE
	cout << "    " << name() << " recv cmd from init" << id << "  / time = " << (int)time.value() << endl;
#endif

	bool push = false;
	do
	{
		push = m_central_buffer.push(id, payload, phase, time);
		if (not push)	// push失败
		{
#ifdef DEBUG_MODULE
			cout << "   init" << id << "cannot push into buffer" << endl;
#endif
			// sc_core::next_trigger(sc_core::SC_ZERO_TIME);
			sc_core::wait(sc_core::SC_ZERO_TIME);
		} 
		else			// push成功
		{
#ifdef DEBUG_MODULE
			cout << "    " <<  name() << " push cmd into buffer / time = " << (int)time.value()
				 << endl;
#endif

			m_cmd_received.notify(sc_core::SC_ZERO_TIME);
		}
	} while (not push);

	return tlm::TLM_COMPLETED;
}


tlm_sync_enum Router::nb_transport_bw( int 					id,
                                       tlm_generic_payload	&payload,
                                       tlm_phase 			&phase,
							           sc_time				&time)
{
	cout << name() << "receive rsp from target" << id << endl;

	for (unsigned int i = 0; i < N_INIT; i++)
		(*targ_socket[i])->nb_transport_bw(payload, phase, time);
	return tlm::TLM_ACCEPTED;
}


unsigned int Router::decode_address( uint64		address,
							         uint64		&masked_address)
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
