/******************************************************************************
 * Author        : feng
 * Creation time : 2019-05-17 10:28
 * Update time   : 2019-06-09 17:08
 * Description   : 
******************************************************************************/
#ifndef __INITIATOR_H__
#define __INITIATOR_H__

#include "common.h"

// Initiator module generating generic payload transactions

class Initiator
	:public sc_core::sc_module
{
private:

	void thread_process();

	void emit_trsac(unsigned int i);

	// TLM-2 backward DMI method
	tlm_sync_enum nb_transport_bw (	tlm_generic_payload	&payload,
									tlm_phase			&phase,
									sc_time				&time);

protected:

	SC_HAS_PROCESS(Initiator);

public:

	sc_core::sc_time 	time = sc_time(0, SC_NS);
	
	unsigned int 		i = 256 - 64;

	sc_core::sc_in_clk	clk;

	tlm_utils::simple_initiator_socket<Initiator>	init_socket;

	Initiator(sc_core::sc_module_name name);

	~Initiator() {}

};

#endif
