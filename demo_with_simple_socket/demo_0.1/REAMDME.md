/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 08:09
 * Update time   : 2019-05-27 18:52
 * Description   : Version v0.1
 *	---------------- Version v0.1--------------------------------
 *	1.	该实例包含若干个initiator，一个router以及若干个memory
 *		作为target，其数量在common.h中声明为N_INIT和N_TARG;
 *	2.	initiator定义在initiator.h文件中，包含一个init_socket，
 *		该socket连接到router的target_socket;
 *	3.	router定义在router.h文件中，包含若干个socket;
 *	4.	memory定义在target.h文件中，扮演target的角色，包含1个
 *		targ_socket，该socket连接到router的init_socket；
 *	5.	该版本能实现单向通信；
 *	6.	组件中socket为simple_xxx_socket
*******************************************************/
