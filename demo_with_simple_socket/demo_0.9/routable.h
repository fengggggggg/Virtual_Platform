/******************************************************************************
 * Author        : feng
 * Creation time : 2019-06-17 10:59
 * Update time   : 2019-06-17 10:59
 * Description   : 
******************************************************************************/

#ifndef __ROUTABLE_H__
#define __ROUTABLE_H__

#include "common.h"

class Routing_Table
{
private:

	map<uint64, unsigned int>	m_table;

public:

	Routing_Table(){}
	~Routing_Table(){}

	void add_item(uint64 targID, unsigned int portID)
	{
		m_table.insert(pair<uint64, unsigned int>(targID, portID));
	}

	unsigned int query(uint64 queryID)
	{
		try{
			return m_table.at(queryID);
		} catch(std::out_of_range& e) {
			std::cerr << queryID << " not int routing table" << endl;
		} catch(...) {
			std::cerr << "Unknown exception occured" << endl;
		}
		
		return 1;
	}

	void print_table()
	{
		for(unsigned int i = 0 ; i < m_table.size(); i++){
        	cout << "targID = " << i << " , portID = " << m_table.at(i) << endl;
		}
	}
};

#endif
