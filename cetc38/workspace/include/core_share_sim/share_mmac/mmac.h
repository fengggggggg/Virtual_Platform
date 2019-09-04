/*
 *mmac.h
 *
 *Created on: Jun 4, 2014
 *Author:	liugu
*/
#ifndef MMAC_H_
#define MMAC_H_

#include "protocol.h"
#include "extension.h"
#include "tlm_utils/peq_with_get.h"

#define CORE_NUMBER 2	//how many cores connected to mmac
#define DDR_NUMBER 2		//how many DDRs connected to mmac

using namespace tlm;
using namespace sc_core;

class mmac:
	public sc_module,
	public tlm_bw_transport_if<PROTOCOL_TYPE>,
	public tlm_fw_transport_if<PROTOCOL_TYPE>
{
public:
	//signals
	sc_in_clk clk;		//module clock signal
	sc_module_name name;	//module name
	//sockets
	tlm_target_socket<512,PROTOCOL_TYPE> target_socket_from_core[CORE_NUMBER];
	tlm_initiator_socket<512,PROTOCOL_TYPE> initiator_socket_to_pmem;
	tlm_initiator_socket<128,PROTOCOL_TYPE> initiator_socket_to_ddr[DDR_NUMBER];

	//PEQ for downstream, which contains all pending REQs from cores
	tlm_utils::peq_with_get<tlm::tlm_generic_payload> m_arbiter_PEQ;
	//PEQs for upstream, which contains all pending RESPs to cores
	tlm_utils::peq_with_get<tlm::tlm_generic_payload> m_back_PEQ;

	//Systemc and TLM functions
	SC_HAS_PROCESS(mmac);
	mmac(sc_module_name module_name);
	~mmac(){}

	virtual tlm_sync_enum nb_transport_bw(
			tlm_generic_payload &trans,
			tlm_phase &phase,
			sc_time &t);
	virtual void invalidate_direct_mem_ptr(
			sc_dt::uint64 start_range,
			sc_dt::uint64 end_range){}
	virtual tlm_sync_enum nb_transport_fw(
			tlm_generic_payload &trans,
			tlm_phase &phase,
			sc_time &t);
	virtual void b_transport(
			tlm_generic_payload &trans,
			sc_time &t){}
	virtual bool get_direct_mem_ptr(
			tlm_generic_payload &trans,
			tlm_dmi &dmi_data){return false;}
	virtual unsigned int transport_dbg(
			tlm_generic_payload &trans){return 0;}
	//Internal logic functions
	void clock_tick();
	
	//Call back functions for PEQs
	void arbiter_method();
	void response_method();
	
	unsigned int StartPC;
	void setStartPC(unsigned int p_StartPC);

#define DEBUG_out cout<<"["<<sc_time_stamp()<<"]"<<name<<": "

};



#endif

