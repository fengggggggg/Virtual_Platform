/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-09 17:09
 * Update time   : 2019-06-19 12:15
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
	// 拆payload包
	// tlm_command		cmd   = payload.get_command();
	int			    adr   = payload.get_address();
	// 当address = -1时，表示该包为路由表建立请求包
	if (adr == 0xFF)
	{
		payload.set_address(m_device_ID);
		return TLM_ACCEPTED;
	}

	SRIO_FRAME* 	frame = (SRIO_FRAME*)payload.get_data_ptr();
	unsigned int    len   = payload.get_data_length();
	unsigned char*  byt   = payload.get_byte_enable_ptr();
	unsigned int    wid   = payload.get_streaming_width();
	
	// 拆SRIO帧
	DSPU32 target_id = (DSPU32)frame->TargetID;
	DSPU32 source_id = (DSPU32)frame->SourceID;
	DSPU32* data	 = (DSPU32*)frame->Data;
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;

	if (target_id != m_device_ID)
	{
		cout << "The wrong package was received\n";
		return TLM_COMPLETED;
	}

	size_t transaction_type;
	if (ftype == 0b0010 && ttype == 0b0100) {
		// NREAD Transaction
		transaction_type = 0;
	} else if (ftype == 0b0101 && ttype == 0b0100) {
		// NWRITE Transaction
		transaction_type = 1;
	} else if (ftype == 0b0101 && ttype == 0b0101) {
		// NWRITE_R Transaction
		transaction_type = 2;
	} else if (ftype == 0b1101 && ttype == 0b0000) {
		// 无有效数据负载的response
		transaction_type = 3;
	} else if (ftype == 0b1101 && ttype == 0b1000) {
		// 有有效数据负载的response
		transaction_type = 4;
	} else{
		// 其他类型事务或出错
		transaction_type = 5;
	}


	cout << "-----> "  << name() << " recv cmd = " << transaction_type
		 << " from = " << source_id << " data = " << data[0]
		 << " / time=" << sc_time_stamp() << endl << endl;

	// Obliged to check address range and check for unsupported features,
	//   i.e. byte enables, streaming, and bursts
	// Can ignore extensions

	// Generate the appropriate error response
	adr = adr / 4;
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
	// if ( cmd == TLM_READ_COMMAND )
		// memcpy(ptr, &mem[adr], len);
	// else if ( cmd == TLM_WRITE_COMMAND )
		// memcpy(&mem[adr], ptr, len);

	// Obliged to set response status to indicate successful completion
	payload.set_response_status( TLM_OK_RESPONSE );
	return TLM_ACCEPTED;
}

unsigned int Target::mem_nr = 0;
