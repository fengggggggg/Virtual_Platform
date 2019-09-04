/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-09 17:09
 * Update time   : 2019-06-16 20:31
 * Description   : 
******************************************************************************/

#include "target.h"

Target::Target( sc_core::sc_module_name name,
				unsigned int 			device_ID )
	: sc_module( name )
	, m_device_ID( device_ID )
	, targ_socket( "targ_socket" )
{
	targ_socket.register_nb_transport_fw( this, &Target::nb_transport_fw);

	// 随机初始化模块内存
	for (int i = 0; i < SIZE; i++)
		mem[i] = 0xAA000000 | (mem_nr << 20) | (rand() % 256);

	++mem_nr;
}

tlm_sync_enum Target::nb_transport_fw( tlm_generic_payload  &payload, 
									   tlm_phase            &phase, 
									   sc_time              &time )
{
	tlm_command		cmd = payload.get_command();
	sc_dt::uint64   adr = payload.get_address() / 4;
	unsigned char*  ptr = payload.get_data_ptr();
	unsigned int    len = payload.get_data_length();
	unsigned char*  byt = payload.get_byte_enable_ptr();
	unsigned int    wid = payload.get_streaming_width();

	cout << "-----> "  << name() << "  recv cmd " << (cmd ? "W" : "R")
		 << "           / time=" << sc_time_stamp() << endl;

	// cout << "data2 = " << &ptr << endl;

	// Obliged to check address range and check for unsupported features,
	//   i.e. byte enables, streaming, and bursts
	// Can ignore extensions

	// Generate the appropriate error response
	if (adr >= SIZE) {
		payload.set_response_status( TLM_ADDRESS_ERROR_RESPONSE );
		 return TLM_ACCEPTED;
	}
	if (byt != 0) {
		payload.set_response_status( TLM_BYTE_ENABLE_ERROR_RESPONSE );
		return TLM_ACCEPTED;
	}
	if (len > 4 || wid < len) {
		payload.set_response_status( TLM_BURST_ERROR_RESPONSE );
		return TLM_ACCEPTED;
	}

	// Obliged to implement read and write commands
	if ( cmd == TLM_READ_COMMAND )
		memcpy(ptr, &mem[adr], len);
	else if ( cmd == TLM_WRITE_COMMAND )
		memcpy(&mem[adr], ptr, len);

	// Obliged to set response status to indicate successful completion
	payload.set_response_status( TLM_OK_RESPONSE );
	return TLM_ACCEPTED;
}

unsigned int Target::mem_nr = 0;
