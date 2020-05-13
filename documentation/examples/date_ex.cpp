#include <date.enh.h>
#include <iostream>


int main()
{
	enh::date dt[] = { {},{std::time(nullptr) + 3600 * 35 * 24}, {21,4,2020,2,75} };

	for (auto i : dt)
	{
		std::cout << i.getDayOfWeek() << " " << i.getDayOfWeekString() << " " << i.getShortDayOfWeekString()
			<< " " << i.getDayOfMonth() << i.getDaySuperScript() << " " << i.getMonth() << " " << i.getMonthString()
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

3 Wednesday Wed 13th 4 May May 133

def : Wednesday, 13th May 2020

Format : shDay, ddth mm yyyy >> Wed, 13th 05 2020
Format : Day, dd Month yyyy >> Wednesday, 13 May 2020
Format : shDay, ddth shMonth yyyy >> Wed, 13th May 2020
Format : dd/mm/yyyy >> 13/05/2020
Format : ddth : Day, Month : yyyy >> 13th : Wednesday, May : 2020
3 Wednesday Wed 17th 5 June Jun 168

def : Wednesday, 17th June 2020

Format : shDay, ddth mm yyyy >> Wed, 17th 06 2020
Format : Day, dd Month yyyy >> Wednesday, 17 June 2020
Format : shDay, ddth shMonth yyyy >> Wed, 17th Jun 2020
Format : dd/mm/yyyy >> 17/06/2020
Format : ddth : Day, Month : yyyy >> 17th : Wednesday, June : 2020
2 Tuesday Tue 21st 4 May May 75

def : Tuesday, 21st May 2020

Format : shDay, ddth mm yyyy >> Tue, 21st 05 2020
Format : Day, dd Month yyyy >> Tuesday, 21 May 2020
Format : shDay, ddth shMonth yyyy >> Tue, 21st May 2020
Format : dd/mm/yyyy >> 21/05/2020
Format : ddth : Day, Month : yyyy >> 21st : Tuesday, May : 2020

******************************************************************************/
