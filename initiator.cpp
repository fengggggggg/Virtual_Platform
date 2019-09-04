/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-09 17:09
 * Update time   : 2019-06-19 12:15
 * Description   : 
******************************************************************************/

#include "initiator.h"


Initiator::Initiator( sc_core::sc_module_name 	name,
					  unsigned int 				device_ID )
	: sc_module( name )
	, m_deviceID( device_ID )
	, init_socket( "socket")
{
    init_socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);

	SC_METHOD(thread_process);
	sensitive << clk.neg();		// 该模块对时钟下降沿敏感，进程在每个下降沿执行一次
	dont_initialize();
}

void Initiator::thread_process()
{
#ifdef DEBUG_MODULE
	cout << name() << "  launch thread_process          / time="
		 << sc_time_stamp() << endl;
#endif

	emit_trsac();
}

tlm_generic_payload* Initiator::generate_payload()
{
	
	// 假设targ的地址为0 ~ N_TARG，随机产生
	unsigned int address = rand() % N_TARG;

	tlm_generic_payload*	payload = new tlm_generic_payload;

	// cmd = 0 = NREAD, cmd = 1 = NWRITE, cmd = 2 = NWRITE_R
	tlm_command cmd = static_cast<tlm_command>(rand() % 3);

	SRIO_FRAME* frame = new SRIO_FRAME;
	frame->TT = 0b00;
	frame->TargetID = 0b00000000 | address;
	frame->SourceID = 0b00000000 | m_deviceID;

	if (cmd == 0)
	{	// NREAD
		frame->Ftype = 0b0010;
		frame->Ttype = 0b0100;
	} else if (cmd == 1)
	{	// NWRITE
		frame->Ftype = 0b0101;
		frame->Ttype = 0b0100;
	}
	else
	{	// NWRITE_R
		frame->Ftype = 0b0101;
		frame->Ttype = 0b0101;
	}

	frame->Data[0] = rand() % 1000;

	payload->set_command( cmd );
	// 目前所里使用address字段传输命令控制字，而我们的例子中仍然传输地址
	payload->set_address( address );
	// payload->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
	// payload->set_data_ptr( reinterpret_cast<unsigned char*>(&frame) );
	payload->set_data_ptr((unsigned char*)frame);
	payload->set_data_length( 4 );
	payload->set_streaming_width( 4 ); // = data_length to indicate no streaming
	payload->set_byte_enable_ptr( 0 ); // 0 indicates unused
	payload->set_dmi_allowed( false ); // Mandatory initial value
	payload->set_response_status( TLM_INCOMPLETE_RESPONSE ); 

	cout << "<----- " << name() << " send cmd = " << cmd
		 << " addr = " << frame->TargetID << " data = "
		 << frame->Data[0] << " / time=" << sc_time_stamp() << endl;

	return payload;
}

void Initiator::emit_trsac()
{

	tlm_generic_payload* payload = generate_payload();
			
	tlm_phase phase = tlm::BEGIN_REQ;

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
