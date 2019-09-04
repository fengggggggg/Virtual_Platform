/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 08:48
 * Update time   : 2019-05-17 10:28
 * Description   : 
******************************************************/

#ifndef __TOP_H__
#define __TOP_H__

#include "initiator.h"
#include "target.h"
#include "router.h"

const unsigned int N_INIT = 2;
const unsigned int N_TARG = 4;

SC_MODULE(Top)
{
	Initiator*			initiator[N_INIT];
	Router<N_TARG>*		router;
	Memory*				memory[N_TARG];

	SC_CTOR(Top)
	{
		// Instantiate components
		for (int i = 0; i < N_INIT; i++)
		{
			char init_name[20];
			sprintf(init_name, "init_%d", i);
			initiator[i] = new Initiator(init_name);
		}

		router = new Router<N_TARG>("router");

		for (int i = 0; i < N_TARG; i++)
		{
			char targ_name[20];
			sprintf(targ_name, "targ_%d", i);
			memory[i] = new Memory(targ_name);
		}

		// Bind sockets
		initiator[0]->init_socket.bind(router->targ_socket);
		initiator[1]->init_socket.bind(router->targ_socket_2);

		for (int i = 0; i < N_TARG; i++)
			router->init_socket[i]->bind( memory[i]->targ_socket );
	}
};

#endif
