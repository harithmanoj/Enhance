/** ***************************************************************************
	\file confined.enh.h

	\brief The file to declare class for confined counts

	Created 16 May 2020

	This file is part of Enhance.

	Copyright 2020 Harith Manoj <harithpub@gmail.com>

	Enhance is free software : you can redistribute it and /or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Enhance is distributed base the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Enhance. If not, see < https://www.gnu.org/licenses/>.

******************************************************************************/

#ifndef CONFINED_ENH_H

#define CONFINED_ENH_H

#include <functional>
#include <stdexcept>


namespace enh
{
	/**
		\brief Define an integral type that is confined to an interval.

		The interval is specified by two functions set during construction.
		The interval check is done by other function set during construction.

		<h3>template</h3>
		<code>integral</code> : The integral type of the value.
	*/
	template<class integral>
	class confined_base
	{
	public:

		/**
			\brief An alias of the integral type.
		*/
		using value_type = integral;

		/**
			\brief The function type of limit checker.
		*/
		using pred_t = std::function<bool(long long)>;

		/**
			\brief The function type of the limit getter.
		*/
		using limit_t = std::function<value_type()>;
	private:

		/**
			\brief The data.
		*/
		value_type value;

		/**
			\brief The upper limit checker.
		*/
		pred_t uLimit_pred;

		/**
			\brief The lower limit checker.
		*/
		pred_t lLimit_pred;

		/**
			\brief The upper limit.
		*/
		limit_t uLimit;
		
		/**
			\brief The lower limit.
		*/
		limit_t lLimit;
	public:
		
		/**
			\brief Construct the object.

			<h3>Exceptions</h3>
			Throws <code>std::invalid_argument</h3> if value passed fails 
			upper and lower predicate.
			Throws <code>std::invalid_argument</h3> if ulimit is less than llimit.
		*/
		inline constexpr confined_base(
			const pred_t &upper_p /**< : <i>in</i> : The upper bounds 
								  checker.*/,
			const pred_t &lower_p /**< : <i>in</i> : The lower bounds
								  checker.*/,
			const limit_t& upper_l /**< : <i>in</i> : Get the upper bounds.*/,
			const limit_t& lower_l /**< : <i>in</i> : Get the lower bounds.*/,
			const value_type &val /**< : <i>in</i> : The value to be set.*/
		) : uLimit_pred(upper_p), lLimit_pred(lower_p), value(val),
			uLimit(upper_l), lLimit(lower_l)
		{
			if (uLimit() < lLimit())
				throw std::invalid_argument("upper limit should be greater than lower");
			if (!uLimit_pred(val) || !lLimit_pred(val))
			{
				value = lLimit() + (uLimit() - lLimit()) / 2;
				throw std::invalid_argument("value not within limits");
			}
		}

		/**
			\brief Construct the object, value as set as lower limit.

			<h3>Exceptions</h3>
			Throws <code>std::invalid_argument</h3> if ulimit is less than llimit.
		*/
		inline constexpr confined_base(
			const pred_t &upper_p /**< : <i>in</i> : The upper bounds
								  checker.*/,
			const pred_t &lower_p /**< : <i>in</i> : The lower bounds
								  checker.*/,
			const limit_t &upper_l /**< : <i>in</i> : Get the upper bounds.*/,
			const limit_t &lower_l /**< : <i>in</i> : Get the lower bounds.*/,
		) : uLimit_pred(upper_p), lLimit_pred(lower_p),
			uLimit(upper_l), lLimit(lower_l)
		{
			if (uLimit() < lLimit())
				throw std::invalid_argument("upper limit should be greater than lower");
			value = lLimit();
		}

		/**
			\brief Sets the value.

			<h3>Exception</h3>
			Throws <code>std::invalid_argument</code> if value is not within
			limits.
		*/
		inline constexpr set(
			const value_type &val /**< : <i>in</i> : The value to be set.*/
		)
		{
			if (!uLimit_pred(val) || !lLimit_pred(val))
			{
				throw std::invalid_argument("value not within limits");
			}
			value = val;
		}

		/**
			\brief Returns the value held.
		*/
		inline constexpr value_type get() const noexcept { return value; }

		/**
			\brief Adds single unit to the value held.

			<h3>Return</h3>
			Returns 1 if value goes above upper limit and value is set to 
			lower limit.
		*/
		inline constexpr unsigned add() noexcept
		{
			++value;
			if (!uLimit_pred(value))
			{
				value = lLimit();
				return 1;
			}
			return 0;
		}

		/**
			\brief Adds to the value held.

			<h3>Return</h3>
			Returns the number of times interval was exceded if value goes 
			above upper limit.

			for confining between 2 and 9 (inclusive),
			from  value 6, add(20) will return 3 and sets value to 5.
		*/
		template<class integral_>
		inline constexpr unsigned add(
			integral_ additional /**< : <i>in</i> : The number of units to
								  add.*/
		) noexcept
		{
			integral_ rem = additional % (uLimit() - lLimit());
			unsigned ret = additional / (uLimit() - lLimit());

			if (!uLimit_pred(value + rem))
			{
				value = value + rem + lLimit() - uLimit();
				++ret;
			}
			value += rem;
			return ret;
		}

		/**
			\brief Subtracts one unit from the value held.

			<h3>Return</h3>
			Returns 1 if value goes below lower limit and value is set to
			upper limit.
		*/
		inline constexpr unsigned sub() noexcept
		{
			--value;
			if (!lLimit_pred(value))
			{
				value = uLimit();
				return 1;
			}
			return 0;
		}

		/**
			\brief Subtracts from the value held.

			<h3>Return</h3>
			Returns the number of times interval was removed from if value goes
			above upper limit.

			for confining between 2 and 9 (inclusive),
			from  value 6, sub(20) will return 3 and set value to 7.
		*/
		template<class integral_>
		inline constexpr unsigned sub(
			integral_ difference /**< : <i>in</i> : The number of units to 
								 subtract.*/
		) noexcept
		{
			integral_ rem = difference % (uLimit() - lLimit());
			unsigned ret = difference / (uLimit() - lLimit());

			rem = value - rem;
			if (!lLimit_pred(rem))
			{
				value = rem + uLimit() - lLimit();
				++ret;
			}
			value = rem;
			return ret;
		}

		/**
			\brief Re-evaluates value according to predicate if anything 
			changed.

			Sets value to ulimit if exceeding upper, llimit if lower then lower limit.

			This is used if the predicate changes according to other values,

			Like if the predicate depends on a global variable or if it is a 
			lambda that captures by reference.

			<h3>Return</h3>
			Returns true if any change happend.
		*/
		inline constexpr bool re_eval() noexcept
		{
			if (!uLimit_pred(value))
			{
				value = uLimit();
				return true;
			}
			if (!lLimit_pred(value))
			{
				value = lLimit();
				return true;
			}
			return false;
		}
	};
}



#endif