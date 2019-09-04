/******************************************************************************
 * Author        : cai
 * Creation time : 2019-06-17 10:59
 * Update time   : 2019-06-19 12:15
 * Description   : 
******************************************************************************/

#ifndef __BASE_ROUTABLE_H__
#define __BASE_ROUTABLE_H__

#include "common.h"

//后期考虑将该结构体可以单独作为模板参数放入class Routing_Table中,作为不同路由表的路由项
typedef struct multi_node
{
	unsigned int data[6];
	struct multi_node* next;
}multi_node;

// 将路由表也设计一个基类,子类可以继承并实现他,形成RapidIO路由表,以太网交换表,DSP内部交换表
//以实现更好的代码复用性和封装性
class Base_Routing_Table
{
public:

	map<unsigned int, uint64> 	m_table;
	unsigned int multi_cast_table[256][6]; 
    //上面为组播路由表采取数组设计形式
	multi_node* head=NULL;
	//每一行为虚拟设备ID,端口0,1,2,3,4,其中端口位置1,则表示需要从该端口转发
    //将数组和链表形式都留下,以方便后期修改调整

public:

	Base_Routing_Table() {}
	~Base_Routing_Table() {}

	// 添加条目
	virtual void add_item(unsigned int targID, uint64 portID)
	{
		m_table.insert(pair<unsigned int, uint64>(targID, portID));
	}

	virtual void update_item(unsigned int targID, uint64 portID)
	{
		m_table[targID] = portID;
	}

	virtual void delete_item(unsigned int targID)
	{
		m_table.erase(targID);
	}

	// 清空路由表
	virtual void clear()
	{
		// 不释放内存
		m_table.clear();
		multi_node* p;
		while(head)
		{
			p=head;
			head=head->next;
			delete p;
		}

		// 释放内存
		// map<uint64, unsigned int> empty_map;
		// m_table.swap(empty_map);
		// m_table.clear();
	}

	virtual int size()
	{
		return m_table.size();
	}

	// 根据设备ID查找目标端口
	virtual int query_port(uint64 targID)
	{
		try {
			return m_table.at(targID);
		} catch (std::out_of_range& e) {
			std::cerr <<"this targetID: " <<targID << " not in routing table" << endl;
		} catch (...) {
			std::cerr << "Unknown exception occured" << endl;
		}
		return -1;
	}

	//根据端口查找设备ID
	virtual int query_addr(unsigned int portID)
	{
		map<unsigned int, uint64>::iterator it;
		for (it = m_table.begin(); it != m_table.end(); it++)
			if (it->second == portID)
				return it->first;
//		cout<<"this port "<<portID<<" not in routing table"<<endl;
		return -1;
	}

	virtual void print_table()
	{
		map<unsigned int, uint64>::iterator it;
		for (it = m_table.begin(); it != m_table.end(); it++)
			cout<<" "<<it->first<<" "<<it->second<<endl;
	}

//多播数据通过虚拟设备ID来表示
	virtual multi_node* query_multi_cast(unsigned int multi_id)
	{
		multi_node* p;
		// multi_node* q=new multi_head;
		if(head==NULL)
			return NULL;
		else
		{
			p=head;
			while(p)
			{
				if(p->data[0]==multi_id)
				{
					return p;
				}
				p=p->next;
			}
			return NULL;
		}	
	}

//可将该形参有int* 类型改为模板参数类型,例如用T代替,以实现通用多态,区别于特定多态(特定多态通常是指函数重载等)
	virtual void add_multi_cast(unsigned int* data)
	{
		multi_node* p;
		multi_node* q;
		if(head==NULL)
		{
			head=new multi_node;
			for(unsigned int i=0;i<6;i++)
			{
				head->data[i]=data[i];
			}
			head->next=NULL;
			return;
		}
		p=query_multi_cast(data[0]);
		if(p==NULL)
		{
			p=head;
			while(p->next)
			{
				p=p->next;
			}
			q=new multi_node;
			for(unsigned int i=0;i<6;i++)
			{
				q->data[i]=data[i];
			}
			q->next=NULL;
			p->next=q;
		}
		else
		{
			//修改该节点数据
			for(unsigned int i=0;i<6;i++)
			{
				p->data[i]=data[i];
			}
		}
	}

	virtual void delete_multi_cast(unsigned int multi_id)
	{
		multi_node* p;
		multi_node* q;
		if(head==NULL)
			return;
		p=head;
		if(p && p->data[0]==multi_id)
		{
			head=head->next;
			delete p;
		}
		else if(p)
		{
			while(p->next)
			{
				if(p->next->data[0]==multi_id)
				{
					q=p->next;
					p->next=p->next->next;
					delete q; 
				}
			}
		}
	}

	virtual void update_multi_cast(unsigned int* data)
	{
		multi_node* p;
		p=query_multi_cast(data[0]);
		if(p==NULL)
		{
			cout<<"not have this multi_cast"<<endl;
		}
		else
		{
			//修改该节点数据
			for(unsigned int i=0;i<6;i++)
			{
				p->data[i]=data[i];
			}
		}
	}

};

#endif
