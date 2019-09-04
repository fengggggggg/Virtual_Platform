/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 19:11
 * Update time   : 2019-05-24 10:50
 * Description   : 
******************************************************/

#include "initiator.h"
#include "target.h"
#include "router.h"

const unsigned int N_INIT = 4;
const unsigned int N_TARG = 4;

class Top
	: public sc_core::sc_module
{
public:

	Initiator	*initiator;
	Router		*router;
	Target		*memory;

	SC_CTOR(Top)
	{
		initiator = new Initiator("initiator");
		router = new Router("router");
		memory = new Target("memory");

		initiator->init_socket(router->targ_socket);
		router->init_socket(memory->targ_socket);	// 该语句报错：E120
	}
};


int sc_main(int argc, char* argv[])
{
	Top top("top");
	sc_start();
	return 0;
}
