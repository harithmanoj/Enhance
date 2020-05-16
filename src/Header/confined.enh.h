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
#include "framework.enh.h"


namespace enh
{
	template<class integral>
	class confined_base
	{
	public:
		using value_type = integral;
		using pred_t = std::function<bool(value_type)>;
		using limit_t = std::function<value_type()>;
	private:
		value_type value;
		pred_t uLimit_pred;
		pred_t lLimit_pred;
		limit_t uLimit;
		limit_t lLimit;
	public:
		
		inline constexpr confined_base(
			const pred_t &upper_p,
			const pred_t &lower_p,
			const limit_t& upper_l,
			const limit_t& lower_l,
			const value_type &val
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

		inline constexpr set(
			const value_type &val
		)
		{
			if (!uLimit_pred(val) || !lLimit_pred(val))
			{
				throw std::invalid_argument("value not within limits");
			}
			value = val;
		}

		inline constexpr value_type get() const noexcept { return value; }

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

		inline constexpr unsigned add(value_type additional) noexcept
		{
			value_type rem = additional % (uLimit() - lLimit());
			value_type ret = additional / (uLimit() - lLimit());

			value += rem;
			if (!uLimit_pred(value))
			{
				value = value + lLimit() - uLimit();
				++ret;
			}

			return ret;
		}
	};
}



#endif