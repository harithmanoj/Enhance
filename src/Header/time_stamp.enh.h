/** ***************************************************************************
	\file time_stamp.enh.h

	\brief File for date-time class.

	Created 12 May 2020

	This file is part of Enhance.

	Copyright 2020 Harith Manoj <harithpub@gmail.com>

	Enhance is free software : you can redistribute it and /or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Enhance is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Enhance. If not, see < https://www.gnu.org/licenses/>.


******************************************************************************/

#ifndef TIME_STAMP_ENH_H

#define TIME_STAMP_ENH_H						time_stamp.enh.h

#include "general.enh.h"
#include <ctime>
#include <string>
#include <ostream>

namespace enh
{
	/**
		\brief Structure to encapsulate time parameters sec, hrs, minutes
	*/
	struct time_
	{
		/**
			\brief Seconds part of time. [0,60]
		*/
		unsigned short seconds;

		/**
			\brief Minutes part of time. [0,59]
		*/
		unsigned short minutes;

		/**
			\brief Hours part of time. [0,23]
		*/
		unsigned short hours;
	};

	/**	
		\brief Structure to encapsulate calender parameters, date, month, year
	*/
	struct date_
	{
		/**
			\brief The day of the month. [1,31]
		*/
		unsigned short day;

		/**
			\brief The month since january. [0,11]
		*/
		unsigned short month;

		/**
			\brief The Year.

			AD is positive.
			BC is negative.
		*/
		long year;

		/**
			\brief Days after Sunday. [0,6]
		*/
		unsigned short wkday;
	};


	/**
		\brief Class that uniquely identifies date-time
	*/
	class time_stamp
	{
		/**
			\brief Seconds part of time. [0,60]
		*/
		unsigned short seconds;

		/**
			\brief Minutes part of time. [0,59]
		*/
		unsigned short minutes;

		/**
			\brief Hours part of time. [0,23]
		*/
		unsigned short hours;

		/**
			\brief The day of the month. [1,31]
		*/
		unsigned short day;

		/**
			\brief The month since january. [0,11]
		*/
		unsigned short month;

		/**
			\brief The Year.

			AD is positive.
			BC is negative.
		*/
		long year;

		/**
			\brief Days after Sunday. [0,6]
		*/
		unsigned short wkday;

		/**
			\brief Add year to time_stamp
		*/
		inline void add_year()
		{
			++year;
		}

		/**
			\brief Add month to time_stamp
		*/
		inline void add_month()
		{
			if (month == 11)
			{
				month = 0;
				++year;
			}
			else
				++month;
		}

	public:

		/**
			\brief Default constructor of the class.

			Sets date-time to current date-time.

			<h3>Overloads</h3>
			-# <code>explicit inline constexpr time_stamp(time_t t) noexcept;
			</code>\n
			-# <code>inline constexpr time_stamp(date_ dt, time_ t) noexcept;
			</code>\n
		*/
		inline time_stamp() noexcept
		{
			auto t = std::time(nullptr);
			auto tm_time = std::localtime(t);
			seconds = tm_time->tm_sec;
			minutes = tm_time->tm_min;
			hours = tm_time->tm_hour;
			day = tm_time->tm_mday;
			month = tm_time->tm_mon;
			year = tm_time->tm_year + 1900;
			wkday = tm_time->tm_wday;
		}

		/**
			\brief Parameterised constructor constructor of the class.

			Sets date-time to date-time indicated by the argument.

			<h3>Overloads</h3>
			-# <code>inline constexpr time_stamp() noexcept;</code>\n
			-# <code>inline constexpr time_stamp(date_ dt, time_ t) noexcept;
			</code>\n
		*/
		explicit inline time_stamp(
			time_t t /**< : <i>in</i> : The time to set the object to.*/
		) noexcept
		{
			auto tm_time = std::localtime(t);
			seconds = tm_time->tm_sec;
			minutes = tm_time->tm_min;
			hours = tm_time->tm_hour;
			day = tm_time->tm_mday;
			month = tm_time->tm_mon;
			year = tm_time->tm_year + 1900;
			wkday = tm_time->tm_wday;
		}

		/**
			\brief Parameterised constructor constructor of the class.

			Sets date-time to date-time indicated by the argument.

			<h3>Overloads</h3>
			-# <code>inline constexpr time_stamp() noexcept;</code>\n
			-# <code>explicit inline constexpr time_stamp(time_t) noexcept;
			</code>\n
		*/
		inline time_stamp(
			date_ dt /**< : <i>in</i> : Date to set the object to.*/,
			time_ t  /**< : <i>in</i> : Time to set the object to.*/
		) noexcept : seconds(t.seconds),
			minutes(t.minutes), hours(t.hours), day(dt.day), month(dt.month),
			year(dt.year), wkday(dt.wkday) {}

		/**
			\brief Sets date-time to current date-time.

			<h3>Overloads</h3>
		*/
		inline void set() noexcept
		{
			auto t = std::time(nullptr);
			auto tm_time = std::localtime(t);
			seconds = tm_time->tm_sec;
			minutes = tm_time->tm_min;
			hours = tm_time->tm_hour;
			day = tm_time->tm_mday;
			month = tm_time->tm_mon;
			year = tm_time->tm_year + 1900;
			wkday = tm_time->tm_wday;
		}

		/**
			\brief Sets date-time to date-time indicated by the argument.

			<h3>Overloads</h3>
		*/
		inline void set(
			time_t t /**< : <i>in</i> : The time to set the object to.*/
		) noexcept
		{
			auto tm_time = std::localtime(t);
			seconds = tm_time->tm_sec;
			minutes = tm_time->tm_min;
			hours = tm_time->tm_hour;
			day = tm_time->tm_mday;
			month = tm_time->tm_mon;
			year = tm_time->tm_year + 1900;
			wkday = tm_time->tm_wday;
		}

		/**
			\brief Sets date-time to date-time indicated by the argument.

			<h3>Overloads</h3>
		*/
		inline bool set(
			date_ dt /**< : <i>in</i> : Date to set the object to.*/,
			time_ t  /**< : <i>in</i> : Time to set the object to.*/
		) noexcept
		{
			return set(dt) && set(t);
		}

		/**
			\brief Sets time to time indicated by the argument.

			<h3>Overloads</h3>
		*/
		inline bool set(
			time_ t  /**< : <i>in</i> : Time to set the object to.*/
		) noexcept
		{
			if (!isConfined(t.seconds, 0, 60, true, true))
				return false;
			if (!isConfined(t.minutes, 0, 59, true, true))
				return false;
			if (!isConfined(t.hours, 0, 23, true, true))
				return false;

			seconds = t.seconds;
			minutes = t.minutes;
			hours = t.hours;

			return true;
		}

		/**
			\brief Sets date to date indicated by the argument.

			<h3>Overloads</h3>
		*/
		inline bool set(
			date_ dt /**< : <i>in</i> : Date to set the object to.*/
		) noexcept
		{
			if (!isConfined(dt.day, 1, 31, true, true))
				return false;
			if (!isConfined(dt.month, 0, 11, true, true))
				return false;
			if (!isConfined(dt.wkday, 0, 6, true, true))
				return false;

			day = dt.day;
			month = dt.month;
			year = dt.year;
			wkday = dt.wkday;
			return true;
		}

		/**
			\brief The maximum date for that month.
		*/
		static constexpr unsigned short month_limit(
			unsigned short mnth /**< : <i>in</i> : The month count.*/,
			long yr /**< : <i>in</i> : The year count.*/
		) noexcept
		{
			switch (mnth)
			{

			case 0: 
				return 31;

			case 1: 
			{
				if ((yr % 4) == 0)
					return 29;
				else
					return 28;
			}

			case 2:
				return 31;

			case 3:
				return 30;

			case 4:
				return 31;

			case 5:
				return 30;

			case 6:
				return 31;

			case 7:
				return 31;

			case 8:
				return 30;

			case 9:
				return 31;

			case 10:
				return 30;

			case 11:
				return 31;

			default:
				return 165;
				break;
			}
		}

		/**
			\brief The week day after day_count number of days from week.
		*/
		static constexpr unsigned short week_day_increments(
			unsigned short week /*< : <i>in</i> : The current week day.*/,
			unsigned long day_count /*< : <i>in</i> : The number of days to add.*/
		) noexcept
		{
			unsigned long long tmp = day_count;
			tmp += week;
			return tmp % 7;
		}

		/**
			\brief Add one day (reflects in month and year if day exceeds month limit)
		*/
		inline void add_day()
		{
			if (wkday == 6)
				wkday = 0;
			else
				++wkday;

			if (day == month_limit(month, year))
			{
				add_month();
				day = 1;
			}
			else
				++day;
		}

		/**
			\brief Add one hour to time_stamp.
		*/
		inline void add_hour()
		{
			if (hour == 23)
			{
				hour = 0;
				add_day();
			}
			else
				++hour;
		}

		/**
			\brief Add one minute to time_stamp.
		*/
		inline void add_minutes()
		{
			if (minutes == 59)
			{
				minutes = 0;
				add_hour();
			}
			else
				++minutes;
		}

		/**
			\brief Add one seconds to time_stamp.
		*/
		inline void add_seconds()
		{
			if (seconds == 59)
			{
				seconds = 0;
				add_minutes();
			}
			else
				++seconds;
		}


		/**
			\brief Get all Date componants.
		*/
		inline date_ getDate() const noexcept
		{
			return { day,month,year,wkday };
		}

		/**
			\brief Get all Times componants.
		*/
		inline time_ getTime() const noexcept
		{
			return { hours,minutes,seconds };
		}

		/**
			\brief Get seconds part of date-time.
		*/
		unsigned short getSeconds() const noexcept
		{
			return seconds;
		}

		/**
			\brief Get minutes part of date-time.
		*/
		unsigned short getMinutes() const noexcept
		{
			return minutes;
		}

		/**
			\brief Get hours part of date-time.
		*/
		unsigned short getHours() const noexcept
		{
			return hours;
		}

		/**
			\brief Get day part of date-time.
		*/
		unsigned short getDay() const noexcept
		{
			return day;
		}

		/**
			\brief Get month part of date-time.
		*/
		unsigned short getMonth() const noexcept
		{
			return month;
		}

		/**
			\brief Get year part of date-time.
		*/
		long getYear() const noexcept
		{
			return year;
		}

		/**
			\brief Get week day part of date-time.
		*/
		unsigned short getWeekDay() const noexcept
		{
			return wkday;
		}
	};

}



#endif