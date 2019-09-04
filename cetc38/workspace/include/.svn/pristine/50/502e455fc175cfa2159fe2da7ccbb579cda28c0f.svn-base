#if 0
/*
 * mp_bus.h
 *
 *  Created on: Jan 31, 2012
 *      Author: root
 *
 *  Memory space: ISSn [n * MEM_BLK_SIZE, (n + 1) * MEM_BLK_SIZE - 1]
 */

#ifndef MP_BUS_H_
#define MP_BUS_H_

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "common.h"
#include "iss_dmac_comm.h"

template<unsigned int ISS_NUM>
class mp_bus : public sc_module
{
	private:

	int m_intCycles;

	bool send_req_insn_rw_core_mem(MSG_INSN_RW_MEM *p_p_msg_insn_rw_mem, int p_intCoreID)
	{

	/*
		tlm::tlm_generic_payload trans;
		tlm::tlm_phase phase;
		sc_time delay;
		MSG_INSN_RW_MEM msg_insn_rw_mem;
		bool bolOK = true;

		memcpy(&msg_insn_rw_mem, p_p_msg_insn_rw_mem, sizeof(MSG_INSN_RW_MEM));
		trans.set_address(CMD_INSN_RW_CORE_MEM);                    // set command
		trans.set_data_ptr( (unsigned char *)(&msg_insn_rw_mem) );
		trans.set_data_length(sizeof(MSG_INSN_RW_MEM));
		phase = tlm::BEGIN_REQ;
			
		m_iDMACSockets[p_intCoreID]->nb_transport_fw(trans, phase, delay);

		if (trans.get_response_status() != tlm::TLM_OK_RESPONSE)
		{
			printf("send_req_insn_rw_out_mem: nb_transport_fw failed\n");
			bolOK = false;
		}		
*/

		return false;
	}
	
	bool DecodeAddr(unsigned int p_u32Addr, unsigned int &p_u32ID, unsigned int &p_u32BlkAddr)
	{
		if (p_u32Addr > (ISS_NUM_DEF * MEM_BLK_SIZE - 1))
		{
			return false;
		}

		p_u32ID = p_u32Addr / MEM_BLK_SIZE;
		p_u32BlkAddr = p_u32Addr - p_u32ID * MEM_BLK_SIZE;

		return true;
	}

	public:

	sc_in_clk m_clk;

	tlm_utils::simple_initiator_socket_tagged<mp_bus> m_iDMACSockets[ISS_NUM];
	tlm_utils::simple_target_socket_tagged<mp_bus> m_tDMACSockets[ISS_NUM];
	tlm_utils::simple_initiator_socket_tagged<mp_bus> m_iDMACCh0WrSockets[ISS_NUM]; // DMAC ch0 burst方式写
	tlm_utils::simple_initiator_socket_tagged<mp_bus> m_iDMACCh0RdSockets[ISS_NUM]; // DMAC ch0 burst方式读

    void DoCycle()
    {
    	int intTest = 0;    	
		MSG_INSN_RW_MEM msg_insn_rw_mem;
    
    	m_intCycles++;

    	if (intTest == 1)
    	{
   /*
    		//------------------------------------------------------
    		// 写核1数据存储空间
			memset(&msg_insn_rw_mem, 0, sizeof(MSG_INSN_RW_MEM));
    		
			msg_insn_rw_mem.u32ElemNum = 1;  // 访存单元个数
			msg_insn_rw_mem.arrInsnsRWInfo[0].bolIsRead = false;  // 写访存请求
			msg_insn_rw_mem.arrInsnsRWInfo[0].u32Bus = 0;
			msg_insn_rw_mem.arrInsnsRWInfo[0].u32AddrIdx = 0;						
			msg_insn_rw_mem.arrInsnsRWInfo[0].u32Addr = 0x2400000; // 核1的数据存储空间
			msg_insn_rw_mem.arrInsnsRWInfo[0].u32Value = 10;

			send_req_insn_rw_core_mem(&msg_insn_rw_mem, 1); // 将访存请求发往核1
*/
			//------------------------------------------------------
			// 读核1数据存储空间
			memset(&msg_insn_rw_mem, 0, sizeof(MSG_INSN_RW_MEM));
    		
			msg_insn_rw_mem.u32ElemNum = 1;  // 访存单元个数
			msg_insn_rw_mem.arrInsnsRWInfo[0].bolIsRead = true;  // 读访存请求
			msg_insn_rw_mem.arrInsnsRWInfo[0].u32Bus = 0;
			msg_insn_rw_mem.arrInsnsRWInfo[0].u32AddrIdx = 0;						
			msg_insn_rw_mem.arrInsnsRWInfo[0].u32Addr = 0x2400000; // 核1的数据存储空间
			msg_insn_rw_mem.arrInsnsRWInfo[0].u32Value = 0;

			send_req_insn_rw_core_mem(&msg_insn_rw_mem, 1); // 将访存请求发往核1

			//------------------------------------------------------
			
    	}

    }

    SC_HAS_PROCESS(mp_bus);
    mp_bus(sc_module_name p_name)
    {
      m_intCycles = 0;

      for (unsigned int i = 0; i < ISS_NUM; i++)
      {
    	  m_iDMACSockets[i].register_nb_transport_bw(this, &mp_bus::nb_transport_bw_dmac, i);
    	  m_tDMACSockets[i].register_nb_transport_fw(this, &mp_bus::nb_transport_fw_dmac, i);
    	  m_iDMACCh0WrSockets[i].register_nb_transport_bw(this, &mp_bus::nb_transport_bw_dmac, i);
    	  m_iDMACCh0RdSockets[i].register_nb_transport_bw(this, &mp_bus::nb_transport_bw_dmac, i);
      }

      SC_METHOD(DoCycle);
      sensitive_pos << m_clk;
    }

	//------------------------------------------------------
    virtual tlm::tlm_sync_enum nb_transport_bw_dmac( int ID, tlm::tlm_generic_payload& trans,
                                                     tlm::tlm_phase& phase, sc_time& delay )
    {
		DSPU32 u32CMD;
		MSG_INSN_RW_MEM msg_insn_rw_mem;
    
		// CMD_INSN_RW_CORE_MEM
		u32CMD = trans.get_address();  // get command
		//if ((u32CMD == CMD_INSN_RW_CORE_MEM) && (phase == tlm::BEGIN_RESP))
		if (false)
		{			

			memcpy(&msg_insn_rw_mem, trans.get_data_ptr(), sizeof(MSG_INSN_RW_MEM));

			// 分析msg_insn_rw_mem信息

		}

    	return tlm::TLM_ACCEPTED;
    }

	//------------------------------------------------------
    virtual tlm::tlm_sync_enum nb_transport_fw_dmac( int ID, tlm::tlm_generic_payload& trans,
                                                     tlm::tlm_phase& phase, sc_time& delay )
    {

		phase = tlm::END_REQ;
		
		return tlm::TLM_UPDATED;

    }
};


#endif /* MP_BUS_H_ */
#endif
