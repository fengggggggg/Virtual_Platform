/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-09 17:09
 * Update time   : 2019-06-09 17:09
 * Description   : 
******************************************************************************/

#include "initiator.h"

Initiator::Initiator(sc_core::sc_module_name name)
{
    init_socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);

    SC_THREAD(thread_process);
}

void Initiator::thread_process()
{
	cout << "launch thread_process / time = " << (int)time.value() << endl;
	// Generate a random sequence of reads and writes
	for (int i = 256-64; i < 256+64; i += 4)
	{
		emit_trsac(i);
	}
}

void Initiator::emit_trsac(unsigned int i)
{
	int data;
	tlm_generic_payload*	payload = new tlm_generic_payload;

	// 随机生成cmd命令
	// cmd为读/写命令，值为0/1，cmd=0时代表读请求，cmd=1时代表写请求
	tlm_command cmd = static_cast<tlm_command>(rand() % 2);
	if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;
      
	payload->set_command( cmd );
	payload->set_address( i );
	payload->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
	payload->set_data_length( 4 );
	payload->set_streaming_width( 4 ); // = data_length to indicate no streaming
	payload->set_byte_enable_ptr( 0 ); // 0 indicates unused
	payload->set_dmi_allowed( false ); // Mandatory initial value
	payload->set_response_status( TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value
			
	tlm_phase phase = tlm::BEGIN_REQ;

	cout << "@@@ " << name() << "  send cmd " << (cmd ? "W" : "R") << "           / time = "
		 << (int)time.value() << endl;

	init_socket->nb_transport_fw( *payload, phase, time );

	sc_core::wait(100, SC_NS);

	if ( payload->is_response_error() )
	{
		// Print response string
		char txt[100];
		sprintf(txt, "Error from b_transport, response status = %s",
                payload->get_response_string().c_str());
		SC_REPORT_ERROR("TLM-2", txt);
	} 
}

tlm_sync_enum Initiator::nb_transport_bw( tlm_generic_payload   &payload,
                                          	tlm_phase             &phase,
                                          	sc_time               &time)
{
    return TLM_UPDATED;
}
