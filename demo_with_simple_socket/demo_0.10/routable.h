/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-17 10:59
 * Update time   : 2019-06-19 12:15
 * Description   : 
******************************************************************************/

#ifndef __ROUTABLE_H__
#define __ROUTABLE_H__

#include "common.h"

class Routing_Table
{
private:

	map<unsigned int, uint64> 	m_table;

public:

	Routing_Table() {}
	~Routing_Table() {}

	// 添加条目
	void add_item(unsigned int portID, uint64 targID)
	{
		m_table.insert(pair<unsigned int, uint64>(portID, targID));
	}

	void update_item(unsigned int portID, uint64 targID)
	{
		m_table[portID] = targID;
	}

	// 清空路由表
	void clear()
	{
		// 不释放内存
		m_table.clear();

		// 释放内存
		// map<uint64, unsigned int> empty_map;
		// m_table.swap(empty_map);
		// m_table.clear();
	}

	int size()
	{
		return m_table.size();
	}

	// 查询
	int query_port(uint64 queryID)
	{
		map<unsigned int, uint64>::iterator it;
		for (it = m_table.begin(); it != m_table.end(); it++)
			if (it->second == queryID)
				return it->first;
		return -1;
	}

	int query_addr(unsigned int portID)
	{
		try {
			return m_table.at(portID);
		} catch (std::out_of_range& e) {
			std::cerr << portID << " not in routing table" << endl;
		} catch (...) {
			std::cerr << "Unknown exception occured" << endl;
		}
		return -1;
	}

	void print_table()
	{
		for (unsigned int i = 0; i < m_table.size(); i++) {
			cout << "targID = " << i << " , portID = " << m_table.at(i) << endl;
		}
	}
};

#endif
