#ifndef ASSISTANT_FUNCTION_H_
#define ASSISTANT_FUNCTION_H_

#include <bitset>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;
/*
	defines assistant functions for comfortable use
*/


/*trans a int array to a string, format it with 32bit, array[0] at right-side*/
//string Uintarray2string(unsigned int * ptr , int len, string & str);

//transfer a unsigned int to given length, for example intToBinString(3 , 5), return 00011
string intToBinString(unsigned int num, int len);


unsigned int uint2mask(const unsigned int uint);


unsigned int string2uint(const string s);


//unsigned int judge_ch_by_addr(const unsigned int ADDR, const unsigned int CORE_ID);


unsigned int myrand(const unsigned int bound);

#endif