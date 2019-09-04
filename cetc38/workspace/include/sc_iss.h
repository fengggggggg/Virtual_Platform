/*
 * iss.h
 *
 *  Created on: Jan 31, 2012
 *      Author: root-
 */

#ifndef SC_ISS_H_
#define SC_ISS_H_
#include "./jtag/jtag.h"
#include "./jtag/IOServer.hpp"
// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES
//------------------------------------------------
#include <systemc.h>

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include <string>
#include <list>
#include <stack>

#include "include/common.h"
#include "iss_dmac_comm.h"

//----------------------------------------------------------
#include "src/sim_defines.h"
#include "src/user_type.h"
#include "src/pipe_reg.h"
#include "icache_sim/icache_module_new.h"
#include "dmac_sim/dmac_global.h"
#include "dmac_sim/DMAC.h"
#include "timer/iss_timer.h"

#include "timer/iss_timer.h"




#ifdef CUSTOM_ASSERT
#define ISS_ASSERT(cond) \
	if(!(cond)) \
		iss_err << "Assertion Failed:" << __FUNCTION__ << "()" << ":" << __FILE__ << ":" << std::dec << __LINE__ \
		<< ": Cycles " << std::hex << (DSPU32)u32r_CyclesH << (DSPU32)u32r_CyclesL<< std::endl
#else
#define ISS_ASSERT(cond) assert(cond)
#endif

enum RES_STAT_PHASE {
	STAT_PHASE_DC3 = 1,
	STAT_PHASE_DC4,
	STAT_PHASE_AC,
	STAT_PHASE_EX,
	STAT_PHASE_WB	
};

using namespace BWDSP104X;
class DMAC;
//------------------------------------------------
class sc_iss : public sc_module
	,public tlm::tlm_fw_transport_if<mydma_protocol_types>
	,public tlm::tlm_bw_transport_if<mydma_protocol_types>
{
public:
	virtual tlm::tlm_sync_enum nb_transport_bw(
		tlm::tlm_generic_payload &trans,
		tlm::tlm_phase &phase,
		sc_core::sc_time &t);

	virtual void invalidate_direct_mem_ptr(
		sc_dt::uint64 start_range,
		sc_dt::uint64 end_range){}

	virtual tlm::tlm_sync_enum nb_transport_fw(
		tlm::tlm_generic_payload &trans,
		tlm::tlm_phase &phase,
		sc_core::sc_time &t);

	virtual void b_transport(
		tlm::tlm_generic_payload &trans,
		sc_core::sc_time &t){}

	virtual bool get_direct_mem_ptr(
		tlm::tlm_generic_payload &trans,
		tlm::tlm_dmi &dmi_data){return false;}

	virtual unsigned int transport_dbg(
		tlm::tlm_generic_payload &trans){return 0;}

private:
	class iss_sync_sc: public sc_core::sc_prim_channel
	{
		private:

		sc_iss  *m_pSCISS;
		virtual void update()
		{
			m_pSCISS->ShiftRegs();
			m_pSCISS->PostShiftRegs();
#ifdef ICMA_TESTING
			m_pSCISS->icma_resp_delay_countdown();
#endif
#ifdef DMAC_TESTING
			m_pSCISS->dmac_resp_delay_countdown();
#endif
	
		}

		public:

		void LinkToISS(sc_iss *p_pSCISS)
		{
			m_pSCISS = p_pSCISS;
		}

	} m_iss_sync_sc;
	
	icache_module_new *m_pICACHE;
	DMAC *m_pDMAC;
	iss_timer *m_pTIMER;
	
	int m_intCycles;
	int m_intID;
	std::string m_strName;

	std::fstream iss_err;

	void DoCycle();


#include "src/funcs.h"

#include "src/dsp_res.h"

#include "src/ctrl.h"

#include "src/ExecSlots.h"

#include "src/ResAcs.h"

#include "src/MemAcsReq.h"

#include "src/CustomINT.h"

#include "src/bus_arbitr.h"

#include "src/watchpoint.h"

#include "src/user_data.h"

#include "src/frm_main.h"

#include "src/JITCache.h"

#include "src/mem_pipe.h"

#include "src/multi_core.h"

#include "src/alu_new.h"

#include "src/mul_new.h"

#include "src/shf_new.h"

#include "src/mem_new.h"

#include "src/spu_new.h"

#include "src/ext_new.h"

#include "src/no_calc_new.h"

#include "src/BPB.h"

#include "src/breakpoint.h"

#include "src/log_info.h"

#ifdef ICMA_TESTING
	#include "src/icma.h"
#endif

#ifdef LIBTESTCODE
	bool m_CodeCovForLibTest;
	typedef struct{
		int cnttrue;
		int cntfalse;
	}SBoolCnt;
	map<unsigned int, int>m_pc;
	map<unsigned int, SBoolCnt>m_cond_pc;

public:	void PrintCodeCoverage(char *FPath);
public:	void PrintCondCoverage();
#endif

	#include "src/iss_dmac.h"

	void ISSStepCycle();
	void ShiftRegs();
	void PostShiftRegs();
	//-----------------------------------------------------------------------------------
	inline void IncCycles()
	{
		m_u32CyclesL++;
		if (m_u32CyclesL == 0)
		{
			m_u32CyclesH++;
		}

		#ifdef  BWSIM_PUB_MODE
		if ( u32ro_ExcpCode == 0 )
		{
			u32r_CyclesL = m_u32CyclesL;
			u32r_CyclesH = m_u32CyclesH;
		}
		#else
		u32r_CyclesL = m_u32CyclesL;
		u32r_CyclesH = m_u32CyclesH;
		#endif		

	}


public:
	sc_in_clk m_clk;
	/*
	tlm_utils::simple_initiator_socket<sc_iss> m_iDMACSocket;
	tlm_utils::simple_target_socket<sc_iss> m_tDMACSocket;

	tlm_utils::simple_target_socket<sc_iss> m_tDMACCh0WrSocket; // DMAC ch0 burst��ʽд
	tlm_utils::simple_target_socket<sc_iss> m_tDMACCh0RdSocket; // DMAC ch0 burst��ʽ��
	*/
	tlm::tlm_initiator_socket <CH_WIDTH_256, mydma_protocol_types> m_iDMACSocket;
	tlm::tlm_target_socket <CH_WIDTH_256, mydma_protocol_types> m_tDMACSocket;
	// used for inter-core memory accessing
#ifdef ICMA_TESTING
	tlm_utils::simple_initiator_socket<sc_iss> m_iICMASocket;
	tlm_utils::simple_target_socket<sc_iss> m_tICMASocket;
#endif

	void PrintDataMem()
	{
		LogDataMem();
	}
	//------------------------------------------------------
	bool SetIOPath(const char *p_pPath);
	void SetLogMode(DSPU32 p_u32Mode);
	void SetTestMode(DSPU32  p_u32Mode);
	void RstDspDataMem();
	void RstDspMem();
	void InitDspMem();
	bool LogDSPMem();
	bool IsTestEnded();

	void SetID(DSPU16 p_u16CoreID);
	void SetICACHE(icache_module_new *p_pICACHE);
	void SetDMAC(DMAC *p_DMAC);

	void ResetCacheMem();
	
	bool GetBootAddr(DSPU32 &u32Addr)
	{
		return (rd_dmac_reg(m_intID + 0x9028010, &u32Addr));
	}
	
	void SetTIMER(iss_timer *p_pTIMER)
	{
		m_pTIMER = p_pTIMER;
	}
	// For ISS statistics use (liuyu)
	void ISSStat();

	void ISSEnStat(bool bolEnStat);
	bool GetResInfo(DSPU32 *pStatInfo);
	void GetResInfo_Phase(RES_STAT_PHASE ePhase, DSPU32 *pStatInfo);

#include "./jtag/JtagInterface.h"

	//------------------------------------------------------
    SC_HAS_PROCESS(sc_iss);
    sc_iss(sc_module_name p_name, int p_intID)
    {
		m_iss_sync_sc.LinkToISS(this);

		m_intCycles = 0;
		m_intID = p_intID;
		m_strName = p_name;
		/*
		m_iDMACSocket.register_nb_transport_bw(this, &sc_iss::nb_transport_bw_dmac);
		m_tDMACSocket.register_nb_transport_fw(this, &sc_iss::nb_transport_fw_dmac);
		m_tDMACCh0WrSocket.register_nb_transport_fw(this, &sc_iss::nb_transport_fw_dmac);
		m_tDMACCh0RdSocket.register_nb_transport_fw(this, &sc_iss::nb_transport_fw_dmac);
		*/
		m_iDMACSocket.bind(*this);
		m_tDMACSocket.bind(*this);
#ifdef ICMA_TESTING
		m_iICMASocket.register_nb_transport_bw(this, &sc_iss::nb_transport_bw_icma);
		m_tICMASocket.register_nb_transport_fw(this, &sc_iss::nb_transport_fw_icma);
#endif
		SC_METHOD(DoCycle);
		sensitive_pos << m_clk;
    }

	void Open_IssErr()
	{
		stringstream ss_err;
		ss_err << g_arrIOPath << "/iss_err.txt";

	//	std::cerr << "iss_err path is: " << ss.str() << std::endl;
		iss_err.open(ss_err.str().c_str(), fstream::out);
		if(!iss_err)
		{
			//std::cerr << "error: unable to open iss_err file: " << iss_err << std::endl;
		}
	}

	~sc_iss()
	{
		if(iss_err != NULL)
		{
			iss_err.close();
		}

		if(ioserver!=NULL)
		{
			delete ioserver;
		}
	}

	bool isFatalExcp()
	{
		return (u32ro_ExcpCode != 0);
	}

	bool isIdle()
	{
		return bolro_Idle;
	}

	bool isStepInsn()
	{
		return m_bolStepInsn;
	}
	
	void ReleaseIdle()
	{
		bolro_Idle = false;
		bolri_Idle = false;
	}

	/*
	�쳣��(exception code)��
	1:�������ݴ洢��д��ַԽ�磨����U��ַ��������
	2:�������ݴ洢��д��ַԽ�磨����V��ַ��������
	3:�������ݴ洢��д��ַԽ�磨����W��ַ��������
	4:�������ݴ洢��дд��ͻ������U��ַ��������
	5:�������ݴ洢��дд��ͻ������V��ַ��������
	6:�������ݴ洢��дд��ͻ������W��ַ��������
	7:�������ݴ洢��дд��ͻ��U��V��W��ַ������֮�䣩
	8:��λ���ڲ��洢��дд��ͻ
	��λ��Ĭ��ֵΪ0��
	*/
	DSPU32 getExcode()
	{
		DSPU32 u32ExCode = 0;
		DSPU32 u32ExcpMask = u32ro_ExcpCode;

		// SHF exceptions
		if(u32ExcpMask >= 65536)
			u32ExCode = 8;
		// Mem access exceptions
		else
		{
			for(int i = 8; i > 0; i--)
			{
				if(GIsBitSet(u32ExcpMask, i))
				{
					u32ExCode = i;
					break;
				}
			}
		}

		return u32ExCode;
	}

	/*
	  * outputPath is output directory
	  * mainAddr is address of entrypoint
	  * return false means creating ouput file error
	  * return true on success
	  */
	bool NotifyABIInfoFromECS(const char *outputPath, DSPU32 mainAddr) {
		FILE *fp = NULL;
		strcpy(g_arrABIPath, outputPath);

		sprintf(g_arrFileName, "%s/ABI.txt", g_arrABIPath);
		if ((fp = fopen(g_arrFileName, "w+")) == NULL) {
			fprintf(stderr, "Cannot open ABI.txt\n");
			return false;			
		}
		
		m_u32ABIMask = 0xf;
		m_u32ABIBase = 0x417fff;
		m_u32ABITop = 0x408000;
		m_bolABIChkEn = true;
		m_bolABIChkFromECS = true;		
		m_u32MainAddr = mainAddr;
		fclose(fp);
		return true;
	}
};

#endif /* SC_ISS_H_ */
