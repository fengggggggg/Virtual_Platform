/******************************************************
 * Author        : feng
 * Creation time : 2019-05-16 19:11
 * Update time   : 2019-06-19 12:16
 * Description   : 
 * 	1.	Router必须定义在Initiator之前，否则Router中的
 * 		线程进程无法启动
******************************************************/

#include "include/common.h"
#include "include/init_adapater.h"
#include "include/targ_adapater.h"
#include "include/initiator.h"
#include "include/target.h"
#include "include/router.h"
#include "include/routable.h"

int _main(int argc, char *argv[])
{
	sc_core::sc_clock 	main_clk("MainCLK", 1, 0.5, 2);
	sc_core::sc_clock 	main_clk1("MainCLK1", 1, 0.5, 2);

	Router			    router("router0", 0, 5, 5);
	Router				router1("router1", 0, 3, 3);
	Router				router2("router2", 0, 2, 2);

	Initiator 			init0("init0", 0x0,0x0);
	Initiator 			init1("init1", 0x1,0xff);
	Initiator 			init2("init2", 0x2,0xff);
	Initiator 			init3("init3", 0x3,0xff);
	Initiator 			init4("init4", 0x4,0xff);
	Initiator 			init5("init5", 0x5,0xff);
	Initiator_adapter 			init_a0("init_a0", 0x0);
	Initiator_adapter 			init_a1("init_a1", 0x1);
	Initiator_adapter 			init_a2("init_a2", 0x2);
	Initiator_adapter 			init_a3("init_a3", 0x3);
	Initiator_adapter 			init_a4("init_a4", 0x4);
	Initiator_adapter 			init_a5("init_a5", 0x5);

	Target_adapter				targ_a0("targ_a0", 0x0);
	Target_adapter				targ_a1("targ_a1", 0x1);
	Target_adapter				targ_a2("targ_a2", 0x2);
	Target_adapter				targ_a3("targ_a3", 0x3);
	Target_adapter				targ_a4("targ_a4", 0x4);
	Target_adapter				targ_a5("targ_a5", 0x5);
	
	Target				targ0("targ0", 0x0);
	Target				targ1("targ1", 0x1);
	Target				targ2("targ2", 0x2);
	Target				targ3("targ3", 0x3);
	Target				targ4("targ4", 0x4);
	Target				targ5("targ5", 0x5);


	init0.clk(main_clk);
	init0.enum_clk(main_clk);
	init1.clk(main_clk);
	init1.enum_clk(main_clk);
	init2.clk(main_clk);
	init2.enum_clk(main_clk);
	init3.clk(main_clk);
	init3.enum_clk(main_clk);
	init4.clk(main_clk);
	init4.enum_clk(main_clk);
	init5.clk(main_clk);
	init5.enum_clk(main_clk);
	router.maintain_table_clk(main_clk);
	router.clk(main_clk1);
	router1.maintain_table_clk(main_clk);
	router1.clk(main_clk1);
	router2.maintain_table_clk(main_clk);
	router2.clk(main_clk1);

	init0.init_socket(init_a0.targ_socket);
	init1.init_socket(init_a1.targ_socket);
	init2.init_socket(init_a2.targ_socket);
	init3.init_socket(init_a3.targ_socket);
	init4.init_socket(init_a4.targ_socket);
	init5.init_socket(init_a5.targ_socket);

	init_a0.init_socket(*router.targ_socket[0]);
	init_a1.init_socket(*router.targ_socket[1]);
	init_a2.init_socket(*router.targ_socket[2]);
	init_a3.init_socket(*router.targ_socket[3]);
	init_a4.init_socket(*router1.targ_socket[0]);
	init_a5.init_socket(*router2.targ_socket[0]);

	targ_a0.targ_socket(*router.init_socket[0]);
	targ_a1.targ_socket(*router.init_socket[1]);
	targ_a2.targ_socket(*router.init_socket[2]);
	targ_a3.targ_socket(*router.init_socket[3]);
	targ_a4.targ_socket(*router1.init_socket[0]);
	targ_a5.targ_socket(*router2.init_socket[0]);
	
	(*router1.targ_socket[1])(*router.init_socket[4]);
	(*router1.init_socket[1])(*router.targ_socket[4]);
	(*router1.targ_socket[2])(*router2.init_socket[1]);
	(*router1.init_socket[2])(*router2.targ_socket[1]);


	targ_a0.init_socket(targ0.targ_socket);
	targ_a1.init_socket(targ1.targ_socket);
	targ_a2.init_socket(targ2.targ_socket);
	targ_a3.init_socket(targ3.targ_socket);
	targ_a4.init_socket(targ4.targ_socket);
	targ_a5.init_socket(targ5.targ_socket);



	sc_core::sc_start(100, SC_NS);

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
