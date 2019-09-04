/*
 *extension.h
 *
 *Create on:	JUL 3, 2014
 *Author:	liugu
*/
#ifndef EXTENSION_H_
#define EXTENSION_H_

#include <tlm.h>

struct CoreID_extension: tlm::tlm_extension<CoreID_extension>
{
	CoreID_extension():core_id(0){}

	virtual tlm_extension_base *clone() const{
		CoreID_extension *t = new CoreID_extension;
		t->core_id = this->core_id;
		return t;
	}

	virtual void copy_from(tlm_extension_base const &ext){
		core_id = static_cast<CoreID_extension const &>(ext).core_id;
	}

	unsigned int core_id;		//Identifier of core which create this transaction
};

#endif
