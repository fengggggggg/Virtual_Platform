#ifndef BRIDGE_MODULE_H_
#define BRIDGE_MODULE_H_

#include "../../dmac_sim/dmac_global.h"


class Bridge_MODULE : public sc_module 
	,public tlm::tlm_bw_transport_if<mydma_protocol_types>
	,public tlm::tlm_fw_transport_if<mydma_protocol_types>{

public:	
	sc_in_clk clk;

	SC_HAS_PROCESS(Bridge_MODULE);

	Bridge_MODULE(sc_module_name mn);
	~Bridge_MODULE(){}


	virtual tlm::tlm_sync_enum nb_transport_bw(
		tlm::tlm_generic_payload &trans,
		tlm::tlm_phase &phase,
		sc_core::sc_time &t);

	virtual void invalidate_direct_mem_ptr(
		sc_dt::uint64 start_range,
		sc_dt::uint64 end_range){}

	virtual tlm::tlm_sync_enum nb_transport_fw(
		tlm::tlm_generic_payload &trans,
		tlm::tlm_phase &phase,
		sc_core::sc_time &t);

	virtual void b_transport(
		tlm::tlm_generic_payload &trans,
		sc_core::sc_time &t){}

	virtual bool get_direct_mem_ptr(
		tlm::tlm_generic_payload &trans,
		tlm::tlm_dmi &dmi_data){return false;}

	virtual unsigned int transport_dbg(
		tlm::tlm_generic_payload &trans){return 0;}


	void clock_tick();


	//tlm::tlm_initiator_socket	<CH_WIDTH_32,mydma_protocol_types> init_socket2AHB; //32 init for bridge
	tlm::tlm_target_socket		<CH_WIDTH_32,mydma_protocol_types> targ_socket2AHB; //32 targ for bridge
	
	tlm::tlm_initiator_socket	<CH_WIDTH_32,mydma_protocol_types> init_socket2APB; //32 init for bridge
	//tlm::tlm_target_socket		<CH_WIDTH_32,mydma_protocol_types> targ_socket2APB; //32 targ for bridge
};




#endif