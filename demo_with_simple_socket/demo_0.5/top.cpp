/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 19:11
 * Update time   : 2019-06-12 11:20
 * Description   : 
 * 	1.	Router必须定义在Initiator之前，否则Router中的
 * 		线程进程无法启动
******************************************************/

#include "common.h"
#include "initiator.h"
#include "target.h"
#include "router.h"

int _main(int argc, char *argv[])
{
	Router		router("router", N_INIT, N_TARG);

	Initiator 	init0("init0");
	Initiator	init1("init1");
	
	Target		targ0("targ0");
	Target		targ1("targ1");

	init0.init_socket(*router.targ_socket[0]);
	init1.init_socket(*router.targ_socket[1]);

	targ0.targ_socket(*router.init_socket[0]);
	targ1.targ_socket(*router.init_socket[1]);


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
