/** ***************************************************************************
	\file general.enh.h

	\brief The file to declare general purpose classes and functions

	Created 11 May 2020

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



#ifndef GENERAL_ENH_H

#define GENERAL_ENH_H				general.enh.h

#include <atomic>
#include <type_traits>
#include "framework.enh.h"


namespace enh
{
	/**
		\brief Check if all the bits high in parameter 'field' are high in
		parameter 'in'.\n

		<h3>Return</h3>
		Returns true if all bits on in 'field' are on in
		'in'.\n

		<h3>Template</h3>
		-#  <code>enumT</code> : The enumeration type (preffered) that is to
		be compared.\n

	*/
	template<class enumT>
	inline bool checkField(
		enumT in /**< : <i>in</i> : The field to check.*/,
		enumT field /**< : <i>in</i> : The fields to check for.*/
	) noexcept
	{
		return ((in | field) == in);
	}

	/**
		\brief [[deprecated]] The signum function, value is 0 if val is 0, 1 if val > 0,
		-1 if  val < 0.

		<b> DEPRECATED </b> : Use constexpr function signum_fn.
	*/
	template<long long val>
	constexpr short signum = (val > 0) ? 1 : -1;

	template<>
	constexpr short signum<0> = 0;

	/**
		\brief [[deprecated]] The rounded up value of the ratio num / denom.

		<b> DEPRECATED </b> : Use constexpr function incl_ratio.
	*/
	template<unsigned long long num, unsigned long long denom>
	constexpr unsigned long long inclusive_ratio = num / denom +
		signum<num %denom>;


	/**
		\brief The mathematical signum function to extract sign.

		<h3>Template</h3>
		<code>class arithmetic</code> : The arithmetic type of the argument.

		<h3>Return</h3>
		The sign : -1 if argument is negative, +1 if argument is postive, 0 
		if argument is 0
	*/
	template<class arithmetic>
	constexpr short signum_fn(arithmetic arg)
	{
		static_assert(std::is_arithmetic_v<arithmetic>, "signum function takes an arithmetic type");
		if (arg > 0)
			return 1;
		else if (arg < 0)
			return -1;
		else
			return 0;
	}

	/**
		\brief The inclusive ratio (ratio rounded up while deviding).

		<h3>Template</h3>
		<code>class integral</code> : The integral type of the argument.

		<h3>Return</h3>
		The rounded up value, returns num / denom rounded up.

		eg : incl_ratio(25,3) == 9
	*/
	template<class integral>
	constexpr integral incl_ratio(
		integral num /*< : <i>in</i> : The numerator of fraction.*/,
		integral denom /*< : <i>in</i> : The denominator of fraction.*/
	)
	{
		static_assert(std::is_integral_v<integral> &&
			std::is_unsigned_v < integral>, "inclusive ratio is for integral types");
		return (num / denom) + signum_fn(num % denom);
	}

}

#endif