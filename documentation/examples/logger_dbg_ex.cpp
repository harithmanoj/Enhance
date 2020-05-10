#ifndef _DEBUG
#define _DEBUG
#endif

#define ENH_OPTIMISATION  0

#include <logger.enh.h>
#include <iostream>

int foo()
{
	int i = 0;
	O4_LOG_VAL(i);		
	O3_LOG_LINE;
	O2_LOG_DESC("now returning");
	return i;
}

int main()
{
	O3_LOG_LINE;
	foo();
	O4_LOG_LINE;
	O3_LOG_DESC("dfghh");
	foo();
	std::cout O5_REPLACE(<< "debug now") << " now\n";
	std::cout << O5_REPLACE_AS("debug", "not");
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