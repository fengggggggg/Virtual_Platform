#ifndef INITIATOR_H
#define INITIATOR_H

#include "systemc.h"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

//#include "tlm.h"
#include <tlm>
#include "tlm_utils/simple_initiator_socket.h"


// Initiator module generating generic payload transactions

SC_MODULE(Initiator)
//struct Initiator: sc_module
{
	// TLM-2 socket, defaults to 32-bits wide, base protocol
	tlm_utils::simple_initiator_socket<Initiator>		socket;

	SC_CTOR(Initiator)
	: socket("socket")  // Construct and name socket
	{
		// Register callbacks for incoming interface method calls
		socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);

		SC_THREAD(thread_process);
	}

	void thread_process()
	{
		// TLM-2 generic payload transaction, reused across calls to b_transport, DMI and debug
		tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
		sc_time delay = sc_time(10, SC_NS);

		// Generate a random sequence of reads and writes
		for (int i = 256-64; i < 256+64; i += 4)
		{
			int data;

			// 随机生成cmd命令
			// cmd为读/写命令，值为0/1，cmd=0时代表读请求，cmd=1时代表写请求
			tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
			if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;
      
			trans->set_command( cmd );
			trans->set_address( i );
			trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
			trans->set_data_length( 4 );
			trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
			trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
			trans->set_dmi_allowed( false ); // Mandatory initial value
			trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value
      
			tlm::tlm_phase phase = tlm::BEGIN_REQ;

			socket->nb_transport_fw( *trans, phase, delay );

			// Initiator obliged to check response status
			if ( trans->is_response_error() )
			{
				// Print response string
				char txt[100];
				sprintf(txt, "Error from b_transport, response status = %s",
                     trans->get_response_string().c_str());
				SC_REPORT_ERROR("TLM-2", txt);

			}

			cout << "trans = {" << (cmd ? 'W' : 'R') << ", " << hex << i
				<< "} , data = " << hex << data << " at time " << sc_time_stamp() << endl;
     
		}
	}

	// TLM-2 backward DMI method
	virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans, tlm::tlm_phase &phase,  sc_time& delay)
	{
		// Ignore range and invalidate all DMI pointers regardless
		// do nothing
		return tlm::TLM_UPDATED;
	}

};

#endif
