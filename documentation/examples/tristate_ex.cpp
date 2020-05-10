#include <common.enh.h>
#include <iostream>

enh::tristate foo(std::string len)
{
	static bool error = false;
	if (error)
		return enh::tristate::PREV_ERR;
	if (len.empty())
	{
		error = true;
		return enh::tristate::ERROR;
	}
	std::cout << len << "\n";

	return enh::tristate::GOOD;

}

int main()
{
	std::cout << std::boolalpha << !!foo("first") << "\n";
	std::cout << (foo({}) == enh::tristate::ERROR) << "\n";
	std::cout << (foo("kk") == enh::tristate::PREV_ERR) << "\n";
	
}


/* ****************************************************************************

Output :

first
true
true
true

******************************************************************************/