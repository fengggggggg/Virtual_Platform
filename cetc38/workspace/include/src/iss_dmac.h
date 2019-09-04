
#ifndef _ISS_DMAC_H
#define _ISS_DMAC_H

#define DMAC_WIDTH 8


//-------------------------------------------
// ͨ��DMAC��ʽ���ʱ��˴洢��
typedef struct 
{
	bool bolInUse;				// �ýṹ���Ƿ����ڱ�ʹ��(�����Ƿ���Ч)
	bool bolInServe;			// Ϊtrue��ʾ����Ϣ�Ѿ����ɹ����͸�Ŀ�ĺ�
	//bool arrDelayServed[2];		// �ýṹ���������ķ��������Ƿ��Ѿ�������
	bool bolri_Served;
	bool bolro_Served;
	DMAC_MEM dmac_mem;
	DSPU32 arrMacroIdx[24];
	DSPU32 arrRegIdx[24];
	DSPU32 arrPageIdx[24];
	DSPU32 u32SpecWrMask;
} DMAC_REQ_T;

//--------------------------------------------------------------

typedef struct
{
	bool		bolInUse;
	bool		bolServed;		// �ýṹ���������ķ��������Ƿ��Ѿ�������
	DSPU32	u32DelaySrv;	// ����request_update()ִ�м�1������
	DSPU32	u32DelayResp;
//	DSPU32	u32ChanIdx;		
	DSPU32	u32ElemNum;	// ��ǰ��δ�������������
	DMAC_MEM dmac_mem;
	DSPU32	u32Block;		// burst��ʽֻ�ܷ���һ��ȷ����block
	OUT_RESP_BANK arrBanks[BANK_NUM_PERBLK];	// �ô������еķô��ַ���ֲܷ���ȷ��block�ڵ�8��bank��
} DMAC_RESP_T;


DMAC_RESP_T m_dmac_resp[DMAC_MAX_CHANNELS];
DMAC_REQ_T m_dmac_req;


/************************************ Declaration ************************************************/
//tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_core::sc_time &delay);
//tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_core::sc_time &delay);
void reset_dmac_req();
void reset_dmac_resp();
bool reset_dmac();
bool send_resp_dmac(DMAC_MEM* p_dmac_mem);
bool send_req_dmac(DMAC_MEM* p_dmac_mem);
void dmac_resp_delay_countdown();
bool fill_dmac_rd_req(DSPU32 p_u32GAddr, DSPU32 p_u32RdBus, DSPU32 p_u32RdIdx);
bool fill_dmac_wr_req(DSPU32 p_u32GAddr, DSPU32 p_u32Value, DSPU32 p_u32PageIdx, DSPU32 p_u32MacroIdx, DSPU32 p_u32SrcRegIdx, DSPU32 p_u32WrBus, DSPU32 p_u32WrIdx, bool p_bolSpecWr);


void PutDMACReq_AC();
void SrvDMACReq_AC();

void GenDMACStall();
bool SrvDMACH_DC4(DMAC_RESP_T *p_dmac_resp);


bool rd_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 *p_pValue);
bool wr_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 p_pValue);

bool jtag_rd_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 *p_pValue);
bool jtag_wr_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 p_pValue);


#if 0
void DelElemIdx_DMAC(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 p_u32ElemIdx);
void SelMinAddr(DMAC_MEM *p_dmac_mem, DSPU32 &p_u32Addr, DSPU32 &p_u32ReqIdx);
bool SelChanIdx_DMAC(DSPU32 &p_u32ChanIdx, DSPU32 p_u32Block);
bool SelReqIdx_DMAC(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 &p_u32ReqIdx, DSPU32 &p_u32ElemIdx, DSPU32 p_u32ChanIdx);
/*------------------------------------------ typedef ------------------------------------------*/
// ������ָ�ʽ���ʺ���洢��

// �ڱ�����DMAC��ͨ�Žӿ�(MSG_INSN_RW_MEM)����������£�
// Ϊ�����ں�ʹ�ö���MSG_INSN_RW_MEM���з�װ�γ�MSG_INSN_RW_MEM_ISS��

typedef struct
{
	// һ���ô�ָ��ķô��ַλ��ͬһbank��ͬһ���(����ַ��ͬ)���������Ϊ4
	DSPU32 arrAddr[4];   // �ô��ַ
	DSPU32 arrAddrIdx[4]; // ��һ��ָ���8���ô��ַ�е����: 0 ~ 7
	DSPU32 u32ElemNum; // �ô��������

} INSN_RW_MEM_ELEM;

typedef struct
{
	// һ���ô�ָ��ķô��ַ���ʹbank�����Ϊ4
	INSN_RW_MEM_ELEM arrDepth[4];
	DSPU32 u32BankDepth;   // bank�����Ϣ������ǰbank�ϵ�bank��ͻ�����Ҫ��cycle�� 
	                      // 0 ��ʾ��ǰBank����Ԫ��

} INSN_RW_MEM_BANK;

typedef struct
{
	// ÿ��block��8��bank.
	INSN_RW_MEM_BANK arrBanks[8];

} INSN_RW_MEM_BLOCK;

typedef struct msg_insn_rw_mem_iss
{
	bool bolInUse;   // �ýṹ���Ƿ����ڱ�ʹ��
	bool bolInServe; // Ϊtrue��ʾ����Ϣ�Ѿ����ɹ����͸�DMAC
	bool bolServed;  // �ýṹ���������ķ��������Ƿ��Ѿ�������
	MSG_INSN_RW_MEM msg_insn_rw_mem;

	// ����д�������ں���ǡ����ʱ������������Ϣ
    // ��ͨ�üĴ�����ΪԴ������
	DSPU32 arrMacroIdx[24];
	DSPU32 arrRegIdx[24];

	// �����ô����ߵ�bank��ͻ��Ϣ
	// arrBusInfo[0]��read_bus_0
    // arrBusInfo[1]��read_bus_1
    // arrBusInfo[2]��write_bus_0
    // arrBusInfo[3]��write_bus_1
	INSN_RW_MEM_BLOCK arrBusBankConfInfo[4];

} MSG_INSN_RW_MEM_ISS;

//--------------------------------------------------
// ������ָ�ʽ���ʱ��˴洢��

// �ڱ�����DMAC��ͨ�Žӿ�(MSG_INSN_RW_MEM)����������£�
// Ϊ�����ں�ʹ�ö���MSG_INSN_RW_MEM���з�װ�γ�MSG_INSN_RW_CORE_MEM_ISS��

typedef struct
{
	DSPU32 u32Index;             // ��MSG_INSN_RW_CORE_MEM_ISS.msg_insn_rw_mem.arrInsnsRWInfo[]�е�������
	bool bolInUse;                 // Is there valid info in this structure?
	bool bolServed;               // �Ƿ��ѱ�����

} INSN_RW_CORE_MEM_ELEM;

typedef struct
{
	// the maximum number of request for each bank from on instr line is 24
	// the maximum number of RW instructions in one execution line is 3
	// ����ָ�����ͬʱ����һ��bank
	INSN_RW_CORE_MEM_ELEM arrElems[24];
	DSPU32 u32ElemNum;                // ��ǰbank��δ�������������

} INSN_RW_CORE_MEM_BANK;

typedef struct
{
	// ÿ��block��8��bank.
	INSN_RW_CORE_MEM_BANK arrBanks[8];
	DSPU32 u32ElemNum;                // ��ǰblock��δ�������������

} INSN_RW_CORE_MEM_BLOCK;

typedef struct msg_insn_rw_core_mem_iss
{
	bool bolInUse;   // �ýṹ���Ƿ����ڱ�ʹ��
	bool bolServed;  // �ýṹ���������ķ��������Ƿ��Ѿ�������
	DSPU32 u32CountDown;  // ����request_update()ִ�м�1������
	MSG_INSN_RW_MEM msg_insn_rw_mem;

	// �������ݴ洢������6��block
	// �����ݽṹ�����ṩ��msg_insn_rw_mem.arrInsnsRWInfo[]������
	INSN_RW_CORE_MEM_BLOCK arrBlocks[6];
	DSPU32 u32ElemNum;  // ��ǰ��δ�������������

} MSG_INSN_RW_CORE_MEM_ISS;

//--------------------------------------------------
// ��burst��ʽ���ʱ��˴洢��

// �ڱ�����DMAC��ͨ�Žӿ�(MSG_RW_CORE_MEM)����������£�
// Ϊ�����ں�ʹ�ö���MSG_RW_CORE_MEM���з�װ�γ�MSG_BURST_RW_CORE_MEM_ISS��

typedef struct
{
	DSPU32 u32Index;             // ��MSG_BURST_RW_CORE_MEM_ISS.msg_rw_core_mem.arrRWElems[]�е�������
	bool bolInUse;                 // Is there valid info in this structure?
	bool bolServed;               // �Ƿ��ѱ�����

} BURST_RW_CORE_MEM_ELEM;

typedef struct
{
	// burst��ʽ�ô�������������8���ô��ַ
	BURST_RW_CORE_MEM_ELEM arrElems[8];
	DSPU32 u32ElemNum;                // ��ǰbank��δ�������������

} BURST_RW_CORE_MEM_BANK;

typedef struct msg_burst_rw_core_mem_iss
{
	bool bolInUse;   // �ýṹ���Ƿ����ڱ�ʹ��
	bool bolServed;  // �ýṹ���������ķ��������Ƿ��Ѿ�������
	bool bolIsRead;  // �������ֶ���������д����
	DSPU32 u32CountDown;  // ����request_update()ִ�м�1������
	MSG_RW_CORE_MEM msg_rw_core_mem;	

	DSPU32 u32BlockIdx;    // burst��ʽֻ�ܷ���һ��ȷ����block
	// �ô������еķô��ַ���ֲܷ���ȷ��block�ڵ�8��bank��
	BURST_RW_CORE_MEM_BANK arrBanks[8];
	DSPU32 u32ElemNum;   // ��ǰ��δ�������������

} MSG_BURST_RW_CORE_MEM_ISS;

//--------------------------------------------------
typedef struct
{
	// u32ElemMask: addr_f addr_e ...... addr_b addr_a(LSB)
	
	DSPU32 u32ElemMask0;  // ��ͻ����ĵ�1�����ڷ������������
	DSPU32 u32ElemMask1;  // ��ͻ����ĵ�2�����ڷ������������
	DSPU32 u32ElemMask2;  // ��ͻ����ĵ�3�����ڷ������������
	DSPU32 u32ElemMask3;  // ��ͻ����ĵ�4�����ڷ������������
	bool bolSingleWord;      // �Ƿ��ǵ��ַô�ָ��
	bool bolIsDM8;          // �Ƿ���˫ģ8ָ��
	
	DSPU32 u32ConfNum;    // ��ͻ���������
	DSPU32 u32ConfState;   // ��ͻ״̬��	

} BANK_CONFLICT_TBL_LINE;

/*----------------------------------- data declarations ----------------------------------*/
MSG_INSN_RW_MEM_ISS m_msg_insn_rw_mem_iss;  // ������ָ�ʽ���ʺ���洢��

MSG_INSN_RW_CORE_MEM_ISS m_msg_insn_rw_core_mem_iss;  // ������ָ�ʽ���ʱ��˴洢��
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_wr_ch00_iss;     // 256bit����д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rd_ch00_iss;     // 256bit���ݶ�
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch1_iss;     // 128bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch2_iss;     // 64bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch3_iss;     // 64bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch4_iss;     // 64bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch5_iss;     // 64bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch6_iss;     // 64bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch7_iss;     // 64bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch8_iss;     // 64bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_ch9_iss;     // 64bit���ݶ�д
MSG_BURST_RW_CORE_MEM_ISS m_msg_burst_rw_cha_iss;     // 32bit���ݶ�д

// bank��ͻ��Ϣ��
BANK_CONFLICT_TBL_LINE m_bank_conflict_tbl[24];  // GRQ: Ϊʲô��24��?

/*-------------------------------------- implimention -------------------------------------*/

void reset_mem_req_frm_out_core();
void memreq_frmout_countdown();
void reset_msg_insn_rw_mem_iss();
bool add_insn_rd_mem_elem(DSPU32 p_u32GAddr, DSPU32 p_u32Slot, MSG_INSN_RW_MEM_ISS &p_msg_insn_rw_mem_iss, bool p_bolAtom, bool p_bolSingleWord, bool p_bolIsDM8, DSPU32 p_u32AddrIdx);
bool add_insn_wr_mem_elem(DSPU32 p_u32GAddr, DSPU32 p_u32Value, DSPU32 p_u32MacroIdx, DSPU32 p_u32SrcRegIdx, DSPU32 p_u32Slot, MSG_INSN_RW_MEM_ISS &p_msg_insn_rw_mem_iss, bool p_bolAtom, bool p_bolSingleWord, bool p_bolIsDM8, DSPU32 p_u32AddrIdx, bool p_bolSpecWr);
DSPU32 get_insn_rd_mem_result(DSPU32 p_u32GAddr, MSG_INSN_RW_MEM_ISS &p_msg_insn_rw_mem_iss);
void init_bank_conflict_tbl();
bool lookup_bank_conflict_tbl(BANK_CONFLICT_TBL_LINE *p_pTableLine, DSPU32 *p_pMemAddr);
bool prepare_lookup_paras(DSPU32 p_u32Bus, MSG_INSN_RW_MEM_ISS *p_p_msg_insn_rw_mem_iss, BANK_CONFLICT_TBL_LINE *p_pTableLine, DSPU32 *p_pMemAddr);
tlm::tlm_sync_enum nb_transport_bw_dmac( tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay );
tlm::tlm_sync_enum nb_transport_fw_dmac( tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay );

// ��MSG_RW_CORE_MEM.arrRWElems[]�ṹ���ҳ���ַ��С�ĵ�Ԫ
void GetMinAddr(MSG_RW_CORE_MEM *p_pMsgRWCoreMem, DSPU32 &p_u32Addr, DSPU32 &p_u32Index);

// ��MSG_INSN_RW_MEM.MSG_INSN_RW_MEM_ELEM.u32Bus��slot���ת��Ϊbus���
// ����ͨ��ʱ�����������Ϊbus���
// �������ڴ����������⣬�ں˽������������Ϊslot���
void InBusToOutBus(MSG_INSN_RW_MEM *p_p_msg_insn_rw_mem);
// ��MSG_INSN_RW_MEM.MSG_INSN_RW_MEM_ELEM.u32Bus��bus���ת��Ϊslot���
void OutBusToInBus(MSG_INSN_RW_MEM *p_p_msg_insn_rw_mem);

//bool RdSharedMem(DSPU32 p_u32Addr, DSPU32 *p_pValue);
//bool WrSharedMem(DSPU32 p_u32Addr, DSPU32 p_u32Value);


// ����ɺ�����burst��ʽ���ʺ��ڴ洢�������
// �ں�ʹ�øýӿ�֪ͨDMAC
bool send_resp_brust_rw_core_mem(MSG_RW_CORE_MEM *p_p_msg_rw_core_mem, bool p_bolIsRead);
// ����ɺ�����ָ�ʽ���ʺ��ڴ洢�������
// �ں�ʹ�øýӿ�֪ͨDMAC
bool send_resp_insn_rw_core_mem(MSG_INSN_RW_MEM *p_p_msg_insn_rw_mem);
// ���ں���Ҫ��ָ�ʽ���ʺ���洢��ʱ
// ʹ�øýӿ�֪ͨDMAC
bool send_req_insn_rw_out_mem(MSG_INSN_RW_MEM_ISS *p_p_msg_insn_rw_mem_iss);
// ���ں���Ҫ��DMAC�Ĵ���ʱ
// ʹ�øýӿ�֪ͨDMAC
bool rd_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 *p_pValue);
// ���ں���ҪдDMAC�Ĵ���ʱ
// ʹ�øýӿ�֪ͨDMAC
bool wr_dmac_reg(DSPU32 p_u32SpecRegAddr, DSPU32 p_u32Value);
// �ں˸�λDMAC
bool reset_dmac();

bool SrvOutInsnReq_DC4(bool p_bolAtom);
bool GetOutInsnRWElemIdx(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 *p_pElemIdx, DSPU32 *p_pIdxOfIdx, DSPU32 p_u32CurrBus, MSG_INSN_RW_CORE_MEM_ISS &p_INST_RW_REQ);
bool GetOutInstrReqCurrBlock(DSPU32 *p_pBusNum, DSPU32 p_u32Block, MSG_INSN_RW_CORE_MEM_ISS &p_OUT_INST_RW_REQ);
void DelOutInsnRWReq(DSPU32 p_u32Block, DSPU32 p_u32Bank, DSPU32 p_u32ElemIdx, MSG_INSN_RW_CORE_MEM_ISS &p_INST_RW_REQ);

bool SrvCHxxReq_DC4(DSPU32 p_u32CHIdx, DSPU32 p_u32Mode);
bool GetBurstElemOnBank(DSPU32 p_u32Bank, DSPU32 *p_pElemIdx, MSG_BURST_RW_CORE_MEM_ISS &p_Burst_RW_REQ);
void DelBurstRWReq(DSPU32 p_u32Bank, DSPU32 p_u32ElemIdx, MSG_BURST_RW_CORE_MEM_ISS &p_BURST_RW_REQ);

void PutOutCoreMemReq_AC();
void GetRdOutCoreResult_AC_POST();
void SrvOutMemReq_AC();
void GenOutCoreMemStall();

#endif

#endif


