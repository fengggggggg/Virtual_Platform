#ifndef JTAG_LOAD_ELF_H
#define JTAG_LOAD_ELF_H

#include <string>
#include <vector>
using namespace std;
extern int ExtractPara(int argc, char **argv, vector<string> &sFile);
extern int ExtractAppPara(int argc, char ** argv, vector<string> &vFile);

extern int LoadFile(vector<string> &vFileName,void *pTop);
#endif



