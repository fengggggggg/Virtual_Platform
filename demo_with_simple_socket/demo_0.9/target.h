/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 09:32
 * Update time   : 2019-06-16 20:30
 * Description   :
 *	
******************************************************/

#ifndef __TARGET_H__
#define __TARGET_H__

#include "common.h"

class Target
	: public sc_core::sc_module
{
private:

	enum { SIZE = 256 };

	const sc_time 		LATENCY;

	int 				mem[SIZE];
	static unsigned int mem_nr;

	unsigned int 		m_device_ID;		// 模块唯一地址，用于寻址

	tlm_sync_enum nb_transport_fw (	tlm_generic_payload	&trans, 
									tlm_phase			&phase, 
									sc_time				&delay );

protected:

	SC_HAS_PROCESS(Target);

public:

	tlm_utils::simple_target_socket<Target> targ_socket;

	Target( sc_core::sc_module_name name,
		    unsigned int 			device_ID );

	~Target() {}

};

#endif
