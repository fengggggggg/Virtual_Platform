/*
 *ddr.h
 *
 *Created on: Jun 5, 2014
 *Author:	liugu
*/
#ifndef DDR_H_
#define DDR_H_

#include "protocol.h"
#include "tlm_utils/peq_with_cb_and_phase.h"
using namespace tlm;
using namespace sc_core;


class ddr:
	public sc_module,
	public tlm_fw_transport_if<PROTOCOL_TYPE>
{
public:
	//DDR id
	unsigned int DDR_id;
	
	//signals
	sc_in_clk clk;		//module clock signal
	sc_module_name name;	//module name
	//sockets
	tlm_target_socket<128,PROTOCOL_TYPE> target_socket_from_mmac;

	//event queue
	tlm_utils::peq_with_cb_and_phase<ddr> m_peq;
	
	//Address space
	#define DDR_DEFAULT_LOW_ADDRESS0 0x80000000
	#define DDR_DEFAULT_LOW_ADDRESS1 0xc0000000
	#define DDR_DEFAULT_SIZE 0x200000	//1Gword
	//Base address, default:0x8000_0000~0xBFFF_FFFF
	unsigned int ddr_low_address;		
	//Space size, in word(32bits) default: 1G
	unsigned int ddr_size;			

	//Memory space
	unsigned int *memory;
	
	
	//Systemc and TLM functions
	SC_HAS_PROCESS(ddr);
	ddr(unsigned int id, sc_module_name module_name);
	~ddr();

	virtual tlm_sync_enum nb_transport_fw(
			tlm_generic_payload&trans,
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
	void reset();
	void NotifyDDRLowAddr(unsigned int low_addr){ddr_low_address = low_addr;}
	void NotifyDDRSize(unsigned int size){ddr_size = size; }
	//PEQ callback function
	void peq_cb_send_RESP(tlm::tlm_generic_payload &trans,const tlm::tlm_phase &phase);
	
	//Interface for JTAG
	bool read_word(unsigned int addr,unsigned int &value);
	bool write_word(unsigned int addr,const unsigned int value);


#define DEBUG_out cout<<"["<<sc_time_stamp()<<"]"<<name<<": "
	
};



#endif


