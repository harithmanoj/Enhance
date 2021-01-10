#ifndef _DEBUG
#define _DEBUG
#endif

#include <logger.enh.h>
#include <iostream>

int foo()
{
	int i = 0;
	LOG_VALUE_E(i);		
	LOG_LINE_W;
	LOG_DESC_I("now returning");
	return i;
}

int main()
{
	LOG_LINE_FE;
	foo();
	LOG_LINE_E;
	LOG_DESC_W("dfghh");
	foo();
	std::cout REPLACE_I(<< "debug now") << " now\n";
	std::cout << REPLACE_AS_I("debug", "not");
	return 0;
}

/* ****************************************************************************
Possible Output:

The number 11452 (thread id) will vary with execution.
The file name depends on the file name of the code.

Console:

debug now now
debug

11452_thread_fn_main.log >

Thread id : 11452
thread first logging function main
				F:\logger_dbg_ex.cpp :     21              main
				F:\logger_dbg_ex.cpp :     13               foo  i = 0
				F:\logger_dbg_ex.cpp :     14               foo
				F:\logger_dbg_ex.cpp :     15               foo ::   now returning
				F:\logger_dbg_ex.cpp :     23              main
				F:\logger_dbg_ex.cpp :     24              main ::   dfghh
				F:\logger_dbg_ex.cpp :     13               foo  i = 0
				F:\logger_dbg_ex.cpp :     14               foo
				F:\logger_dbg_ex.cpp :     15               foo ::   now returning

******************************************************************************/