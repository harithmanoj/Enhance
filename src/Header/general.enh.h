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
		\brief the signum function, value is 0 if val is 0, 1 if val > 0,
		-1 if  val < 0.
	*/
	template<long long val>
	constexpr short signum = (val > 0) ? 1 : -1;

	template<>
	constexpr short signum<0> = 0;

	/**
		\brief The rounded up value of the ratio num / denom.
	*/
	template<unsigned long long num, unsigned long long denom>
	constexpr unsigned long long inclusive_ratio = num / denom +
		signum<num %denom>;

}