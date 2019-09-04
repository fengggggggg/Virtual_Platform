/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 19:11
 * Update time   : 2019-05-27 18:52
 * Description   : 
******************************************************/

#include "common.h"
#include "initiator.h"
#include "target.h"
#include "router.h"

int _main(int argc, char *argv[])
{
    Initiator*					initiator[N_INIT];
	Router*						router;
	Target*						memory[N_TARG];

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
		// initiator[i]->init_socket(router->targ_socket[i]);
		initiator[i]->init_socket(*router->targ_socket[i]);

	for (int i = 0; i < N_TARG; i++)
		router->init_socket[i]->bind(memory[i]->targ_socket );

	/////////////////////////////////
	// START
	/////////////////////////////////
	sc_core::sc_start();

	return 0;

}

int sc_main(int argc, char *argv[])
{
    try {
        return _main(argc, argv);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception occured" << std::endl;
        throw;
    }
    return 1;
}