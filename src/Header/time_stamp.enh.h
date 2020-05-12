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
		inline void set(
			date_ dt /**< : <i>in</i> : Date to set the object to.*/,
			time_ t  /**< : <i>in</i> : Time to set the object to.*/
		) noexcept
		{
			seconds = t.seconds;
			minutes = t.minutes;
			hours = t.hours;
			day = dt.day;
			month = dt.month;
			year = dt.year;
			wkday = dt.wkday;
		}

		/**
			\brief Sets time to time indicated by the argument.

			<h3>Overloads</h3>
		*/
		inline void set(
			time_ t  /**< : <i>in</i> : Time to set the object to.*/
		) noexcept
		{
			seconds = t.seconds;
			minutes = t.minutes;
			hours = t.hours;
		}

		/**
			\brief Sets date to date indicated by the argument.

			<h3>Overloads</h3>
		*/
		inline void set(
			date_ dt /**< : <i>in</i> : Date to set the object to.*/
		) noexcept
		{
			day = dt.day % 31 + 1;
			month = dt.month;
			year = dt.year;
			wkday = dt.wkday;
		}


	};

}



#endif