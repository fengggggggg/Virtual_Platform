#include "include/circular_buffer.h"

namespace soclib { namespace tlmdt {

circular_buffer::circular_buffer()
  : front(0)
  , rear(0)
  , buffer_length(0)
  , name("buffer")
{
	buffer = new transaction[MAX_SIZE];
	max_size = MAX_SIZE;
}

circular_buffer::circular_buffer(int n)
  : front(0)
  , rear(0)
  , buffer_length(0)
  , name("buffer")
{
	buffer = new transaction[n];
	max_size = n;
}

circular_buffer::~circular_buffer()
{
   //delete buffer;
}

bool circular_buffer::push
( tlm::tlm_generic_payload &payload,
  tlm::tlm_phase           &phase,
  sc_core::sc_time         &time)
{
	if(is_full()) {
		return false;
	}
  
#if SOCLIB_MODULE_DEBUG
	soclib_payload_extension *ext;
	payload.get_extension(ext);
	std::cout << "[" << name << "] PUSH src_id = " << ext->get_src_id()
			  << " pkt_id = " << ext->get_pkt_id() << std::endl;
#endif
  

	buffer[rear].payload = &payload;
	buffer[rear].phase   = &phase;
	buffer[rear].time    = &time;
  
	rear = rear < max_size-1 ? rear + 1 : 0;


	ATOMIC_ADD(&buffer_length, 1);
  
	assert( buffer_length <= max_size );

#if SOCLIB_MODULE_DEBUG
	std::cout << "[" << name << "] INCREMENT QUEUE buffer_length = "
			  << buffer_length << " front = " << front << " rear = " << rear << std::endl;
#endif
    
	return true;
}

bool circular_buffer::get_front( tlm::tlm_generic_payload *&payload,
								 tlm::tlm_phase           *&phase,
								 sc_core::sc_time         *&time)
{
	if(!is_empty()) {
		payload = buffer[front].payload;
		phase = buffer[front].phase;
		time = buffer[front].time;

		return true;
	}
	return false;
}
    
bool circular_buffer::pop( tlm::tlm_generic_payload *&payload,
						   tlm::tlm_phase           *&phase,
						   sc_core::sc_time         *&time)
{
	if(!is_empty()) {

		payload = buffer[front].payload;
		phase = buffer[front].phase;
		time = buffer[front].time;
   
		front = (front < max_size-1) ? front + 1 : 0;

		ATOMIC_SUB(&buffer_length,1);
    
		assert(buffer_length >= 0);

#if SOCLIB_MODULE_DEBUG
		soclib_payload_extension *ext;
		payload->get_extension(ext);
		std::cout << "[" << name << "] POP  src_id = " << ext->get_src_id()
				  << " pkt_id = " << ext->get_pkt_id() << std::endl;
#endif

#if SOCLIB_MODULE_DEBUG
		std::cout << "[" << name << "] INCREMENT HEADER buffer_length = "
				  << buffer_length << " front = " << front << " rear = " << rear << std::endl;
#endif

		return true;
	}
	return false;
}

//加入一个优先级入队函数,根据pkt_id,pkt_id小的放在前面
bool circular_buffer::push_sort (
                tlm::tlm_generic_payload &payload,
                tlm::tlm_phase          &phase,
                sc_core::sc_time         &time )
{
	// cout<<"push_sort"<<endl;
	if(is_full()) {
		return false;
	}
    // 拆payload
	SRIO_FRAME* frame =new SRIO_FRAME;
	soclib_payload_extension* extension = new soclib_payload_extension;
	soclib_payload_extension* extension_index = new soclib_payload_extension;
	payload.get_extension(extension);                      //参数为soclib_payload_extension*类型
	frame=(SRIO_FRAME*)payload.get_data_ptr();
	unsigned int cmd=extension->get_command();
	unsigned int target_id=(DSPU32)extension->get_trd_id();
	unsigned int source_id=(DSPU32)extension->get_src_id();
	unsigned int pkt_id=(DSPU32)extension->get_pkt_id();

	DSPU32* data	 = (DSPU32*)frame->Data;
	DSPU32 ftype	 = (DSPU32)frame->Ftype;
	DSPU32 ttype	 = (DSPU32)frame->Ttype;
	DSPU32 hop_count	 = (DSPU32)frame->Extension;
    int index_front=front;
	int	index_rear=rear;
	int success=0;
    if(is_empty())
	{
		return push(payload,phase,time);
	}
	// cout<<"not empty"<<endl;
    while(index_front!=index_rear)
    {
		//序号小的包放前面
        buffer[index_front].payload->get_extension(extension_index);
		if(extension_index->get_pkt_id()<=extension->get_pkt_id())
		{
			index_front=(index_front+1)%max_size;
		}
		else
		{
			while(index_front!=index_rear)
			{
				buffer[(index_rear+1)%max_size]=buffer[index_rear];
				index_rear=(index_rear+max_size-1)%max_size;
			}
			buffer[(index_front+1)%max_size]=buffer[index_front];
			buffer[index_front].payload=&payload;
			buffer[index_front].phase=&phase;
			buffer[index_front].time=&time;
			success=1;
			break;
		}
    }
	if(success==0)
	{
		// cout<<"call push"<<endl;
		return push(payload,phase,time);
	}
	rear = rear < max_size-1 ? rear + 1 : 0;
	ATOMIC_ADD(&buffer_length, 1); 
	assert( buffer_length <= max_size );
#if SOCLIB_MODULE_DEBUG
	std::cout << "[" << name << "] INCREMENT QUEUE buffer_length = "
			  << buffer_length << " front = " << front << " rear = " << rear << std::endl;
#endif    
	return true;
}
   

void circular_buffer::set_name(std::string n)
{
	name = n;
}

}}
