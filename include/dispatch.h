#include <systemc>
#include <sstream>
#include "common.h"
#include "centralized_buffer.h"

///////////////////////////////////////////////////////////////////////////////
// This function implements the PDES time filtering algorithm:
// All active initiators are scanned, to select the earliest date.
// - if there is no transaction for this initiator, (false) is returned,
//   and no transaction is consumed in the central buffer.
// - if there is a transaction, (true) is returned. The selected 
//   initiator index is returned in (from). The transaction parameters 
//   are returned in (payload, phase, time), the transaction is 
//   removed from the central buffer, and the selected port time is updated.
// 轮训调度算法
///////////////////////////////////////////////////////////////////////////////
namespace soclib{ namespace tlmdt{
bool  pop_payload(centralized_buffer &central_buffer,
                                size_t                    &from,
                               tlm::tlm_generic_payload* &payload,
                               tlm::tlm_phase*           &phase,
                               sc_core::sc_time*         &time )
{
    uint64_t min_time = std::numeric_limits<uint64_t>::max();
    size_t sel_id = 0;              // selected port
    uint64_t time_value;            // date of the port
  
    // searching the earliest (smaller time) active port
    // we implement a round-robin priority because,
    // in case of equal times, the first found is selected
    for( size_t k=0 ; k<central_buffer.m_slots ; k++ )
    {
        size_t i = (central_buffer.m_previous + k + 1) % central_buffer.m_slots;

        if(central_buffer.m_port_array[i].active && not central_buffer.m_port_array[i].buffer.is_empty())   // 只有活动的port参与竞争
        {
            // get time
            if(central_buffer.m_port_array[i].buffer.is_empty())   // buffer空，输出端口时间
            {
                time_value = central_buffer.m_port_array[i].port_time.value();
                // std::cout << "@@@ port " << i << " / empty / time = " 
                //          << std::dec << time_value << std::endl;
            } else                                  // buffer不空，输出端口时间，取出最早事务
            {
                central_buffer.m_port_array[i].buffer.get_front(payload, phase, time);
                time_value = (*time).value();
                // std::cout << "@@@ port " << i << " /  ok   / time = " 
                //          << std::dec << time_value << std::endl;
            }

            // test if it is the earliest
            if(time_value < min_time)
            {
                min_time = time_value;
                sel_id   = i;
            }
        }
    }

    if( not central_buffer.m_port_array[sel_id].buffer.is_empty() )    // success
    {
        central_buffer.m_port_array[sel_id].buffer.pop( payload, phase, time);
        from = sel_id;      
        central_buffer.m_previous = sel_id;
        central_buffer.set_port_time( sel_id, *time );
        return true;
    } else                                              // no eligible command
    {
        return false;
    }
} // end pop_payload()

//优先级调度算法,可扩展后支持设置不同输入buffer队列的优先级
bool  pop_payload_priority(centralized_buffer &central_buffer,
                                size_t                    &from,
                               tlm::tlm_generic_payload* &payload,
                               tlm::tlm_phase*           &phase,
                               sc_core::sc_time*         &time )
{
    uint64_t min_time = std::numeric_limits<uint64_t>::max();
    size_t sel_id = 0;              // selected port
    uint64_t time_value;            // date of the port
  
    // searching the earliest (smaller time) active port
    // we implement a round-robin priority because,
    // in case of equal times, the first found is selected
    for( size_t k=0 ; k<central_buffer.m_slots ; k++ )
    {
        if( not central_buffer.m_port_array[k].buffer.is_empty() )    // success
        {
        central_buffer.m_port_array[k].buffer.pop( payload, phase, time);
        from = k;      
        central_buffer.m_previous = k;
        central_buffer.set_port_time( k, *time );
        return true;
        } 
    }
    return false;
} // end pop_payload_priority()

//调度过程已经考虑了轮训机制,可再考虑时间机制,在每个端口优先级基础上再加上先来的优先级最高
bool  pop_payload_time(centralized_buffer &central_buffer,
                                size_t                    &from,
                               tlm::tlm_generic_payload* &payload,
                               tlm::tlm_phase*           &phase,
                               sc_core::sc_time*         &time )
{
    uint64_t min_time = std::numeric_limits<uint64_t>::max();
    size_t sel_id = 0;              // selected port
    uint64_t time_value;            // date of the port
  
    // searching the earliest (smaller time) active port
    // we implement a round-robin priority because,
    // in case of equal times, the first found is selected
    for( size_t k=0 ; k<central_buffer.m_slots ; k++ )
    {
        if( not central_buffer.m_port_array[k].buffer.is_empty() )    // success
        {
        //可再加上一个时间机制,用于先到的包先进行调度
        central_buffer.m_port_array[k].buffer.pop( payload, phase, time);
        from = k;      
        central_buffer.m_previous = k;
        central_buffer.set_port_time( k, *time );
        return true;
        } 
    }
    return false;
 } // end pop_payload()
}
}

