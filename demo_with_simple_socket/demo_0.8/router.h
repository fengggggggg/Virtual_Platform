/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 23:09
 * Update time   : 2019-06-16 20:30
 * Description   : 
*	1.	在RapidIO中，系统的每个可直接寻址设备有一个或多个独占的设备标识符。
* 		产生包时，SrcID和TargID放在包头。目的设备在产生响应包时会使用SrcID，
* 		并交还SrcID和TargID。
	2.	RapidIO互联结构中每一个交换机都有一个路由查询表，指示交换机将包
		从输入端口路由到输出端口。最简单的形式是在任意两个设备之间只允许存在
		一条路径。更复杂的方法是自适应路由以提高冗余并减缓拥塞。
	3.	板卡级模拟中，4个DSP直连到Router中，任意2个DSP之间的路径是唯一的
		因此考虑使用第一种简单的路由机制。
	4.	系统级模拟中，各板卡可能会构成网格结构，其路由机制可另行处理
	5.	路由不必有DeviceID
	6.	目前考虑对于板卡内，不构建路由表。每个路由维护一个端口——设备对应表。
		对于多板卡则构建一个全局路由表
******************************************************/

#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "common.h"
#include "centralized_buffer.h"

class Router
	: sc_core::sc_module
{

private:
	//////////////////////////////////////////////////////
	// Member Variables
	//////////////////////////////////////////////////////
	
	size_t								m_inits;			// number of initiators
	size_t								m_targs;			// number of targets

	soclib::tlmdt::centralized_buffer	m_central_buffer;	// input fifos

	// sc_core::sc_event					m_cmd_received;		// any command received

	//////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////
	
	void execLoop();

	void route( size_t						from,
				tlm::tlm_generic_payload	&payload,
				tlm::tlm_phase				&phase,
				sc_core::sc_time			&time);

	tlm_sync_enum nb_transport_fw( int					id,
								   tlm_generic_payload	&payload, 
								   tlm_phase			&phase,
								   sc_time				&time);
  
	tlm_sync_enum nb_transport_bw( int 					id, 
								   tlm_generic_payload	&payload, 
								   tlm_phase 			&phase,
								   sc_time				&time);

protected:

	SC_HAS_PROCESS(Router);

public:

	sc_in_clk											clk;

	vector<simple_target_socket_tagged<Router> *>		targ_socket;
	vector<simple_initiator_socket_tagged<Router> *>	init_socket;

	Router( sc_core::sc_module_name		name,
			const size_t				n_inits,
			const size_t				n_targs);

	~Router() {}

};

#endif
