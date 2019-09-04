#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>
//#define DEBUG_INFO_STREAM(info) std::cout<<info

extern std::ofstream flogout;

//#define LOG_OUTPUT			//turn off when no use log file
#define INFO_STREAM(info) std::cout<<info
#ifdef LOG_OUTPUT
//#define  DEBUG_INFO_STREAM(info)
//#define DEBUG_INFO_STREAM(info) std::cout<<info
#define DEBUG_INFO_STREAM(info) flogout<<info

#else
#define  DEBUG_INFO_STREAM(info)
#endif

typedef  unsigned int  DSPU32;
//#include "user_type.h"
#include "icache_type.h"
#include "pipe_fe_reg.h"
//#include "../pipe_fe_reg.h"


#endif
