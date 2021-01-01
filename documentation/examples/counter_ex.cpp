#include <counter.enh.h>
#include <iostream>

int main()
{
	enh::Counter ct;						// 0s 0m 0h 0d
	enh::Counter state(25, 15, 12, 365);	// 25s 15m 12h 365d

	std::cout << ct.getSeconds() << " " << ct.getMinutes() << " "
		<< ct.getHours() << " " << ct.getDays() << " " 
		<< ct.getTotalHours() << "\n";

	std::cout << state.getSeconds() << " " << state.getMinutes() << " "
		<< state.getHours() << " " << state.getDays() << " " 
		<< state.getTotalHours() << "\n";

	std::cout << enh::Counter(2, 3, 4, 256) << "\n";
	std::cout << enh::Counter(2, 25, 6, 251).getString() << "\n";

	return 0;

}

/* ****************************************************************************

Output: 

0 0 0 0 0
25 15 12 365 8772
2s : 3min : 4hr : 256days ; 6148 total hours
2s : 25min : 6hr : 251days ; 6030 total hours

******************************************************************************/