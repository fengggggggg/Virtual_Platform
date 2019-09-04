
#ifndef DSP_TOP_H_
#define DSP_TOP_H_


// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#ifdef DSP_WIN32
#include ".\src\AlgoriLib\dsptypes.h"
#else
#include "./src/AlgoriLib/dsptypes.h"
#endif

#include "sc_iss.h"

#include <systemc.h>

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#ifdef BWSIM_CMP_100_104
#include <unistd.h> 
#endif

#include "common.h"
#include "mp_bus.h"

#include "./core_share_sim/share_mmac/mmac.h"
#include "./core_share_sim/share_progmem/pmem.h"
#include "./core_share_sim/share_progmem/ddr.h"
#include "./core_share_sim/share_progmem/share_sram.h"

#include "./dmac_sim/DMAC.h"
#include "./core_share_sim/share_modules/SystemConfigReg.h"
#include "./core_share_sim/share_modules/DDR_MODULE.h"
#ifdef DSP_WIN32
#include "icache_sim\icache_module_new.h"
#else
#include "icache_sim/icache_module_new.h"
#endif

using namespace BWDSP104X;

//extern sc_iss* p_iss[ISS_NUM_DEF];

class dsp_top : public sc_module
{
private:

	int m_intCycles;
	sc_iss* m_pISS[ISS_NUM_DEF];
	//dsp_icache* m_pICACHE[ISS_NUM_DEF];

	mmac *m_pMMAC;
	pmem *m_pMEM;
	ddr *m_pDDR[2];
	share_sram * m_share_sram;

	icache_module_new* m_pICACHE_LG[ISS_NUM_DEF];
	DMAC* dmac_ptr[ISS_NUM_DEF];
	SystemConfigReg* m_pSysCfgReg;
	DDR_MODULE * m_pDDRMODULE;

	char m_arrLogDir[100];

#ifdef BWSIM_CMP_100_104
	char m_arrCurrWorkDir[100];
#endif


public:

	sc_signal<bool> m_pseudo_clk;
	sc_in_clk m_dsp_top_clk;
	sc_iss *GetCoreHandle(unsigned int p_u32CoreID);
	DSPU32 ReadXR8ofCore(unsigned int p_u32CoreID);

	DDR_MODULE* GetDDRHandle(){
		return m_pDDRMODULE;
	}

	pmem *GetPMemHandle()
	{
		return m_pMEM;
	}

	share_sram *GetShareSRAMHandle()
	{
		return m_share_sram;
	}

	mmac *GetMmacHandle()
	{
		return m_pMMAC;
	}

	SystemConfigReg* GetSysCfgRegHandle()
	{
		return m_pSysCfgReg;
	}

	ddr* GetDDR0Handle()
	{
		return m_pDDR[0];
	}

	ddr* GetDDR1Handle()
	{
		return m_pDDR[1];
	}


	SC_HAS_PROCESS(dsp_top);
	dsp_top(sc_module_name p_name)
	{
		char arrName[100];
		iss_timer *p_timer;

		for (int i = 0; i < ISS_NUM_DEF; i++)
		{
			sprintf(arrName, "iss%d", i);

			m_pISS[i] = new sc_iss(arrName, i);			
			m_pISS[i]->m_clk(m_dsp_top_clk);
			//m_pISS[i]->m_clk(m_pseudo_clk);  // ���øò���			

			//m_pICACHE[i] = new dsp_icache;

			sprintf(arrName, "cache%d", i);
			m_pICACHE_LG[i] = new icache_module_new(arrName);	
			m_pICACHE_LG[i]->NotifyCoreID(i);
			m_pICACHE_LG[i]->clk(m_dsp_top_clk);

			m_pISS[i]->SetICACHE(m_pICACHE_LG[i]);


			sprintf(arrName, "timer%d", i);
			p_timer = new iss_timer(arrName, i);
			p_timer->clk(m_dsp_top_clk);
			m_pISS[i]->SetTIMER(p_timer);

			sprintf(arrName, "DMAC%d", i);
			dmac_ptr[i] = new DMAC(arrName,i);
			m_pISS[i]->SetDMAC(dmac_ptr[i]);

			m_pISS[i]->m_iDMACSocket(dmac_ptr[i]->targ_socket2core);
			dmac_ptr[i]->init_socket2core(m_pISS[i]->m_tDMACSocket);

			dmac_ptr[i]->clk(m_dsp_top_clk);

		}

		dmac_ptr[0]->init_socket2other(dmac_ptr[1]->targ_socket2other);
		dmac_ptr[1]->init_socket2other(dmac_ptr[0]->targ_socket2other);

		m_pMMAC = new mmac("MMAC");
		m_pMEM = new pmem("PMEM");
		m_pDDR[0] = new ddr(0,"DDR0");
		m_pDDR[1] = new ddr(1,"DDR1");
		m_share_sram= new share_sram("SharedSRAM");
		m_pSysCfgReg = new SystemConfigReg("SysCfgReg");
		m_pDDRMODULE	= new DDR_MODULE("DDR_MODULE");

		dmac_ptr[0]->init_socket2SyscfgReg(m_pSysCfgReg->targ_socket2dmac0);
		m_pSysCfgReg->init_socket2dmac0(dmac_ptr[0]->targ_socket2SyscfgReg);
		dmac_ptr[1]->init_socket2SyscfgReg(m_pSysCfgReg->targ_socket2dmac1);
		m_pSysCfgReg->init_socket2dmac1(dmac_ptr[1]->targ_socket2SyscfgReg);

		m_pSysCfgReg->clk(m_dsp_top_clk);
		m_pSysCfgReg->reset();

		
		dmac_ptr[0]->init_socket2ddr(m_pDDRMODULE->targ_socket2dmac0);
		m_pDDRMODULE->init_socket2dmac0(dmac_ptr[0]->targ_socket2ddr);
		dmac_ptr[1]->init_socket2ddr(m_pDDRMODULE->targ_socket2dmac1);
		m_pDDRMODULE->init_socket2dmac1(dmac_ptr[1]->targ_socket2ddr);

		
		//////////////////////////////////////////////////////////////////////

		m_pDDRMODULE->clk(m_dsp_top_clk);
		m_pDDRMODULE->reset();

		m_pMMAC->clk(m_dsp_top_clk);
		m_pMEM->clk(m_dsp_top_clk);
		m_pMEM->reset();

		m_pDDR[0]->clk(m_dsp_top_clk);
		m_pDDR[1]->clk(m_dsp_top_clk);
		m_pDDR[0]->reset();
		m_pDDR[1]->reset();

		m_share_sram->clk(m_dsp_top_clk);
		m_share_sram->reset();

		m_pMMAC->initiator_socket_to_pmem(m_pMEM->target_socket_from_mmac);
		m_pMMAC->initiator_socket_to_ddr[0](m_pDDR[0]->target_socket_from_mmac);
		m_pMMAC->initiator_socket_to_ddr[1](m_pDDR[1]->target_socket_from_mmac);

		for(int i=0;i<ISS_NUM_DEF;i++)
		{
#ifdef ICMA_TESTING
			// core 0 -> core 1
			if(i%2 == 0)
			{
				m_pISS[i]->m_iICMASocket(m_pISS[i+1]->m_tICMASocket);
			}
			// core 1 -> core 0
			else
			{
				m_pISS[i]->m_iICMASocket(m_pISS[i-1]->m_tICMASocket);
			}			
#endif		
			m_pICACHE_LG[i]->init_socket_to_sram(m_pMMAC->target_socket_from_core[i]);
			m_pICACHE_LG[i]->init_socket_to_shared_sram(m_share_sram->target_socket_from_icache[i]);

			// ISS�еı���u32r_CoreID, g_arrIOPath, m_u32LogMode, m_u32TestMode��δ��ʼ�������
			// �����ڴ˴��ֱ�ʹ��SetID(), SetIOPath(), SetLogMode(), SetTestMode()��ʼ��һ�Ρ�
			// ISS��Reset()�����ڵ��Թ����лᱻ��������ε��ã�
			// �������ﱻ��ʼ����u32r_CoreID, g_arrIOPath, m_u32LogMode, m_u32TestMode��������Reset()�б����㡣
			m_pISS[i]->Reset();
			m_pISS[i]->SetID(i);
			m_pISS[i]->RstDspMem();
			// for mem test use (liuyu)
			m_pISS[i]->InitDspMem();
			m_pISS[i]->ResetCacheMem();

#ifdef DSP_WIN32
			sprintf(m_arrLogDir, "c:\\DSPLog_core%d", i);
#else
			sprintf(m_arrLogDir,"./DSPLog_core%d",i);
#endif

#ifdef BWSIM_CMP_100_104
			// get current work directory and log directory
			getcwd(m_arrCurrWorkDir, 100);
			sprintf(m_arrLogDir, "%s/log_104_core%d", m_arrCurrWorkDir, i);
#endif

			m_pISS[i]->SetIOPath(m_arrLogDir);

#ifdef SC_ISS_DBG
			m_pISS[i]->SetLogMode(1);
			m_pISS[i]->SetTestMode(4);
#else
			m_pISS[i]->SetLogMode(0);
#endif
			m_pISS[i]->InitJtagRegister();

			m_pISS[i]->Open_IssErr();
		}

#ifdef SC_ISS_RUN_ALONE
		// fill_prog_data(p_iss[0]);
#else

#endif
	} // dsp_top(sc_module_name p_name)
};


#endif /* DSP_TOP_H_ */
