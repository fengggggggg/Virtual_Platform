/******************************************************************************
 * Author        : feng
 * Creation time : 2019-05-17 10:28
 * Update time   : 2019-06-19 12:14
 * Description   : 
******************************************************************************/
#ifndef __INITIATOR_H__
#define __INITIATOR_H__

#include "common.h"

// Initiator module generating generic payload transactions

class Initiator
	: public sc_module
	,public tlm::tlm_fw_transport_if<mydma_protocol_types>
	,public tlm::tlm_bw_transport_if<mydma_protocol_types>
{
public:

	unsigned int 		m_deviceID; 		// m_address作为模块地址

	sc_core::sc_time 	time = sc_time(4, SC_NS);

	tlm::tlm_initiator_socket<256,mydma_protocol_types>	init_socket;
	// tlm::tlm_target_socket<256,mydma_protocol_types>	targ_socket;

	unsigned int global_id=0;
	sc_core::sc_time init_time=sc_time(4,SC_NS);
	tlm_phase init_phase = tlm::BEGIN_REQ;
	tlm_generic_payload*	init_payload = new tlm_generic_payload;
	unsigned int pktid=0;
	int count=-1;
	int check_response=1;        //当该标志位为1时，发送初始化维护读数据包
	unsigned int switch_array[256]={0};
	int switch_index=-1;
	unsigned int check_read_switch=0;       //该标志1时，表示收到switch读响应，
	unsigned int check_write_switch=0;       //该标志1时，表示收到switch写响应，
	unsigned int check_read_endpoint=0; //该标志1时，表示收到endpoint读响应，
	unsigned int check_write_endpoint=0; //该标志1时，表示收到endpoint写响应，
	unsigned int dengdaixiangying=1;     
	unsigned int dengdaixiangying1=0; 
	//dengdaixiangying表示期望收到几个响应包，dengdaixiangying1表示目前收到几个响应包，
	//当dengdaixiangying==dengdaixiangying1时，则设置上面某个标志位为1
	//利用dengdaixiangying和dengdaixiangying1作为期望接收几个响应的处理
	unsigned int start_flag=1;
	unsigned int end_flag=1;       //当end_flag=0时，表示系统初始化枚举过程结束
	unsigned int CSR[3]={0,0,0};
	//register CSR分别代表masterenable,discovered,deviceid;

	void thread_process();

	void emit_trsac();

	tlm_generic_payload* generate_payload();

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


virtual	tlm_sync_enum nb_transport_fw(	tlm_generic_payload	&payload,
									tlm_phase			&phase,
									sc_time				&time)
									{
										cout<<"success"<<endl;
									}

virtual	tlm_sync_enum nb_transport_bw (	tlm_generic_payload	&payload,
									tlm_phase			&phase,
									sc_time				&time);

void switch_response();

void endpoint_response(int hop_count,int way);

void enumeration();

void check();
									

	SC_HAS_PROCESS(Initiator);

public:

	sc_core::sc_in_clk								clk;	// 输入时钟信号，用于驱动模块
	sc_core::sc_in_clk								enum_clk;

	Initiator( sc_module_name 	name,
					  unsigned int 				device_ID,
					  unsigned int base_ID )
	: sc_module( name )
	{
	m_deviceID=device_ID;
    init_socket.bind(*this);
	// targ_socket.bind(*this);
	CSR[0]=1;
	CSR[1]=1;
	CSR[2]=0xff;
	CSR[2]=base_ID;

	SC_METHOD(check);
	sensitive << enum_clk.pos();	

	SC_METHOD(thread_process);
	sensitive << clk.neg();		// 该模块对时钟下降沿敏感，进程在每个下降沿执行一次
	dont_initialize();
	}

	~Initiator() {}

};

#endif
