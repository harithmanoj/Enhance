#include <date_time.enh.h>
#include <iostream>


int main()
{
	enh::DateTime dt[] = {
		{}, {}, {}, {std::time(nullptr) + 30 * 24 * 60 * 60}, {
			22,6,2020,0,300,25,16,21
		}
	};

	dt[0].addHour();

	dt[1].add_day();

	for (auto i : dt)
	{
		std::cout << i.getHours() << " " << i.getMinutes() << " " << i.getSeconds() << "\n";
		std::cout << i.getDayOfWeek() << " " << i.getDayOfWeekString() << " " << i.getShortDayOfWeekString()
			<< " " << i.getDayOfMonth() << i.getDaySuperScript() << " " << i.getMonth() << " " << i.getMonthString()
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
23 45 47
3 Wednesday Wed 13th 4 May May 133

def : 23 : 45 : 47 ; Wednesday, 13th May 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 47:45:23; Wednesday, 13th - May - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 47 of the 45th minute of the 23th hour in the day of Wednesday which is 13th of May of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 47/45/23/Wed/13/May/2020
format :  hour : shDay, dd mm yyyy
>> 23 : Wed, 13 05 2020

22 45 47
4 Thursday Thu 14th 4 May May 133

def : 22 : 45 : 47 ; Thursday, 14th May 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 47:45:22; Thursday, 14th - May - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 47 of the 45th minute of the 22th hour in the day of Thursday which is 14th of May of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 47/45/22/Thu/14/May/2020
format :  hour : shDay, dd mm yyyy
>> 22 : Thu, 14 05 2020

22 45 47
3 Wednesday Wed 13th 4 May May 133

def : 22 : 45 : 47 ; Wednesday, 13th May 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 47:45:22; Wednesday, 13th - May - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 47 of the 45th minute of the 22th hour in the day of Wednesday which is 13th of May of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 47/45/22/Wed/13/May/2020
format :  hour : shDay, dd mm yyyy
>> 22 : Wed, 13 05 2020

22 45 47
5 Friday Fri 12th 5 June Jun 163

def : 22 : 45 : 47 ; Friday, 12th June 2020

format :  sec:min:hour; Day, ddth - Month - yyyy
>> 47:45:22; Friday, 12th - June - 2020
format :  sec of the minth minute of the hourth hour in the day of Day which is ddth of Month of yyyy
>> 47 of the 45th minute of the 22th hour in the day of Friday which is 12th of June of 2020
format :  sec/min/hour/shDay/dd/shMonth/yyyy
>> 47/45/22/Fri/12/Jun/2020
format :  hour : shDay, dd mm yyyy
>> 22 : Fri, 12 06 2020

21 16 25
0 Sunday Sun 22nd 6 July Jul 300

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
