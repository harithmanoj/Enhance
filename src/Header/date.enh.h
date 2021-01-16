/** ***************************************************************************
	\file date.enh.h

	\brief File for date class.

	Created 12 May 2020

	This file is part of project Enhance C++ Libraries.

	Copyright 2020 Harith Manoj <harithpub@gmail.com>
	
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

#ifndef DATE_ENH_H

#	define DATE_ENH_H							date.enh.h

#	include "general.enh.h"
#	include "LimitedNumber.enh.h"
#	include <string_view>
#	include <ctime>
#	include <exception>
#	include <stdexcept>



namespace enh
{
	/**
			\brief wrapper over unsafe localtime function.

			Calls localtime_s if using MSVC, std::localtime else.

			<h3> Return </h3>
			Returns structure filled with current time and date.
		*/
	inline tm localTime(
		time_t *arith_tm /**< : <i>in</i> : The pointer to tm structure to 
				   assign time values.*/
	)
	{
		tm str_tm;
#	ifdef _MSC_VER
		localtime_s(&str_tm, arith_tm);
#	else
		str_tm = *std::localtime(arith_tm);
#	endif
		return str_tm;
	}

	/**
			\brief The maximum date for that month.
	*/
	inline constexpr std::uint8_t monthTotalDays(
		std::uint8_t mnth /**< : <i>in</i> : The month count.*/,
		std::int32_t yr /**< : <i>in</i> : The year count.*/
	) noexcept
	{
		switch (mnth)
		{

		case 0: [[fallthrough]];
		case 2: [[fallthrough]];
		case 4: [[fallthrough]];
		case 6: [[fallthrough]];
		case 7: [[fallthrough]];
		case 9: [[fallthrough]];
		case 11:
			return 31;

		case 3: [[fallthrough]];
		case 5: [[fallthrough]];
		case 8: [[fallthrough]];
		case 10:
			return 30;


		case 1:
		{
			if ((yr % 4) == 0)
				if ((yr % 100) == 0)
					if ((yr % 400) == 0)
						return 29;
			return 28;
		}

		default:
			return 165;
			break;
		}
	}

	/**
		\brief The maximum date for that year.
	*/
	inline constexpr std::uint16_t yearTotalDays(
		std::int32_t yr /**< : <i>in</i> : The year count.*/
	) noexcept
	{
		if (yr % 4 == 0)
			return 366;
		else
			return 365;
	}

	/**
		\brief The week day after day_count number of days from week.
	*/
	inline constexpr std::uint8_t weekDayAfter(
		std::uint8_t week /*< : <i>in</i> : The current week day.*/,
		std::int64_t day_count /*< : <i>in</i> : The number of days to
								add.*/
	) noexcept
	{
		auto day = std::uint64_t(0);

		day = 7 + signumFunction(day_count) * (day_count + week);

		return day % 7;
	}

	namespace numeric
	{
		/**
			\brief Numerical value confined to ones that month can take 
			[0,11].
		*/
		using MonthNumber = UnsignedLimitedNumber<std::uint8_t, 12>;

		/**
			\brief Numerical value confined to ones that week day can take
			[0,6].
		*/
		using WeekDayNumber = UnsignedLimitedNumber<std::uint8_t, 7>;

		/**
			\brief Numerical type that is confined to interval 
			[1,monthTotalDays].

			<b>NOTE</b> : The argument references lifetime must be longer or 
			equal to the lifetime of this object. This is used to get the 
			upper limit for date.

		*/
		class MonthDayNumber : public ConfinedValue<std::uint8_t>
		{
			
		public:

			/**
				\brief Constructor for the MonthDayNumber.

				<b>NOTE</b> : References must last atleast until this object 
				destructs.
			*/
			constexpr inline MonthDayNumber(
				const MonthNumber &mnth /**< : <i>in</i> : The value of month.*/,
				const std::int32_t &yr /**< : <i>in</i> : The value of year.*/,
				std::uint8_t dy /**< : <i>in</i> : The value of day.*/
			) : ConfinedValue(
					[&mnth, &yr](value_type a) 
					{
						return (a <= monthTotalDays(mnth.get(), yr));
					},
					[](value_type a)
					{
						return (a >= 1);
					},
					[&mnth, &yr]()
					{
						return monthTotalDays(mnth.get(), yr);
					},
					[]()
					{
						return 1;
					},
					dy)
			{}
		};


		/**
			\brief Numerical type that is confined to interval
			[1,yearTotalDays].

			<b>NOTE</b> : The argument references lifetime must be longer or
			equal to the lifetime of this object. This is used to get the
			upper limit for date.

		*/
		class YearDayNumber : public ConfinedValue<std::uint16_t>
		{

		public:

			/**
				\brief Constructor for the YearDayNumber.

				<b>NOTE</b> : References must last atleast until this object
				destructs.
			*/
			constexpr inline YearDayNumber(
				const std::int32_t &yr /**< : <i>in</i> : The value of year.*/,
				std::uint16_t yrdy /**< : <i>in</i> : The value of year
									day.*/
			) : ConfinedValue(
				[&yr](value_type a)
				{
					return (a < yearTotalDays(yr));
				},
				[](value_type a)
				{
					return (a >= 0);
				},
				[&yr]()
				{
					return yearTotalDays(yr) - 1;
				},
				[]()
				{
					return 0;
				},
				yrdy)
			{}
		};
	}

	/**
		\brief Class for date manipulation and representation.

		<h3>Example</h3>

		\include{lineno} Date.ex.cpp
	*/
	class Date
	{
		std::int32_t _year; 
		numeric::MonthNumber _month;
		numeric::MonthDayNumber _monthDay;
		numeric::WeekDayNumber _weekDay;
		numeric::YearDayNumber _yearDay;

	public:

		/**
			\brief Sets the date to the date indicated by arguments.
			
			<h3>Exception</h3>
			Throws <code>std::invalid_argument</code> if dy, mnth, week, ydy is
			not within bounds. [0,monthTotalDays], [0,11], [0,6], 
			[0,yearTotalDays)
			respectively.
		*/
		constexpr inline void setDate(
			std::uint8_t dy /**< : <i>in</i> : The day of the month
							  [1,monthTotalDays].*/,
			std::uint8_t mnth /**< : <i>in</i> : The number of months after
								January [0,11].*/,
			std::int32_t yr /**< : <i>in</i> : The Year.*/,
			std::uint8_t week /**< : <i>in</i> : The day of the week after
								Sunday [0,6].*/,
			std::uint16_t ydy /**< : <i>in</i> : The number of day after 01 
							  January
						 of that year [1,yearTotalDays).*/
		)
		{
			_year = yr;
			_month.set(mnth);
			_monthDay.set(dy);			
			_weekDay.set(week);
			_yearDay.set(ydy);
		}

		/**
			\brief Sets the date to the date indicated by argument.
		*/
		inline void setDate(
			time_t timeStamp /**< : <i>in</i> : The time stamp which
							 contains the date.*/
		)
		{
			tm temp = enh::localTime(&timeStamp);
			setDate(temp.tm_mday, temp.tm_mon, std::int64_t(temp.tm_year) 
				+ 1900, temp.tm_wday, temp.tm_yday);
		}

		/**
			\brief Sets the date to the date current date.
		*/
		inline void setDate()
		{
			setDate(std::time(nullptr));
		}

		/**
			\brief Sets the date to the date indicated by arguments.

			<h3>Exception</h3>
			Throws <code>std::invalid_argument</code> if dy, mnth, week, ydy is
			not within bounds. [0,monthTotalDays], [0,11], [0,6], 
			[0,yearTotalDays)
			respectively.
		*/
		constexpr inline Date(
			std::uint8_t dy /**< : <i>in</i> : The day of the month
							  [1,monthTotalDays].*/,
			std::uint8_t mnth /**< : <i>in</i> : The number of months after
								January [0,11].*/,
			std::int32_t yr /**< : <i>in</i> : The Year.*/,
			std::uint8_t week /**< : <i>in</i> : The day of the week after
								Sunday [0,6].*/,
			std::int16_t ydy /**< : <i>in</i> : The number of day after 01 
							 January
						 of that year [1,yearTotalDays).*/
		) : _year(yr), _month(mnth), _monthDay(_month, _year, dy), 
			_weekDay(week), _yearDay(_year, ydy) {}

		/**
			\brief Sets the date to the date indicated by argument.
		*/
		inline Date(
			time_t timeStamp /**< : <i>in</i> : The time stamp which
							 contains the date.*/
		) : _year(2020), _month(0), _monthDay(_month, _year, 1), _weekDay(0),
			_yearDay(_year, 0)
		{
			setDate(timeStamp);
		}

		/**
			\brief Sets the date to the date current date.
		*/
		inline Date() : _year(2020), _month(0), _monthDay(_month, _year, 1),
			_weekDay(0), _yearDay(_year, 0)
		{
			setDate();
		}

		/**
			\brief The day of this month.
		*/
		constexpr inline std::uint8_t getDayOfMonth() const noexcept 
		{
			return _monthDay.get(); 
		}

		/**
			\brief The number of months after January of this year.
		*/
		constexpr inline std::uint8_t getMonth() const noexcept
		{ 
			return _month.get(); 
		}

		/**
			\brief The name of the month.
		*/
		constexpr inline std::string_view getMonthString() const noexcept
		{
			switch (_month.get())
			{
			case 0: return "January";
			case 1: return "February";
			case 2: return "March";
			case 3: return "April";
			case 4: return "May";
			case 5: return "June";
			case 6: return "July";
			case 7: return "August";
			case 8: return "September";
			case 9: return "October";
			case 10: return "November";
			case 11: return "December";
			default: return "Error";
			}
		}

		/**
			\brief The name of the month (shortened).
		*/
		constexpr inline std::string_view getShortMonthString() const noexcept
		{
			switch (_month.get())
			{
			case 0: return "Jan";
			case 1: return "Feb";
			case 2: return "Mar";
			case 3: return "Apr";
			case 4: return "May";
			case 5: return "Jun";
			case 6: return "Jul";
			case 7: return "Aug";
			case 8: return "Sep";
			case 9: return "Oct";
			case 10: return "Nov";
			case 11: return "Dec";
			default: return "Error";
			}
		}

		/**
			\brief The Year.
		*/
		constexpr inline std::uint32_t getYear() const noexcept 
		{ return _year; }

		/**
			\brief The number of days after last Sunday.
		*/
		constexpr inline std::uint8_t getDayOfWeek() const noexcept
		{ 
			return _weekDay.get();
		}


		/**
			\brief The number of days after 1st of January this year.
		*/
		constexpr inline std::uint16_t getDayOfYear() const noexcept
		{ 
			return _yearDay.get();
		}

		/**
			\brief The name of the day.
		*/
		constexpr inline std::string_view getDayOfWeekString() const
		{
			switch (_weekDay.get())
			{
			case 0: return "Sunday";
			case 1: return "Monday";
			case 2: return "Tuesday";
			case 3: return "Wednesday";
			case 4: return "Thursday";
			case 5: return "Friday";
			case 6: return "Saturday";
			default: return "Error";
			}
		}

		/**
			\brief The name of the day (shortened).
		*/
		constexpr inline std::string_view getShortDayOfWeekString() const
		{
			switch (_weekDay.get())
			{
			case 0: return "Sun";
			case 1: return "Mon";
			case 2: return "Tue";
			case 3: return "Wed";
			case 4: return "Thu";
			case 5: return "Fri";
			case 6: return "Sat";
			default: return "Error";
			}
		}

		/**
			\brief Get The date as a string.
			Format : Day, ddth Month yyyy\n
			eg : Tuesday, 12th May 2020
			<h3>Overload</h3>
			-# <code>inline std::string getStringDate(std::string format)
			const;</code>\n
		*/
		inline std::string getStringDate() const
		{
			return std::string(getDayOfWeekString()) + ", " 
				+ std::to_string(_monthDay.get()) 
				+ std::string(getOrdinalIndicator(_monthDay.get())) + " " 
				+ std::string(getMonthString()) + " " + std::to_string(_year);
		}

		/**
			\brief Get The date as a string in custom format.
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
			<h3>Overload</h3>
			-# <code>inline std::string getStringDate() const;</code>\n
		*/
		inline std::string getStringDate(
			std::string format /**< : <i>in</i> : The format of date.*/
		) const
		{
			std::size_t pDay, pshDay, pdd, pddth, pMonth, pmm, pshMonth,
				pyyyy;
			pshDay = format.find("shDay");
			if (pshDay != std::string::npos)
				format.replace(pshDay, 5, getShortDayOfWeekString());
			else
			{
				pDay = format.find("Day");
				if (pDay != std::string::npos)
					format.replace(pDay, 3, getDayOfWeekString());
			}

			pddth = format.find("ddth");
			if (pddth != std::string::npos)
				format.replace(pddth, 4, signExtendValue(_monthDay.get(), 2) +
					std::string(getOrdinalIndicator(_monthDay.get())));
			else
			{
				pdd = format.find("dd");
				if (pdd != std::string::npos)
					format.replace(pdd, 2, 
						signExtendValue(_monthDay.get(), 2));
			}

			pshMonth = format.find("shMonth");
			if (pshMonth != std::string::npos)
				format.replace(pshMonth, 7, getShortMonthString());
			else
			{
				pMonth = format.find("Month");
				if (pMonth != std::string::npos)
					format.replace(pMonth, 5, getMonthString());
				else
				{
					pmm = format.find("mm");
					if (pmm != std::string::npos)
						format.replace(pmm, 2, signExtendValue(_month.get()
							+ 1, 2));
				}
			}

			pyyyy = format.find("yyyy");
			if (pyyyy != std::string::npos)
				format.replace(pyyyy, 4, signExtendValue(_year, 4));
			return format;
		}

		/**
			\brief Checks if argument is equal to this object.
			<h3>Return</h3>
			Returns true if year, month and day of argument is equal to
			current object.
		*/
		constexpr inline bool isEqualTo(
			const Date &dt /**< : <i>in</i> : The date to compare with.*/
		) const noexcept
		{
			return (_year == dt._year) && (_month == dt._month) 
				&& (_monthDay == dt._monthDay);
		}

		/**
			\brief Checks if argument is not equal to this object.
			<h3>Return</h3>
			Returns true if year, month and day of argument is not equal to
			current object.
		*/
		constexpr inline bool isNotEqualTo(
			const Date &dt /**< : <i>in</i> : The date to compare with.*/
		) const noexcept
		{
			return !isEqualTo(dt);
		}

		/**
			\brief Checks if current date is lesser than argument.
			<h3>Return</h3>
			Returns true if current date is lesser than argument.
		*/
		constexpr inline bool isLesserThan(
			const Date &dt /**< : <i>in</i> : The date to compare with.*/
		) const noexcept
		{
			if (_year < dt._year)
				return true;
			else if (_year > dt._year)
				return false;
			else
			{
				if (_month < dt._month)
					return true;
				else if (_month > dt._month)
					return false;
				else
				{
					if (_monthDay < dt._monthDay)
						return true;
					else if (_monthDay > dt._monthDay)
						return false;
					else
						return false;

				}
			}
		}

		/**
			\brief Checks if current date is lesser than or equal to argument.
			<h3>Return</h3>
			Returns true if current date is lesser than or equal to argument.
		*/
		constexpr inline bool isLesserThanEq(
			const Date &dt /**< : <i>in</i> : The date to compare with.*/
		) const noexcept
		{
			if (_year < dt._year)
				return true;
			else if (_year > dt._year)
				return false;
			else
			{
				if (_month < dt._month)
					return true;
				else if (_month > dt._month)
					return false;
				else
				{
					if (_monthDay < dt._monthDay)
						return true;
					else if (_monthDay > dt._monthDay)
						return false;
					else
						return true;

				}
			}
		}

		/**
			\brief Checks if current date is greater than argument.
			<h3>Return</h3>
			Returns true if current date is greater than argument.
		*/
		constexpr inline bool isGreaterThan(
			const Date &dt /**< : <i>in</i> : The date to compare with.*/
		) const noexcept
		{
			return !isLesserThanEq(dt);
		}

		/**
			\brief Checks if current date is greater than or equal to
			argument.
			<h3>Return</h3>
			Returns true if current date is greater than or equal to 
			argument.
		*/
		constexpr inline bool isGreaterThanEq(
			const Date &dt /**< : <i>in</i> : The date to compare with.*/
		) const noexcept
		{
			return !isLesserThan(dt);
		}

		/**
			\brief Add number of days to the current date.
		*/
		constexpr inline void addDay(
			unsigned long long dy /**< : <i>in</i> : The days to add.*/
		) noexcept
		{
			_weekDay.add(dy);
			unsigned long long additional = dy % (365 + 365 + 365 + 366);
			unsigned long long yr_add = 4 * (dy / (365 + 365 + 365 + 366));
			_year += yr_add;

			auto current_step = monthTotalDays(_month.get(), _year) - 1;
			while (additional > current_step)
			{
				auto yr = _month.add(_monthDay.add(current_step));
				_yearDay.add(current_step);
				_year += yr;

				additional -= current_step;
				current_step = monthTotalDays(_month.get(), _year) - 1;
			}
			
			auto yr = _month.add(_monthDay.add(additional));		
			_yearDay.add(current_step);
			_year += yr;
		}

		/**
			\brief subtract number of days to the current date.
		*/
		constexpr inline void subDay(
			unsigned long long dy /**< : <i>in</i> : The days to subtract.*/
		) noexcept
		{
			_weekDay.sub(dy);
			unsigned long long difference = dy % (365 + 365 + 365 + 366);
			unsigned long long yr_sub = 4 * (dy / (365 + 365 + 365 + 366));
			_year -= yr_sub;

			auto current_step = monthTotalDays(_month.get(), _year) - 1;
			while (difference > current_step)
			{
				auto yr = _month.sub(_monthDay.sub(current_step));
				_yearDay.sub(current_step);
				_year -= yr;

				difference -= current_step;
				current_step = monthTotalDays(_month.get(), _year) - 1;
			}

			auto yr = _month.sub(_monthDay.sub(difference));
			_yearDay.sub(current_step);
			_year -= yr;
		}


	};
	

	/**
		\brief Checks if lhs is equal to rhs.
	*/
	constexpr inline bool operator == (
		const Date &lhs /**< : <i>in</i> : The left hand side of the 
						expression.*/,
		const Date &rhs /**< : <i>in</i> : The right hand side of the 
						expression.*/
	) noexcept
	{
		return lhs.isEqualTo(rhs);
	}

	/**
		\brief Checks if lhs is not equal to rhs.
	*/
	constexpr inline bool operator != (
		const Date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const Date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return lhs.isNotEqualTo(rhs);
	}

	/**
		\brief Checks if lhs is greater than rhs.
	*/
	constexpr inline bool operator > (
		const Date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const Date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return rhs.isLesserThan(lhs);
	}

	/**
		\brief Checks if lhs is greater than or equal to rhs.
	*/
	constexpr inline bool operator >= (
		const Date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const Date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return rhs.isLesserThanEq(lhs);
	}

	/**
		\brief Checks if lhs is lesser than rhs.
	*/
	constexpr inline bool operator < (
		const Date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const Date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return lhs.isLesserThan(rhs);
	}

	/**
		\brief Checks if lhs is lesser than or equal to rhs.
	*/
	constexpr inline bool operator <= (
		const Date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const Date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return lhs.isLesserThanEq(rhs);
	}
}


#endif