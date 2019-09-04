/////////////////////////////////////////////////////////////////////////////////////
// Implementation note:
// The centralized_buffer is actually an array of initiator ports descriptors.
// There is one entry per initiator connected to the interconnect in this array.
// Each port descriptor can store one or several transaction (payload, phase, time)
// in a circular buffer (defined in soclib/lib) acting as a software FIFO.
/////////////////////////////////////////////////////////////////////////////////////

#ifndef CENTRALIZED_BUFFER_H
#define CENTRALIZED_BUFFER_H

//#include <tlmdt>	            
#include "circular_buffer.h"

namespace soclib { namespace tlmdt {

////////////////////////////
class init_port_descriptor
////////////////////////////
{
    friend class centralized_buffer;
  
    circular_buffer         buffer;      // circular buffer of transactions
    sc_core::sc_time        port_time;   // date of last transaction transmited 
    bool                    active;      // initiator port activated if true

public:

    // constructor    
    init_port_descriptor()
    : buffer() , port_time(sc_core::SC_ZERO_TIME)
    {
        active = true;
    }
};

//////////////////////////
class centralized_buffer
//////////////////////////
  : public sc_core::sc_module       
{
    // member variables
    const size_t            m_slots;       // number of initiators                 
    init_port_descriptor*   m_port_array;  // array of initiator port descriptors
    int                     m_count_push;  // cumulated push counter
    int                     m_count_pop;   // cumulate pop counter
    size_t                  m_previous;    // last selected port index (for round-robin)

public:

    // constructor destructor
    centralized_buffer( sc_core::sc_module_name name,
                        size_t                  slots );

    ~centralized_buffer();

    // methods
    bool push ( size_t                    from,
                tlm::tlm_generic_payload  &payload,
                tlm::tlm_phase            &phase,
                sc_core::sc_time          &time );

    bool pop (  size_t                    &from,
                tlm::tlm_generic_payload* &payload,
                tlm::tlm_phase*           &phase,
                sc_core::sc_time*         &time );

    circular_buffer get_buffer(size_t index);

    const size_t get_nslots();

    const size_t get_free_slots();

    sc_core::sc_time get_port_time(size_t index);

    void set_activity(size_t index, bool b);

    void set_port_time(size_t index, sc_core::sc_time t);
};

}}

#endif
