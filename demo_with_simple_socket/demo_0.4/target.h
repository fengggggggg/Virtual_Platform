/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 09:32
 * Update time   : 2019-05-27 18:53
 * Description   :
 *	1.	target中定义fw函数，该函数由initiator(即router)调用
******************************************************/
#ifndef __TARGET_H__
#define __TARGET_H__

// Needed for the simple_target_socket
#include "common.h"


class Target
	: public sc_core::sc_module
{
private:

	enum { SIZE = 256 };
	const sc_time LATENCY;

	int mem[SIZE];
	static unsigned int mem_nr;

	// TLM-2 blocking transport method
	tlm_sync_enum nb_transport_fw (	tlm_generic_payload& trans, 
											tlm_phase& phase, 
											sc_time& delay );

protected:

	SC_HAS_PROCESS(Target);

public:
	// TLM-2 socket, defaults to 32-bits wide, base protocol
	tlm_utils::simple_target_socket<Target> targ_socket;

	Target(sc_core::sc_module_name name);

	~Target() {}

};

#endif
