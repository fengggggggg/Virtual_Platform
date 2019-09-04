/******************************************************************************
 * Author        : cai
 * Creation time : 2019-05-27 09:51
 * Update time   : 2019-06-19 12:13
 * Description   : 
******************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc>
#include <fstream>
#include <queue>
#include <map>
#include <stdexcept>
#include <iostream>
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/passthrough_target_socket.h"
#include "tlm_utils/multi_passthrough_initiator_socket.h"
#include "tlm_utils/multi_passthrough_target_socket.h"
#include "tlm_utils/peq_with_cb_and_phase.h"
#include "tlm_utils/instance_specific_extensions.h"
#include "soclib_payload_extension.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace tlm;
using namespace tlm_utils;

#define band_width 32
#define protocol tlm::tlm_base_protocol_types 
// #define DEBUG_MODULE 1

typedef unsigned int DSPU32;

const unsigned int N_INIT = 4;
const unsigned int N_TARG = 4;

// enum {};

typedef struct 
{
	DSPU32 TT               = 0b00;     // 长2b，指示地址长度为8b/16b
	DSPU32 Ftype            = 0b0010;   // 包类型定义，请求/响应
	DSPU32 TargetID;                    // 目标地址
	DSPU32 SourceID;                    // 源地址
	DSPU32 Ttype            = 0b0100;   // 事务类型，读/写
	DSPU32 Extension        = 0b0000;
	DSPU32 TID              = 0x00;     // 事务ID
	//门铃包格式下,将TID视为SourceTID,主要用于发送中断消息
	//将Wdptr和Addr分别作为info(msb)和infor(lsb),分别为高八位和第八位
	DSPU32 OffsetAddress    = 0x0000;
	DSPU32 Wdptr            = 0b0;
	DSPU32 Addr             = 0b00;
	DSPU32 Data[64]         = {0};
} SRIO_FRAME;

/*User-defined protocol traits class in dmac*/
struct mydma_protocol_types{
	typedef tlm::tlm_generic_payload	tlm_payload_type;
	typedef tlm::tlm_phase				tlm_phase_type;
};

#endif
