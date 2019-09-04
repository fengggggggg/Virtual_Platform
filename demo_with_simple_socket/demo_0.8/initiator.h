/******************************************************************************
 * Author        : feng
 * Creation time : 2019-05-17 10:28
 * Update time   : 2019-06-16 20:30
 * Description   : 
******************************************************************************/
#ifndef __INITIATOR_H__
#define __INITIATOR_H__

#include "common.h"

// Initiator module generating generic payload transactions

class Initiator
	: public sc_core::sc_module
{
private:

	unsigned int 		m_device_ID; 		// m_address作为模块地址

	sc_core::sc_time 	time = sc_time(0, SC_NS);

	void thread_process();

	void emit_trsac();

	tlm_generic_payload* generate_payload();

	tlm_sync_enum nb_transport_bw (	tlm_generic_payload	&payload,
									tlm_phase			&phase,
									sc_time				&time);

protected:

	SC_HAS_PROCESS(Initiator);

public:

	sc_core::sc_in_clk	clk;	// 输入时钟信号，用于驱动模块

	tlm_utils::simple_initiator_socket<Initiator>	init_socket;

	Initiator( sc_core::sc_module_name 	name,
			   unsigned int 			device_ID );

	~Initiator() {}

};

#endif
