/******************************************************
 * Author        : feng
 * Creation time : 2019-06-07 08:09
 * Update time   : 2019-06-12 11:30
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
 *	1.	(未实现)加入一个FIFO，实现互斥锁机制
 *		--	之前版本中，多init时，各init会争抢向router发送，导致
 *			出现莫名的问题
 *		--	加入FIFO，实现按时间入队，按时间出队，在入队时可能
 *			需要实现互斥锁
 *	2.	当前问题:
 *		--	整个demo中包含两个进程，分别是initiator中的进程
 *			thread_process和Router中的进程ecexLoop。
 *		--	首先启动的是execLoop，由于buffer为空无法pop，
 *			使用wait将进程挂起，并等待一个信号量m_cmd_received。
 *		--	随后启动thread_process生成transaction并push到buffer中,
 *			并且在push成功后能够正确的发送信号通知m_cmd_received。
 *		--	正常情况下，m_cmd_received接收到信号后，execLoop会重新
 *			激活并尝试pop。但是该demo中execLoop进程出现问题而没有
 *			退出wait状态，即没有退出挂起状态
 *	3.	分析
 *		i.	第一个可能的原因是execLoop进程没有正确接受到m_cmd_received，
 *			这个不太可能且极难调试
 *		ii.	第二个可能的原因是：之所以soclib搞出tlmdt，是因为tlm不支持
 *			分布式时间建模(有待验证)，猜测可能是因为tlm不支持同一时间的两个进程的
 *			并行执行，即：当thread_process开始执行时，execLoop从挂起状态
 *			被杀死，因此即使接收到m_cmd_received信号也无法正常执行
 *
 *	4.	问题已解决：execLoop挂起后，将执行权交给thread_process，thread_process在
 *					发出transaction后，并没有将执行权交还execLoop，所以即使execLoop
 *					收到notify，也还是无法重新唤醒。
 *		解决办法：在thread_process发出事务后，将其挂起一段时间，这段时间足以将事务
 *				  正确路由并返回response状态

 *  ----------------- Version v0.6 -----------------------------
        清晰化Initiator的进程

 *	----------------- Version v0.7 -----------------------------
 *		将SC_THREAD改为SC_METHOD
*******************************************************/
