/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 19:11
 * Update time   : 2019-06-16 20:31
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

	sc_core::sc_clock 	main_clk("MainCLK", 2, 0.5, 5);

	Router				router("router", N_INIT, N_TARG);

	Initiator 			init0("init0", 0x0);
	// Initiator			init1("init1", 0x1);
	
	Target				targ0("targ0", 0x0);
	Target				targ1("targ1", 0x1);
	Target				targ2("targ2", 0x2);
	Target				targ3("targ3", 0x3);

	init0.clk(main_clk);
	// init1.clk(main_clk);
	router.clk(main_clk);

	init0.init_socket(*router.targ_socket[0]);
	// init1.init_socket(*router.targ_socket[1]);

	targ0.targ_socket(*router.init_socket[0]);
	targ1.targ_socket(*router.init_socket[1]);
	targ2.targ_socket(*router.init_socket[2]);
	targ3.targ_socket(*router.init_socket[3]);

	sc_core::sc_start(20, SC_NS);

	return 0;
}

int sc_main(int argc, char *argv[])
{
	// 关闭IEEE警告
	sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated",
                                             sc_core::SC_DO_NOTHING );
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
