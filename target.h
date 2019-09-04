/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 09:32
 * Update time   : 2019-06-19 12:15
 * Description   :
 *	
******************************************************/

#ifndef __TARGET_H__
#define __TARGET_H__

#include "common.h"
#include "circular_buffer.h"

class Target
	: public sc_module
	,public tlm::tlm_fw_transport_if<mydma_protocol_types>
	,public tlm::tlm_bw_transport_if<mydma_protocol_types>
{
public:

	enum { SIZE = 1024 };

	const sc_time 		LATENCY;
	unsigned int 		mem[SIZE];
	unsigned int mem_nr=0;
	soclib::tlmdt::circular_buffer*	target_buffer;
	unsigned int 		m_device_ID;		// 模块唯一地址，用于寻址
	unsigned int CSR[3]={0,0,0};
	unsigned int check_enable=1;

	void check_on()
	{
		check_enable=1;
	}

	void check_off()
	{
		check_enable=0;
	}

	virtual tlm_sync_enum nb_transport_fw(	tlm_generic_payload	&trans, 
									tlm_phase			&phase, 
									sc_time				&delay);

	virtual tlm_sync_enum nb_transport_bw (	tlm_generic_payload	&trans, 
									tlm_phase			&phase, 
									sc_time				&delay){}

	
	virtual void invalidate_direct_mem_ptr(
		sc_dt::uint64 start_range,
		sc_dt::uint64 end_range){}


	virtual void b_transport(
		tlm::tlm_generic_payload &trans,
		sc_core::sc_time &t){}

	virtual bool get_direct_mem_ptr(
		tlm::tlm_generic_payload &trans,
		tlm::tlm_dmi &dmi_data){return false;}

	virtual unsigned int transport_dbg(
		tlm::tlm_generic_payload &trans){return 0;}

	SC_HAS_PROCESS(Target);

public:

	tlm::tlm_target_socket<256,mydma_protocol_types> targ_socket;

   Target( sc_core::sc_module_name name,
				unsigned int 			device_ID )
	: sc_module( name )
{
	target_buffer=new soclib::tlmdt::circular_buffer();
	m_device_ID=device_ID;
	targ_socket.bind(*this);
	CSR[0]=0;
	CSR[1]=0;
	CSR[2]=0;
	// 随机初始化模块内存
	for (int i = 0; i < SIZE; i++)
		mem[i] = 0xAA000000 | (mem_nr << 20) | (rand() % 256);

	++mem_nr;
}

	~Target() {}

};

#endif
