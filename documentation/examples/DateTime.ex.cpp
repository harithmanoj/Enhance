#include <DateTime.enh.h>
#include <iostream>


int main()
{
	enh::DateTime dt[] = {
		{}, {}, {}, {std::time(nullptr)}, {
			22,6,2020,0,300,25,16,21
		}
	};

	dt[0].addHours(25);

	dt[1].addDay(200);

	dt[2].addDay(50);
	dt[2].addMinutes(360);

	for (auto i : dt)
	{
		std::cout << i.getHours() << " " << i.getMinutes() << " " << i.getSeconds() << "\n";
		std::cout << i.getDayOfWeek() << " " << i.getDayOfWeekString() << " " << i.getShortDayOfWeekString()
			<< " " << i.getDayOfMonth() << " " << i.getMonth() << " " << i.getMonthString()
			<< " " << i.getShortMonthString() << " " << i.getDayOfYear() << "\n\n";
		std::cout << "def : " << i.getStringDateTime() << "\n\n";

		std::string form[] = {
			"sec:min:hour; Day, ddth - Month - yyyy",
			"sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy",
			"sec/min/hour/shDay/dd/shMonth/yyyy",
			"hour : shDay, dd mm yyyy"
		};

		for (auto j : form)
			std::cout << "format :  " << j << " \n>> " << i.getStringDateTime(j) << "\n";
		std::cout << "\n";

	}

	return 0;
}


/* ****************************************************************************

Output :

20 38 12
1 Monday Mon 18 4 May May 167

def : 20 : 38 : 12 ; Monday, 18th May 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 12:38:20; Monday, 18th - May - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 12 of the 38th minute of the 20th hour in the day of Monday which is 18th of May of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 12/38/20/Mon/18/May/2020
format :  hour : shDay, dd mm yyyy
>> 20 : Mon, 18 05 2020

18 38 12
2 Tuesday Tue 9 11 December Dec 344

def : 18 : 38 : 12 ; Tuesday, 9th December 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 12:38:18; Tuesday, 09th - December - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 12 of the 38th minute of the 18th hour in the day of Tuesday which is 09th of December of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 12/38/18/Tue/09/Dec/2020
format :  hour : shDay, dd mm yyyy
>> 18 : Tue, 09 12 2020

0 44 12
3 Wednesday Wed 8 6 July Jul 226

def : 00 : 44 : 12 ; Wednesday, 8th July 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 12:44:00; Wednesday, 08th - July - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 12 of the 44th minute of the 00th hour in the day of Wednesday which is 08th of July of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 12/44/00/Wed/08/Jul/2020
format :  hour : shDay, dd mm yyyy
>> 00 : Wed, 08 07 2020

18 38 12
0 Sunday Sun 17 4 May May 137

def : 18 : 38 : 12 ; Sunday, 17th May 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 12:38:18; Sunday, 17th - May - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 12 of the 38th minute of the 18th hour in the day of Sunday which is 17th of May of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 12/38/18/Sun/17/May/2020
format :  hour : shDay, dd mm yyyy
>> 18 : Sun, 17 05 2020

21 16 25
0 Sunday Sun 22 6 July Jul 300

def : 21 : 16 : 25 ; Sunday, 22nd July 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 25:16:21; Sunday, 22nd - July - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 25 of the 16th minute of the 21th hour in the day of Sunday which is 22nd of July of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 25/16/21/Sun/22/Jul/2020
format :  hour : shDay, dd mm yyyy
>> 21 : Sun, 22 07 2020



******************************************************************************/
