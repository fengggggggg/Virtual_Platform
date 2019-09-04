#ifndef SYSTEMCONFIGREG_H_
#define SYSTEMCONFIGREG_H_

#include "../../dmac_sim/dmac_global.h"


class SystemConfigReg : public sc_module 
	,public tlm::tlm_bw_transport_if<mydma_protocol_types>
	,public tlm::tlm_fw_transport_if<mydma_protocol_types>{

public:	
	sc_in_clk clk;

	SC_HAS_PROCESS(SystemConfigReg);

	SystemConfigReg(sc_module_name mn);
	~SystemConfigReg(){}


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


class iss_sync_sc: public sc_core::sc_prim_channel
	{
	private:

		SystemConfigReg  *m_pSysCfgReg;
		virtual void update()
		{
			m_pSysCfgReg->ShiftRegs();
		}

	public:

		void LinkToReg(SystemConfigReg *p_pSysCfgReg)
		{
			m_pSysCfgReg = p_pSysCfgReg;
		}

	} m_sync_ins;

	void clock_tick();


	tlm::tlm_initiator_socket	<CH_WIDTH_256,mydma_protocol_types> init_socket2dmac0; //32 init for core0
	tlm::tlm_target_socket		<CH_WIDTH_256,mydma_protocol_types> targ_socket2dmac0; //32 targ for core0

	tlm::tlm_initiator_socket	<CH_WIDTH_256,mydma_protocol_types> init_socket2dmac1; //32 init for core1
	tlm::tlm_target_socket		<CH_WIDTH_256,mydma_protocol_types> targ_socket2dmac1; //32 targ for core1


	void send_event_to_core(unsigned int core_id, unsigned int event_num, bool is_posedge);

	//void GetSystemConfigHandle(SystemConfigReg* m_SysCfgPtr);

	void ShiftRegs();

	void reset();

	bool write_reg(unsigned int addr,unsigned int val );	

	bool read_reg(unsigned int addr, unsigned int & result);	

	

	//Global
	RegType	CIDR_R;
	RegType	GCSR_R;
	RegType	BOOTCOMPLETE_R;
	RegType	CISR_R;
	RegType	C0_BOOT_ADDR_R;
	RegType	C1_BOOT_ADDR_R;
	RegType	BOOT_DEVICE_R;
	RegType	BOOT_DEVICE_CFG_R;
	RegType	PCIE_MODE_R;
	RegType	CHIP_MODE_R;
		//µ˜ ‘œµÕ≥∏®÷˙≈‰÷√ø’º‰	
	RegType	MCRCR_R;
		//PMA∏®÷˙≈‰÷√ø’º‰
	RegType	PMACR0_R;
	RegType	PMACR1_R;
	RegType	PMACR2_R;
	RegType	PMACR3_R;
	RegType	PMACR4_R;
	RegType	PMACR5_R;
		//PCIE∏®÷˙≈‰÷√ø’º‰
	RegType	PGSR_R;
	RegType	PLACR_R;
	RegType	PLICR_R;
	RegType	PLIPSR_R;
	RegType	PLIPMR_R;
	RegType	PLISR_R;
	RegType	PCER_R;
	RegType	PPSCAR_R;
	RegType	PCEFR_R;
	RegType	PMSGR0_R;
	RegType	PMSGR1_R;
	RegType	PMSGR2_R;
	RegType	PMSGR3_R;
	RegType	PMSGR4_R;
	RegType	PMSGR5_R;
	RegType	PMUER_R;
	RegType	PVFER_R;
	RegType	EP_IRQ_SET_R;
	RegType	ER_IRQ_CLR_R;
	RegType	ER_IRQ_STATUS_R;
	RegType	MSI_DATA_R;
	RegType	MSI0_IRQ_STATUS_R;
	RegType	MSI0_IRQ_ENABLE_R;
	RegType	MSI0_IRQ_CLR_R;
	RegType	MSI1_IRQ_STATUS_R;
	RegType	MSI1_IRQ_ENABLE_R;
	RegType	MSI1_IRQ_CLR_R;
	RegType	MSI2_IRQ_STATUS_R;
	RegType	MSI2_IRQ_ENABLE_R;
	RegType	MSI2_IRQ_CLR_R;
	RegType	MSI3_IRQ_STATUS_R;
	RegType	MSI3_IRQ_ENABLE_R;
	RegType	MSI3_IRQ_CLR_R;
	RegType	MSI4_IRQ_STATUS_R;
	RegType	MSI4_IRQ_ENABLE_R;
	RegType	MSI4_IRQ_CLR_R;
	RegType	MSI5_IRQ_STATUS_R;
	RegType	MSI5_IRQ_ENABLE_R;
	RegType	MSI5_IRQ_CLR_R;
	RegType	MSI6_IRQ_STATUS_R;
	RegType	MSI6_IRQ_ENABLE_R;
	RegType	MSI6_IRQ_CLR_R;
	RegType	MSI7_IRQ_STATUS_R;
	RegType	MSI7_IRQ_ENABLE_R;
	RegType	MSI7_IRQ_CLR_R;
	RegType	L1_PM_SUBSTATE_R;
	RegType HRTR_R; //add by wangqiang on 2016.5.11
		//SRIO∏®÷˙≈‰÷√ø’º‰ 
	RegType	SEITR0_R;
	RegType	SEISR0_R;
	RegType	SEICR0_R;
	RegType	SLCR0_R;
	RegType	SDIDCAR0_R;
	RegType	SDINFCAR0_R;
	RegType	SAIDCAR0_R;
	RegType	SGCR0_R;
	RegType	SPNR0_R;
	RegType	SPVR0_R;
	RegType	SDPSR0_R;
	RegType	SSPLSR0_R;
	RegType	SPSR0_R;
	RegType	SPCR0_R;
	RegType	SSLSSR0_R;
//add by wangqiang on 2016.5.11
	RegType SLKSPD0_R;
	RegType TXPRSTINSI0_R;
	RegType TXPOMAX0_R;
	RegType TXPOMIN0_R;
	RegType TXMAMAX0_R;
	RegType TXMAMIN0_R;
	RegType TXPEMAX0_R;
	RegType TXPEMIN0_R;
	RegType RETREMC0_R;
	RegType TIMERC20_R;
	RegType TIMERC10_R;
	RegType TIMERC00_R;
	RegType AETST0_R;

	RegType	SEITR1_R;
	RegType	SEISR1_R;
	RegType	SEICR1_R;
	RegType	SLCR1_R;
	RegType	SDIDCAR1_R;
	RegType	SDINFCAR1_R;
	RegType	SAIDCAR1_R;
	RegType	SGCR1_R;
	RegType	SPNR1_R;
	RegType	SPVR1_R;
	RegType	SDPSR1_R;
	RegType	SSPLSR1_R;
	RegType	SPSR1_R;
	RegType	SPCR1_R;
	RegType	SSLSSR1_R;
//add by wangqiang on 2016.5.11
	RegType SLKSPD1_R;
	RegType TXPRSTINSI1_R;
	RegType TXPOMAX1_R;
	RegType TXPOMIN1_R;
	RegType TXMAMAX1_R;
	RegType TXMAMIN1_R;
	RegType TXPEMAX1_R;
	RegType TXPEMIN1_R;
	RegType RETREMC1_R;
	RegType TIMERC21_R;
	RegType TIMERC11_R;
	RegType TIMERC01_R;
	RegType AETST1_R;

		//∫Àº‰÷–∂œ
	RegType	IPCGR0_R;
	RegType	IPCSR0_R;
	RegType	IPCCR0_R;
	RegType	IPCGR1_R;
	RegType	IPCSR1_R;
	RegType	IPCCR1_R;

		//DDR AXI ≈‰÷√
	RegType DDR_AXI_CFG0_R;
	RegType DDR_AXI_CFG1_R;


		// ±÷”°¢∏¥Œª≈‰÷√º∞◊¥Ã¨ºƒ¥Ê∆˜
	RegType	PLL0_STATUS_R;
	RegType	PLL0_CTL0_R;
	RegType	PLL0_CTL1_R;
	RegType	PLL0_CTL2_R;
	//RegType	PLL0_STATUS1_R;
	RegType	CLK_SYS_CTL_R;

	RegType	PLL1_STATUS_R;
	RegType	PLL1_CTL0_R;
	RegType	PLL1_CTL1_R;
	RegType	PLL1_CTL2_R;

	RegType	CLK_PP_CTL_R;
	RegType	CLK_ETHM_CTL_R;
	RegType	CLK_ETHS_CTL_R;
	RegType	CLK_PM_CTL_R;

	RegType CLK_I2C_CTL_R;
	RegType CLK_SPI_CTL_R;


	RegType	PLL2_STATUS_R;
	RegType	PLL2_CTL0_R;
	RegType	PLL2_CTL1_R;
	RegType	PLL2_CTL2_R;

	RegType	CLK_DDR_CTL_R;

	RegType	RST_STATUS_R;
	RegType	RST_TYPE_STATUS_R;

	RegType	RST_RM_STATUS_R;
	
	RegType	RST_CTL_R;
	RegType	RST_INIT_CTL_R;
	RegType	RST_SDS_CTL_R;

	RegType RST_SDS_STATUS_R;
	RegType DBG_CTL_R;

		//∂® ±∆˜º∞watchdog≈‰÷√ø’º‰
	RegType	TCR0_R;
	RegType	TCSR0_R;
	RegType	TCCR0_R;
	RegType	TPRLO0_R;
	RegType	TPRHI0_R;
	RegType	TCNTLO0_R;
	RegType	TCNTHI0_R;

	RegType	TCR1_R;
	RegType	TCSR1_R;
	RegType	TCCR1_R;
	RegType	TPRLO1_R;
	RegType	TPRHI1_R;
	RegType	TCNTLO1_R;
	RegType	TCNTHI1_R;

	RegType	TCR2_R;
	RegType	TCSR2_R;
	RegType	TCCR2_R;
	RegType	TPRLO2_R;
	RegType	TPRHI2_R;
	RegType	TCNTLO2_R;
	RegType	TCNTHI2_R;

	RegType	TCR3_R;
	RegType	TCSR3_R;
	RegType	TCCR3_R;
	RegType	TPRLO3_R;
	RegType	TPRHI3_R;
	RegType	TCNTLO3_R;
	RegType	TCNTHI3_R;

	RegType	TCR4_R;
	RegType	TCSR4_R;
	RegType	TCCR4_R;
	RegType	TPRLO4_R;
	RegType	TPRHI4_R;
	RegType	TCNTLO4_R;
	RegType	TCNTHI4_R;

	RegType	TCR5_R;
	RegType	TCSR5_R;
	RegType	TCCR5_R;
	RegType	TPRLO5_R;
	RegType	TPRHI5_R;
	RegType	TCNTLO5_R;
	RegType	TCNTHI5_R;

	RegType	TCR6_R;
	RegType	TCSR6_R;
	RegType	TCCR6_R;
	RegType	TPRLO6_R;
	RegType	TPRHI6_R;
	RegType	TCNTLO6_R;
	RegType	TCNTHI6_R;

	RegType	TCR7_R;
	RegType	TCSR7_R;
	RegType	TCCR7_R;
	RegType	TPRLO7_R;
	RegType	TPRHI7_R;
	RegType	TCNTLO7_R;
	RegType	TCNTHI7_R;

	RegType	WDTCR0_R;
	RegType	WDTCSR0_R;
	RegType	WDTCCR0_R;
	RegType	WDTPRLO0_R;
	RegType	WDTPRHI0_R;
	RegType	WDTCNTLO0_R;
	RegType	WDTCNTHI0_R;

	RegType	WDTCR1_R;
	RegType	WDTCSR1_R;
	RegType	WDTCCR1_R;
	RegType	WDTPRLO1_R;
	RegType	WDTPRHI1_R;
	RegType	WDTCNTLO1_R;
	RegType	WDTCNTHI1_R;		



	//Rabio Ctl0
	RegType RAB_RST_CTRL0_R;

	//Rabio Ctl1
	RegType	RAB_RST_CTRL1_R;

		//UART Ctl
	RegType	LCR_R;
	RegType	FAR_R;
		//I2C  Ctl


		//GPIO Ctl
	RegType	GPIOPADR_R;											//gpio_swporta_dr
	RegType	GPIOPCDR_R;											//gpio_swportc_dr
	RegType	GPIOPDCTL_R;											//gpio_portd_ctl
		//SPI  Ctl
	RegType	CTRLR0_R;
	RegType	BAUDR_R;
	RegType	DR_R;
		//PCIE  Ctl
	RegType	IBADDR0A_R;											//ib_addr0_pcie0,
	RegType	IBADDR0B_R;											//ib_addr0_pcie1









//”≤º˛–≈∫≈¡ø
	RegType	HW_SEM_R[HSRegNum];
};




#endif
