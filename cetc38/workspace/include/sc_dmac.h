#ifndef SC_DMAC_H_
#define SC_DMAC_H_

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES
//------------------------------------------------
#include <systemc.h>

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

class sc_dmac : public sc_module
{
private:
	

public:
	sc_in_clk m_clk;
	tlm_utils::simple_initiator_socket<sc_dmac> m_isocket;
	tlm_utils::simple_target_socket<sc_dmac> m_tsocket;

	//------------------------------------------------------
    SC_HAS_PROCESS(sc_dmac);
    sc_dmac(sc_module_name p_name)
    {
		m_isocket.register_nb_transport_bw(this, &sc_dmac::nb_transport_bw);
		m_tsocket.register_nb_transport_fw(this, &sc_dmac::nb_transport_fw);


    }

	virtual tlm::tlm_sync_enum nb_transport_bw( tlm::tlm_generic_payload& trans,
                                                     tlm::tlm_phase& phase, sc_time& delay )
    {
    
    	return tlm::TLM_ACCEPTED;
    }

	virtual tlm::tlm_sync_enum nb_transport_fw( tlm::tlm_generic_payload& trans,
                                                     tlm::tlm_phase& phase, sc_time& delay )
    {


    	return tlm::TLM_ACCEPTED;
    }

};

#endif


