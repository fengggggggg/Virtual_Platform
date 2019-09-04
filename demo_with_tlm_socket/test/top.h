/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 08:48
 * Update time   : 2019-05-23 10:14
 * Description   : 
******************************************************/

#ifndef __TOP_H__
#define __TOP_H__

#include "initiator.h"
#include "target.h"
#include "router.h"

const unsigned int N_INIT = 4;
const unsigned int N_TARG = 4;

class Top
	: public sc_core::sc_module
{
public:
	//Initiator*					initiator[N_INIT];
	//Router<N_INIT, N_TARG>*		router;
	//Target*						memory[N_TARG];
	Initiator	*initiator;
	Router		*router;
	Target		*memory;

	SC_CTOR(Top)
	{
		initiator = new Initiator("initiator");
		router = new Router("router");
		memory = new Target("memory");

		initiator->init_socket.bind(router->targ_socket);
		router->init_socket.bind(memory->targ_socket);
	}
};

#endif
