/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 08:48
 * Update time   : 2019-05-27 18:53
 * Description   : 
******************************************************/

#ifndef __TOP_H__
#define __TOP_H__

#include "common.h"
#include "initiator.h"
#include "target.h"
#include "router.h"

class Top
	: public sc_core::sc_module
{
protected:

	SC_HAS_PROCESS(Top);

public:

	Initiator*					initiator[N_INIT];
	Router*						router;
	Target*						memory[N_TARG];

	Top(sc_core::sc_module_name name)
	{
		for (int i = 0; i < N_INIT; i++)
		{
			char init_name[20];
			sprintf(init_name, "init_%d", i);
			initiator[i] = new Initiator(init_name);
		}

		router = new Router("router");

		for (int i = 0; i < N_TARG; i++)
		{
			char targ_name[20];
			sprintf(targ_name, "targ_%d", i);
			memory[i] = new Target(targ_name);
		}

		for (int i = 0; i < N_INIT; i++)
			initiator[i]->init_socket(router->targ_socket[i]);

		for (int i = 0; i < N_TARG; i++)
			router->init_socket[i]->bind( memory[i]->targ_socket );
	}
};

#endif
