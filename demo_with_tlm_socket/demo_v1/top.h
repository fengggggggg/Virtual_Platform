#ifndef TOP_H
#define TOP_H

#include "initiator.h"
#include "target.h"
#include "router.h"

const unsigned int N_TARG = 2;

SC_MODULE(Top)
{
	Initiator*			initiator;
	Router<N_TARG>*		router;
	Memory*				memory[N_TARG];

	SC_CTOR(Top)
	{
		// Instantiate components
		// 此处实例化两个Initiator
		initiator = new Initiator("initiator");
		//initiator[1] = new Initiator("initiator1");
		router		 = new Router<N_TARG>("router");
		for (int i = 0; i < N_TARG; i++)
		{
			char txt[20];
			sprintf(txt, "memory_%d", i);
			memory[i]   = new Memory(txt);
		}

		// Bind sockets
		// 此处socket绑定也需要修改
		initiator->init_socket.bind(router->targ_socket);
		//initiator[1]->socket.bind(router->target_socket[1]);

		for (int i = 0; i < N_TARG; i++)
			router->init_socket[i]->bind( memory[i]->targ_socket );
	}
};

#endif
