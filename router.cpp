/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-05 09:38
 * Update time   : 2019-06-19 12:15
 * Description   : 
******************************************************************************/

#include "router.h"

Router::Router( sc_core::sc_module_name name,
				const size_t			router_id,
				const size_t			n_inits,
				const size_t			n_targs)
	: sc_module( name )
	, m_router_id( router_id )
	, m_inits( n_inits )
	, m_targs( n_targs )
	, m_central_buffer( "central_buffer", n_inits )
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

	SC_METHOD(maintain_table_thread);
	sensitive << maintain_table_clk.pos();

	SC_METHOD(execLoop);
	sensitive << clk.pos();
	dont_initialize();
}

// 动态构建路由表进程
void Router::maintain_table_thread()
{
#ifdef DEBUG_MODULE
	cout << "launch ctor_talbe_thread / time = " << sc_time_stamp() << endl;
#endif

	// 由Router向每个端口发送一个包，根据收到的响应中的信息修改路由表
	unsigned int num_socket = init_socket.size();
	for (unsigned int i = 0; i < num_socket; i++)
	{
		tlm_generic_payload* payload = new tlm_generic_payload;
		payload->set_command( static_cast<tlm_command>(-1) );
		// 目前所里使用address字段传输命令控制字，而我们的例子中仍然传输地址
		payload->set_address( 0xFF );
		payload->set_data_ptr( reinterpret_cast<unsigned char*>(-1) );
		payload->set_data_length( 4 );
		payload->set_streaming_width( 4 ); // = data_length to indicate no streaming
		payload->set_byte_enable_ptr( 0 ); // 0 indicates unused
		payload->set_dmi_allowed( false ); // Mandatory initial value
		payload->set_response_status( TLM_INCOMPLETE_RESPONSE );

		tlm_phase phase = tlm::BEGIN_REQ;

		(*init_socket[i])->nb_transport_fw(*payload, phase, time);

		unsigned int target_id = payload->get_address();

		// 包发送后，查找该地址在表中是否存在
		int port_id = routing_table.query_port(target_id);
		uint64 addr = routing_table.query_addr(i);

		if (port_id == -1 && (int)addr == -1) {
			// 当TargID在路由中不存在，且该端口为空时，将TargID-portID对添加进路由表
			routing_table.add_item(i, target_id);
		} else if (port_id == -1 && (int)addr != -1) {
			// 当targID在路由表中不存在，但该端口不空时，说明该端口对应的地址变动，需要更新路由表
			routing_table.update_item(i, target_id);
		}

	}
#ifdef DEBUG_MODULE
	routing_table.print_table();
#endif

	// 每4NS触发一次进程
	if (sc_time_stamp() < sc_time(10, SC_NS)) {
		next_trigger(4, SC_NS);
	} else {
		next_trigger(20, SC_NS);
	}
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
	// 拆帧
	SRIO_FRAME* frame = (SRIO_FRAME*)payload.get_data_ptr();
	// DSPU32 source_id = (DSPU32)frame->SourceID;
	DSPU32 target_id = (DSPU32)frame->TargetID;

	// uint64 address = payload.get_address();

	// 根据地址查端口
	int port_id = routing_table.query_port(target_id);

	if (port_id == -1)
	{
		cout << "Not found target_id in routing table.\n";
		return;
	}

#ifdef DEBUG_MODULE
	cout << "       route  the  cmd to   targ" << target_id << "     / time=" << sc_time_stamp() << endl;
#endif

	tlm_sync_enum fw_statu = (*init_socket[port_id])->nb_transport_fw(payload, phase, time);

	if (fw_statu != tlm::TLM_ACCEPTED)
	{
		cout << "forward error in " << name() << " ----> target" << endl;
	} else if ( payload.is_response_error() )
	{
		cout << payload.get_response_string().c_str() << endl;
	} 
}


void Router::execLoop()
{
#ifdef DEBUG_MODULE
	cout << name() << " launch execLoop                / time=" << sc_time_stamp() << endl;
#endif

	size_t						from;
	tlm::tlm_generic_payload*	payload_ptr;
	tlm::tlm_phase*				phase_ptr;
	sc_core::sc_time*			time_ptr;

	while (m_central_buffer.pop(from, payload_ptr, phase_ptr, time_ptr))
	{
		route(from, *payload_ptr, *phase_ptr, *time_ptr);
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
	cout << "       " << name() << " recv cmd from init" << id << "     / time=" << sc_time_stamp() << endl;
#endif

	bool push = false;
	do
	{
		push = m_central_buffer.push(id, payload, phase, time);
		if (not push)	// push失败
		{
#ifdef DEBUG_MODULE
			cout << "      init" << id << "cannot push into buffer" << endl;
#endif
		} 
		else			// push成功
		{
#ifdef DEBUG_MODULE
			cout << "       " <<  name() << " push cmd into buffer    / time=" << sc_time_stamp() << endl;
#endif
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
