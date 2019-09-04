/******************************************************
 * Author        : feng
 * Creation time : 2019-05-17 08:09
 * Update time   : 2019-05-17 08:20
 * Description   : Version v0.2
 *	---------------- Version v0.1--------------------------------
 *	1.	该例程包含一个initiator，一个router以及4个memory作为target
 *	2.	initiator定义在initiator.h文件中，仅包含一个输出socket，
 *		该socket连接到router的target_socket
 *	3.	router定义在router.h文件中，包含5个socket，其中1个
 *		target_socket绑定到initiator的socket,
 *		4个initiator_socket绑定到4个memory的socket
 *	4.	memory定义在target.h文件中，扮演target的角色，包含1个socket
 *	5.	该版本能实现单向通信
 *
 *	---------------- Version v0.2-------------------------
 *	1.	修改Router，主要目标是实现多Initiator通信
*******************************************************/
