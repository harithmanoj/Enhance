#include <VersionInfo.enh.h>
#include <iostream>

int main()
{
	constexpr enh::VersionInfo ver(VERSION_INFO_FIN(1, 2, 3, 789));
	constexpr enh::VersionInfo ver2(VERSION_INFO_BETA(25, 36, 2, 7895));
	constexpr const char* ver1_str = ver.string().data();
	constexpr const char* ver2_str = ver2.string().data();

	std::cout << ver.string() << " " << ver1_str << "\n"
		<< ver.getMajor() << " " << ver.getMinor() << " "
		<< ver.getRevision() << " " << ver.getBuild() << "\n"
		<< ver.toString() << "\n";

	std::cout << ver2.string() << " " << ver2_str << "\n"
		<< ver2.getMajor() << " " << ver2.getMinor() << " "
		<< ver2.getRevision() << " " << ver2.getBuild() << "\n"
		<< ver2.toString() << "\n";

	std::cout << enh::VersionInfo(1,2,3,4,enh::ReleaseType::RELEASE).string() 
		<< " " << "\n" 
		<< enh::VersionInfo(1,2,3,4,enh::ReleaseType::RELEASE).getMajor() << " "
		<< enh::VersionInfo(1,2,3,4,enh::ReleaseType::RELEASE).getMinor() << " "
		<< enh::VersionInfo(1,2,3,4,enh::ReleaseType::RELEASE).getRevision()
		<< " " 
		<< enh::VersionInfo(1,2,3,4,enh::ReleaseType::RELEASE).getBuild() << "\n"
		<< enh::VersionInfo(1,2,3,4,enh::ReleaseType::RELEASE).toString() << "\n";
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