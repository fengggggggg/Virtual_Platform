#ifndef ICACHE_TYPE_H_
#define ICACHE_TYPE_H_

typedef struct ictype_bool{
	bool val;

	ictype_bool(){
		val = false;
	}

	ictype_bool(bool v){
		val = v;
	}
	void reset(){
		val = false;
	}
	ictype_bool& operator =(const ictype_bool& rhs){
		val = rhs.val;
		return *this;
	}
//	ictype_bool& operator =(const bool& rhs){
//		val = rhs;
//		return *this;
//	}

	

	bool operator ==(const bool& rhs){
		return val == rhs;		
	}

	bool operator !(){
		return !val;
	}

	bool operator ||(const bool& rhs){
		return val || rhs;
	}

	bool operator || (const ictype_bool& rhs){
		return val || rhs.val;
	}

	bool operator &&(const bool& rhs){
		return val && rhs;
	}

//	bool operator && (const ictype_bool& rhs){
//		return val && rhs.val;
//	}
}ictype_bool;

#endif
