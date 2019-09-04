/*
 *protocol.h
 *
 *Created on:	Jun 4, 2014
 *Author:	liugu
*/
#ifndef PROTOCOL_CORE_MMAC_H_
#define PROTOCOL_CORE_MMAC_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include <tlm.h>

struct mmac_protocol_types{
	typedef tlm::tlm_generic_payload	tlm_payload_type;
	typedef tlm::tlm_phase			tlm_phase_type;
};

//phase between icache<==>mmac
DECLARE_EXTENDED_PHASE(BEGIN_REQ_CACHE_LINE);	//icache==>mmac
DECLARE_EXTENDED_PHASE(END_REQ_CACHE_LINE);	//mmac==>icache
DECLARE_EXTENDED_PHASE(BEGIN_RESP_CACHE_LINE);	//mmac==>icache
DECLARE_EXTENDED_PHASE(END_RESP_CACHE_LINE);	//icache==>mmac
//phase between icache<===>shared_sram
DECLARE_EXTENDED_PHASE(BEGIN_REQ_CACHE_LINE_SHARED_SRAM_UP);	//icache==>share_sram
DECLARE_EXTENDED_PHASE(BEGIN_REQ_CACHE_LINE_SHARED_SRAM_DOWN);	//icache==>share_sram
DECLARE_EXTENDED_PHASE(END_REQ_CACHE_LINE_SHARED_SRAM);		//share_sram==>icache
DECLARE_EXTENDED_PHASE(BEGIN_RESP_CACHE_LINE_SHARED_SRAM);	//icache==>share_sram
DECLARE_EXTENDED_PHASE(END_RESP_CACHE_LINE_SHARED_SRAM);	//share_sram==>icache

#define PROTOCOL_TYPE mmac_protocol_types

#endif

