/******************************************************************************
 * Author        : feng
 * Creation time : 2019-05-17 10:28
 * Update time   : 2019-06-19 12:14
 * Description   : 
******************************************************************************/
#ifndef __INITIATOR_ADAPTER_H__
#define __INITIATOR_ADAPTER_H__

#include "common.h"

// Initiator module generating generic payload transactions
class Initiator_adapter
	: public sc_module
		,public tlm::tlm_fw_transport_if<mydma_protocol_types>
	,public tlm::tlm_bw_transport_if<mydma_protocol_types>
{
public:

	unsigned int 		m_deviceID; 		// m_address作为模块地址

	sc_core::sc_time 	time = sc_time(20, SC_NS);



virtual	tlm_sync_enum nb_transport_bw (	tlm_generic_payload	&payload,
									tlm_phase			&phase,
									sc_time				&time)
									{
										targ_socket->nb_transport_bw(payload,phase,time);
									}
 virtual   tlm_sync_enum nb_transport_fw (	tlm_generic_payload	&payload,
									tlm_phase			&phase,
									sc_time				&time)
                                    {
                                        init_socket->nb_transport_fw(payload,phase,time);
                                    }
tlm_sync_enum nb_transport_bw_ (	tlm_generic_payload	&payload,
									tlm_phase			&phase,
									sc_time				&time)
									{
										targ_socket->nb_transport_bw(payload,phase,time);
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


	SC_HAS_PROCESS(Initiator_adapter);

public:

//	sc_core::sc_in_clk								clk;	// 输入时钟信号，用于驱动模块

    tlm::tlm_target_socket<256,mydma_protocol_types> targ_socket;
	tlm_utils::simple_initiator_socket<Initiator_adapter>	init_socket;

	Initiator_adapter( sc_core::sc_module_name 	name,
			   unsigned int 			device_ID ):
               sc_module(name),m_deviceID(device_ID)
               {
                targ_socket.bind(*this);
				init_socket.register_nb_transport_bw(this,&Initiator_adapter::nb_transport_bw_);
               }

	~Initiator_adapter() {}

};

#endif
