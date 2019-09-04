#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <limits>
//#include <tlmdt>
#include "common.h"       

#define MAX_SIZE 512    //2^9 = 512

#if defined(__APPLE__)
# include <libkern/OSAtomic.h>
# define ATOMIC_ADD(addr, val) OSAtomicAdd32(val, addr)
# define ATOMIC_SUB(addr, val) OSAtomicAdd32(-val, addr)
#else
# define ATOMIC_ADD __sync_fetch_and_add
# define ATOMIC_SUB __sync_fetch_and_sub
#endif

namespace soclib { namespace tlmdt {

class circular_buffer
{
private:

  struct transaction{
    tlm::tlm_generic_payload *payload;
    tlm::tlm_phase           *phase;
    sc_core::sc_time         *time;
  };

  transaction            *buffer;
  int                     front;
  int                     rear;
  volatile int            buffer_length;
  int                     max_size;
  std::string             name;

public:
  circular_buffer(int n);

  circular_buffer();

  ~circular_buffer();

  bool push
  ( tlm::tlm_generic_payload &payload,
    tlm::tlm_phase           &phase,
    sc_core::sc_time         &time);

  bool pop
  ( tlm::tlm_generic_payload *&payload,
    tlm::tlm_phase           *&phase,
    sc_core::sc_time         *&time);

  bool push_sort (
                tlm::tlm_generic_payload &payload,
                tlm::tlm_phase           &phase,
                sc_core::sc_time         &time );

  bool get_front
  ( tlm::tlm_generic_payload *&payload,
    tlm::tlm_phase           *&phase,
    sc_core::sc_time         *&time);

  inline const bool is_empty() { return (buffer_length == 0); }

  inline const bool is_full()  { return (buffer_length == max_size); }
                                   
  inline const int get_size() { return buffer_length; }

  inline const int get_max_size() { return max_size; }

  void set_name(std::string n);

};

}}

#endif
