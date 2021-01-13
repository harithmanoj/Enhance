/** ***************************************************************************
	\file Tristate.enh.h

	\brief The file to declare enumeration for static error status. 

	Created 03 January 2021

	This file is part of project Enhance C++ Libraries.

	Copyright 2021 Harith Manoj <harithpub@gmail.com>

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


#ifndef TRISTATE_ENH_H

#	define TRISTATE_ENH_H				Tristate.enh.h

#	include<cstdint>

/*
	\brief The namespace for all the functions and classes of this library
*/
namespace enh
{


	/**
		\brief A byte long type that takes 3 values, good (0), error(1),
		previous_error(2).

		<h3> Examples</h3>

		\include{lineno} Tristate.ex.cpp
	*/
	enum class Tristate : std::uint8_t
	{
		GOOD = 0 /**< : <i>1</i> : No error flag set. */,
		ERROR = 1 /**< : <i>0</i> : Error flag set now. */,
		PREV_ERR = 2 /**< : <i>-1</i> : Error flag was set by some
					  previous function. */
	};

	/**
		\brief checks if input is not safe (not GOOD).

		<h3>Return</h3>
		Returns false if e is Tristate::GOOD and true
		else.\n
	*/
	inline bool operator !(
		Tristate e /**< : <i>in</i> : The Tristate to check.*/
		) noexcept
	{
		return (e != Tristate::GOOD);
	}
}

#endif