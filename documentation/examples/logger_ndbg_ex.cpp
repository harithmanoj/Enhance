
#define ENH_CLEAR_OP__

#include <logger.enh.h>
#include <iostream>

int foo()
{
	int i = 0;
	LOG_VALUE_E(i);
	LOG_LINE_FE;
	LOG_DESC_I("now returning");
	LOG_DESC_W("warn");
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
	std::cout << REPLACE_AS_E("debug", "not");
	return 0;
}

/* ****************************************************************************
No log file is generated

Possible Output:

 now
not

******************************************************************************/