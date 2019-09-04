/*******************************************************************************
**                                                                            **
**        This confidential and proprietary software may be used only         **
**          as authorized by a licensing agreement from CoWare, Inc.          **
**      In the event of publication, the following notice is applicable:      **
**                                                                            **
**                      (c) COPYRIGHT 2005 COWARE, INC.                       **
**                            ALL RIGHTS RESERVED                             **
**                                                                            **
**    The entire notice above must be reproduced on all authorized copies.    **
**                                                                            **
*******************************************************************************/

/* $Id: sim_defines.h,v 1.2 2005/03/11 14:25:52 fiedler Exp $
 */
#ifndef _SIM_DEFINES_H
#define _SIM_DEFINES_H

/* ignore this line, just legacy */
// endianess mode doesn't affect result of assembler + linker, 
// just affect data format stored in the memory space of processor
#define MEMORY_ENDIANESS LISA_MEMORY_BIG_ENDIAN

#include "AlgoriLib/AlgoriLib.h"
#include "OMFuncs.h"

#endif


