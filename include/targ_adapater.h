/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 09:32
 * Update time   : 2019-06-19 12:15
 * Description   :
 *	
******************************************************/
#ifndef __TARGET_ADAPTER_H__
#define __TARGET_ADAPTER_H__

#include "common.h"

class Target_adapter
	: public sc_module
	 ,public tlm::tlm_fw_transport_if<mydma_protocol_types>
	,public tlm::tlm_bw_transport_if<mydma_protocol_types>
{
public:

	enum { SIZE = 1024 };

	const sc_time 		LATENCY;

	unsigned int 				mem[SIZE];
	static unsigned int mem_nr;

	unsigned int 		m_device_ID;		// 模块唯一地址，用于寻址

virtual	tlm_sync_enum nb_transport_fw (	tlm_generic_payload	&payload, 
									tlm_phase			&phase, 
									sc_time				&delay )
                            {
								//该nb_transport_fw仅供发送方的tlm_init_socket使用
                                init_socket->nb_transport_fw(payload,phase,delay);
                            }
 virtual   tlm_sync_enum nb_transport_bw (	tlm_generic_payload	&payload, 
									tlm_phase			&phase, 
									sc_time				&delay )
                                    {
										targ_socket->nb_transport_bw(payload,phase,delay);
                                    }

tlm_sync_enum nb_transport_fw_ (	tlm_generic_payload	&payload, 
									tlm_phase			&phase, 
									sc_time				&delay )
                            {
                                init_socket->nb_transport_fw(payload,phase,delay);
								//该方法使用的是接收方的tlm_targ_socket的nb_transport_socket方法
                            }

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


	SC_HAS_PROCESS(Target_adapter);

public:

	tlm_utils::simple_target_socket<Target_adapter> targ_socket;
    tlm::tlm_initiator_socket<256,mydma_protocol_types> init_socket;

	Target_adapter( sc_core::sc_module_name name,
		    unsigned int 			device_ID ):
            sc_module(name),m_device_ID(device_ID)
    {
		init_socket.bind(*this);
        targ_socket.register_nb_transport_fw(this,&Target_adapter::nb_transport_fw_);
    }

	~Target_adapter() {}

};

#endif
