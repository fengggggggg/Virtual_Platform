/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-09 17:09
 * Update time   : 2019-06-13 19:58
 * Description   : 
******************************************************************************/

#include "initiator.h"


Initiator::Initiator(sc_core::sc_module_name name)
{
    init_socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);

	SC_METHOD(thread_process);
	sensitive << clk.neg();
	dont_initialize();
}

void Initiator::thread_process()
{
	// 不加这个语句程序会出错
	// cout << endl;

#ifdef DEBUG_MODULE
	cout << name() << "  launch thread_process       / time="
		 << sc_time_stamp() << endl;
#endif

	if (i < 256 - 32)
	{
		emit_trsac(i);
		i += 4;
	} else
	{
	}
}

void Initiator::emit_trsac(unsigned int i)
{
	int data;
	tlm_generic_payload*	payload = new tlm_generic_payload;

	// cmd = 0 = read, cmd = 1 = write
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

	cout << "<----- " << name() << "  send cmd " << (cmd ? "W" : "R") 
		 << "           / time=" << sc_time_stamp() << endl;

	tlm_sync_enum fw_statu = init_socket->nb_transport_fw( *payload, phase, time );

	if (fw_statu != tlm::TLM_COMPLETED)
	{
		cout << "forward error in " << name() << " ----> router" << endl;
	}
}

tlm_sync_enum Initiator::nb_transport_bw( tlm_generic_payload   &payload,
                                          tlm_phase             &phase,
                                          sc_time               &time)
{
    return TLM_UPDATED;
}
