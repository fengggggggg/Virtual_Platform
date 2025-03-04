#ifndef DMAC_GLOBAL_H_
#define DMAC_GLOBAL_H_

//global define for dmac module created by wangqiang on 14.6.3

#include <systemc.h>
#include <tlm.h>
#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>
#include <bitset>
#include <vector>
#include <time.h>

#include "../iss_dmac_comm.h"
#include "assistant_function.h"

using namespace std;


/*User-defined protocol traits class in dmac*/
struct mydma_protocol_types{
	typedef tlm::tlm_generic_payload	tlm_payload_type;
	typedef tlm::tlm_phase				tlm_phase_type;
};


//icache need PROTOCOL_TYPE type
//#define PROTOCOL_TYPE mydma_protocol_types



//#define SIMULATOR_TESTING

#ifdef  SIMULATOR_TESTING

#define DMAC_LOG

#endif
//#define DMAC_LOG



//switch for output sentence valid or not

//#define wrlog
//#define output_valid

#ifdef	DMAC_LOG

#define  NORMAL_REPORT_CORE(s) cout<<(sc_time_stamp().value()/1000 - 5)/10<<"	,CORE_"<<m_intID<<" report:"<<s<<endl; 
#define  ERROR_REPORT_CORE(s)  cerr<<(sc_time_stamp().value()/1000 - 5)/10<<"	,CORE_"<<m_intID<<" report:"<<s<<endl;

#define  NORMAL_REPORT_DMAC(s) DmacLog<<(sc_time_stamp().value()/1000 - 5)/10<<"	,DMAC_"<<core_id<<" report:"<<s<<endl; 
#define  ERROR_REPORT_DMAC(s)  DmacLog<<(sc_time_stamp().value()/1000 - 5)/10<<"	,DMAC_"<<core_id<<" report:"<<s<<endl;

#define NORMAL_REPORT_REG(s)   cout<<(sc_time_stamp().value()/1000 - 5)/10<<"	,Reg_"<<core_id<<" report:"<<s<<endl; 
#define ERROR_REPORT_REG(s)    cerr<<(sc_time_stamp().value()/1000 - 5)/10<<"	,Reg_"<<core_id<<" report:"<<s<<endl; 

#define  NORMAL_REPORT_AHB(s) cout<<(sc_time_stamp().value()/1000 - 5)/10<<"	,AHB report:"<<s<<endl; 
#define  ERROR_REPORT_AHB(s)  cerr<<(sc_time_stamp().value()/1000 - 5)/10<<"	,AHB report:"<<s<<endl;

#define  NORMAL_REPORT_SYSCFG(s) cout<<(sc_time_stamp().value()/1000 - 5)/10<<"	,SYSCFGREG report:"<<s<<endl;
#define  ERROR_REPORT_SYSCFG(s) cerr<<(sc_time_stamp().value()/1000 - 5)/10<<"	,SYSCFGREG report:"<<s<<endl;

#else

#define  NORMAL_REPORT_CORE(s)  ;
#define  ERROR_REPORT_CORE(s)   ;

#define  NORMAL_REPORT_DMAC(s)	;
#define  ERROR_REPORT_DMAC(s)	;

#define NORMAL_REPORT_REG(s)	;
#define ERROR_REPORT_REG(s)		;


#define  NORMAL_REPORT_AHB(s)   ;
#define  ERROR_REPORT_AHB(s)    ;

#define  NORMAL_REPORT_SYSCFG(s) ;
#define  ERROR_REPORT_SYSCFG(s) ;
#endif



#define DELAY_INTERRUPT 4999 //actually delay is DELAY_INTERRUPT+1 cycles

//enum define for DMAC_model
enum mission_type{
	WR_REQ,
	WR_REQ_RD_CORE,
	WR_REQ_SRC_ADDR_ERR,
	WR_REQ_DST_ADDR_ERR,
	

	RD_REQ,
	RD_REQ_DST_ADDR_ERR,
	RD_REQ_SRC_ADDR_ERR,
	RD_ACK,

	WR_CONFIG_ERR,
	RD_CONFIG_ERR
};


//enum define for TLM socket function return TYPE
enum respType{
	RESP_NULL=0,
	RESP_OK=1,
	RESP_STOP=2,
	RESP_CONFIG_ERROR=3,
	RESP_ADDR_ERROR=4
};





//------------ task_list_entry define based on sc_prim_channel,all add/clear behavior call request_update, allow multi_driver
enum task_list_type{
	NO_TYPE = -1, DMA_REQ = 0, DMA_ACK, INSN_REQ, INSN_ACK
};

//enum for diff Channel width
enum channelWidth{ CH_WIDTH_32=32,CH_WIDTH_64=64,CH_WIDTH_128=128,CH_WIDTH_256=256 };


//enum for define diff mission check return value
enum check_mission_return{
	MISSION_CHECK_ERROR = -1, NO_MISSION = 0 , NEW_MISSION, STALLED_MISSION, CANCEL_MISSION, BUSY_MISSION
};



//enum for define all NOCI ID
enum NOCI_ID{
	DEFAULT_ID		= -1,
	CORE0_ID		= 0x0,
	CORE1_ID		= 0x1,
	CORE_DMAC0_ID	= 0xf0,
	CORE_DMAC1_ID	= 0xf1,
	DDR0_ID		= 0xff0,
	DDR1_ID		= 0xff1,
	SERDES0_ID		= 0xfff0,
	SERDES1_ID		= 0xfff1,	 
	SERDES2_ID		= 0xfff2,
	SERDES3_ID		= 0xfff3,
	SERDES4_ID		= 0xfff4,
	SERDES5_ID		= 0xfff5,
	SERDES6_ID		= 0xfff6,
	SERDES7_ID		= 0xfff7,
	MMAC_ID		= 0xffff0,
	JTAG_ID		= 0xffff1,
	ParaPort_ID	= 0xffff2, 
	GPIO_ID		= 0xffff3,
	SysAgent_ID	= 0xffff4,
	Timer_ID		= 0xffff5,
	Semaphore_ID	= 0xffff6,
	ETH0_CTL_ID	= 0xffff7,
	ETH1_CTL_ID	= 0xffff8,
	UART_ID		= 0xffff9

};

//enum for REGS name & CH_name

enum CH_NAME{
		HCH = 0,
		XCH0,
		//XCH1,
		XCH2,
		XCH3
};

enum reg_name{
	NO_NAME = -1,
	GLB_STATUS,				//ofst_addr = 1						
	//GLB_ID,					//ofst_addr = 2
	//GLB_TGT_ID0,			//ofst_addr = 3
	//GLB_TGT_ID1,			//ofst_addr = 4
	//GLB_TGT_ID2,			//ofst_addr = 5


	HCH_START,						// ofst_addr =  32 + 0x00
	HCH_STATUS,						// ofst_addr =  32 + 0x01
	HCH_CTL,						// ofst_addr =  32 + 0x02
	HCH_DST_START_ADDRH,			// ofst_addr =  32 + 0x0c //add 2015.1.12
	HCH_SRC_START_ADDR,				// ofst_addr =  32 + 0x10
	HCH_SRC_LEN_X,					// ofst_addr =  32 + 0x11
	HCH_SRC_ADDR_STEP,				// ofst_addr =  32 + 0x12
	HCH_SRC_LEN_Y,					// ofst_addr =  32 + 0x13
	HCH_SRC_CURR_ADDR,				// ofst_addr =  32 + 0x14
	HCH_SRC_LEN_REM_X,				// ofst_addr =  32 + 0x15
	HCH_SRC_LEN_REM_Y,				// ofst_addr =  32 + 0x16
	HCH_DST_START_ADDRL,				// ofst_addr =  32 + 0x18//mod 2012.1.12
	HCH_DST_LEN_X,					// ofst_addr =  32 + 0x19
	HCH_DST_ADDR_STEP,				// ofst_addr =  32 + 0x1a
	HCH_DST_LEN_Y,					// ofst_addr =  32 + 0x1b
	HCH_DST_CURR_ADDR,				// ofst_addr =  32 + 0x1c
	HCH_DST_LEN_REM_X,				// ofst_addr =  32 + 0x1d
	HCH_DST_LEN_REM_Y,				// ofst_addr =  32 + 0x1e


	XWCHi_START,					// ofst_addr =  (1+i)*64 + 0x00
	XWCHi_STATUS,					// ofst_addr =	(1+i)*64 + 0x01
	XWCHi_CTL,						// ofst_addr =	(1+i)*64 + 0x02
	XWCHi_DST_START_ADDRH,			// ofst_addr =  (1+i)*64 + 0x0c //add 2015.1.12
	XWCHi_SRC_START_ADDR,			// ofst_addr =  (1+i)*64 + 0x10
	XWCHi_SRC_LEN_X,				// ofst_addr =  (1+i)*64 + 0x11
	XWCHi_SRC_ADDR_STEP,			// ofst_addr =  (1+i)*64 + 0x12
	XWCHi_SRC_LEN_Y,				// ofst_addr =  (1+i)*64 + 0x13
	XWCHi_SRC_CURR_ADDR,			// ofst_addr =  (1+i)*64 + 0x14
	XWCHi_SRC_LEN_REM_X,			// ofst_addr =  (1+i)*64 + 0x15
	XWCHi_SRC_LEN_REM_Y,			// ofst_addr =  (1+i)*64 + 0x16
	XWCHi_DST_START_ADDRL,				// ofst_addr =  (1+i)*64 + 0x18//mod 2012.1.12
	XWCHi_DST_LEN_X,				// ofst_addr =  (1+i)*64 + 0x19
	XWCHi_DST_ADDR_STEP,			// ofst_addr =  (1+i)*64 + 0x1a
	XWCHi_DST_LEN_Y,				// ofst_addr =  (1+i)*64 + 0x1b
	XWCHi_DST_CURR_ADDR,			// ofst_addr =  (1+i)*64 + 0x1c
	XWCHi_DST_LEN_REM_X,			// ofst_addr =  (1+i)*64 + 0x1d
	XWCHi_DST_LEN_REM_Y,			// ofst_addr =  (1+i)*64 + 0x1e
	XRCHi_START,					// ofst_addr =  (1+i)*64 + 0x20
	XRCHi_STATUS,					// ofst_addr =  (1+i)*64 + 0x21
	XRCHi_CTL,						// ofst_addr =  (1+i)*64 + 0x22
	XRCHi_DST_START_ADDRH,			// ofst_addr =  (1+i)*64 + 0x2c //add 2015.1.12
	XRCHi_SRC_START_ADDR,			// ofst_addr =  (1+i)*64 + 0x30
	XRCHi_LEN_X,					// ofst_addr =  (1+i)*64 + 0x31
	XRCHi_SRC_ADDR_STEP,			// ofst_addr =  (1+i)*64 + 0x32
	XRCHi_SRC_LEN_Y,				// ofst_addr =  (1+i)*64 + 0x33
	XRCHi_SRC_ADDR_CURR,			// ofst_addr =  (1+i)*64 + 0x34
	XRCHi_SRC_LEN_REM_X,			// ofst_addr =  (1+i)*64 + 0x35
	XRCHi_SRC_LEN_REM_Y,			// ofst_addr =  (1+i)*64 + 0x36
	XRCHi_DST_START_ADDRL,				// ofst_addr =  (1+i)*64 + 0x38//mod 2012.1.12
	XRCHi_DST_LEN_X,				// ofst_addr =  (1+i)*64 + 0x39
	XRCHi_DST_ADDR_STEP,			// ofst_addr =  (1+i)*64 + 0x3a
	XRCHi_DST_LEN_Y,				// ofst_addr =  (1+i)*64 + 0x3b
	XRCHi_DST_CURR_ADDR,			// ofst_addr =  (1+i)*64 + 0x3c
	XRCHi_DST_LEN_REM_X,			// ofst_addr =  (1+i)*64 + 0x3d
	XRCHi_DST_LEN_REM_Y,			// ofst_addr =  (1+i)*64 + 0x3e
	//------------------------------------------------------------------for dma over

	//DMA_WR_MISSION_START_sig,			//own define signals
	//DMA_RD_MISSION_START_sig,

	//------------------------------------------------------------------for insn
	INSN_REQ_INFO,	
	INSN_ACK_INFO,
//==================================================================================for SystemCfgReg
		

//zqw+ 2019.1.11 SRIO��ؼĴ���  
    //дDMA����
	RAB_WDMA_N_CTRL,            // дDMA���ƼĴ���  0x20800
    RAB_WDMA_N_ADDR,            // дDMA��������ַ�Ĵ��� 0x20804
    RAB_WDMA_N_STAT,            // дDMA״̬�Ĵ��� 0x20808
    RAB_WDMA_N_ADDR_EXT,        // дDMA��λ��ַ�Ĵ��� 0x2080C
	//��DMA����
	RAB_RDMA_N_CTRL,			// ��DMA���ƼĴ���  0x20880S
    RAB_RDMA_N_ADDR,            // ��DMA��������ַ�Ĵ��� 0x20884
	RAB_RDMA_N_STAT,            // ��DMA״̬�Ĵ��� 0x20888
	RAB_RDMA_N_ADDR_EXT,        // ��DMA��λ��ַ�Ĵ��� 0x2088C
	//DMA������
	RAB_DMA_IADDR_DESC_SEL,	        // DMA������ѡ��Ĵ���  0x20900
	RAB_DMA_IADDR_DESC_CTRL,	    // DMA�������Ĵ���-���������ƼĴ���  0x20904
	RAB_DMA_IADDR_DESC_SRC_ADDR,    // DMA�������Ĵ���-Դ��ַ�Ĵ���      0x20908
	RAB_DMA_IADDR_DESC_DEST_ADDR,   // DMA�������Ĵ���-Ŀ�ĵ�ַ�Ĵ���    0x2090C
	RAB_DMA_IADDR_DESC_NEXT_ADDR,   // DMA�������Ĵ���-��һָ���ַ�Ĵ���  0x209010

//zqw+ 2019.2.25 ���豸ID�Ĵ�����ҳ��
	Base_Device_ID_CSR,             //���豸ID�Ĵ��������ڴ��Source ID
	RAB_APB_CSR,                    //RAB_APB_CSR Register��APB����״̬�Ĵ���  0x20030  ���ڴ��ҳ��


//Global
	CIDR,
	GCSR,
	BOOTCOMPLETE,
	CISR,
	C0_BOOT_ADDR,
	C1_BOOT_ADDR,
	BOOT_DEVICE,
	BOOT_DEVICE_CFG,
	PCIE_MODE,
	CHIP_MODE,
//����ϵͳ�������ÿռ�	
	MCRCR,
//PMA�������ÿռ�
	PMACR0,
	PMACR1,
	PMACR2,
	PMACR3,
	PMACR4,
	PMACR5,
//PCIE�������ÿռ�
	PGSR,
	PLACR,
	PLICR,
	PLIPSR,
	PLIPMR,
	PLISR,
	PCER,
	PPSCAR,
	PCEFR,
	PMSGR0,
	PMSGR1,
	PMSGR2,
	PMSGR3,
	PMSGR4,
	PMSGR5,
	PMUER,
	PVFER,
	EP_IRQ_SET,
	ER_IRQ_CLR,
	ER_IRQ_STATUS,
	MSI_DATA,
	MSI0_IRQ_STATUS,
	MSI0_IRQ_ENABLE,
	MSI0_IRQ_CLR,
	MSI1_IRQ_STATUS,
	MSI1_IRQ_ENABLE,
	MSI1_IRQ_CLR,
	MSI2_IRQ_STATUS,
	MSI2_IRQ_ENABLE,
	MSI2_IRQ_CLR,
	MSI3_IRQ_STATUS,
	MSI3_IRQ_ENABLE,
	MSI3_IRQ_CLR,
	MSI4_IRQ_STATUS,
	MSI4_IRQ_ENABLE,
	MSI4_IRQ_CLR,
	MSI5_IRQ_STATUS,
	MSI5_IRQ_ENABLE,
	MSI5_IRQ_CLR,
	MSI6_IRQ_STATUS,
	MSI6_IRQ_ENABLE,
	MSI6_IRQ_CLR,
	MSI7_IRQ_STATUS,
	MSI7_IRQ_ENABLE,
	MSI7_IRQ_CLR,
	L1_PM_SUBSTATE,
	HRTR,
//SRIO�������ÿռ� 
	SEITR0,
	SEISR0,
	SEICR0,
	SLCR0,
	SDIDCAR0,
	SDINFCAR0,
	SAIDCAR0,
	SGCR0,
	SPNR0,
	SPVR0,
	SDPSR0,
	SSPLSR0,
	SPSR0,
	SPCR0,
	SSLSSR0,

	SLKSPD0,
	TXPRSTINSI0,
	TXPOMAX0,
	TXPOMIN0,
	TXMAMAX0,
	TXMAMIN0,
	TXPEMAX0,
	TXPEMIN0,
	RETREMC0,
	TIMERC20,
	TIMERC10,
	TIMERC00,
	AETST0,





	SEITR1,
	SEISR1,
	SEICR1,
	SLCR1,
	SDIDCAR1,
	SDINFCAR1,
	SAIDCAR1,
	SGCR1,
	SPNR1,
	SPVR1,
	SDPSR1,
	SSPLSR1,
	SPSR1,
	SPCR1,
	SSLSSR1,


	SLKSPD1,
	TXPRSTINSI1,
	TXPOMAX1,
	TXPOMIN1,
	TXMAMAX1,
	TXMAMIN1,
	TXPEMAX1,
	TXPEMIN1,
	RETREMC1,
	TIMERC21,
	TIMERC11,
	TIMERC01,
	AETST1,

//�˼��ж�
	IPCGR0,
	IPCSR0,
	IPCCR0,
	IPCGR1,
	IPCSR1,
	IPCCR1,
//DDRAXICFG
	DDR_AXI_CFG0,
	DDR_AXI_CFG1,

//ʱ�ӡ���λ���ü�״̬�Ĵ���
	PLL0_STATUS,
	PLL0_CTL0,
	PLL0_CTL1,
	PLL0_CTL2,
	//PLL0_STATUS1,
	CLK_SYS_CTL,
	
	PLL1_STATUS,
	PLL1_CTL0,
	PLL1_CTL1,
	PLL1_CTL2,

	CLK_PP_CTL,
	CLK_ETHM_CTL,
	CLK_ETHS_CTL,
	CLK_PM_CTL,

	CLK_I2C_CTL,
	CLK_SPI_CTL,

	PLL2_STATUS,
	PLL2_CTL0,
	PLL2_CTL1,
	PLL2_CTL2,

	CLK_DDR_CTL,

	RST_STATUS,
	RST_TYPE_STATUS,
	RST_RM_STATUS,
	RST_CTL,
	RST_INIT_CTL,
	RST_SDS_CTL,
	RST_SDS_STATUS,
	DBG_CTL,
//��ʱ����watchdog���ÿռ�
	TCR0,
	TCSR0,
	TCCR0,
	TPRLO0,
	TPRHI0,
	TCNTLO0,
	TCNTHI0,

	TCR1,
	TCSR1,
	TCCR1,
	TPRLO1,
	TPRHI1,
	TCNTLO1,
	TCNTHI1,

	TCR2,
	TCSR2,
	TCCR2,
	TPRLO2,
	TPRHI2,
	TCNTLO2,
	TCNTHI2,

	TCR3,
	TCSR3,
	TCCR3,
	TPRLO3,
	TPRHI3,
	TCNTLO3,
	TCNTHI3,

	TCR4,
	TCSR4,
	TCCR4,
	TPRLO4,
	TPRHI4,
	TCNTLO4,
	TCNTHI4,

	TCR5,
	TCSR5,
	TCCR5,
	TPRLO5,
	TPRHI5,
	TCNTLO5,
	TCNTHI5,

	TCR6,
	TCSR6,
	TCCR6,
	TPRLO6,
	TPRHI6,
	TCNTLO6,
	TCNTHI6,

	TCR7,
	TCSR7,
	TCCR7,
	TPRLO7,
	TPRHI7,
	TCNTLO7,
	TCNTHI7,

	WDTCR0,
	WDTCSR0,
	WDTCCR0,
	WDTPRLO0,
	WDTPRHI0,
	WDTCNTLO0,
	WDTCNTHI0,

	WDTCR1,
	WDTCSR1,
	WDTCCR1,
	WDTPRLO1,
	WDTPRHI1,
	WDTCNTLO1,
	WDTCNTHI1,





//Rabio Ctl0
	RAB_RST_CTRL0,

//Rabio Ctl1
	RAB_RST_CTRL1,

//UART Ctl
	ULCR,
	UFAR,
//I2C  Ctl


//GPIO Ctl
	GPIOPADR,											//gpio_swporta_dr
	GPIOPCDR,											//gpio_swportc_dr
	GPIOPDCTL,											//gpio_portd_ctl
//SPI  Ctl
	CTRLR0,
	BAUDR,
	DR,
//PCIE  Ctl
	IBADDR0A,											//ib_addr0_pcie0,
	IBADDR0B											//ib_addr0_pcie1
};







//enum for behavior boot from regs writing
enum reg_behavior_type{	
	START_DMA_REQ = 0, CANCEL_DMA_REQ, START_DMA_ACK, CANCEL_DMA_ACK,	START_INSN_REQ, START_INSN_ACK
};






//-----------------------------------------12 bit reg_addr's base addr
#define Global_Start_Addr_reg		0x600						//size = 32
#define Global_End_Addr_reg			0x61f

#define HMCH0_Start_Addr_reg		0x620    					//size = 32 AHB ctr regs 
#define HMCH0_End_Addr_reg			0x63f

#define	XMCH0_Start_Addr_reg		0x640						//size = 64 Core2Core ctr regs 
#define XMCH0_End_Addr_reg			0x67f

#define	XMCH2_Start_Addr_reg		0x6c0						//size = 64 Core2DDR0 ctr regs
#define XMCH2_End_Addr_reg			0x6ff

#define	XMCH3_Start_Addr_reg		0x700						//size = 32 Core2DDR1 ctr regs
#define XMCH3_End_Addr_reg			0x73f

#define SRIO0_Start_Addr_reg         0x0a0c0000                   //SRIO0�ӿڻ���ַ
#define SRIO0_End_Addr_reg           0x0a0c0fff                  //zqw+ 2019.1.3

#define SRIO1_Start_Addr_reg         0x0a0c8000                   //SRIO1�ӿڻ���ַ
#define SRIO1_End_Addr_reg           0x0a0c8fff                  //zqw+ 2019.1.3


//--------------------------------------define all wr_enable regs mask
#define GLB_STATUS_MASK				0x100f3						//vld_data[16,7-4,1-0]
#define XX_START_MASK				0x3							//vld_data[1-0]	
#define XX_STATUS_MASK				0x2771						//vld_data[13,10-8,6-4,0]



//#define XX_CTL_MASK					0x11313						//vld_data[16,12,9-8,4,1-0]
#define H_CTL_MASK					0x3f511313
//#define H_CRL_MASK_JTAG				
#define X_23_CTL_MASK				0x3f510013
#define X_0_CTL_MASK				0x3f510013 


//#define AHB_CTL_MASK				0x1313						//vld_data[12,9-8,4,1-0]
//#define AXI_CTL_MASK				0x13						//vld_data[4,1-0]
#define XX_SRC_START_ADDR_MASK		0xffffffff					//vld_data[31-0]
#define XX_SRC_LEN_X_MASK			0x7ffff						//vld_data[18-0]
#define XX_SRC_ADDR_STEP_MASK		0xffffffff					//vld_data[31-16,15-0]
#define XX_SRC_LEN_Y_MASK			0x7ffff						//vld_data[18-0]

#define XX_SRC_CURR_ADDR_MASK		0xffffffff					//vld_data[31-0]
#define XX_SRC_LEN_REM_X_MASK		0x7ffff						//vld_data[18-0]
#define XX_SRC_LEN_REM_Y_MASK		0x7ffff						//vld_data[18-0]


#define XX_DST_START_ADDRH_MASK		0xf							//vld_data[3-0]
#define XX_DST_START_ADDRL_MASK		0xffffffff					//vld_data[31-0]
#define XX_DST_LEN_X_MASK			0x7ffff						//vld_data[18-0]
#define XX_DST_ADDR_STEP_MASK		0xffffffff					//vld_data[31-16,15-0]
#define XX_DST_LEN_Y_MASK			0x7ffff						//vld_data[18-0]	

#define XX_DST_CURR_ADDR_MASK		0xffffffff					//vld_data[31-0]
#define XX_DST_LEN_REM_X_MASK		0x7ffff						//vld_data[18-0]
#define XX_DST_LEN_REM_Y_MASK		0x7ffff						//vld_data[18-0]


//zqw+ 2019.1.3 SRIO��ؼĴ�������
//дDMA����
#define XX_RAB_WDMA_N_CTRL_MASK		    0xffff0017            // дDMA���ƼĴ���  0x20800
#define XX_RAB_WDMA_N_ADDR_MASK		    0xfffffffe            // дDMA��������ַ�Ĵ��� 0x20804
#define XX_RAB_WDMA_N_STAT_MASK		    0x0000011f            // дDMA״̬�Ĵ��� 0x20808
#define XX_RAB_WDMA_N_ADDR_EXT_MASK		0x0000000f            // дDMA��λ��ַ�Ĵ��� 0x2080C
//��DMA����
#define XX_RAB_RDMA_N_CTRL_MASK		    0xffff0017  		  // ��DMA���ƼĴ���  0x20880
#define XX_RAB_RDMA_N_ADDR_MASK	    	0xfffffffe            // ��DMA��������ַ�Ĵ��� 0x20884
#define XX_RAB_RDMA_N_STAT_MASK	    	0x0000013f            // ��DMA״̬�Ĵ��� 0x20888
#define XX_RAB_RDMA_N_ADDR_EXT_MASK		0x0000000f            // ��DMA��λ��ַ�Ĵ��� 0x2088C
//DMA������
#define XX_RAB_DMA_IADDR_DESC_SEL_MASK		    0x000000f1	   // DMA������ѡ��Ĵ���  0x20900
#define XX_RAB_DMA_IADDR_DESC_CTRL_MASK		    0xffffffff	   // DMA�������Ĵ���-���������ƼĴ���  0x20904
#define XX_RAB_DMA_IADDR_DESC_SRC_ADDR_MASK		0xffffffff     // DMA�������Ĵ���-Դ��ַ�Ĵ���      0x20908
#define XX_RAB_DMA_IADDR_DESC_DEST_ADDR_MASK	0xffffffff     // DMA�������Ĵ���-Ŀ�ĵ�ַ�Ĵ���    0x2090C
#define XX_RAB_DMA_IADDR_DESC_NEXT_ADDR_MASK	0xffffffff     // DMA�������Ĵ���-��һָ���ַ�Ĵ���  0x209010
//zqw+ 2019.2.25 ���豸ID�Ĵ�����ҳ��
#define XX_Base_Device_ID_CSR_MASK              0xffffff00      //���豸ID�Ĵ��������ڴ��Source ID
#define XX_RAB_APB_CSR_MASK                     0xffffffff       //RAB_APB_CSR Register��APB����״̬�Ĵ���  0x20030  ���ڴ��ҳ��

#define  CH0_RD_INTR_ID			0x22
#define  CH0_WR_INTR_ID			0x23



//define max operate number for one insn behavior
#define  INSN_MAX_OP						24





enum RegsType{
	WR_SRC_CURR,
	WR_SRC_X_REM,
	WR_SRC_Y_REM,

	WR_DST_CURR,
	WR_DST_X_REM,
	WR_DST_Y_REM,

	RD_SRC_CURR,
	RD_SRC_X_REM,
	RD_SRC_Y_REM,

	RD_DST_CURR,
	RD_DST_X_REM,
	RD_DST_Y_REM,

	WR_OVER,
	RD_OVER
};


//define for read_req time cnt
//class cycle_cnt_rd{
//public:
//	DMAC_RW_REG_S msg;
//	unsigned int waited;
//};

//define general payload extension class 
struct noci_extension:tlm::tlm_extension<noci_extension>
{
	noci_extension():m_slaveID(0),m_masterID(0){}
	virtual tlm_extension_base * clone() const{
		noci_extension *t= new noci_extension;
		t->m_slaveID = this->m_slaveID;
		t->m_masterID = this->m_masterID;
		//t->cmd = this->cmd;
		t->m_dv = this->m_dv;
		t->m_resp = this->m_resp;
		t->m_data_valid = this->m_data_valid;
		t->core_delay_record = this->core_delay_record;// add by wangqiang for core burst_read debug only
		return t;
	}
	virtual void copy_from(tlm_extension_base const &ext){
		m_slaveID = static_cast<noci_extension const &>(ext).m_slaveID;
		m_masterID = static_cast<noci_extension const &>(ext).m_masterID;
		//cmd = static_cast<noci_extension const &>(ext).cmd;
		m_dv = static_cast<noci_extension const &>(ext).m_dv;
		m_resp = static_cast<noci_extension const &>(ext).m_resp;
		m_data_valid = static_cast<noci_extension const &>(ext).m_data_valid;
		core_delay_record = static_cast<noci_extension const &>(ext).core_delay_record;// add by wangqiang for core burst_read debug only
	}
	unsigned int m_slaveID;
	unsigned int m_masterID;
	//tlm_core_dmac_command cmd;
	unsigned int m_dv;
	respType m_resp;
	bool m_data_valid;
	int	 core_delay_record;// add by wangqiang for core burst_read debug only
};





//------------ register define based on sc_prim_channel,all write behavior call request_update, allow multi_driver
class prim_register: public sc_prim_channel{
public:

	prim_register()
		:name(NO_NAME),offset_addr(0x0),old_value(0),new_value(0){}

	~prim_register(){}

	void write(unsigned int val){
		new_value = val;
		request_update();
	}
	unsigned int read(){
		return old_value;
	}
	unsigned int old_value, new_value;
	reg_name     name;
	unsigned int offset_addr;

private:
	virtual void update(){
		old_value = new_value;
	}
};



//define task list class 
class task_list_entry: public sc_prim_channel{
public:

	task_list_entry()
		:type(NO_TYPE)
		,channel_id(0x0)
		,empty_old(true)			,empty_new(true)
		,is_started_old(false)		,is_started_new(false)
		,is_stalled_old(false)		,is_stalled_new(false)
		,wait_ack_old(false)		,wait_ack_new(false)
		,cancel_flag_old(false)		,cancel_flag_new(false){}

	~task_list_entry(){}




/*
this is be called by class reg_file::mission_add() indirect by DMAC: insn_req; core: dma_req; slave: dma_ack, insn_ack; 
wait_data_back_or_not is true: wait data back; false: do not wait data back, 
*/
	void mission_add(bool wait_data_back_or_not){
		empty_new = false;
		is_started_new = false;
		wait_ack_new = wait_data_back_or_not;
		request_update();
	}




/*
this is be called by class reg_file::mission_end() indirect by master,
when master get resp ok/stop from slave or get the last trans_end accept 
*/
	void mission_end(){
		empty_new = true;
		is_started_new = false;
		is_stalled_new = false;
		wait_ack_new  = false;
		cancel_flag_new = false;
		request_update();
	}




/*
this is be called by class reg_file::mission_start(), indirect by master, when master judge to start a mission
*/
	void mission_start(){
		is_started_new = true;
		request_update();
	}




/*
this is be called by class reg_file::mission_stall(), indirect by master, when master judge to stall a dma mission
*/
	void mission_stall(){
		is_stalled_new = true;
		request_update();
	}




/*
this is be called by class reg_file::mission_restore(), indirect by master, when master judge to restore a dma mission
*/
	void mission_restore(){
		is_stalled_new = false;
		request_update();
	}




/*
this is be called by reg_file::mission_cancel(), when core set cancel bit to 1
*/
	void mission_cancel(){
		cancel_flag_new = true;
		request_update();
	}




/*
this is be called by reg_file::mission_check(), indirect by master, when master clock_tick()
*/
	check_mission_return mission_check(){//return 0: no mission exist;return 1: a new mission(not start) exist; return 2: a stalled mission exist; 

		if(type ==  DMA_REQ || type == DMA_ACK){
			if(is_stalled_old && !cancel_flag_old){
				return STALLED_MISSION;
			}

			if(cancel_flag_old){
				return CANCEL_MISSION;
			}
		}

		if((!empty_old) && (!is_started_old)){
			return NEW_MISSION;
		}

		if((!empty_old) && (is_started_old)){
			return  BUSY_MISSION;
		}

		return NO_MISSION;
	}




/*
this is be called by reg_file::wait_data_back_check(), indirect by master, when master get the resp_ok from slave side
*/
	bool wait_data_back_check(){
		return wait_ack_old;
	}
	//---------member define
	task_list_type 	     type;
	unsigned int		 channel_id;
	bool 				 empty_old, empty_new; //true: empty, no this kind task need to do; false: full, there is a this kind task need to do
	bool				 is_started_old, is_started_new;// mission is started or is not
	bool 				 is_stalled_old, is_stalled_new; //for dma task, true is be stalled by insn task, false is not; for insn task,true is stall other, false is not
	bool 				 wait_ack_old, wait_ack_new; //true: this task need data back,  false: don't need data back;
	bool				 cancel_flag_old, cancel_flag_new;

private:
	virtual void update(){
		empty_old		 = empty_new;
		is_started_old	 = is_started_new;
		is_stalled_old	 = is_stalled_new;
		wait_ack_old	 = wait_ack_new;
		cancel_flag_old  = cancel_flag_new;
	}
};



/*
//------------------insn info register, 
class insn_register: public sc_prim_channel{
public:

	insn_register()	{}

	~insn_register(){}

	void write(MSG_INSN_RW_MEM & val){
		new_value = val;
		for(int i = 0; i != val.u32ElemNum; i++){
			new_value.arrInsnsRWInfo[i] = val.arrInsnsRWInfo[i];
		}
		request_update();
	}

	MSG_INSN_RW_MEM read(){
		return old_value;
	}

	void clear(){
		old_value.bolAtom = false;			new_value.bolAtom = false;
		old_value.u32ID = 0x0;				new_value.u32ID = 0x0;
		old_value.u32ElemNum = 0x0;			new_value.u32ElemNum = 0x0;
		for(int i = 0; i != INSN_MAX_OP; i++){
			old_value.arrInsnsRWInfo[i].bolIsRead = true;old_value.arrInsnsRWInfo[i].u32Addr = 0x0;old_value.arrInsnsRWInfo[i].u32Bus = 0x0;old_value.arrInsnsRWInfo[i].u32Value = 0x0;
			new_value.arrInsnsRWInfo[i].bolIsRead = true;new_value.arrInsnsRWInfo[i].u32Addr = 0x0;new_value.arrInsnsRWInfo[i].u32Bus = 0x0;new_value.arrInsnsRWInfo[i].u32Value = 0x0;
		}
	}
	MSG_INSN_RW_MEM old_value, new_value;



private:
	virtual void update(){
		old_value = new_value;

		for(int i = 0; i != INSN_MAX_OP; i++){
			old_value.arrInsnsRWInfo[i] = new_value.arrInsnsRWInfo[i];
		}
	}
};

*/


/*
struct latest_insn_record 
{
	unsigned int mask;  //mask for r0r1 record; 0->no read mission; 1->r0 only; 2->r1 only; 3->both read valid
	MSG_INSN_RW_MEM insn_req_info;


	void reset(){
		mask = 0x0;
		insn_req_info.u32ID = 0;
		insn_req_info.bolAtom = false;
		insn_req_info.u32ElemNum = 0x0;
		for(int i =0; i != 4 ; i++){
			insn_req_info.arrBusInfo[i].bolAtom = false;
			insn_req_info.arrBusInfo[i].bolIsDM8 = false;
			insn_req_info.arrBusInfo[i].bolSingleWord = false;
			insn_req_info.arrBusInfo[i].u32BankConflictNum = 0x0;
			insn_req_info.arrBusInfo[i].u32BankConflictState = 0x0;
			insn_req_info.arrBusInfo[i].u32SlotPlus1 = 0x0;
		}
		for(int i =0; i !=24; i++){
			insn_req_info.arrInsnsRWInfo[i].bolIsRead = false;
			insn_req_info.arrInsnsRWInfo[i].u32Addr = 0x0;
			insn_req_info.arrInsnsRWInfo[i].u32AddrIdx = 0x0;
			insn_req_info.arrInsnsRWInfo[i].u32Bus = 0x0;
			insn_req_info.arrInsnsRWInfo[i].u32Value = 0x0;
		}

	}
};
*/



//----------------------------------------for distinguish different DMA_REQ mission
#define  INSN_MISSION			0x0
#define  DMA_READ_MISSION		0x1
#define	 DMA_WRITE_MISSION		0x2
#define  DMA_TRANS_MISSION		0x3


//define channel_id
#define  CH0_ID			0x0
#define  CH1_ID			0x1
#define  CH2_ID			0x2
#define  CH3_ID			0x3
#define  CH4_ID			0x4
#define  CH5_ID			0x5
#define  CH6_ID			0x6
#define  CH7_ID			0x7
#define  CH8_ID			0x8
#define  CH9_ID			0x9
#define  CHA_ID			0xa




//define different info dv value
#define		ROUTE_INFO_DV	0x1						//route_info
#define		INSN_CFG_DV		0x2						//insn_config_info
#define		DMA_CFG_1D_DV	0x3						//dma_config_1d
#define		DMA_CFG_2D_DV	0x4						//dma_config_2d





//define reg_info len and its start position in reg
#define		DMA_ACK_TASK_ENTRY_VALID_CH_1_LEN					0x1
#define		DMA_ACK_TASK_ENTRY_VALID_CH_1_REG_START				0x11
#define		DMA_ACK_TASK_ENTRY_VALID_CH_0_LEN					0x1
#define		DMA_ACK_TASK_ENTRY_VALID_CH_0_REG_START				0x10

#define		DMA_REQ_TASK_ENTRY_VALID_CH_AHB_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_AHB_REG_START			0xa
#define		DMA_REQ_TASK_ENTRY_VALID_CH_8_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_8_REG_START				0x8	
#define		DMA_REQ_TASK_ENTRY_VALID_CH_7_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_7_REG_START				0x7	
#define		DMA_REQ_TASK_ENTRY_VALID_CH_6_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_6_REG_START				0x6
#define		DMA_REQ_TASK_ENTRY_VALID_CH_5_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_5_REG_START				0x5
#define		DMA_REQ_TASK_ENTRY_VALID_CH_4_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_4_REG_START				0x4	
#define		DMA_REQ_TASK_ENTRY_VALID_CH_3_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_3_REG_START				0x3	
#define		DMA_REQ_TASK_ENTRY_VALID_CH_2_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_2_REG_START				0x2	
#define		DMA_REQ_TASK_ENTRY_VALID_CH_1_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_1_REG_START				0x1	
#define		DMA_REQ_TASK_ENTRY_VALID_CH_0_LEN					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_CH_0_REG_START				0x0	

//-----------------------------REQ_REGS
//DCHRi_START offset = 0x0
#define		DMA_REQ_CANCEL_FLAG_LEN								0x1
#define		DMA_REQ_CANCEL_FLAG_REG_START						0x1
#define		DMA_REQ_START_FLAG_LEN								0x1
#define		DMA_REQ_START_FLAG_REG_START						0x0

//DCHRi_STATUS offset = 0x1
#define		DMA_REQ_STALLED_FLAG_LEN							0x1
#define		DMA_REQ_STALLED_FLAG_REG_START						0xd
#define		DMA_REQ_NEED_DATA_BACK_FLAG_LEN						0x1
#define		DMA_REQ_NEED_DATA_BACK_FLAG_REG_START				0xb
#define		DMA_REQ_ERR_CODE_LEN								0x2
#define		DMA_REQ_ERR_CODE_REG_START							0x8
#define		DMA_REQ_END_REASON_LEN								0x2
#define		DMA_REQ_END_REASON_REG_START						0x4
#define		DMA_REQ_HAS_END_LEN									0x1
#define		DMA_REQ_HAS_END_REG_START							0x2
#define		DMA_REQ_IS_TRANSFERRING_LEN							0x1
#define		DMA_REQ_IS_TRANSFERRING_REG_START					0x1
#define		DMA_REQ_TASK_ENTRY_VALID_LEN						0x1
#define		DMA_REQ_TASK_ENTRY_VALID_REG_START					0x0


//DCHRi_CTL offset = 0x2
#define		DMA_REQ_SRC_IP_LEN									0x6
#define		DMA_REQ_SRC_IP_REG_START							0x10
#define		DMA_REQ_DST_IP_LEN									0x6
#define		DMA_REQ_DST_IP_REG_START							0x8
#define		DMA_REQ_INTER_MASK_FLAG_LEN							0x1
#define		DMA_REQ_INTER_MASK_FLAG_REG_START					0x2
#define		DMA_REQ_TRANS_MODE_LEN								0x2
#define     DMA_REQ_TRANS_MODE_REG_START						0x0


//DCHRi_SRC_START_ADDR offset = 0x3
#define		DMA_REQ_SRC_START_ADDR_LEN							0x20
#define		DMA_REQ_SRC_START_ADDR_REG_START					0x0

//DCHRi_SRC_LEN_X		offset = 0x4
#define		DMA_REQ_SRC_D_SEL_LEN								0x1
#define		DMA_REQ_SRC_D_SEL_REG_START							0x18
#define		DMA_REQ_SRC_LEN_X_LEN								0x12
#define		DMA_REQ_SRC_LEN_X_REG_START							0x0

//DCHRi_SRC_ADDR_STEP	offset = 0x5
#define		DMA_REQ_SRC_Y_STEP_LEN								0x10
#define		DMA_REQ_SRC_Y_STEP_REG_START						0x10
#define		DMA_REQ_SRC_X_STEP_LEN								0x10
#define		DMA_REQ_SRC_X_STEP_REG_START						0x0


//DCHRi_SRC_LEN_Y		offset = 0x6
#define		DMA_REQ_SRC_LEN_Y_LEN								0x12
#define		DMA_REQ_SRC_LEN_Y_REG_START							0x0


//DCHRi_SRC_CURR_ADDR	offset = 0x7
#define		DMA_REQ_SRC_CURR_ADDR_LEN							0x20
#define		DMA_REQ_SRC_CURR_ADDR_REG_START						0x0

//DCHRi_SRC_LEN_REM_X	offset = 0x8
#define		DMA_REQ_SRC_REM_LEN_X_LEN							0x12
#define		DMA_REQ_SRC_REM_LEN_X_REG_START						0x0


//DCHRi_SRC_LEN_REM_Y	offset = 0x9
#define		DMA_REQ_SRC_REM_LEN_Y_LEN							0x12
#define		DMA_REQ_SRC_REM_LEN_Y_REG_START						0x0

//DCHRi_DST_START_ADDR offset = 0xb
#define		DMA_REQ_DST_START_ADDR_LEN							0x20
#define		DMA_REQ_DST_START_ADDR_REG_START					0x0

//DCHRi_DST_LEN_X		offset = 0xc
#define		DMA_REQ_DST_D_SEL_LEN								0x1
#define		DMA_REQ_DST_D_SEL_REG_START							0x18
#define		DMA_REQ_DST_LEN_X_LEN								0x12
#define		DMA_REQ_DST_LEN_X_REG_START							0x0

//DCHRi_DST_ADDR_STEP	offset = 0xd
#define		DMA_REQ_DST_Y_STEP_LEN								0x10
#define		DMA_REQ_DST_Y_STEP_REG_START						0x10
#define		DMA_REQ_DST_X_STEP_LEN								0x10
#define		DMA_REQ_DST_X_STEP_REG_START						0x0


//DCHRi_DST_LEN_Y		offset = 0xe
#define		DMA_REQ_DST_LEN_Y_LEN								0x12
#define		DMA_REQ_DST_LEN_Y_REG_START							0x0

//-------------------------------ACK_REGS
//DCHAi_START offset = 0x10
#define		DMA_ACK_CANCEL_FLAG_LEN								0x1
#define		DMA_ACK_CANCEL_FLAG_REG_START						0x1
#define		DMA_ACK_START_FLAG_LEN								0x1
#define		DMA_ACK_START_FLAG_REG_START						0x0

//DCHAi_STATUS offset = 0x11
#define		DMA_ACK_STALLED_FLAG_LEN							0x1
#define		DMA_ACK_STALLED_FLAG_REG_START						0xd
#define		DMA_ACK_NEED_DATA_BACK_FLAG_LEN						0x1
#define		DMA_ACK_NEED_DATA_BACK_FLAG_REG_START				0xb
#define		DMA_ACK_ERR_CODE_LEN								0x2
#define		DMA_ACK_ERR_CODE_REG_START							0x8
#define		DMA_ACK_END_REASON_LEN								0x2
#define		DMA_ACK_END_REASON_REG_START						0x4
#define		DMA_ACK_HAS_END_LEN									0x1
#define		DMA_ACK_HAS_END_REG_START							0x2
#define		DMA_ACK_IS_TRANSFERRING_LEN							0x1
#define		DMA_ACK_IS_TRANSFERRING_REG_START					0x1
#define		DMA_ACK_TASK_ENTRY_VALID_LEN						0x1
#define		DMA_ACK_TASK_ENTRY_VALID_REG_START					0x0

//DCHAi_CTL offset = 0x12
#define		DMA_ACK_SRC_IP_LEN									0x6
#define		DMA_ACK_SRC_IP_REG_START							0x10
#define		DMA_ACK_DST_IP_LEN									0x6
#define		DMA_ACK_DST_IP_REG_START							0x8
#define		DMA_ACK_INTER_MASK_FLAG_LEN							0x1
#define		DMA_ACK_INTER_MASK_FLAG_REG_START					0x2
#define		DMA_ACK_TRANS_MODE_LEN								0x2
#define		DMA_ACK_TRANS_MODE_REG_START						0x0

//DCHAi_DST_START_ADDR offset = 0x13
#define		DMA_ACK_DST_START_ADDR_LEN							0x20
#define		DMA_ACK_DST_START_ADDR_REG_START					0x0

//DCHAi_DST_LEN_X		offset = 0x14
#define		DMA_ACK_DST_D_SEL_LEN								0x1
#define		DMA_ACK_DST_D_SEL_REG_START							0x18
#define		DMA_ACK_DST_LEN_X_LEN								0x12
#define		DMA_ACK_DST_LEN_X_REG_START							0x0

//DCHAi_DST_ADDR_STEP	offset = 0x15
#define		DMA_ACK_DST_Y_STEP_LEN								0x10
#define		DMA_ACK_DST_Y_STEP_REG_START						0x10
#define		DMA_ACK_DST_X_STEP_LEN								0x10
#define		DMA_ACK_DST_X_STEP_REG_START						0x0


//DCHAi_DST_LEN_Y		offset = 0x16
#define		DMA_ACK_DST_LEN_Y_LEN								0x12
#define		DMA_ACK_DST_LEN_Y_REG_START							0x0

//DCHAi_DST_CURR_ADDR	offset = 0x17
#define		DMA_ACK_DST_CURR_ADDR_LEN							0x20
#define		DMA_ACK_DST_CURR_ADDR_REG_START						0x0

//DCHAi_DST_LEN_REM_X	offset = 0x18
#define		DMA_ACK_DST_REM_LEN_X_LEN							0x12
#define		DMA_ACK_DST_REM_LEN_X_REG_START						0x0

//DCHAi_DST_LEN_REM_Y	offset = 0x19
#define		DMA_ACK_DST_REM_LEN_Y_LEN							0x12
#define		DMA_ACK_DST_REM_LEN_Y_REG_START						0x0

//DCHATi_DST_START_ADDR offset = 0x1b
#define		DMA_ACK_DST_START_ADDR_LEN							0x20
#define		DMA_ACK_DST_START_ADDR_REG_START					0x0

//DCHATi_DST_LEN_X		offset = 0x1c
#define		DMA_ACK_DST_D_SEL_LEN								0x1
#define		DMA_ACK_DST_D_SEL_REG_START							0x18
#define		DMA_ACK_DST_LEN_X_LEN								0x12
#define		DMA_ACK_DST_LEN_X_REG_START							0x0

//DCHATi_DST_ADDR_STEP	offset = 0x1d
#define		DMA_ACK_DST_Y_STEP_LEN								0x10
#define		DMA_ACK_DST_Y_STEP_REG_START						0x10
#define		DMA_ACK_DST_X_STEP_LEN								0x10
#define		DMA_ACK_DST_X_STEP_REG_START						0x0


//DCHATi_DST_LEN_Y		offset = 0x1e
#define		DMA_REQ_DST_LEN_Y_LEN								0x12
#define		DMA_REQ_DST_LEN_Y_REG_START							0x0



#define LATEST_NOT_CON_READ_DELAY 1 //delay cycles for latest insn_req not contain read mission

#define RD_FIFO_DEPTH 8

#define FBP_FIFO_DEPTH 2

#define CORE_DELAY_BASE 5            //delay of core preparing data for dmac read data commond

#define CHANNEL_NUM	4					//define whole channel_num

#define SRIO_NUM 2                      // define SRIO numben  zqw+2019.1.3

#define TASK_TYPE_NUM 4					//define whole dmac task;

#define RESP_DELAY	5


#define  CH0_DATA_WIDTH_WORDS				0x8
#define  CHZ_DATA_WIDTH_WORDS				0x2

//zqw+ 2019.1.21  SRIO���ݿ���
#define  SRIO_DATA_WIDTH_WORDS				0x40


#define  INSN_MAX_OP						24

#define  READ_BUS_0_INDEX						0x0
#define  READ_BUS_1_INDEX						0x1
#define  WRITE_BUS_0_INDEX						0x2
#define  WRITE_BUS_1_INDEX						0x3

//----------------------------define CH0 different phase last cycles
#define		CH0_DMA_REQ_CYCLES				0x1
#define		CH0_DMA_CFG_CYCLES				0x1



//----------------------------delay define
#define    DMA_START2FIRST_BURST_READ_DELAY						0x4
#define	   LAST1D_END2NEXT_1D_FIRST_BURST_READ_DELAY			0x3


#define    RSTN2FIRST_DMA_REQ_ENTRY_UP							0x3
#define    LAST_BURST_READ_RETURN2DMA_REQ_ENTRY_UP				0x5
#define	   START_REG_WR2DMA_REQ_ENTRY_DOWN						0x3






class RegType
{
public:
	RegType ():name(NO_NAME),offset_addr(0x0),m_out(0),m_in(0)
	{		
	}			
	~RegType(){}

	void write(unsigned int val){
		m_in = val;
		//request_update();
	}
	unsigned int read(){
		return m_out;
	}

	void shift()
	{
		m_out = m_in;
	}
	
	void SetVal(unsigned int val){
		m_in = val;
		m_out = val;	
	}

	reg_name     name;
	unsigned int offset_addr;
	unsigned int m_out, m_in;
	
};







//========================================================define SystemConfigReg BaseAddr & MaxOffset
#define   GlobalRegBase						0x09028000
#define	  GlobalRegMaxOffset				0xff

#define   MCRCRRegBase						0x09028100
#define	  MCRCRRegMaxOffset					0xff

#define   PMARegBase						0x09028200
#define	  PMARegMaxOffset					0xff

#define	  PCIERegBase						0x09028300
#define   PCIERegMaxOffset					0xff

#define	  SRIORegBase						0x09028400
#define   SRIORegMaxOffset					0xff

#define   IPCRegBase						0x09028500
#define	  IPCRegMaxOffset					0xff

#define   DDRCFGBase						0x09028600
#define   DDRCFGMaxOffset 					0xff

#define	  CLK_RST_RegBase					0x09030000
#define   CLK_RST_MaxOffset					0x7f


#define	  TCR_WDT_RegBase					0x0a100000
#define   TCR_WDT_MaxOffset					0x3ff

//add by wangqiang on 2016.5.11
#define   RabioCtl0_RegBase					0x0a0c0000
#define   RabioCtl0_MaxOffset				0x7ff

#define   RabioCtl1_RegBase					0x0a0c8000
#define   RabioCtl1_MaxOffset				0x7ff

#define	  UartCtl_RegBase					0x0a108000
#define   UartCtl_MaxOffset					0x3ff

#define   I2CCtl_RegBase					0x0a110000
#define   I2CCtl_MaxOffset					0x3ff

#define	  GPIOCtl_RegBase					0x0a118000
#define   GPIOCtl_MaxOffset					0x3ff

#define	  SPICtl_RegBase					0x0a120000
#define   SPICtl_MaxOffset					0x3ff

#define   PCIECtl_RegBase					0x0a200000
#define	  PCIECtl_MaxOffset					0x1fffff

//#define	  DDRDataStart						0xc1000000
#define	  DDRDataStart						0x80000000  //zqw+ 2019.1.2
#define   DDRData_MaxOffset					0x3fffff


// Ӳ���ź����Ĵ���
#define	HSRegBase		0x09010000
#define	HSRegNum		0x10
#define	HSRegMask		0xff
//==========================================================define SystemConfigReg Mask

#define CIDR_MASK										0x7f800670
#define GCSR_MASK										0x101
#define BOOTCOMPLETE_MASK								0x3
#define CISR_MASK										0xff
#define C0_BOOT_ADDR_MASK								0xffffffff
#define C1_BOOT_ADDR_MASK								0xffffffff
#define BOOT_DEVICE_MASK								0x7
#define BOOT_DEVICE_CFG_MASK							0x7f
#define PCIE_MODE_MASK									0x1
#define CHIP_MODE_MASK									0x3

#define MCRCR_MASK										0x1

#define PMACR_MASK										0x7f
#define PGSR_MASK										0x3
#define PLACR_MASK										0x3
#define PLICR_MASK										0xfff87f03
#define PLIPSR_MASK										0xf
#define PLIPMR_MASK										0x10101
#define PLISR_MASK										0xf
#define PCER_MASK										0x1
#define PPSCAR_MASK										0x1
#define PCEFR_MASK										0x1
#define PMSGR0_MASK										0xffffffff
#define PMSGR1_MASK										0xffffffff
#define PMSGR2_MASK										0xffffffff
#define PMSGR3_MASK										0xffffffff
#define PMSGR4_MASK										0xffff
#define PMSGR5_MASK										0x7
#define PMUER_MASK										0x1
#define PVFER_MASK										0x8001
#define EP_IRQ_SET_MASK									0x1
#define ER_IRQ_CLR_MASK									0x1
#define ER_IRQ_STATUS_MASK								0x1
#define MSI_DATA_MASK									0xffffffff
#define MSI0_IRQ_STATUS_MASK							0xf
#define MSI0_IRQ_ENABLE_MASK							0xf
#define MSI0_IRQ_CLR_MASK								0xf
#define MSI1_IRQ_STATUS_MASK							0xf
#define MSI1_IRQ_ENABLE_MASK							0xf
#define MSI1_IRQ_CLR_MASK								0xf
#define MSI2_IRQ_STATUS_MASK							0xf
#define MSI2_IRQ_ENABLE_MASK							0xf
#define MSI2_IRQ_CLR_MASK								0xf
#define MSI3_IRQ_STATUS_MASK							0xf
#define MSI3_IRQ_ENABLE_MASK							0xf
#define MSI3_IRQ_CLR_MASK								0xf
#define MSI4_IRQ_STATUS_MASK							0xf
#define MSI4_IRQ_ENABLE_MASK							0xf
#define MSI4_IRQ_CLR_MASK								0xf
#define MSI5_IRQ_STATUS_MASK							0xf
#define MSI5_IRQ_ENABLE_MASK							0xf
#define MSI5_IRQ_CLR_MASK								0xf
#define MSI6_IRQ_STATUS_MASK							0xf
#define MSI6_IRQ_ENABLE_MASK							0xf
#define MSI6_IRQ_CLR_MASK								0xf
#define MSI7_IRQ_STATUS_MASK							0xf
#define MSI7_IRQ_ENABLE_MASK							0xf
#define MSI7_IRQ_CLR_MASK								0xf
#define L1_PM_SUBSTATE_MASK								0xff
#define HRTR_MASK										0x1




#define SEITR_MASK										0xffff								
#define SEISR_MASK										0xffff
#define SEICR_MASK										0xffff
#define SLCR_MASK										0x3
#define SDIDCAR_MASK									0xffffffff
#define SDINFCAR_MASK									0xffffffff
#define SAIDCAR_MASK									0xffffffff
#define SGCR_MASK										0xffff000f
#define SPNR_MASK										0xf
#define SPVR_MASK										0x7f
#define SDPSR_MASK										0x1
#define SSPLSR_MASK										0x1	
#define SPSR_MASK										0xf
#define SPCR_MASK										0x7fffff
#define SSLSSR_MASK										0xf

#define SLKSPD_MASK										0x1ffff
#define	TXPRSTINSI_MASK									0xffffffff
#define	TXPOMAX_MASK									0x3ffff
#define	TXPOMIN_MASK									0xfffffff
#define	TXMAMAX_MASK									0xfffffff
#define	TXMAMIN_MASK									0xfffffff
#define	TXPEMAX_MASK									0xfffffff
#define	TXPEMIN_MASK									0xfffffff
#define	RETREMC_MASK									0xff
#define	TIMERC2_MASK									0x1fffffff
#define	TIMERC1_MASK									0x1ffffff
#define	TIMERC0_MASK									0xffff
#define	AETST_MASK										0xfffff
			

#define DDR_AXI_CFG_MASK								0xffffffff   //�ĵ���û���ҵ�����ʱ��Ϊȫ��Ч





#define IPCGR_MASK										0xfffffff0
#define IPCSR_MASK										0xfffffff0
#define IPCCR_MASK										0xfffffff0


#define PLLi_STATUS_MASK								0x70001
#define PLLi_CTL0_MASK									0x1007f
#define PLLi_CTL1_MASK									0x3f0fff
#define PLLi_CTL2_MASK									0x77ffffff
//#define PLLi_STATUS1_MASK								0x1010fff
#define CLK_SYS_CTL_MASK								0x710301
#define CLK_PP_CTL_MASK									0xf0101
#define CLK_ETHM_CTL_MASK								0x3f0101
#define CLK_ETHS_CTL_MASK								0x3370101
#define CLK_PM_CTL_MASK									0x3f0101

#define CLK_I2C_CTL_MASK								0xf0101
#define	CLK_SPI_CTL_MASK								0xf0101

#define CLK_DDR_CTL_MASK								0x303

#define RST_STATUS_MASK									0x80000003
#define RST_TYPE_STATUS_MASK							0x1117
#define RST_RM_STATUS_MASK								0x3fffff
#define RST_CTL_MASK									0x10001
#define RST_INIT_CTL_MASK								0x1
#define RST_SDS_CTL_MASK								0x3f0000
#define RST_SDS_STATUS_MASK								0x3f3f3f3f
#define DBG_CTL_MASK									0x3

#define TCRi_MASK										0xffffffff
#define TCSRi_MASK										0xffffffff
#define TCCRi_MASK										0xffffffff
#define TPRLOi_MASK										0xffffffff
#define TPRHIi_MASK										0xffffffff
#define TCNTLOi_MASK									0xffffffff
#define TCNTHIi_MASK									0xffffffff

#define WDTCRi_MASK										0xffffffff
#define WDTCSRi_MASK									0xffffffff
#define WDTCCRi_MASK									0xffffffff
#define WDTPRLOi_MASK									0xffffffff
#define WDTPRHIi_MASK									0xffffffff
#define WDTCNTLOi_MASK									0xffffffff
#define WDTCNTHIi_MASK									0xffffffff

//add by wangqiang 2016.5.11
//Rabio Ctl0
#define RAB_RST_CTRL0_MASK								0XFFFFFFFF

//Rabio Ctl1
#define RAB_RST_CTRL1_MASK								0XFFFFFFFF

//UART Ctl
#define LCR_MASK										0XDF
#define FAR_MASK										0X1
//I2C  Ctl


//GPIO Ctl
#define GPIOPADR_MASK									0XFFFF							//gpio_swporta_dr
#define GPIOPCDR_MASK									0XFFFF		//gpio_swportc_dr
#define GPIOPDCTL_MASK									0x1	//gpio_portd_ctl
//SPI  Ctl
#define CTRLR0_MASK										0XFFFF
#define BAUDR_MASK										0XFFFF
#define DR_MASK											0XFFFF
//PCIE  Ctl
#define IBADDR0A_MASK									0xFFFFFF3F				//ib_addr0_pcie0,
#define IBADDR0B_MASK									0xFFFFFF3F		//ib_addr0_pcie1






#define SYSCFG_GLOBAL_BASE								0x9028000
#define SYSCFG_GLOBAL_MAX								SYSCFG_GLOBAL_BASE + 0xff
#define SYSCFG_DGB_BASE									0x9028100
#define SYSCFG_DGB_MAX									SYSCFG_DGB_BASE + 0xff
#define SYSCFG_PMA_BASE									0x9028200
#define SYSCFG_PMA_MAX									SYSCFG_PMA_BASE + 0xff
#define SYSCFG_PCIE_BASE								0x9028300
#define SYSCFG_PCIE_MAX									SYSCFG_PCIE_BASE + 0xff	
#define SYSCFG_SRIO_BASE								0x9028400
#define SYSCFG_SRIO_MAX									SYSCFG_SRIO_BASE + 0xff
#define SYSCFG_INT_BASE									0x9028500
#define SYSCFG_INT_MAX									SYSCFG_INT_BASE + 0xff
#define CLK_RST_BASE									0x9030000
#define CLK_RST_MAX										CLK_RST_BASE + 0x7f
#define TIMER_WDG_BASE									0xa100000
#define TIMER_WDG_MAX									TIMER_WDG_BASE + 0x3ff

// definition of source event
#define IPC_SRC_EVT 36
#endif
