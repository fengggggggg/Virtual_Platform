/*
 * icache_module_new.h
 *
 *  Created on: Jan 3, 2014
 *      Author: liugu
 */

#ifndef ICACHE_MODULE_NEW_H_
#define ICACHE_MODULE_NEW_H_


#include "global.h"
#include "icache_ram_new.h"
//#include "L2_mmc_new.h"
#include "register32.h"

#include <systemc.h>
#include <tlm.h>
//#define USING_FOPEN_S				//Turn on when using fopen_s to open a file

#ifdef LOG_OUTPUT
#define GEN_STIMULATION				//Turn on when generate input file for verification
#define ICACHE_TRACE_ON
#endif
#define SC_ICACHE				//Turn on when using SystemC features, false will build a pure C++ class

#define SOFTWARE_SIMULATOR

#define BASIC_FLUSH_DELAY 5
#ifndef SOFTWARE_SIMULATOR
#define USING_L2_INTERNAL_MEM		//Initialize with L2 internal memory loaded from file "a.out.img"
#endif
#define USING_L2_ACK_SIGNALS		//undef this when modular test

#ifdef SC_ICACHE
#include "protocol.h"
#endif

//#define L2_SC_INOUT				//This macro is defined for L2 related ports
//#define INNER_SRAM_SC_INOUT			//This macro is turn on in branch-dmac, off in branch-compiler
//#define SHARE_SRAM_SC_INOUT
#define TLM_SHARED_SRAM				//This macro is turned on in branch-compiler, with TLM-based software-modeled shared sram

#define TEST_LOG_OUT				//This macro is turned on for output log file in testing all function points
namespace BWDSP104X{
	class icache_module_new
#ifdef SC_ICACHE
			: public sc_module, public tlm::tlm_bw_transport_if<PROTOCOL_TYPE>
#endif
	{
	public:
#ifdef SC_ICACHE
		sc_in_clk clk;
		sc_module_name module_name;
		tlm::tlm_initiator_socket<512,PROTOCOL_TYPE> init_socket_to_sram;

		//registers for systemC socket bufferring
		register_basic<ictype_bool> L2_ack_reg;
		register32 L2_ack_pc_reg;
		register_basic<insnLine512> L2_ack_insn_reg;
		
		//pointer to last pending generic payload
		tlm::tlm_generic_payload * m_pCacheLineRequest;
		//can send a new Cache Line request
		bool m_send_new_request;
		bool m_last_trans_finished;

#ifdef L2_SC_INOUT
		sc_out<bool>		sc_l2_irq_w;
		sc_out<sc_bv<32> >	sc_l2_irq_pc;
		sc_in<bool>			sc_l2_ack;
		sc_in<sc_bv<32> >	sc_l2_ack_pc;
		sc_in<sc_bv<16*32> >	sc_l2_inst;
		sc_out<bool>			sc_l2_irq_dma;
#endif


		/*Inner SRAM*/
		unsigned int	*inner_sram;
		#define InnerSRAMStart			0xE20000
		#define InnerSRAMEnd			0xE2FFFF
		unsigned int	inner_sram_size;		//SRAM size in word, default is 0x10000(64K word)
		unsigned int	inner_sram_start_addr;	//default is InnerSRAMStart
		unsigned int	inner_sram_end_addr;	//default is InnerSRAMEnd
		
		register_basic<ictype_bool> 	inner_sram_rddata_bak_en;
		register_basic<insnLine512>		inner_sram_rddata_bak_data;

		void reset_inner_sram();				//Allocate space for inner SRAM

		/*Inner SRAM related signals*/
		bool									isFE0InnerSRAM_w;
		register_basic<ictype_bool>				isFE2InnerSRAM;
		insnLine512								inner_sram_inst;

		bool					inner_sram_mod;
		bool					inner_sram_cen;
		bool					inner_sram_wrn;
		//bool					inner_sram_wrmaskn;
		unsigned int			inner_sram_addr;		//12 bits valid
		insnLine512				inner_sram_wrdata;
		insnLine512				inner_sram_rddata;

		register_basic<insnLine512>		inner_sram_rddata_buf;

		register32				inner_sram_jtg_addr_1d;		//4 bits valid
		register_basic<insnLine512>		inner_sram_rddata_1d;

		void access_inner_sram();				//Read and write inner SRAM

		bool read_inner_sram(unsigned int addr, unsigned int *value);
		bool write_inner_sram(unsigned int addr,unsigned int value);

		bool				inner_sram_jtg_en;			//jtg ports in
		bool				inner_sram_jtg_wr;			//jtg ports in
		unsigned int		inner_sram_jtg_addr;		//jtg ports in,16 bits
		unsigned int		inner_sram_jtg_wdat;		//jtg ports in,32bits
		unsigned int		inner_sram_jtg_rdat;		//jtg ports out,32bits

#ifdef INNER_SRAM_SC_INOUT
		sc_in<bool>				sc_inner_sram_jtg_en;
		sc_in<bool>				sc_inner_sram_jtg_wr;
		sc_in<sc_bv<16> >		sc_inner_sram_jtg_addr;
		sc_in<sc_bv<32> >		sc_inner_sram_jtg_wdat;
		sc_out<sc_bv<32> >		sc_inner_sram_jtg_rdat;

		void proc_inner_sram_jtg_signals(){
			inner_sram_jtg_en = sc_inner_sram_jtg_en.read();
			inner_sram_jtg_wr = sc_inner_sram_jtg_wr.read();
			inner_sram_jtg_addr = sc_inner_sram_jtg_addr.read().to_ulong();
			inner_sram_jtg_wdat = sc_inner_sram_jtg_wdat.read().to_ulong();
		}

		void proc_inner_sram_jtg_rdat(){
			sc_inner_sram_jtg_rdat.write(inner_sram_rddata.insnSlot[sc_inner_sram_jtg_addr.read().to_ulong() % 16]);
		}
#endif

#ifdef SHARE_SRAM_SC_INOUT
		sc_out<bool>			sc_share_sram_irq_plus;
		sc_in<sc_bv<32> >		sc_share_sram_ack_pc;
		sc_in<sc_bv<512> >		sc_share_sram_ack_inst;
#endif

		/*Share SRAM*/
		#define ShareSRAMStart			0x0			/*0x60000000*/
		#define ShareSRAMEnd			0x17FFF	  /*0x60017FFF*/	

		bool									isFE0ShareSRAM_w;
		register_basic<ictype_bool>				isFE2ShareSRAM;
		register32								share_sram_irq_plus;
		unsigned int							share_sram_ack_pc;		//input, 32bits
		insnLine512								share_sram_ack_inst;	//input, 512bits

#ifdef TLM_SHARED_SRAM
		tlm::tlm_initiator_socket<512,PROTOCOL_TYPE> init_socket_to_shared_sram;				//TLM channel to shared sram
		register32								share_sram_ack_pc_reg;
		register_basic<insnLine512>				share_sram_ack_inst_reg;
#endif

		
#endif
		std::string name;
		enum icache_mode{ICACHE_INVALID = 0,ICACHE_NORMAL = 1,ICACHE_SRAM = 2};
		icache_mode mode;
		bool cache_lock;
		unsigned int m_core_id;
		void NotifyCoreID(unsigned int p_id){ m_core_id = p_id;}

		unsigned int local_cycle_L,local_cycle_H;
#ifdef SOFTWARE_SIMULATOR
#define ICACHE_BASE_ADDR 0x0 //0x0120c000					//Base address for SRAM mode
#else
#define ICACHE_BASE_ADDR 0x0120c000
#endif

#define ICACHE_PROGMEM_BASE_ADDR 0x0b000000		//Log: 2015-4-21, single core sim  origin=0x0				//Base address for program memory, 0 for 104 and 0x0110_0000 for 200

#define DEFAULT_DDR_ADDR_START 0x80000000//0x20000//0x09c00000
#define DEFAULT_DDR_ADDR_END   0xffffffff//0x2ffff//0x09dfffff

		//Maskes for each register
#define MASK_ICGC 0x0101010f
#define MASK_ICACNT 0xffffffff
#define MASK_ICMCNT 0xffffffff
#define MASK_ICFLUSH_CON 0x1
#define MASK_ICDMA_CON 0x10101
#define MASK_ICDMA_LEN 0x7ff
#define MASK_ICDMA_DST_ADDR 0xffffffff
#define MASK_ICDMA_SRC_ADDR 0xffffffff
#define MASK_ICDMA_AUTOLEN 0x7ff

		//Input signals
		bool IAB_HALT;			//Come from IAB level

		bool dsp_en;			//New interface for dsp debug

		register_basic<ictype_bool> dsp_en_reg;		

		unsigned int ro_CJMP;	//Come from ... level?
		unsigned int ro_LC[4];	//LC[0..3] register value

		bool exFlush;			//flush pipeline, true valid
		unsigned int exFlushPC;	//flush PC
		unsigned int exFlushPri;	//flush priority
		bool isFlushRETI;			//flush is Interruption Return?




		bool INT_proc;				//Interrupt happens
		unsigned int INT_PC;		//Interrupt PC
		unsigned int INT_pri;		//Interrupt priority

		bool calcPCFromPMASK;		//signal for shift priority to INT_pri
		bool calcPCFromPMASK_new;		//signal for shift priority to INT_pri
		register_basic<ictype_bool> isExRETI_1d;	//ExRETI 1 cycle later
		register_basic<ictype_bool> isExRETI_2d;	//ExRETI 2 cycle later



		//Output signals;
		//Generated by FE1
		bool	isFE1_load_w;
		//Generated by FE2
		bool		submitToIAB_w;
		insnLine512 insnLine_toIAB;

		bool	hitFE2_w;
		bool	isFE2B_w;
		unsigned int PCFE2B_w;

		unsigned int firstBPos;				//If branch predication is done, indicate the position
		unsigned int iab_launchB_maks;		//Indicate branch slots: 0 no branch
											//						 1: slot[0]
											//						 2: slot[4]
											//						 4: slot[8]
											//						 8: slot[12]
		//FE0 related signals
		unsigned int PCFE0_w;
		bool icWbDelay_2nd_w;				//Indicate that write back is conflict 2nd time

		//Pipeline registers
		//FE0 level registers
		register32 PCFE0;
		register32 priFE0;
		register_basic<ictype_bool> PCFE0_en;

		register_basic<ictype_bool> ISRFirstLine_FE0;
		register_basic<ictype_bool> IsNormalSeq_FE0;

		bool ISRFirstLine_FE0_w;
		bool IsNormalSeq_FE0_w;

		//FE0/FE1 level register
		register32 PCFE1;
		register_basic<ictype_bool> isFE1BUB;
		register32 priFE1;
		register_basic<ictype_bool> ISRFirstLine_FE1;
		register_basic<ictype_bool> IsNormalSeq_FE1;

		//FE1/FE2 level register
		register32 PCFE2;
		register_basic<ictype_bool> isFE2BUB;
		register32 priFE2;
		register_basic<cacheLine2136> bufCacheLine;
		register_basic<ictype_bool> ISRFirstLine_FE2;
		register_basic<ictype_bool> IsNormalSeq_FE2;

		//icache dedicated registers
		enum ICACHE_REG_TYPE{
			ICACHE_ICGC,ICACHE_ICACNT,ICACHE_ICMCNT,ICACHE_ICFLUSH_CON,ICACHE_ICDMA_CON,
			ICACHE_ICDMA_LEN,ICACHE_ICDMA_DST_ADDR,ICACHE_ICDMA_SRC_ADDR,ICACHE_ICDMA_AUTOLEN
		};

		register32 ICGC;
		register32 ICACNT;
		register32 ICMCNT;
		register32 ICFLUSH_CON;
		register32 ICDMA_CON;			//[16] boot: 0=DST==SRC, 1=DST!=SRC
										//[8]  terminate: terminate before DMA end when INT come
										//[6]  auto DMA end
										//[5]  auto DMA start
										//[4]  auto DMA request
										//[2]  manual DMA end
										//[1]  manual DMA start
										//[0]  manual DMA request


		register32 ICDMA_LEN;
		register32 ICDMA_DST_ADDR;
		register32 ICDMA_SRC_ADDR;
		register32 ICDMA_AUTOLEN;

		//external PC and Pri for software module, using wrFPC() interface
		unsigned int externalPC_w;
		unsigned int externalPri_w;

		bool exflush_during_internal_process;			//true if an exFLush happens in the process of internal DMA/FLUSH

		//Notified by external software module
		bool extern_INT_w;
		bool extern_ExFlush_w;
		DSPU32 extern_ExFlush_PC_w;
		DSPU32 extern_ExFlush_pri_w;

		bool readREG(ICACHE_REG_TYPE reg_id, unsigned int *value);
		bool readREG_in(ICACHE_REG_TYPE reg_id, unsigned int *value);
		bool writeREG(ICACHE_REG_TYPE reg_id,unsigned int value);
		bool getBitREG(ICACHE_REG_TYPE reg_id,unsigned int idx);		//if REG[idx] == 1 return true
		bool setBitREG(ICACHE_REG_TYPE reg_id,unsigned int idx);		//Set REG[idx] =1
		bool clrBitREG(ICACHE_REG_TYPE reg_id,unsigned int idx);		//Set REG[idx] =0
		//DMA related
		unsigned int DDRAddrStart;
		unsigned int DDRAddrEnd;
		unsigned int autoDMAPC;
		bool icDMAProc;					//true when DMA is active
		bool icDMAFirst3Addr_w;
		bool icDMASelfMiss;
		bool icDMAAck;
		bool icDMATerminal;
		bool icDMABoot;
		bool icDMAPCEn;
		register_basic<ictype_bool> icDMAPCEn_1d;
		register_basic<ictype_bool> icDMAPCEn_2d;

		register32 icdma_cnt;			//counter for DMA proc, set to LEN and decrease
		register_basic<ictype_bool> icDMAProc_1d;
		register_basic<ictype_bool> dmaTerminalSet;						//terminate DMA when INT come
		register_basic<ictype_bool> autoDMASet;
		register_basic<ictype_bool> isFE2PCDDR;							//is PCFE2 is in DDR?
		register32 icDMAPC;								//DMA PC used to read cache
		register32 icDMARdAddr;							//DMA PC used to load L2 cache
		register_basic<ictype_bool> icDMAProc_d[3];		//flag for first 3 cycle in DMA process

		register32 innerOptBakPC;						//Backup PC when DMA or FLUSH happen
		register32 innerOptBakPri;						//Backup Priority when DMA or FLUSH happen

		register_basic<ictype_bool> innerOptBakISRFirstLn;

		unsigned int currentBakPC_w;
		unsigned int currentBakPri_w;
		bool currentBakISRFirstLn_w;

		//FLUSH operation related
		register32 icFlushPC;
		bool icFlushProc;
		register_basic<ictype_bool> icFlushProc_1d;

		//BPB pointer and size
		unsigned int *p_BPB;
		unsigned int sizeBPB;

		//internal submodule
		icache_ram_new ICACHE_RAM;
		//L2_mmc_new L2MMC;

		//internal signals
		//Come from L2 submodule
		bool L2_ack_w;
		unsigned int L2_ack_pc_w;
		insnLine512 L2_ack_insn_w;

		//to L2 submodule
		bool L2_irq_w;
		unsigned int L2_irq_pc_w;
		register32 L2_irq_pc;

		//L2 ack signals
		bool L2_ack_true;
		register_basic<ictype_bool> L2_ack_true_tmp;		//hold true until submit

		//write back
		bool write_En;
		unsigned int write_PC;
		cacheLine2136 write_Line;

		//Cache ram output
		cacheLine2136 cacheOutput[4];

		//other
		bool 		hitFromFE2Buffer_w;	//true if FE2 buffer has hit

		bool		icHit_w[4];
		bool		icHitWbEn_w;
		bool		pcFE2_launch_en_w;

		insnLine512 hitFE2Inst_w;		//carry hit instruction line
		unsigned int hitway_w;			//which way is hit;
		insnLine512 insnLine_toIAB_w;	//get ready to write to output

		//branch predict
		PIPE_FE_REG_CONTENT::PIPE_FE2_ACTION_INFO branchInfo[4];
		register_basic<ictype_bool> branpredhasdone;	//branch predicate for once
		bool L2_ackB_w;			//branch taken predict from L2_ack_insn_w
		register_basic<ictype_bool> lastLineNotComplete;	//true when last line is not complete
		//cache reflush
		bool isReflushBegin_w;
		bool isReflushEnd_w;
		register_basic<ictype_bool> isReflush_proc;				//when reflush happens set to true, default false
		unsigned int timer_reflush;			//timer for reflush process. typically = 129
		bool usingResvPC;					//only recover PC from FE1 or FE2 is true;

		bool updateUsingResvPC;				//true when reflush ends
		unsigned int ResvPC;				//PC reserved
		unsigned int ResvINTLvl;			//Interrupt level reserved
		bool ResvISRFirstLine;
		bool ResvIsNormalSeq;



		//cache read and write valid and conflict
		bool isFPCUsed_w;

		bool cgcr0IntFlush_w;


		//immediate write channel
		bool imme_wr[4];		//Enable signal for each channel
		unsigned int imme_wAddr[4];		//register address
		unsigned int imme_wData[4];		//register value

		//Next PC for check in WrFPC()
		unsigned int nextPC;
		unsigned int nextPC_extern;	//next PC input from outside
		

		//For send_request() test
#define TEST_REQUEST
#ifdef TEST_REQUEST
		register_basic<ictype_bool>  tr_pro;
		register32 l2_irq_pc_1d;
		register_basic<ictype_bool> l2_irq_1d;
		register_basic<ictype_bool>  tr_bypass;
#endif

	public:

		SC_HAS_PROCESS(icache_module_new);
#ifdef SC_ICACHE
		icache_module_new(
				sc_module_name nm, unsigned int *p_pBPB, unsigned int BPBsize);
		icache_module_new(sc_module_name nm ):module_name(nm){
			init_socket_to_sram.bind(*this);

#ifdef TLM_SHARED_SRAM
			init_socket_to_shared_sram.bind(*this);
#endif
			/*
			SC_METHOD(clock_tick);
			sensitive<<clk.pos();

			dont_initialize();
			*/

#ifdef INNER_SRAM_SC_INOUT
			SC_METHOD(proc_inner_sram_jtg_signals);
			sensitive<<sc_inner_sram_jtg_en<<sc_inner_sram_jtg_wr<<sc_inner_sram_jtg_addr
				<<sc_inner_sram_jtg_wdat<<sc_inner_sram_jtg_rdat;

			SC_METHOD(proc_inner_sram_jtg_rdat);
			sensitive<<sc_inner_sram_jtg_addr;
#endif
			//reset();
			DEBUG_INFO_STREAM("EVENT: icache module "<<nm<<" created successfully\n");

			insnLine_toIAB_w.reset();
			hitFE2Inst_w.reset();
			
			inner_sram = new unsigned int[0x10000];	
			if(!inner_sram)
			{
				printf("error in new\n");				
			}
			else{
				memset(inner_sram, 0, sizeof(unsigned int) * 0x10000);
			}
			return;
		};
#else
		icache_module_new(std::string nm, unsigned int * p_pBPB, unsigned int BPBsize);
		icache_module_new(){};
#endif
		//~icache_module_new(){};
#ifdef SC_ICACHE
		virtual tlm::tlm_sync_enum nb_transport_bw(
				tlm::tlm_generic_payload &trans,
				tlm::tlm_phase &phase,
				sc_core::sc_time &t);
		virtual void invalidate_direct_mem_ptr(
				sc_dt::uint64 start_range,
				sc_dt::uint64 end_range){}

		void clock_tick();

		void send_REQUEST();
		void process_RESPONSE(tlm::tlm_generic_payload &gp);

#ifdef  TLM_SHARED_SRAM
		void send_REQUEST_to_Shared_SRAM(bool irq_plus, bool dsp_en);
		void process_RESPONSE_from_Shared_SRAM(tlm::tlm_generic_payload &gp);
#endif
		
#endif
		void reset(unsigned int bootaddr);		//module reset at beginning

		//External interface
		//void ResetCache();
		void ResetCacheReg(unsigned int boot_addr);			//Reset cache when running
		void ResetCacheMem();
		void SetStartPC(unsigned int p_u32StartPC);
		//bool LoadCacheFromFile();
		void SetMode(icache_mode m);
		void incCycle();
		void CacheDoCycle();			//Cyclic evaluate phase
		void CacheShiftReg();			//Cyclic update phase
		void WrFPC(DSPU32 p_u32PCNotAlign,bool p_bolISRFirstLine, DSPU32 p_u32INTLvl, bool p_bolIsNormalSeq);				//Write PCFE1 register
		DSPU32 RdFPC();									//Read PCFE1 register

		DSPU32 RdNextActivePC();					//used when INT or FLUSH return


		bool WrCacheReg(DSPU32 p_u32RegAddr, DSPU32 p_u32Value);
		bool RdCacheReg(DSPU32 p_u32RegAddr, DSPU32 *p_pValue);

		bool WrCacheReg_dbg(DSPU32 p_u32RegAddr, DSPU32 p_u32Value);
		bool RdCacheReg_dbg(DSPU32 p_u32RegAddr, DSPU32 *p_pValue);
		bool WrCacheReg_Jtag(DSPU32 p_u32RegAddr, DSPU32 p_pValue);
		//void ReadSlots(DSPU32 *p_pPC, bool *p_Hit, DSPU32 *p_pINTLvl, DSPU32 * p_pSlots);
		void  ReadCacheSlots(bool *p_pHit, PIPE_FE_REG_CONTENT *p_pPipeRegContent);

		void jtagReadCacheSlots(bool *p_pHit,PIPE_FE_REG_CONTENT *p_pPipeRegContent);
		void jtagReadCacheSlots_noalign(bool *p_pHit,PIPE_FE_REG_CONTENT *p_pPipeRegContent);

		void GetFE2BraInfo(bool *p_pFE2BraTaken, DSPU32 *p_pFE2TgtAddr, DSPU32 *p_pFE2INTLvl, bool* p_bolIsFrmL2);
		void GetFPCReserveInfo(bool* p_pbolReservedPCUpdate, DSPU32* p_pu32Addr, DSPU32* p_pu32INTLvl);
		bool GetCacheBusyStatus();

		bool IsFPCUsed();
		bool IsCacheSlotsReady();
		bool IsCacheBusy();		//return true if cache is doing flush of dma
		void NotifyIABHalt(bool p_bolHalt);

		void NotifyDspen(bool p_bolDspen);
		
		void NotifyPipeBefFlushInfo(bool p_bolPipeBefFlushed, DSPU32 p_u32INTLvl);
		void NotifyPipeBefFlushInfo_software(bool p_bolPipeBefFlushed, DSPU32 p_u32INTLvl, DSPU32 p_u32TargetPC);

		void NotifyRETI(bool p_bolIsRETI);

		void NotifyCgcr0IntFlush(bool p_bolCgcr0IntFlush);

		void NotifyExFlushPC(DSPU32 p_u32ExFlushPC);
		void NotifyIntInfo(bool p_bolINT, DSPU32 p_u32INTLvl);	//Interruption info
		void NotifyIntInfo_software(bool p_bolINT);
		void NotifyIntPC(DSPU32 p_u32INTPC);
		void NotifyCJMPValue(DSPU32 p_u32Value);
		void NotifyLCValue(DSPU32 p_u32LCIdx, DSPU32 p_u32Value);

		bool WrCacheMem(DSPU32 p_u32Addr, DSPU32 p_u32Value);	//used to initialize icache_ram
		bool RdCacheMem(DSPU32 p_u32Addr, DSPU32 *p_pValue);	//used to look up icache_ram

		void SetBPB(unsigned int *p_pBPB, unsigned int p_u32BPBSize ); //Call once at beginning

		void SetCacheSpace(DSPU32 p_LowAddr);

		//My add
		void GetBubble(bool *p_isFE1BUB,bool *p_isFE2BUB);
		void WriteFE1BUB(bool val);
		void processReflush();
		void processReflush_complex();
		void writeback();
		unsigned int pickVictimLine();
		void LogIntoBranchInfo(unsigned int slot,bool processed,bool taken,unsigned int TgtPC);


		//Inner logic
		void evaluate();		//Evaluation phase
		void update();			//Update phase

		//evaluate phase
		void evaluate_REG();		//dedicated registers evaluation

		void evaluate_ex();			//for exFlush, INT and other things


		void evaluate_FE2();
		void evaluate_FE1();
		void evaluate_FE0();

		void evaluate_FE0_software_pre();	//Must evaluate first before FE0
		void evaluate_FE0_software();		//this interface for software simulator only
		//FE2 logic
		void cacheHit_logic();
		void L2ireq_logic();
		void branchPred_logic();
		void submitIAB_logic();
		void writeBack_logic();
		//exFlush logic
		//void exFlushProc_logic();


		bool calcHitCache();	//return true when hit, false when miss
		void branchPred_analysis();		//analyze hitFE2Inst_w to generate branch prediction info.
		bool isBranchInsn(unsigned int idx);	//return true when hitFE2Inst_w[idx] is a branch instruction

		bool isEndOfLine(unsigned int idx);			//hitFE2Inst_w[idx] is the end of line
		bool isRetInsn(unsigned int idx);			//hitFE2Inst_w[idx] is RET instruction
		bool isBNInsn(unsigned int idx);			//hitFE2INST_w[idx] is BN instruction
		bool isDoubleInsn(unsigned int idx);		//hitFE2Inst_w[idx,idx+1] is a dword instruction
		bool predTaken(unsigned int bpb_value);

		bool isAlignTo16(DSPU32 PC);
		bool isSecondWordInDW(unsigned int insn_word,bool *isHead);

		void flushFE1register();
		void flushFE2register();
		//Prologue functions

		void display();

		void genStimulation();

		void dumpIcacheRam();

		void genOutputRef();


		void share_sram_docycle(bool isJTAG);

		//Trace file related
		void initTraceFile();
		//Stimulus file related
		void initStmFile();

		//Tools functions
		DSPU32 GSignExtend(DSPU32 p_u32Src, int p_intSrcLen);
		DSPU32 ExtractBinStr(DSPU32 p_u32BinStr, DSPU32 p_u32StartBit, DSPU32 p_u32BitLen);
		double Utilization();
		double MissRate();

		//immediate write channel iterface
		void NotifyImmeWr(bool wr_en[4], unsigned int wr_addr[4], unsigned int wr_data[4]);
		void ImmeWrReg();

		bool returnFromDMA(){
			return ((icDMAProc==false) && (icDMAProc_1d.read().val == true));
			//return icDMAProc_1d.read().val;
		}
		bool returnFromFLUSH(){
			return ((icFlushProc==false)&& (icFlushProc_1d.read().val == true));
		}
		DSPU32 getCurrentPri(){
			return (priFE2.read());
		}

		DSPU32 jtag_read_FE1(){
			return (isFE1BUB.read().val ? 0 : PCFE1.read());
		}

		DSPU32 jtag_read_FE2(){
			return (isFE2BUB.read().val ? 0 : PCFE2.read());
		}

		bool jtag_read_FE1BUB(){
			return isFE1BUB.read().val;
		}

		bool jtag_read_FE2BUB(){
			return isFE2BUB.read().val;
		}

	};
}




#endif /* ICACHE_MODULE_NEW_H_ */
