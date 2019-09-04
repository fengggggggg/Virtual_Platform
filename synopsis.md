/*****************************************************************
 * Author        : feng
 * Creation time : 2019-06-07 08:09
 * Update time   : 2019-06-19 12:15
 * Description   : 
 *	---------------- Version v0.1--------------------------------
 *	1.	该实例包含若干个initiator，一个router以及若干个memory
 *		作为target，其数量在common.h中声明为N_INIT和N_TARG;
 *	2.	initiator定义在initiator.h文件中，包含一个init_socket，
 *		该socket由simple_initiator_socket实现，并连接到router
 *		的target_socket;
 *	3.	router定义在router.h文件中，包含若干个socket，该socket
 *		由simple_target_socket实现；
 *	4.	memory定义在target.h文件中，扮演target的角色，包含1个
 *		targ_socket，该socket连接到router的init_socket；
 *	5.	该版本能实现单向通信；
 *
 *	---------------- Version v0.2 ------------------------------
 *		将Router的socket全部改为simple_xxx_socket_tagged，并
 *		使用vector实现，保证和vgmn一致
 *
 *	---------------- Version v0.3 ------------------------------
 *		Router的定义和实现分离
 *
 *  ---------------- Version v0.4 ------------------------------
 *      定义-实现分离
 *
 *	---------------- Version v0.5 ------------------------------
 *		加入central_buffer
 *
 *	----------------- Version v0.6 -----------------------------
 *		将SC_THREAD改为SC_METHOD
 *
 *	----------------- Version v0.7 -----------------------------
 *	1.	加入静态路由表
 *	2.	修改payload字段
 *
 *	----------------- Version v0.10 ----------------------------
 *		实现了动态路由，多init、多targ下测试系统正常、正确运行
********************************************************************/
