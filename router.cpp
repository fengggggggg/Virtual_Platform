/******************************************************************************
 * Author        : cai
 * Creation time : 2019-06-05 09:38
 * Update time   : 2019-06-19 12:15
 * Description   : 
 * 1.考虑到实现的规范化,所有响应应该均采取nb_transport_bw函数实现,bw函数采取直通转发方式,
 * 并非fw函数采取存储转发方式,如果采取
 * payload.get_response方式获得,则会出现数据包被暂时缓存在switch中,而无法获得真实的响应情况
******************************************************************************/

#include "include/router.h"
#include "include/dispatch.h"
#include <string>
#include <sstream>

//n_inits参数实际上是router上target接口数,而n_targs则是router上init接口数
Router::Router( sc_core::sc_module_name name,
				const size_t			router_id,
				const size_t			n_inits,
				const size_t			n_targs)
	: sc_module( name )
	, m_router_id( router_id )
	, m_inits( n_inits )
	, m_targs( n_targs )
	, m_central_buffer( "central_buffer", n_inits )
{
    for (unsigned int i = 0; i < m_inits; i++)
	{
		char socket_name[30];
		sprintf(socket_name, "targ_socket_%d", i);
		targ_socket.push_back(new simple_target_socket_tagged<Router>(socket_name));

		targ_socket[i]->register_nb_transport_fw(this, &Router::nb_transport_fw, i);
	}

	for (unsigned int i = 0; i < m_targs; i++)
	{
		char socket_name[30];
		sprintf(socket_name, "init_socket_%d", i);
		init_socket.push_back(new simple_initiator_socket_tagged<Router>(socket_name));

		init_socket[i]->register_nb_transport_bw(this, &Router::nb_transport_bw, i);
	}

	//CSR寄存器通常用于标示发现位,设备ID等信息,而CAR寄存器则是记录交换芯片端口连接,默认端口等信息
	CSR[0]=0;
	CSR[1]=0;
	CSR[2]=0xff;

	CAR[0]=m_targs;
	CAR[1]=0x0;
	CAR[2]=0;

	// SC_METHOD(maintain_table_thread);
	// sensitive << maintain_table_clk.pos();

	// SC_METHOD(clear_multi_broad);
	// sensitive<<maintain_table_clk.pos();
	// dont_initialize();

	SC_METHOD(execLoop);
	sensitive << clk.neg();
	//加入dont_initialize()函数后就会从时钟定义开始执行，不会从0ns时开始执行
	dont_initialize();
}


void Router::clear_multi_broad()
{
	multi_pkt_index=0;
	broad_pkt_index=0;

#ifdef DEBUG_MODULE
	routing_table.print_table();
#endif
	cout<<"clear_multi_broad is executed  the time is"<<sc_time_stamp()<<endl;

	// 每4NS触发一次进程
	if (sc_time_stamp() < sc_time(0.5, SC_NS)) {
		next_trigger(10, SC_NS);
	} else {
		next_trigger(5, SC_NS);
	}
}

void Router::broad_cast( int 		from, 
				tlm_generic_payload	&payload, 
				tlm_phase 			&phase,
				sc_time				&time)
{
	cout<<"execute broadcast algorithms"<<endl;
	for(unsigned int i=0;i<m_inits;i++)
	{
		if(from!=i)
		{
			(*init_socket[i])->nb_transport_fw(payload,phase,time);
			//采取简化设计原则,广播和组播数据包无须响应数据包
		}
	}
}

void Router::multi_cast( int 		from, 
				tlm_generic_payload	&payload, 
				tlm_phase 			&phase,
				sc_time				&time)
{
	cout<<"execute mutli algorithms"<<endl;
	SRIO_FRAME* frame = (SRIO_FRAME*)payload.get_data_ptr();
	soclib_payload_extension* extension = new soclib_payload_extension;
	payload.get_extension(extension);                      //参数为soclib_payload_extension*类型
	
	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32* data	 = (DSPU32*)frame->Data;
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;
	multi_node* p=routing_table.query_multi_cast(target_id);
	if(p==NULL)
	{
		cout<<"not have this multi_cast group"<<endl;
	}
	else
	{
		for(unsigned int i=1;i<6;i++)
		{
			if(p->data[i]==1 && i!=from)
			{
				(*init_socket[i])->nb_transport_fw(payload,phase,time);
			}
		}
	}
}

//系统初始化枚举过程路由模块应该提供的功能
void Router::enumeration( int 		from, 
								   tlm_generic_payload	&payload, 
								   tlm_phase 			&phase,
								   sc_time				&time)
{
	// 拆payload
	SRIO_FRAME* frame = (SRIO_FRAME*)payload.get_data_ptr();
	soclib_payload_extension* extension = new soclib_payload_extension;
	payload.get_extension(extension);                      //参数为soclib_payload_extension*类型
	
	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32* data	 = (DSPU32*)frame->Data;
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;
	DSPU32 wdptr     =(DSPU32)frame->Wdptr;

	if(ttype==0b0000)
	{
			//首先需要添加一条默认路由,将未指定的设备地址路由到初始端口,该部分直接有CAR[1]表示
			command cmd=static_cast<command>(0%2);
			extension->set_command(cmd);
			extension->set_src_id(0x00);
			extension->set_trd_id(0xff);
			extension->set_pkt_id(5);

			frame->Ftype=0b1000;
			frame->Ttype=0b0010;

			//响应包数据部分第一个数据0表示switch信息,1表示endpoint响应
			frame->Data[0]=0;
			frame->Data[1]=CAR[0];
			CAR[1]=from;
			frame->Data[2]=CAR[1];
			frame->Data[3]=CAR[2];

			payload.set_data_ptr((unsigned char*)frame);
			payload.set_extension(extension);
			(*targ_socket[from])->nb_transport_bw(payload,phase,time);

	}
	else if(ttype==0b0001)
	{
		if(wdptr==0)
		{
			//添加路由信息,路由信息在数据负载部分
			for(unsigned int i=0;i<256;)
			{
				if(data[i]==0xff)
				{
					break;
				}
				routing_table.add_item(data[i],data[i+1]);
				// cout<<"i:"<<i<<" data[i]:"<<data[i]<<" data[i+1]:"<<data[i+1]<<" data[i+2]:"<<data[i+2]<<endl;
				i+=2;
			}
			if(routing_table.query_port(0xff)==-1)
			{
				unsigned int j;
				for(j=0;j<m_targs;j++)
				{
					if(routing_table.query_addr(j)==-1 && j!=CAR[1])
						break;
				}
				if(j<m_targs)
				{
					routing_table.add_item(0xff,j);
				}
				else
				{
					//后期修改下该部分,需要重新设计0xff的添加规则
					routing_table.add_item(0xff,m_targs-1);
				}
			}
		}
		else
		{
			//添加0xff对应的路由信息
			if(routing_table.query_port(0xff)!=-1)
			{
				routing_table.delete_item(0xff);
			}
			if(routing_table.query_port(0xff)==-1)
			{
				unsigned int j;
				for(j=0;j<m_targs;j++)
				{
					if(routing_table.query_addr(j)==-1 && j!=CAR[1])
						break;
				}
				if(j<m_targs)
				{
					routing_table.add_item(0xff,j);
				}
				else
				{
					routing_table.add_item(0xff,m_targs-1);
				}
			}
		}
		cout<<name()<<endl;
		routing_table.print_table();

		extension->set_src_id(0x00);
		extension->set_trd_id(0xff);

		frame->Ftype=0b1000;
		frame->Ttype=0b0011;

		//响应包数据部分第一个数据0表示switch信息,1表示endpoint响应
		payload.set_data_ptr((unsigned char*)frame);
		payload.set_extension(extension);
		(*targ_socket[from])->nb_transport_bw(payload,phase,time);
	}
}


//读取文件建立静态路由表
void Router::static_table_thread()
{
#ifdef DEBUG_MODULE
	cout << "launch ctor_talbe_thread / time = " << sc_time_stamp() << endl;
#endif

	string strone;
	//该模块嵌入到DSP中时需要完整静态路由表文件名,从根目录开始,防止报错
	ifstream in("router_table.txt");
	int flag=0;
	while(getline(in,strone))
	{
		//flag标志用于不读取第一行的说明,从第二行开始读取路由表记录
		if(flag!=0)
		{		
			stringstream ss;
			ss<<strone;
			unsigned int portid,deviceid;
			ss>>portid>>deviceid;
			cout<<portid<<"  "<<deviceid<<" time is "<< sc_time_stamp() <<endl;
			routing_table.add_item(portid,deviceid);
		}
		flag+=1;
	}

#ifdef DEBUG_MODULE
	routing_table.print_table();
#endif

	// 每4NS触发一次进程
	if (sc_time_stamp() < sc_time(10, SC_NS)) {
		next_trigger(50, SC_NS);
	} else {
		next_trigger(50, SC_NS);
	}
}

void Router::maintain_packet( int 		from, 
					tlm_generic_payload	&payload, 
					tlm_phase 			&phase,
					sc_time				&time)
{
	//维护数据包相应算法
	SRIO_FRAME* frame = (SRIO_FRAME*)payload.get_data_ptr();
	soclib_payload_extension* extension = new soclib_payload_extension;
	payload.get_extension(extension);                      //参数为soclib_payload_extension*类型
	
	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32* data	 = (DSPU32*)frame->Data;
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;
	//根据ttype确定是否需要读写响应等,通常是需要维护单播路由信息和组播路由信息
}


////////////////////////////////////////////////////////////
// 该函数实际上执行fw函数的功能。该函数根据payload的地址，将payload
// 发送到正确的target
////////////////////////////////////////////////////////////
void Router::route(	size_t						from,
					tlm::tlm_generic_payload	&payload,
					tlm::tlm_phase				&phase,
					sc_core::sc_time			&time)
{
	// 拆payload
	SRIO_FRAME* frame = (SRIO_FRAME*)payload.get_data_ptr();
	soclib_payload_extension* extension = new soclib_payload_extension;
	payload.get_extension(extension);                      //参数为soclib_payload_extension*类型
	
	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32* data	 = (DSPU32*)frame->Data;
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;

	size_t transaction_type;
    unsigned int multi_cast_id=100;
	unsigned int broad_cast_id=101;

	//判断是否是组播包和广播包,如果是的话则需要进行组播和广播操作
	//判断收到的包pkt是否已经缓存在router中
	//从接收端口外的其他端口进行发送
	//判断是否是初始化数据包
	if(ftype==0b1000 && target_id==0xff)
	{
		transaction_type=7;
		if(hop_count==0)
		{
			enumeration(from,payload,phase,time);
			//然后再根据情况,发送响应包,响应包可以直接调用nb_transport_bw
			return;
		}
		else
		{
			frame->Extension-=1;
			payload.set_data_ptr((unsigned char*)frame);
			#ifdef DEBUG_MODULE
			cout << "       route  the  cmd to   targ" << target_id << "     / time=" << sc_time_stamp() << endl;
			#endif

			// 根据地址查端口
			int port_id = routing_table.query_port(target_id);

			if (port_id == -1)
			{
				cout<<"router enumeration function"<<endl;
				return;
			}

			tlm_sync_enum fw_statu = (*init_socket[port_id])->nb_transport_fw(payload, phase, time);

			// if (fw_statu != tlm::TLM_ACCEPTED)
			// {
			// 	cout << "forward error 2 in " << name() << " ----> target" << endl;
			// } else if ( payload.is_response_error() )
			// {
			// 	cout << payload.get_response_string().c_str() << endl;
			// } 
			return;
		}
	}
	else if(ftype==0b1000)
	{
		//维护包,当Ttype=0b0010或者0b0011时,status=0b1100-0b1111时为用户自定义维护包
		transaction_type=7;
		if(hop_count==0)
		{
			maintain_packet(from,payload,phase,time);
			//然后再根据情况,发送响应包,响应包可以直接调用nb_transport_bw
			return;
		}
		else
		{
			frame->Extension-=1;
			payload.set_data_ptr((unsigned char*)frame);
			#ifdef DEBUG_MODULE
			cout << "       route  the  cmd to   targ" << target_id << "     / time=" << sc_time_stamp() << endl;
			#endif

			// 根据地址查端口
			int port_id = routing_table.query_port(target_id);

			if (port_id == -1)
			{
				cout << "Not found target_id in routing table."<<endl;
				if(from==CAR[1])
				{
					cout<<" default port is entry port, so not delivery"<<endl;
					return;
				}
				port_id=CAR[1];
			}

			tlm_sync_enum fw_statu = (*init_socket[port_id])->nb_transport_fw(payload, phase, time);

			if (fw_statu != tlm::TLM_ACCEPTED)
			{
				cout << "forward error 3 in " << name() << " ----> target" << endl;
			} else if ( payload.is_response_error() )
			{
				cout << payload.get_response_string().c_str() << endl;
			} 
			return;
		}
	}else if(target_id==multi_cast_id)         //可考虑将组播事务包转化为类型15的包,然后设计读写响应规则
	{
		for(unsigned int i=0;i<multi_pkt_index;i++)
		{
			if(pkt_id==multi_pkt_buffer[i][0] && source_id==multi_pkt_buffer[i][1])
			{
				cout<<"have received this broad_cast packet"<<endl;
				return;
			}
		}
		multi_pkt_buffer[multi_pkt_index++][0]=pkt_id;
		multi_pkt_buffer[multi_pkt_index][1]=source_id;
		multi_cast(from,payload,phase,time);
		cout<<"execute multicast algorithms"<<endl;
		return;
	}else if(target_id==broad_cast_id)
	{
		for(unsigned int i=0;i<broad_pkt_index;i++)
		{
			if(pkt_id==broad_pkt_buffer[i][0] && source_id==broad_pkt_buffer[i][1])
			{
				cout<<"have received this broad_cast packet"<<endl;
				return;
			}
		}
		broad_pkt_buffer[broad_pkt_index++][0]= pkt_id;
		broad_pkt_buffer[broad_pkt_index][1]=source_id;
		broad_cast(from,payload,phase,time);
		return;
	}else if(target_id==source_id)
	{
		cout<<"target is equal Initiator,so not delivery!"<<endl;
		return;
	}

	// 根据地址查端口,若不存在,考虑从默认端口CAR[1]标志位转发出去
	int port_id = routing_table.query_port(target_id);

	if (port_id == -1)
	{
		cout << "take the default port:"<<CAR[1]<<endl;
		port_id=CAR[1];
		if(port_id==from)
		{
			cout<<" default port is entry port, so not delivery"<<endl;
			return;
		}
	}

#ifdef DEBUG_MODULE
	cout << "       route  the  cmd to   targ" << target_id << "     / time=" << sc_time_stamp() << endl;
#endif

	tlm_sync_enum fw_statu = (*init_socket[port_id])->nb_transport_fw(payload, phase, time);

	if (fw_statu != tlm::TLM_ACCEPTED && fw_statu != tlm::TLM_COMPLETED)
	{
		cout << "forward error 1 in " << name() << " ----> target" << endl;
	} else if ( payload.get_response_status()<0 )
	{
		cout << name()<<payload.get_response_string().c_str() << endl;
	} 
}


void Router::execLoop()
{
#ifdef DEBUG_MODULE
	cout << name() << " launch execLoop                / time=" << sc_time_stamp() << endl;
#endif

	size_t						from;
	bool success=false;
	tlm::tlm_generic_payload*	payload_ptr;
	tlm::tlm_phase*				phase_ptr;
	sc_core::sc_time*			time_ptr;

	//每次只弹出一个数据包
	success=pop_payload(m_central_buffer,from, payload_ptr, phase_ptr, time_ptr);
	if(success)
	{
		route(from, *payload_ptr, *phase_ptr, *time_ptr);
	}
	// cout<<name()<<" execloop function success"<<endl;
}


//////////////////////////////////////////////////////////////////
// 该函数由initiator执行，当initiator发出一个事务时调用router的fw方法，
// 并尝试将事务推送到buffer中
//////////////////////////////////////////////////////////////////
tlm_sync_enum Router::nb_transport_fw( int					from,
							           tlm_generic_payload	&payload,
                                       tlm_phase			&phase,
                                       sc_time				&time)
{	
	// cout<<name()<<" nb_transport_fw"<<endl;
	// 拆payload
	SRIO_FRAME* frame = (SRIO_FRAME*)payload.get_data_ptr();
	soclib_payload_extension* extension = new soclib_payload_extension;
	payload.get_extension(extension);                      //参数为soclib_payload_extension*类型
	
	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32* data	 = (DSPU32*)frame->Data;
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;

	size_t transaction_type;
    unsigned int multi_cast_id=100;
	unsigned int broad_cast_id=101;

#ifdef DEBUG_MODULE
	cout << "       " << name() << " recv cmd from init" << id << "     / time=" << sc_time_stamp() << endl;
#endif

	bool push = false;
	do
	{
		//这里将从端口进入对应缓冲改为从对应source_id进入对应缓冲
		//后面改为source_id%5取余作为对应缓冲id,因为考虑多个switch和设备id,在大型网络拓扑结构中
		push = m_central_buffer.push(from, payload, phase, time);
		if (not push)	// push失败,通常是由于buffer已满,相当于溢出导致push失败
		{
#ifdef DEBUG_MODULE
			cout << "      init" << id << "cannot push into buffer" << endl;
#endif
			cout<<name()<<" buffer is not have location for this packet"<<endl;
			payload.set_response_status( TLM_GENERIC_ERROR_RESPONSE );
			// (*targ_socket[from])->nb_transport_bw(payload,phase,time);
			return tlm::TLM_COMPLETED;
		} 
		else			// push成功
		{
			//当某个端口buffer缓冲区使用空间达到一半时,通知发送方
			if(m_central_buffer.m_port_array[from].buffer.get_size()>=(0.5*MAX_SIZE))
			{
				cout<<name()<<" port "<<from<<" had restore half packets"<<endl;
				payload.set_response_status( TLM_GENERIC_ERROR_RESPONSE);
				// (*targ_socket[from])->nb_transport_bw(payload,phase,time);
			}
			else
			{
				// cout<<name()<<" receive a packet"<<endl;
			}
			
#ifdef DEBUG_MODULE
			cout << "       " <<  name() << " push cmd into buffer    / time=" << sc_time_stamp() << endl;
#endif
		}
	} while (not push);

	return tlm::TLM_COMPLETED;
}


//下述id参数表示第几个init_socket所注册的bw函数
tlm_sync_enum Router::nb_transport_bw( int 					id,
                                       tlm_generic_payload	&payload,
                                       tlm_phase 			&phase,
							           sc_time				&time)
{
	// 拆payload
	// cout<<name()<<" router_nb_transport_bw"<<endl;
	SRIO_FRAME* frame = (SRIO_FRAME*)payload.get_data_ptr();
	soclib_payload_extension* extension = new soclib_payload_extension;
	payload.get_extension(extension);                      //参数为soclib_payload_extension*类型
	
	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32 data[256];
	for(unsigned int j=0;j<55;j++)
	{
		data[j]=frame->Data[j];
	}

	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;
	// cout<<name()<<" ftype "<<ftype<<endl;
	//判断是否系统初始化时维护读写响应包,并做相应计数器进行操作
	if(ftype==0b1000 && ttype==0b0010 && target_id==0xff)
	{
		if(data[0]==1)
		{
			for(unsigned int i=0;i<256;i++)
			{
				if(frame->Data[i]==0xff)
				{
					frame->Data[i]=id;
					// cout<<name()<<" id is "<<id<<endl;
					frame->Data[i+1]=0xff;
					break;
				}
			}
			payload.set_data_ptr((unsigned char*)frame);
		}
	}
	else if(ftype==0b1000 && ttype==0b0011 && target_id==0xff)
	{
		// cout<<name()<<" this packet is write response"<<endl;
	}

	unsigned int port_id=routing_table.query_port(source_id);

	if(port_id==-1)
	{
		port_id=CAR[1];
	}
	(*targ_socket[port_id])->nb_transport_bw(payload,phase,time);
	return tlm::TLM_ACCEPTED;
}