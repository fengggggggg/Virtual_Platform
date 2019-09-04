/*
 * cfg.h
 *
 *  Created on: Jan 24, 2014
 *      Author: liugu
 */

#ifndef CFG_H_
#define CFG_H_

typedef struct cfg_data_type{
	unsigned int m_cycle_limit;
	bool m_randomize;
	unsigned int m_rand_seed;
	unsigned int m_pct_IAB_HALT;
	unsigned int m_pct_ExFlush;
	unsigned int m_ExFlushPC_limit;
	unsigned int m_pct_INT;
	bool m_nested_INT;
	unsigned int m_pct_dma;
	unsigned int m_pct_flush;


	cfg_data_type(){
		m_cycle_limit = 1000;
		m_randomize = false;
		m_rand_seed = 0;
		m_pct_IAB_HALT = 0;
		m_pct_ExFlush = 0;
		m_ExFlushPC_limit = 0x2000;
		m_nested_INT = false;
		m_pct_INT = 0;
		m_pct_dma = 0;
		m_pct_flush = 0;
	}
}cfg_data_type;




#endif /* CFG_H_ */
