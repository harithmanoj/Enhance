#include <Tristate.enh.h>
#include <iostream>

enh::Tristate foo(std::string len)
{
	static bool error = false;
	if (error)
		return enh::Tristate::PREV_ERR;
	if (len.empty())
	{
		error = true;
		return enh::Tristate::ERROR;
	}
	std::cout << len << "\n";

	return enh::Tristate::GOOD;

}

int main()
{
	std::cout << std::boolalpha << !!foo("first") << "\n";
	std::cout << (foo({}) == enh::Tristate::ERROR) << "\n";
	std::cout << (foo("kk") == enh::Tristate::PREV_ERR) << "\n";
	std::cout << !(enh::Tristate::ERROR) 
		<< "\n" << !(enh::Tristate::PREV_ERR) 
		<< "\n" << !(enh::Tristate::GOOD);
	return 0;
}


/* ****************************************************************************

Output :

first
true
true
true
true
true
false

******************************************************************************/