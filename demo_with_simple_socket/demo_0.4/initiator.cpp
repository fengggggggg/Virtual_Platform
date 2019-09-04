#include "initiator.h"

Initiator::Initiator(sc_core::sc_module_name name)
{
    init_socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);

    SC_THREAD(thread_process);
}

void Initiator::thread_process()
{
    // TLM-2 generic payload transaction, reused across calls to b_transport, DMI and debug
	tlm_generic_payload* trans = new tlm_generic_payload;
	sc_time delay = sc_time(10, SC_NS);

	// Generate a random sequence of reads and writes
	for (int i = 256-64; i < 256+64; i += 4)
	{
		int data;

		// 随机生成cmd命令
		// cmd为读/写命令，值为0/1，cmd=0时代表读请求，cmd=1时代表写请求
		tlm_command cmd = static_cast<tlm_command>(rand() % 2);
		if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;
      
		trans->set_command( cmd );
		trans->set_address( i );
		trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
		trans->set_data_length( 4 );
		trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
		trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
		trans->set_dmi_allowed( false ); // Mandatory initial value
		trans->set_response_status( TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value
			
		tlm_phase phase = tlm::BEGIN_REQ;

		init_socket->nb_transport_fw( *trans, phase, delay );

		// Initiator obliged to check response status
		if ( trans->is_response_error() )
		{
			// Print response string
			char txt[100];
			sprintf(txt, "Error from b_transport, response status = %s",
                    trans->get_response_string().c_str());
			SC_REPORT_ERROR("TLM-2", txt);
		} 
	}
}

tlm_sync_enum Initiator::nb_transport_bw( tlm_generic_payload   &trans,
                                          tlm_phase             &phase,
                                          sc_time               &time)
{
    return TLM_UPDATED;
}
