#include <TimeStamp.enh.h>
#include <iostream>

int main()
{
	enh::TimeStamp time_array[] = { {}, {std::time(nullptr)}, {25,36,12} };

	time_array[1].addHours(230);
	time_array[1].addHours(230);

	for (auto i : time_array)
	{
		std::cout << i.getHours() << " " << i.getMinutes() << " " << i.getSeconds() << "\n\n";
		std::cout << "def : " << i.getStringTime() << "\n";

		std::string form[] = {
			"sec, min, hour",
			"secs min minutes, hour hours",
			"hour : min / 60 : sec / 3600",
			"hour/min/sec",
			"houro min' sec''"
		};

		for (auto j : form)
		{
			std::cout << "format : " << j << " >>  " << i.getStringTime(j) << "\n";
		}
		std::cout << "\n";
	}

	return 0;
}

/* ****************************************************************************

Output :


17 3 38

def : 17 : 03 : 38
format : sec, min, hour >>  38, 03, 17
format : secs min minutes, hour hours >>  38s 03 minutes, 17 hours
format : hour : min / 60 : sec / 3600 >>  17 : 03 / 60 : 38 / 3600
format : hour/min/sec >>  17/03/38
format : houro min' sec'' >>  17o 03' 38''

17 3 38

def : 17 : 03 : 38
format : sec, min, hour >>  38, 03, 17
format : secs min minutes, hour hours >>  38s 03 minutes, 17 hours
format : hour : min / 60 : sec / 3600 >>  17 : 03 / 60 : 38 / 3600
format : hour/min/sec >>  17/03/38
format : houro min' sec'' >>  17o 03' 38''

12 36 25

def : 12 : 36 : 25
format : sec, min, hour >>  25, 36, 12
format : secs min minutes, hour hours >>  25s 36 minutes, 12 hours
format : hour : min / 60 : sec / 3600 >>  12 : 36 / 60 : 25 / 3600
format : hour/min/sec >>  12/36/25
format : houro min' sec'' >>  12o 36' 25''



******************************************************************************/