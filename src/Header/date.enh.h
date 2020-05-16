/** ***************************************************************************
	\file date.enh.h

	\brief File for date class.

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

#ifndef DATE_ENH_H

#define DATE_ENH_H							date.enh.h

#include "general.enh.h"
#include "numeral_system.enh.h"
#include <ctime>
#include <exception>
#include <stdexcept>



namespace enh
{
	/**
			\brief wrapper over unsafe localtime function.

			The Microsoft version localtime_s is called. Please Edit if not working.
		*/
	inline void localtime(
		tm *str_tm /**< : <i>in</i> : The pointer to tm structure to 
				   assign time values.*/,
		time_t *arith_tm /**< : <i>in</i> : The pointer to tm structure to 
				   assign time values.*/
	)
	{
		localtime_s(str_tm, arith_tm);
	}

	/**
			\brief The maximum date for that month.
	*/
	inline constexpr unsigned short month_limit(
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
		\brief The maximum date for that year.
	*/
	inline constexpr unsigned year_limit(
		long yr /**< : <i>in</i> : The year count.*/
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
	inline constexpr unsigned short week_day_increments(
		unsigned short week /*< : <i>in</i> : The current week day.*/,
		unsigned long day_count /*< : <i>in</i> : The number of days to
								add.*/
	) noexcept
	{
		unsigned long long tmp = day_count;
		tmp += week;
		return tmp % 7;
	}


	namespace date_types
	{
		/**
			\brief Numerical value confined to ones that month can take 
			[0,11].
		*/
		using month_t = NumericSystem<unsigned short, 12>;

		/**
			\brief Numerical value confined to ones that week day can take
			[0,6].
		*/
		using weekday_t = NumericSystem<unsigned short, 7>;

		/**
			\brief Neumerical type that is confined to interval 
			[1,month_limit].

			<b>NOTE</b> : The argument references lifetime must be longer or 
			equal to the lifetime of this object. This is used to get the 
			upper limit for date.

		*/
		class day_t : public confined_base<unsigned short>
		{
			
		public:

			/**
				\brief Constructor for the day_t.

				<b>NOTE</b> : References must last atleast until this object 
				destructs.
			*/
			constexpr inline day_t(
				const month_t &mnth /**< : <i>in</i> : The value of month.*/,
				const long long &yr /**< : <i>in</i> : The value of year.*/,
				unsigned short dy /**< : <i>in</i> : The value of day.*/
			) : confined_base(
					[&](long long a) 
					{
						return (a <= month_limit(mnth.get(), yr));
					},
					[&](long long a)
					{
						return (a >= 1);
					},
					[&]()
					{
						return month_limit(mnth.get(), yr);
					},
					[&]()
					{
						return 1;
					},
					dy)
			{}
		};

	}


	

	/**
		\brief Checks if lhs is equal to rhs.
	*/
	constexpr inline bool operator == (
		const date &lhs /**< : <i>in</i> : The left hand side of the 
						expression.*/,
		const date &rhs /**< : <i>in</i> : The right hand side of the 
						expression.*/
	) noexcept
	{
		return lhs.isEqualTo(rhs);
	}

	/**
		\brief Checks if lhs is not equal to rhs.
	*/
	constexpr inline bool operator != (
		const date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return lhs.isNotEqualTo(rhs);
	}

	/**
		\brief Checks if lhs is greater than rhs.
	*/
	constexpr inline bool operator > (
		const date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return rhs.isLesserThan(lhs);
	}

	/**
		\brief Checks if lhs is greater than or equal to rhs.
	*/
	constexpr inline bool operator >= (
		const date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return rhs.isLesserThanEq(lhs);
	}

	/**
		\brief Checks if lhs is lesser than rhs.
	*/
	constexpr inline bool operator < (
		const date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return lhs.isLesserThan(rhs);
	}

	/**
		\brief Checks if lhs is lesser than or equal to rhs.
	*/
	constexpr inline bool operator <= (
		const date &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const date &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
	) noexcept
	{
		return lhs.isLesserThanEq(rhs);
	}
}


#endif