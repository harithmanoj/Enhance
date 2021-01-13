#include <date.enh.h>
#include <iostream>


int main()
{
	enh::Date dt[] = { {},{std::time(nullptr)}, {21,4,2020,2,75} };

	dt[1].addDay(250);

	for (auto i : dt)
	{
		std::cout << i.getDayOfWeek() << " " << i.getDayOfWeekString() << " " << i.getShortDayOfWeekString()
			<< " " << i.getDayOfMonth() << " " << i.getMonth() << " " << i.getMonthString()
			<< " " << i.getShortMonthString() << " " << i.getDayOfYear() << "\n\n";
		std::cout << "def : " << i.getStringDate() << "\n\n";
		std::string form[] = {
			"shDay, ddth mm yyyy",
			"Day, dd Month yyyy",
			"shDay, ddth shMonth yyyy",
			"dd/mm/yyyy",
			"ddth : Day, Month : yyyy"
		};
		for (auto j : form)
			std::cout << "Format : " << j << " >> " << i.getStringDate(j) << "\n";
	}

	return 0;
}


/* ****************************************************************************

Output :

0 Sunday Sun 17 4 May May 137

def : Sunday, 17th May 2020

Format : shDay, ddth mm yyyy >> Sun, 17th 05 2020
Format : Day, dd Month yyyy >> Sunday, 17 May 2020
Format : shDay, ddth shMonth yyyy >> Sun, 17th May 2020
Format : dd/mm/yyyy >> 17/05/2020
Format : ddth : Day, Month : yyyy >> 17th : Sunday, May : 2020
4 Thursday Thu 30 0 January Jan 38

def : Thursday, 30th January 2021

Format : shDay, ddth mm yyyy >> Thu, 30th 01 2021
Format : Day, dd Month yyyy >> Thursday, 30 January 2021
Format : shDay, ddth shMonth yyyy >> Thu, 30th Jan 2021
Format : dd/mm/yyyy >> 30/01/2021
Format : ddth : Day, Month : yyyy >> 30th : Thursday, January : 2021
2 Tuesday Tue 21 4 May May 75

def : Tuesday, 21st May 2020

Format : shDay, ddth mm yyyy >> Tue, 21st 05 2020
Format : Day, dd Month yyyy >> Tuesday, 21 May 2020
Format : shDay, ddth shMonth yyyy >> Tue, 21st May 2020
Format : dd/mm/yyyy >> 21/05/2020
Format : ddth : Day, Month : yyyy >> 21st : Tuesday, May : 2020

******************************************************************************/
