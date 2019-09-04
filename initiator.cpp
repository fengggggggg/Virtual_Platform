/******************************************************************************
 * Author        : cai
 * Creation time : 2019-06-09 17:09
 * Update time   : 2019-06-19 12:15
 * Description   : 
******************************************************************************/

#include "initiator.h"

void Initiator::thread_process()
{
#ifdef DEBUG_MODULE
	cout << name() << "  launch thread_process          / time="
		 << sc_time_stamp() << endl;
#endif
	emit_trsac();
	if (sc_time_stamp() < sc_time(35, SC_NS)) {
		next_trigger(30, SC_NS);
	} else {
		next_trigger(5, SC_NS);
	}
}

void Initiator::check()
{
	if(CSR[2]!=0x00)
	{
		return;
	}
	if(check_response==1 )
	{
		//准备发送维护读
		check_response=0;
		cout<<name()<<" switch_index "<<switch_index<<endl;
		if(switch_index==-1)         //表示整个系统刚开始初始化，准备发送第一个维护读数据包
		{
			if(start_flag)
			{
				start_flag=0;
				enumeration();
			}
			else
			{
				return;
			}
			
		}
		else if(switch_array[switch_index]==0)
		{
			switch_index-=1;
			dengdaixiangying=1;
			dengdaixiangying1=0;
			//发送一个调整0xff的写数据包
			if(switch_index==-1)
			{	
				end_flag=0;
				return;
			}
			else
			{
				endpoint_response(switch_index,0);
			}
		}
		else
		{
			dengdaixiangying=1;
			dengdaixiangying1=0;
			enumeration();
		}
		
	}
	else if(end_flag)
	{
		if(check_read_switch==1)
		{
			check_read_switch=0;
			dengdaixiangying=1;
			dengdaixiangying1=0;
			//写一条初始化路由信息,然后再添加一条0xff路由信息,因为原始switch没有0xff,所以会默认添加0xff对应
			switch_response();
		}
		else if(check_write_switch==1)
		{
			//判断累积的写是否是已经达到switch个数
		}
		else if(check_read_endpoint==1)
		{
			check_read_endpoint=0;
			//判断是endpoint读响应
			//根据index每个switch都写一个路由信息
			//index对应交换机端口个数减一
			//if(端口数为0.再添加一个路由写)
			dengdaixiangying=switch_index+1;
			dengdaixiangying1=0;
			endpoint_response(switch_index+1,1);
		}
		else if(check_write_endpoint==1)
		{
			check_write_endpoint=0;
			dengdaixiangying=1;
			dengdaixiangying1=0;
			endpoint_response(switch_index,0);
		}
	}
}

void Initiator::switch_response()
{
	// 拆payload
	cout<<"switch_response"<<endl;
	tlm_generic_payload*	payload = new tlm_generic_payload;
	SRIO_FRAME* frame = new SRIO_FRAME;
	soclib_payload_extension *extension=new soclib_payload_extension;
	frame = (SRIO_FRAME*)init_payload->get_data_ptr();
	init_payload->get_extension(extension);                 //参数为soclib_payload_extension*类型

	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32 data[256];
	for(unsigned int j=0;j<256;j++)
	{
		data[j]=frame->Data[j];
		if(frame->Data[j]==0xff)
			break;
	}
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;
	

	unsigned int total=data[1];
	unsigned int number=data[2];

	frame->Ftype=0b1000;
	frame->Ttype=0b0001;
	frame->Extension=switch_index;
	frame->Wdptr=0;
	frame->Data[0]=0x00;
	frame->Data[1]=data[2];
	frame->Data[2]=0xff;
	frame->Data[50]=0;
	//实际中第一次调用该函数应该将其改为数据部分
	tlm_command tlm_cmd=static_cast<tlm_command>(0);
	//设置payload->wdptr为0时写入路由信息,为1时写入设备id255对应的路由信息
	payload->set_command(tlm_cmd);
	extension->set_src_id(0x00);
	extension->set_trd_id(0xff);
	payload->set_data_ptr((unsigned char*)frame);
	payload->set_extension(extension);
	//host发送维护写,该函数是当收到switch的响应时,向对应的那个交换机写入到达主机的路由信息
	init_socket->nb_transport_fw(*payload,init_phase,init_time);
}


void Initiator::endpoint_response(int hop_count,int way)
{
	// 拆payload
	cout<<"endpoint_response"<<endl;
	tlm_generic_payload*	payload = new tlm_generic_payload;
	SRIO_FRAME* frame = new SRIO_FRAME;
	soclib_payload_extension *extension=new soclib_payload_extension;
	frame = (SRIO_FRAME*)init_payload->get_data_ptr();
	init_payload->get_extension(extension);                 //参数为soclib_payload_extension*类型

	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32 data[256];
	for(unsigned int j=0;j<256;j++)
	{
		data[j]=frame->Data[j];
		// if(frame->Data[j]==0xff)
		// 	break;
	}
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	frame->Ftype=0b1000;
	frame->Ttype=0b0001;
	frame->Wdptr=0;
	tlm_command tlm_cmd=static_cast<tlm_command>(way);
	payload->set_command(tlm_cmd);
	extension->set_src_id(0x00);
	extension->set_trd_id(0xff);
	command ext_cmd=static_cast<command>(way);
	extension->set_command(ext_cmd);
	payload->set_extension(extension);
	if(way==1)
	{
		for(unsigned int i=0;i<hop_count;i++)
		{
			payload=new tlm_generic_payload;
			frame=new SRIO_FRAME;
			extension=new soclib_payload_extension;
			frame->Ftype=0b1000;
			frame->Ttype=0b0001;
			frame->Data[0]=data[1];
			frame->Data[1]=data[hop_count+1-i];
			frame->Data[2]=0xff;
			frame->Extension=i;
			frame->Wdptr=0;
			payload->set_command(tlm_cmd);
			payload->set_data_ptr((unsigned char*)frame);
			extension->set_src_id(0x00);
			extension->set_trd_id(0xff);
			payload->set_extension(extension);
			//host收到endpoint发回的响应数据包时,向从主机到达该endpoint的每一个交换机分别发送一条维护写
			//数据包,用来分别更新每个交换机的路由信息,采用由近到远的添加方式
			init_socket->nb_transport_fw(*payload,init_phase,init_time);
		}
	}
	else
	{
		frame->Ftype=0b1000;
		frame->Ttype=0b0001;
		frame->Wdptr=1;
		frame->Extension=hop_count;
		extension->set_src_id(0x00);
		extension->set_trd_id(0xff);
		payload->set_data_ptr((unsigned char*)frame);
		init_socket->nb_transport_fw(*payload,init_phase,init_time);
	}
}

void Initiator::enumeration()
{
	tlm_generic_payload*	payload = new tlm_generic_payload;
	SRIO_FRAME* frame = new SRIO_FRAME;
	soclib_payload_extension *extension=new soclib_payload_extension;
	tlm_phase phase = tlm::BEGIN_REQ;
	frame->Ftype=0b1000;
	frame->Ttype=0b0000;
	frame->Extension=switch_index+1;
	frame->Addr=global_id;
	frame->Wdptr=0;
	frame->Data[50]=0;
	command cmd=static_cast<command>(0%2);
	tlm_command tlm_cmd=static_cast<tlm_command>(0%2);
	payload->set_command(tlm_cmd);
	extension->set_command(cmd);
	extension->set_src_id(0x00);
	extension->set_trd_id(0xff);
	extension->set_pkt_id(5);
	payload->set_data_ptr((unsigned char*)frame);
	payload->set_extension(extension);
	cout<<"initialization_enumeration"<<endl;
	init_socket->nb_transport_fw( *payload, init_phase, init_time );
}

tlm_generic_payload* Initiator::generate_payload()
{
	
	// 假设targ的地址为0 ~ N_TARG，随机产生
	unsigned int address = rand() % N_TARG;

	tlm_generic_payload*	payload = new tlm_generic_payload;
	soclib_payload_extension *extension=new soclib_payload_extension;
	
	// CoreID_extension* ext_data=new CoreID_extension;
	// cout<<"ext_data->flag:"<<ext_data->core_id<<endl;
	// cmd = 0 = NREAD, cmd = 1 = NWRITE, cmd = 2 = NWRITE_R
	// tlm_command cmd = static_cast<tlm_command>(rand() % 3);
	command cmd=static_cast<command>(rand()%2);

	SRIO_FRAME* frame = new SRIO_FRAME;
	frame->TT = 0b00;
	frame->TargetID = 0b00000000 | address;
	frame->SourceID = 0b00000000 | m_deviceID;
	
	if (cmd == 0)
	{	// NREAD
		frame->Ftype = 0b0010;
		frame->Ttype = 0b0100;
	} else if (cmd == 1)
	{	// NWRITE
		frame->Ftype = 0b0101;
		frame->Ttype = 0b0100;
	}
	else
	{	// NWRITE_R
		frame->Ftype = 0b0101;
		frame->Ttype = 0b0101;
	}

	frame->Data[0] = rand() % 100;
	frame->Data[1]=100;
	unsigned int data_len=sizeof(*frame);

	extension->set_command(cmd);
	extension->set_src_id(frame->SourceID);
	extension->set_trd_id(frame->TargetID);
	unsigned int pktid=rand()%100;
	extension->set_pkt_id(pktid);
	// cout<<"the packet pkt_id is: "<<pktid<<endl;
	// 目前所里使用address字段传输命令控制字，而我们的例子中仍然传输地址,该地址指数据在接收端存储器中的地址,
	//属于IO/DMA传输方式
	payload->set_address( address );
	payload->set_data_ptr((unsigned char*)frame);
	payload->set_data_length(data_len);    //最大256字节
	payload->set_response_status( TLM_INCOMPLETE_RESPONSE ); 
	payload->set_extension(extension);

	// cout << "<----- " << name() << " send cmd = " << cmd
	// 	 << " addr = " << frame->TargetID << " data = "
	// 	 << frame->Data[0] << " / time=" << sc_time_stamp() << endl;

	return payload;
}

void Initiator::emit_trsac()
{
	tlm_generic_payload* payload = generate_payload();
	soclib_payload_extension *extension=new soclib_payload_extension;
	SRIO_FRAME* frame = new SRIO_FRAME;
	payload->get_extension(extension);
	frame=(SRIO_FRAME*)payload->get_data_ptr();
			
	tlm_phase phase = tlm::BEGIN_REQ;
	tlm_sync_enum fw_statu;
	unsigned int flag=0;
	while(flag<1)
	{
		cout << "<----- " << name() << " send cmd = " << (DSPU32)extension->get_command()
			<< " addr = " << frame->TargetID << " data = "
			<< frame->Data[0] << " / time=" << sc_time_stamp() << endl;
		fw_statu = init_socket->nb_transport_fw( *payload, phase, time );
		flag+=1;
		if(payload->get_response_status()==TLM_GENERIC_ERROR_RESPONSE)
		{
			cout<<"the buffer is full,so the packet is error"<<endl;
			break;
		}
	}
	if (fw_statu != tlm::TLM_COMPLETED)
	{
		cout << "forward error in " << name() << " ----> router" << endl;
	}
}

tlm_sync_enum Initiator::nb_transport_bw( tlm_generic_payload   &payload,
                                          tlm_phase             &phase,
                                          sc_time               &time)
{
	//根据接收到的响应数据包进行处理,后期可能分为初始化枚举和普通响应包
	//拆payload
	SRIO_FRAME* frame = (SRIO_FRAME*)payload.get_data_ptr();
	soclib_payload_extension* extension = new soclib_payload_extension;
	payload.get_extension(extension);                      //参数为soclib_payload_extension*类型
	tlm_response_status response_status=(tlm_response_status)payload.get_response_status();

	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;

	unsigned int tlm_cmd=(DSPU32)payload.get_command();
	DSPU32 data[256];
	for(unsigned int j=0;j<55;j++)
	{
		data[j]=frame->Data[j];
		// if(frame->Data[j]==0xff)
		// 	break;
	}

	//如果是初始化枚举响应包,判断是switch响应还是endpoint响应,根据响应包frame->Data[0]进行判断
	if(ftype==0b1000 && ttype==0b0010 && target_id==0xff)
	{
		// cout<<"read response"<<endl;
		init_phase=phase;
		init_time=time;
		init_payload=&payload;
		dengdaixiangying1+=1;
		if(dengdaixiangying1==dengdaixiangying)
		{
			if(data[0]==0)
			{
				// cout<<name()<<" check_read_endpoint"<<endl;
				if(switch_index>=0)
				{
					switch_array[switch_index]-=1;
				}
				switch_index+=1;
				switch_array[switch_index]=data[1]-1;
				check_read_switch=1;
			}
			else if(data[0]==1)
			{
				global_id+=1;
				// cout<<name()<<" check_read_switch"<<endl;
				switch_array[switch_index]-=1;
				check_read_endpoint=1;
			}
		}
	}
	else if(ftype==0b1000 && ttype==0b0011 && target_id==0xff)
	{
		// cout<<"write response"<<endl;
		init_phase=phase;
		init_time=time;
		init_payload=&payload;
		dengdaixiangying1+=1;
		if(dengdaixiangying1==dengdaixiangying)
		{
			if(tlm_cmd==0)
			{
				check_response=1;
				// cout<<"check_response is 1"<<endl;
			}
			else if(tlm_cmd==1)
			{
				check_write_endpoint=1;
				// cout<<"check_write_endpoint is 1"<<endl;
			}
		}
	}
	else if(ftype==0b1000)
	{
		cout<<"maintain_packet_response"<<endl;
	}
	else
	{
		//根据pkt_id确定是对哪个包的响应,以及是否需要删除掉已经发送的该数据包
		if(response_status==TLM_GENERIC_ERROR_RESPONSE)
		{
			cout<<"read_write_response"<<endl;
		}
	}
    return TLM_UPDATED;
}
