/** ***************************************************************************
	\file date_time.enh.h

	\brief File for combined date time class.

	Created 13 May 2020

	This file is part of project Enhance C++ Libraries.

	Copyright 2020-2021 Harith Manoj <harithpub@gmail.com>
	
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

******************************************************************************/

#ifndef DATE_TIME_ENH_H

#define DATE_TIME_ENH_H					DateTime.enh.h


#include "TimeStamp.enh.h"

namespace enh
{
	/**
		\brief Class for date and time joint manipulation.

		<h3> Examples </h3>

		\include{lineno} DateTime.ex.cpp
	*/
	class DateTime : public Date, public TimeStamp
	{
	
	public:


		/**
			\brief Get the Date time as a 52 bit stream
			 (for use as bitstream, storage or transmit Date time).
		*/
		constexpr inline std::bitset<52> getDateTimeRaw() const noexcept
		{
			std::bitset<52> ret;
			ret.reset();

			ret |= getDateRaw().to_ulong();
			ret |= getTimeRaw().to_ulong() << 32;
			
			return ret;
		}

		/**
			\brief Use 52 bit stream Date Time representation
			( from enh::DateTime::getDateTimeRaw() ) to set Time.
		*/
		constexpr inline void setDateTimeRaw(
			std::bitset<52> data /**< : <i>in</i> : The 52 bit date time
							   representation. */
		) noexcept
		{
			setDateRaw((data & std::bitset<52>(0x0'00'00'ff'ff'ff'ffull)).to_ullong());
			setTimeRaw(((data) >> 32).to_ullong());
		}

		
		/**
			\brief Sets the time and date to the time and date indicated by 
			argument.
		*/
		constexpr inline void set(
			std::uint8_t dy /**< : <i>in</i> : The day of the month 
							  [1,monthTotalDays].*/,
			std::uint8_t mnth /**< : <i>in</i> : The number of months after
								January [0,11].*/,
			std::int32_t yr /**< : <i>in</i> : The Year.*/,
			std::uint8_t week /**< : <i>in</i> : The day of the week after
								Sunday [0,6].*/,
			std::uint8_t ydy /**< : <i>in</i> : The number of day after 01 January
						 of that year [1,yearTotalDays).*/,
			std::uint8_t sec /**< : <i>in</i> : The seconds field [0,60].*/,
			std::uint8_t min /**< : <i>in</i> : The minutes field [0,59].*/,
			std::uint8_t hr /**< : <i>in</i> : The hours field [0,59].*/
		)
		{
			setDate(dy, mnth, yr, week, ydy);
			setTime(sec, min, hr);
		}

		/**
			\brief Sets the time and date to the time and date indicated by
			argument.
		*/
		inline void set(
			time_t stamp /**< : <i>in</i> : The time stamp which 
							 contains the date and time.*/
		)
		{
			tm temp = localTime(&stamp);
			if (temp.tm_sec <= 59)
				set(temp.tm_mday, temp.tm_mon, temp.tm_year + 1900, temp.tm_wday,
					temp.tm_yday, temp.tm_sec, temp.tm_min, temp.tm_hour);
			else
				set(temp.tm_mday, temp.tm_mon, temp.tm_year + 1900, temp.tm_wday,
					temp.tm_yday, 59, temp.tm_min, temp.tm_hour);
		}

		/**
			\brief Sets the time and date to the current time and date.
		*/
		inline void set()
		{
			set(std::time(nullptr));
		}

		/**
			\brief Sets the time and date to the time and date indicated by
			argument.
		*/
		constexpr inline DateTime(
			std::uint8_t dy /**< : <i>in</i> : The day of the month
							  [1,monthTotalDays].*/,
			std::uint8_t mnth /**< : <i>in</i> : The number of months after
								January [0,11].*/,
			std::int32_t yr /**< : <i>in</i> : The Year.*/,
			std::uint8_t week /**< : <i>in</i> : The day of the week after
								Sunday [0,6].*/,
			std::uint8_t ydy /**< : <i>in</i> : The number of day after 01 January
						 of that year [1,yearTotalDays).*/,
			std::uint8_t sec /**< : <i>in</i> : The seconds field [0,60].*/,
			std::uint8_t min /**< : <i>in</i> : The minutes field [0,59].*/,
			std::uint8_t hr /**< : <i>in</i> : The hours field [0,59].*/
		) : Date(dy, mnth, yr, week, ydy), TimeStamp(sec, min, hr) {}

		/**
			\brief Sets the time and date to the time and date indicated by
			argument.
		*/
		inline DateTime(
			time_t stamp /**< : <i>in</i> : The time stamp which
							 contains the date and time.*/
		) : Date(1,0,0,0,0), TimeStamp(0,0,0) 
		{
			set(stamp);
		}

		/**
			\brief Sets the time and date to the current time and date.
		*/
		inline DateTime() : Date(1, 0, 0, 0, 0), TimeStamp(0, 0, 0) 
		{
			set();
		}

		/**
			\brief Get The date and time as a string in default format.

			hour:min:sec ; Day, ddth Month yyyy\n\n

			<h3>Overload</h3>
			-# <code>inline std::string getStringDateTime(std::string format)
			const;</code>\n
		*/
		inline std::string getStringDateTime()
		{
			return getStringTime() + " ; " + getStringDate();
		}


		/**
			\brief Get The date and time as a string in custom format.

			Pass Argument as a string containing any of the following
			components.

			<b>Day</b> : Name of day (Sunday) OR <b>shDay</b> : shortened
			name (Sun).\n
			<b>dd</b> : The date (20) OR <b>ddth</b> : date with
			superscript (21st).\n
			<b>Month</b> : The name of Month (January) OR <b>mm</b> : The
			numerical month (01 for January) OR <b>shMonth</b> : The name of
			month shortened (Jan).\n
			<b>yyyy</b> : Year (2020).\n
			<b>sec</b> : The seconds.\n
			<b>min</b> : The minutes.\n
			<b>hour</b> : The hours.\n

			<h3>Overload</h3>
			-# <code>inline std::string getStringDateTime() const;</code>\n
		*/
		inline std::string getStringDateTime(
			std::string format /**< : <i>in</i> : The format of date.*/
		)
		{
			return getStringDate(getStringTime(format));
		}

		/**
			\brief Adds to the hour part of time held.
		*/
		constexpr inline void addHours(
			std::uint64_t hr /**< : <i>in</i> : The hours to add.*/
		) noexcept
		{
			addDay(TimeStamp::addHours(hr));
		}

		/**
			\brief Adds to the minute part of time held (also hour).
		*/
		constexpr inline void addMinutes(
			std::uint64_t min /**< : <i>in</i> : The minutes to add.*/
		) noexcept
		{
			addDay(TimeStamp::addMinutes(min));
		}

		/**
			\brief Adds to the second part of time held (also hour).
		*/
		constexpr inline void addSeconds(
			std::uint64_t sec  /**< : <i>in</i> : The seconds to add.*/
		) noexcept
		{
			addDay(TimeStamp::addSeconds(sec));
		}

		/**
			\brief Reduce the hour part of time held.
		*/
		constexpr inline void subHours(
			std::uint64_t hr /**< : <i>in</i> : The hours to reduce.*/
		) noexcept
		{
			subDay(TimeStamp::subHours(hr));
		}

		/**
			\brief Reduce the minute part of time held (also hour).
		*/
		constexpr inline void subMinutes(
			std::uint64_t min /**< : <i>in</i> : The minutes to reduce.*/
		) noexcept
		{
			subDay(TimeStamp::subMinutes(min));
		}

		/**
			\brief Reduces the second part of time held (also hour).
		*/
		constexpr inline void subSeconds(
			std::uint64_t sec /**< : <i>in</i> : The seconds to reduce.*/
		) noexcept
		{
			subDay(TimeStamp::subSeconds(sec));
		}

		/**
			\brief Checks if argument is equal to this object.

			<h3>Return</h3>
			Returns true if year, month and day of argument is equal to
			current object.
		*/
		constexpr inline bool isEqualTo(
			const DateTime &dt /**< : <i>in</i> : The DateTime to compare with.*/
		) const noexcept
		{
			return Date::isEqualTo(dt) && TimeStamp::isEqualTo(dt);
		}

		/**
			\brief Checks if argument is not equal to this object.

			<h3>Return</h3>
			Returns true if year, month and day of argument is not equal to
			current object.
		*/
		constexpr inline bool isNotEqualTo(
			const DateTime &dt /**< : <i>in</i> : The DateTime to compare with.*/
		) const noexcept
		{
			return !isEqualTo(dt);
		}

		/**
			\brief Checks if current DateTime is lesser than argument.

			<h3>Return</h3>
			Returns true if current DateTime is lesser than argument.
		*/
		constexpr inline bool isLesserThan(
			const DateTime &dt /**< : <i>in</i> : The DateTime to compare with.*/
		) const noexcept
		{
			return Date::isLesserThan(dt) && TimeStamp::isLesserThan(dt);
		}

		/**
			\brief Checks if current DateTime is lesser than or equal to argument.

			<h3>Return</h3>
			Returns true if current DateTime is lesser than or equal to argument.
		*/
		constexpr inline bool isLesserThanEq(
			const DateTime &dt /**< : <i>in</i> : The DateTime to compare with.*/
		) const noexcept
		{
			return Date::isLesserThanEq(dt) && TimeStamp::isLesserThanEq(dt);
		}

		/**
			\brief Checks if current DateTime is greater than argument.

			<h3>Return</h3>
			Returns true if current DateTime is greater than argument.
		*/
		constexpr inline bool isGreaterThan(
			const DateTime &dt /**< : <i>in</i> : The DateTime to compare with.*/
		) const noexcept
		{
			return !isLesserThanEq(dt);
		}

		/**
			\brief Checks if current DateTime is greater than or equal to argument.

			<h3>Return</h3>
			Returns true if current DateTime is greater than or equal to argument.
		*/
		constexpr inline bool isGreaterThanEq(
			const DateTime &dt /**< : <i>in</i> : The DateTime to compare with.*/
		) const noexcept
		{
			return !isLesserThan(dt);
		}
	};

	/**
		\brief Checks if lhs is equal to rhs.
	*/
	constexpr inline bool operator == (
		const DateTime &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const DateTime &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return lhs.isEqualTo(rhs);
	}

	/**
		\brief Checks if lhs is not equal to rhs.
	*/
	constexpr inline bool operator != (
		const DateTime &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const DateTime &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return lhs.isNotEqualTo(rhs);
	}

	/**
		\brief Checks if lhs is greater than rhs.
	*/
	constexpr inline bool operator > (
		const DateTime &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const DateTime &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return rhs.isLesserThan(lhs);
	}

	/**
		\brief Checks if lhs is greater than or equal to rhs.
	*/
	constexpr inline bool operator >= (
		const DateTime &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const DateTime &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return rhs.isLesserThanEq(lhs);
	}

	/**
		\brief Checks if lhs is lesser than rhs.
	*/
	constexpr inline bool operator < (
		const DateTime &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const DateTime &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return lhs.isLesserThan(rhs);
	}

	/**
		\brief Checks if lhs is lesser than or equal to rhs.
	*/
	constexpr inline bool operator <= (
		const DateTime &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const DateTime &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return lhs.isLesserThanEq(rhs);
	}

}

#endif