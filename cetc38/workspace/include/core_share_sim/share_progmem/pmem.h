/*
 *pmem.h
 *
 *Created on: Jun 5, 2014
 *Author:	liugu
*/
#ifndef PMEM_H_
#define PMEM_H_

#include "protocol.h"
#include "tlm_utils/peq_with_cb_and_phase.h"
using namespace tlm;
using namespace sc_core;
using namespace std;

class pmem:
	public sc_module,
	public tlm_fw_transport_if<PROTOCOL_TYPE>
{
//	#define USING_PEQ_WITH_CB_AND_PHASE			//Turn this off when using self-managed request queue

public:
	struct request_item{
	// typedef struct request_item{
		tlm_generic_payload * p_trans;
		tlm_phase phase;
		sc_time delay_timer;
		request_item(){
			//Default constructor
			p_trans =  NULL;
			phase = 0;
			delay_timer = SC_ZERO_TIME;
		}
		request_item(tlm_generic_payload * t,tlm_phase p, sc_time d){
			//constructor
			p_trans = t;
			phase = p;
			delay_timer = d;
		}
	};

	//signals
	sc_in_clk clk;		//module clock signal
	sc_module_name name;	//module name
	//sockets
	tlm_target_socket<512,PROTOCOL_TYPE> target_socket_from_mmac;

	//event queue
	#ifdef USING_PEQ_WITH_CB_AND_PHASE
	tlm_utils::peq_with_cb_and_phase<pmem> m_peq;
	#else
	vector<request_item> v_request;			//Self-managed request event queue;
	#endif

	//Address space
	#define PMEM_DEFAULT_LOW_ADDRESS 0x0b000000		//ROM
	#define PMEM_DEFAULT_SIZE 0x200000
	//Base address, default:0x0000_0000~0x001F_FFFF
	unsigned int pmem_low_address;		
	//Space size, in word(32bits) default: 2M
	unsigned int pmem_size;			

	//Memory space
	unsigned int *memory;
	
	
	//Systemc and TLM functions
	SC_HAS_PROCESS(pmem);
	pmem(sc_module_name module_name);
	~pmem();

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
	void setStartPC(unsigned int p_StartPC);
	void NotifyPMEMLowAddr(unsigned int low_addr){ pmem_low_address = low_addr;}
	void NotifyPMEMSize(unsigned int size){ pmem_size = size; }
	#ifdef USING_PEQ_WITH_CB_AND_PHASE
	//PEQ callback function
	void peq_cb_send_RESP(tlm::tlm_generic_payload &trans,const tlm::tlm_phase &phase);
	#else
	//Self-managed request event queue function
	void send_RESP(tlm::tlm_generic_payload &trans,const tlm::tlm_phase &phase);
	#endif
	//Interface for JTAG
	bool read_word(unsigned int addr,unsigned int &value);
	bool write_word(unsigned int addr,const unsigned int value);


#define DEBUG_out cout<<"["<<sc_time_stamp()<<"]"<<name<<": "
	
};



#endif


