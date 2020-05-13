#include <time_stamp.enh.h>
#include <iostream>

int main()
{
	enh::time_stamp time_array[] = { {}, {std::time(nullptr)}, {25,36,12} };

	time_array[1].addHour();
	time_array[1].addHour();

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


21 12 3

def : 21 : 12 : 03
format : sec, min, hour >>  03, 12, 21
format : secs min minutes, hour hours >>  03s 12 minutes, 21 hours
format : hour : min / 60 : sec / 3600 >>  21 : 12 / 60 : 03 / 3600
format : hour/min/sec >>  21/12/03
format : houro min' sec'' >>  21o 12' 03''

23 12 3

def : 23 : 12 : 03
format : sec, min, hour >>  03, 12, 23
format : secs min minutes, hour hours >>  03s 12 minutes, 23 hours
format : hour : min / 60 : sec / 3600 >>  23 : 12 / 60 : 03 / 3600
format : hour/min/sec >>  23/12/03
format : houro min' sec'' >>  23o 12' 03''

12 36 25

def : 12 : 36 : 25
format : sec, min, hour >>  25, 36, 12
format : secs min minutes, hour hours >>  25s 36 minutes, 12 hours
format : hour : min / 60 : sec / 3600 >>  12 : 36 / 60 : 25 / 3600
format : hour/min/sec >>  12/36/25
format : houro min' sec'' >>  12o 36' 25''


******************************************************************************/