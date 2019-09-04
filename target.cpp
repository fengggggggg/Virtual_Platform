/******************************************************************************
 * Author        : cai
 * Creation time : 2019-06-09 17:09
 * Update time   : 2019-06-19 12:15
 * Description   : 
******************************************************************************/

#include "include/target.h"

tlm_sync_enum Target::nb_transport_fw( tlm_generic_payload  &payload, 
									   tlm_phase            &phase, 
									   sc_time              &time )
{
	// 拆payload包
	int		adr   = payload.get_address();
	// 当address = -1时，表示该包为路由表建立请求包
	if (adr == 0xFF)
	{
		payload.set_address(m_device_ID);
		return TLM_ACCEPTED;
	}

	//事务类型
	size_t transaction_type;
	unsigned int multi_id=100;
	unsigned int broad_id=101;
	SRIO_FRAME* 	frame = (SRIO_FRAME*)payload.get_data_ptr();
	soclib_payload_extension* extension=new soclib_payload_extension;
	payload.get_extension(extension);
	unsigned char* ptr=payload.get_data_ptr();
	unsigned int    len   = payload.get_data_length();
	unsigned char*  byt   = payload.get_byte_enable_ptr();

	//拆extension
	unsigned int cmd=(DSPU32)extension->get_command();
	DSPU32 target_id = (DSPU32)extension->get_trd_id();
	DSPU32 source_id = (DSPU32)extension->get_src_id();
	DSPU32 pkt_id=(DSPU32)extension->get_pkt_id();

	
	// 拆SRIO帧
	DSPU32* data	 = (DSPU32*)frame->Data;
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 addr      = (DSPU32)frame->Addr;


	if(ftype==0b1000 && ttype==0b0000 && target_id==0xff)
	{
		CSR[1]=1;
		CSR[2]=addr+1;          
		//对于初始化枚举维护包,该值加上1构成当前设备ID,并且发回响应包,当host收到响应包,则将global_id+1
		//作为当前已分配的设备ID
		cout<<name()<<" the base device id is:"<<CSR[2]<<endl;
		frame->Data[0]=1;
		frame->Data[1]=addr+1;
		frame->Data[2]=0xff;
		frame->Ttype=0b0010;
		extension->set_src_id(0x00);
		extension->set_trd_id(0xff);
		payload.set_data_ptr((unsigned char*)frame);
		payload.set_extension(extension);
		payload.set_response_status( TLM_OK_RESPONSE );
		targ_socket->nb_transport_bw(payload,phase,time);
		return TLM_ACCEPTED;
	}
	else if(ftype==0b1000 && ttype==0b0001 && target_id==0xff)
	{
		return TLM_ACCEPTED;
	}
	//判断是否是维护包
	else if(ftype==0b1000)
	{
		cout<<"this packet is maintain packets"<<endl;
		//发送响应事务包时需要设置hop_count为0xff以防止被switch处理
		return TLM_COMPLETED;
	}
	
	//加上是否等于多播和广播事务,通过类型判断,默认开启校验功能
	if(check_enable)
	{
		if(target_id==multi_id)
		{
			//multi_cast and broad_cast
		}
		else if(target_id==broad_id)
		{
			//
		}else if (target_id != CSR[2])        	//接收方地址是否正确
		{
			cout << "The wrong package was received    CSR[2] is:"<<CSR[2]<<endl;
			targ_socket->nb_transport_bw(payload,phase,time);
			//发送响应事件
			return TLM_COMPLETED;
		}
	}
	//下面的代码是为了验证circular_buffer中增加的push_sort函数正常工作，用于模拟1x模式
	bool flag=false;
	flag=target_buffer->push_sort(payload,phase,time);
	if(flag)
	{
		 cout<<"the packet is entry target_buffer success"<<endl;
	}
	else
	{
		//cout<<"target buffer is full"<<endl;
	}
	

	//接着在判断包类型和事务类型
	if (ftype == 0b0010 && ttype == 0b0100) {
		// NREAD Transaction
		transaction_type = 0;
	} else if (ftype == 0b0101 && ttype == 0b0100) {
		// NWRITE Transaction
		transaction_type = 1;
	} else if (ftype == 0b0101 && ttype == 0b0101) {
		// NWRITE_R Transaction
		transaction_type = 2;
	} else if (ftype == 0b1101 && ttype == 0b0000) {
		// 无有效数据负载的response
		transaction_type = 3;
	} else if (ftype == 0b1101 && ttype == 0b1000) {
		// 有有效数据负载的response
		transaction_type = 4;
	} else if (ftype==0b1010)
	{
		//门铃包格式下,将TID视为SourceTID,主要用于发送中断消息或信号量等
		//将Wdptr和Addr分别作为info(msb)和infor(lsb),分别为高八位和低8位
		//没有数据部分,可以考虑不用rapidIO DMI包中数据
		transaction_type=5;
	} else if(ftype==0b1011)
	{
		//message信箱包
		//主要是在sourceID后,其格式为
		//4位Msglen,4位Ssize,2位Letter,2位Mbox,4位Xmbox/Msgseg,其中必须包括邮箱号,即接收者对其进行操作的地址
		//最后有数据部分8-4096字节
		transaction_type=6;
	} else if(ftype==0b1000) 
	{
		//维护包,当Ttype=0b0010或者0b0011时,status=0b1100-0b1111时为用户自定义维护包
		transaction_type=7;
	}
	else{
		// 其他类型事务或出错
		transaction_type = 8;
	}


	cout << "-----> "  << name() << " recv cmd = " << cmd
		 << " from = " << source_id << " data = " << data[0]
		 << " / time=" << sc_time_stamp() <<endl<<endl;
		 
	payload.set_response_status( TLM_OK_RESPONSE );
	return TLM_ACCEPTED;
	//响应方式一:通过bw函数实现,sourceid和targetid还是收到包的,无须互换
	//响应方式二:要发送响应包,应该以重新发送方式,将收到的包源ID与目的ID互换
}


