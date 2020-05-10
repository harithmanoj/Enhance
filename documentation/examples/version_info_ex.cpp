#include <framework.enh.h>
#include <iostream>

int main()
{
	constexpr enh::version_info ver(VERSION_INFO_FIN(1, 2, 3, 789));
	constexpr enh::version_info ver2(VERSION_INFO_BETA(25, 36, 2, 7895));
	constexpr const char* ver1_str = ver.string().data();
	constexpr const char* ver2_str = ver2.string().data();

	std::cout << ver.string() << " " << ver1_str << "\n"
		<< ver.get_major() << " " << ver.get_minor() << " "
		<< ver.get_revision() << " " << ver.get_build() << "\n"
		<< ver.to_string() << "\n";

	std::cout << ver2.string() << " " << ver2_str << "\n"
		<< ver2.get_major() << " " << ver2.get_minor() << " "
		<< ver2.get_revision() << " " << ver2.get_build() << "\n"
		<< ver2.to_string() << "\n";

	std::cout << enh::version_info(1,2,3,4,enh::rel_type::RELEASE).string() 
		<< " " << "\n" 
		<< enh::version_info(1,2,3,4,enh::rel_type::RELEASE).get_major() << " " 
		<< enh::version_info(1,2,3,4,enh::rel_type::RELEASE).get_minor() << " "
		<< enh::version_info(1,2,3,4,enh::rel_type::RELEASE).get_revision() 
		<< " " 
		<< enh::version_info(1,2,3,4,enh::rel_type::RELEASE).get_build() << "\n"
		<< enh::version_info(1,2,3,4,enh::rel_type::RELEASE).to_string() << "\n";
	return 0;
}

/* ****************************************************************************
Output:

1.2.3.789.fin 1.2.3.789.fin
1 2 3 789
1.2.3.789.fin
25.36.2.7895.beta 25.36.2.7895.beta
25 36 2 7895
25.36.2.7895.beta

1 2 3 4
1.2.3.4.fin

******************************************************************************/