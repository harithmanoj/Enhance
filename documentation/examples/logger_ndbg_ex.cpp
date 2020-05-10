
#define ENH_CLEAR_OP__

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
No log file is generated

Possible Output:

 now
not

******************************************************************************/