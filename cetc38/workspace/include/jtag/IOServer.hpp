#ifndef HOSTSERVER_HPP_
#define HOSTSERVER_HPP_
#include <map>
//#include <unistd.h>
/* request of redirecting monitor io to IDE */
//#define AT_WINDOWS
//#define REDIRECT_STDOUT
//#define REDIRECT_STDERR
//#define REDIRECT_STDIN
#define WRITE_MODE_STR "a"
#define READ_MODE_STR "r"

//#define SIM_MODEL 0
//#define EMU_MODEL 1

#define IOBUFFER_SIZE 5

//#define VECTOR_BUF
//#define TEMP_STDOUT_FILE "stdouttemp.log"
//#define TEMP_STDIN_FILE "stdintemp.log"
//extern char TEMP_STDIN_FILE[1024];
//extern char TEMP_STDOUT_FILE[1024];
//extern char PRJ_DIR[1024];
#include "../src/AlgoriLib/dsptypes.h"
/* Model headers :						           */
#include "hxproto.h"
using namespace std;
//#define  MULTI_CORE_PRINT_TO_FILE
enum OPMODE{ASC,BIN};
typedef struct OpenMode{
	int fd;
	OPMODE mode;
	char filename[200];
} OpenMode;

class sc_iss;
class IOHostServer{
  public:
	 IOHostServer();
	 IOHostServer(sc_iss *ower,unsigned int flag_addr, unsigned int sbuff_addr);
	 ~IOHostServer();
	 //void set_path(char* prj_dir, char* temp_stdin_file, char* temp_stdout_file);
	 /*if model_num is 0, simulator is selected as the current model
	 * if model_num is 1, simulator is selected as the current model
	 */
	 //void selectmodel(int model_num);
	 /* Set Debugger*/
	 void setdebugger(sc_iss *piss);
	 /*Set core index*/
	 //void setcoreindex(int coreIdx);
	 /* Set buffer address */
	 void setbufaddr(unsigned int addr);
	 /* Get buffer address */
	 unsigned int getbufaddr();
	 /* Set flag address  */
	 void setflagaddr(unsigned int addr);
	 /* Get flag address  */
	 unsigned int getflagaddr();
	 /* Set Debug Data address */
	 void setdebugdataaddr(unsigned int addr);
	 /* Print debug data */
	 //void print_debug_data();
	 int getstdoutflag();
	 int getstdinflag();
	 int getstdbufflag();
	 unsigned int* getplotparams();
	 vector<unsigned int>* getstdbuf();
	 void clrstdoutflag();
	 void clrstdinflag();
	 void clrstdbuf();
	/*basic functions: ReadMem(addr, &val) and WriteMem(addr, val)
	* All memory read/write functions are created by these two basic functions
	*/
	/*Read data of IOBUFFER_SIZE in advance from shared memory, put them into _iobuffer
	* this function should be called at the begining of exec()
	* IOBUFFER_SIZE is 4
	* buffer content:
	* 1. reading operation buffer(4 words): _global_pserver | op_code | fd | length 
	* 2. writing operation buffer(5 words): _global_pserver | op_code | fd | length | A word
	*/
	bool preread();
	/* Execute a command stored in the buffer 
	 * Return 1 if the command is executed, 
	 *        0 if there is no new command or buffer is null
	 */
	int exec();
	char* prj_dir();
	//char* temp_stdin_file();
	//char* temp_stdout_file();
  private:

	  bool _writeMemory(unsigned int start, unsigned int len, vector<unsigned int> *pvData);
	  bool _readMemory(unsigned int start, unsigned int len, vector<unsigned int> *pvData);

	  //int coreIndex;
  	/************************data member**************************/
    /* new command flag, 0:old command  1:new command */
  	unsigned int  _global_pserver_addr;
    /* shared buffer */
    unsigned int _sbuffer_addr;
	/* shared buffer */
    unsigned int _debug_data_addr;
    /* model */
    sc_iss* _owner;

	//int _model_num;/*0:simulator, 1:emulator*/
	/* file open mode list*/
	map<int, OpenMode> _opmod_list;
	//IO redirected files
	char PRJ_DIR[1024];
	//char TEMP_STDIN_FILE[1024];
	//char TEMP_STDOUT_FILE[1024];
	//MsgPool _msgpool;
	vector<unsigned int> _data_buf;
	vector<unsigned int> _iobuffer;
	int _cursor;
#ifdef 	MULTI_CORE_PRINT_TO_FILE
	FILE *fstdout,*fstdin;
#endif
	

	int _arr_len;
	int _stdbuf_flag;
	vector<unsigned int> _stdbuf;
	//{length, data type, step, 2D/3D, distance}
	//data type: 1(integer), 2(unsigned integer), 3(float)
	//2D/3D: 1(2D), 2(3D)
	unsigned int _plot_params[5];
	/**********************file-open-mode list operation ***********************/
	/*initialize _opmod_list, add stdin, stdout and stderr to the list*/
	void __init_opmodlist();
	/* add file-open-mode to _opmode_list */
	void __addmod(int fd, const char *filename, OPMODE mode);
	/* get file-open-mode of a file, ASC or BIN. If not found, return -1 */
	int __getmod(int fd);
	/* get file name*/
	void __getfilename(int fd, char *filename);
	/* delete file-open-mode from _opmode_list */
	int __delmod(int fd);
	/*Show all file-open modes*/
	void __showallmods();
	/************************memory read/write**************************/
	/*Write _iobuffer back to shared memory*/
	bool _writeback();
	/*Updating the place of cursor where _iobuffer is changed, it only can be moved ahead */
	void __mv_cursor(int new_place);
	/* Get flag value.
	 * That flag is equal to 0 means there is no new command in the shared buffer.
	 * That flag is equal to 1 means there is a new command in the shared buffer, hostserver can do it .
	 */
	int __getflag();
	/* Set flag value */
	void __setflag(int flag);
	/* Pick  operation code up from shared memory */
	int __op_code();
	/* Pick string length up from shared memory */
	int __len();
	/* Get the value at offset place  */
	int __val(unsigned int offset);
	/* Set the value at offset place */
	void __setval(unsigned int val, unsigned int offset);
	/* Allocate buffer space 
	 * pbuf will pointer to new buffer address, len is buffer size, return new buffer address
	 */
	char* __allocbuf(char **pbuf, unsigned int len);
	/* Release buffer space */
	void __freebuf(char *buf);
	/*
	 *Load a string in shared memory into a temporay buffer
	 *offset : the offset of string in shared memory
	 *tmp_buf: temporary buffer address
	 *len: string length
	 *mode: file open mode  ASC(ASCII) or BIN(Binary)
	 *Return the length(unit:bytes) of the string in the temporary buffer
	 */
	int __readbuf(unsigned int offset, char *tmp_buf, int len, OPMODE mode);

	/*
	 *Fill things in the  temporay buffer into the shared memory starting at offset
	 *offset : the offset of string in shared memory
	 *tmp_buf: temporary buffer address
	 *len: string length
	 *mode: file open mode  ASC(ASCII) or BIN(Binary)
	 *Return the length(unit:word) of the string  in the shared memory
	 */
	int __filbuf(unsigned int offset, char *tmp_buf, int len, OPMODE mode);
	/*
	 *Set result of a file operation, SUCCESS or ERROR, offset in shared memory is 0 .
	 */
	void __setresult(unsigned int ret);
	/*
	*Set string length, offset in shared memory is 1.
	*/
	void __setlen(unsigned int len);

	/*
	*Read/Write a single word from/to shared memory
	*/
	bool __readdata(unsigned int startaddr, unsigned int* data);
	bool __writedata(unsigned int startaddr, unsigned int data);
	/********************file operation***************************/
	int _open(const char *filename, int spoflag, ...);
	int _close(int fd);
	int _read (int fd, void *buf, size_t nbytes);
	int _write (int fd, const void *buf, size_t nbytes);
	int _ferror (int fd);
	int _eof (int fd);
	void _exit(int status);
	int _remove (const char *filename);
	int _rename(const char* oldfname, const char* newfname);
	long _lseek (int fd, long offset, int origin, OPMODE mod);
	long _tell (int fd, OPMODE mod);
	char* _getenv (const char *name, char *value, size_t len);
	int _system (const char *string);
	int _time (time_t *local, time_t *UTC);
#ifdef DSP_WIN32
	int _socket_create (unsigned int domain,unsigned int type, unsigned int protocol);
	int _socket_connect();
	int _socket_send();
	int _socket_recv();
	int _socket_close();
	int _socket_shutdown();
	int _socket_bind();
	int _socket_listen();
	int _socket_accept();

	int _socket_setopt();
	int _socket_sendto();
	int _socket_recvfrom();
	int _socket_getlasterror();
#endif
private: int sock_last_error;
};
#endif /*HOSTSERVER_HPP_*/
