#ifndef _ICMA_H
#define _ICMA_H

/*------------------------------------------ typedef ------------------------------------------*/
enum tlm_icma_command 
{
	CMD_SWI_REQ,
	// 发送ICMA请求send_req_icma
	CMD_ICMA_REQ,
	// 发送ICMA响应send_resp_icma
	CMD_ICMA_RD_RESP,
	// 全写请求的响应信号
	CMD_ICMA_WR_RESP,
	CMD_RESERVED
};

typedef struct
{
	DSPU32 u32ElemNum; 
	// 在硬件设计中,若一个执行行中有一个原子访存操作,
	// 则该执行行中的所有访存操作都被认为是原子的。(不区分读写)
	bool bolAtom; 
	bool bolAllWrReq;

	RD_BUS_T icma_rbus[RD_BUS_MAX];
	WR_BUS_T icma_wbus[WR_BUS_MAX];
} ICMA_MEM;

typedef struct
{
	DSPU32 u32RdAddr[16];
	DSPU32 u32RdValue[16];
	DSPU32 u32ElemNum;
} ICMA_RD_RESULT;

typedef struct
{
	bool bolInUse;   // 该结构体是否正在被使用
	bool bolServed;  // 该结构体所包含的访问请求是否已经被服务
	DSPU32 u32DelayResp;
	DSPU32 u32DelaySrv;
	ICMA_MEM icma_mem;
	ICMA_RD_RESULT icma_rd_result;	
} ICMA_RESP_T;

typedef struct 
{
	bool bolInUse;			// 该结构体是否正在被使用(内容是否有效)
	bool bolInServe;			// 为true表示该消息已经被成功发送给目的核
	bool bolri_Served;			// 该结构体所包含的访问请求是否已经被服务
	bool bolro_Served;
	ICMA_MEM icma_mem;
	ICMA_RD_RESULT icma_rd_result;
} ICMA_REQ_T;

#define ICMA_WR_DEPTH 3

ICMA_REQ_T m_icma_req;  // 本核以指令方式访问簇内核间存储器
ICMA_RESP_T m_icma_resp;

#define ICMA_ARRIVED() ( m_icma_resp.bolInUse && !m_icma_resp.bolServed && ( m_icma_resp.u32DelaySrv == 0) )
/*-------------------------------------- implemention -------------------------------------*/

void reset_icma_resp();
void reset_icma_req();
void icma_resp_delay_countdown();
bool send_req_icma(ICMA_MEM *p_icma_mem);
bool send_resp_icma(ICMA_RD_RESULT *p_icma_rd_result);
bool send_resp_icma();

void GenICMAStall();
bool PermitICMA();
void RespICMA();
void SrvICMA_DC4();
void SrvICMAReq_AC();
void PutICMAReq_AC();
void SrvICMA_RdBus(RD_BUS_T *p_RdBus);
void SrvICMA_WrBus(WR_BUS_T *p_WrBus);

tlm::tlm_sync_enum nb_transport_bw_icma(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &delay);
tlm::tlm_sync_enum nb_transport_fw_icma(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &delay);


#endif
