#ifndef DDR_MODULE_H_
#define DDR_MODULE_H_

#include "./dmac_sim/dmac_global.h"
#include "common.h"

#define Delay 5
#define LEN 1024
//#define DDRDataStart 0x1c000000

class DDR_MODULE : public sc_module 
	,public tlm::tlm_bw_transport_if<mydma_protocol_types>
	,public tlm::tlm_fw_transport_if<mydma_protocol_types>{

public:	
	sc_in_clk clk;

	SC_HAS_PROCESS(DDR_MODULE);

	DDR_MODULE(sc_module_name mn);
	~DDR_MODULE(){}


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


	void clock_tick();
	void reset();
	bool write_ddr(int tranport_type,unsigned char* msg);
	bool read_ddr(int tranport_type,unsigned char* msg);

	void rdack();
	void rdackprepare();
	bool addrjudge(int tranport_type,unsigned char* msg);

	tlm::tlm_initiator_socket	<CH_WIDTH_256,mydma_protocol_types> init_socket2dmac0;
	tlm::tlm_target_socket		<CH_WIDTH_256,mydma_protocol_types> targ_socket2dmac0; //128 targ for core 0

	tlm::tlm_initiator_socket	<CH_WIDTH_256,mydma_protocol_types> init_socket2dmac1;
	tlm::tlm_target_socket		<CH_WIDTH_256,mydma_protocol_types> targ_socket2dmac1; //128 targ for core 1



	unsigned int data[DDRData_MaxOffset+1];

	vector<pair<DMAC_MEM, unsigned int> > rd_data_vec[ISS_NUM_DEF];
	vector<pair<SRIO_FRAME, unsigned int> > srio_rd_data_vec[ISS_NUM_DEF]; //zqw+ 2019.3.22 srio_rd_data_vec���ڴ��SRIO_FRAME����


	unsigned int Sdst_x_len_record[ISS_NUM_DEF];
	unsigned int Sdst_y_len_record[ISS_NUM_DEF];
	bool Sdst_D_sel_rd[ISS_NUM_DEF];//0-1d,1-2d
	DSPU64 Sdst_curr_addr_rd[ISS_NUM_DEF];
	int Sdst_rem_x_len_rd[ISS_NUM_DEF];	
	int Sdst_rem_y_len_rd[ISS_NUM_DEF];	
	int Sdst_addr_x_step_rd[ISS_NUM_DEF];
	int Sdst_addr_y_step_rd[ISS_NUM_DEF];

	prim_register	 dma_rdack_mission_on[ISS_NUM_DEF];
	// zqw+ 2019.1.28  SRIO���� 
	prim_register	 srio_rdack_mission_on[SRIO_NUM];
	DSPU64 Ssrio_dst_curr_addr_rd[SRIO_NUM];
	int Ssrio_dst_rem_x_len_rd[SRIO_NUM];

	int u32ChanIdx;  //zqw+ 2019.2.15 ��ʾ��������
	unsigned int  tranport_type; //zqw+ 2019.3.22 ��ʾ�������� 0��DMA 1��SRIO

	//zqw+ 2019.3.22 ��DDR�ж�д����
	unsigned int srio_wr_len;
	unsigned int srio_rd_len;
	bool wr_first_frame_flag;
	bool rd_first_frame_flag;
	unsigned int ddr_addr;  //��д����ʱ��ddr�ڲ���ַ



	//Interface for JTAG
	bool read_word(unsigned int addr,unsigned int &value);
	bool write_word(unsigned int addr,const unsigned int value);

};




#endif