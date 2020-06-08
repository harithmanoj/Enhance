/** ***************************************************************************
	\file WeightedField.enh.h

	\brief The file to declare class for a weighted field number

	Created 08 June 2020

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

#ifndef WEIGHTED_FIELD_ENH_H


#define WEIGHTED_FIELD_ENH_H

#include <type_traits>

namespace enh
{
	template<class integral>
	class WeightedField
	{
		static_assert(std::is_integral_v<integral>, "underlying type for "
			"WeightedField must be integral");

	public:

		/**
			\brief The underlying value type used.
		*/
		using value_type = integral;

	private:

		value_type rawValue;

		unsigned fieldWeight[2];

	public:

		constexpr inline WeightedField() noexcept : rawValue{ 0 }, fieldWeight{ 1,1 } { }

		constexpr inline WeightedField(
			value_type val
		) noexcept : rawValue{ val }, fieldWeight{ 1,1 } { }

		constexpr inline WeightedField(
			value_type val,
			unsigned weight[2]
		) noexcept : rawValue{ val }, fieldWeight{ weight } {}

		constexpr inline WeightedField(
			value_type val[3],
			unsigned weight[2]
		) noexcept : fieldWeight{ weight }, rawValue{ val[0] + (val[1] 
			* weight[0]) + (val[2] * weight[1]) } {}

		constexpr inline value_type getRaw() const noexcept 
		{ 
			return rawValue; 
		}

		constexpr inline value_type getField0() const noexcept 
		{ 
			return (rawValue % fieldWeight[0]); 
		}

		constexpr inline value_type getField1() const noexcept 
		{ 
			return ((rawValue / fieldWeight[0]) % fieldWeight[1]); 
		}

		constexpr inline value_type getField2() const noexcept
		{
			return (rawValue / (fieldWeight[0] * fieldWeight[1]));
		}
		
		constexpr inline unsigned getweight0() const noexcept
		{
			return fieldWeight[0];
		}

		constexpr inline unsigned getweight1() const noexcept
		{
			return fieldWeight[1];
		}

		constexpr inline unsigned getweights(unsigned short value) const noexcept
		{
			return fieldWeight[value % 2];
		}

	};
}


#endif

