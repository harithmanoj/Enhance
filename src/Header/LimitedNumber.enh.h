/** ***************************************************************************
	\file numeral_system.enh.h

	\brief The file to declare class for a custom numeral system

	Created 16 May 2020

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

#ifndef NUMERAL_SYSTEM_ENH_H

#define NUMERAL_SYSTEM_ENH_H					numeral_system.enh.h

#include "ConfinedValue.enh.h"

namespace enh
{
	/**
		\brief The class for a value that stays between 0 and upper.

		<h3>template</h3>
		-# <code>integral</code> : The type of value.\n
		-# <code>integral upper</code> : The upper limit for the value.\n
	*/
	template<class integral, integral upper>
	class UnsignedLimitedNumber : public ConfinedValue<integral>
	{
	public:
		
		/**
			\brief The upper limit for values of this type.
		*/
		static constexpr ConfinedValue<integral>::value_type limit = upper;

		/**
			\brief The constructor the class initialises value to 0.
		*/
		constexpr inline UnsignedLimitedNumber() noexcept
			: ConfinedValue<integral>::ConfinedValue(
				[&](long long a) {return a < limit; },
				[&](long long a) { return a >= 0; },
				[&]() {return limit - 1; },
				[&]() {return 0; },
				0)
		{}

		/**
			\brief The constructor initiliases with the value of parameter.

			<h3>Exception</h3>
			Throws <code>std::invalid_argument</code> if value is greater 
			than or equal to upper.
		*/
		constexpr inline UnsignedLimitedNumber(
			ConfinedValue<integral>::value_type val
		) : ConfinedValue<integral>::ConfinedValue(
				[&](long long a) {return a < limit; },
				[&](long long a) { return a >= 0; },
				[&]() {return limit - 1; },
				[&]() {return 0; },
				val)
		{}
	};

	/**
		\brief The class for a value that stays between lower and upper 
		constant numbers.

		<h3>template</h3>
		-# <code>integral</code> : The type of value.\n
		-# <code>integral upper</code> : The upper limit for the value.\n
	*/
	template<class integral, integral lower, integral upper>
	class LimitedNumber : public ConfinedValue<integral>
	{
	public:

		/**
			\brief The upper limit for values of this type.
		*/
		static constexpr ConfinedValue<integral>::value_type upperLimit = upper;

		/**
			\brief The upper limit for values of this type.
		*/
		static constexpr ConfinedValue<integral>::value_type lowerLimit = lower;

		/**
			\brief The constructor the class initialises value to 0.
		*/
		constexpr inline LimitedNumber() noexcept
			: ConfinedValue<integral>::ConfinedValue(
				[&](long long a) {return a < upperLimit; },
				[&](long long a) { return a > lowerLimit; },
				[&]() {return upperLimit - 1; },
				[&]() {return lowerLimit + 1; },
				(upperLimit + lowerLimit)/2)
		{}

		/**
			\brief The constructor initiliases with the value of parameter.

			<h3>Exception</h3>
			Throws <code>std::invalid_argument</code> if value is greater
			than or equal to upper.
		*/
		constexpr inline UnsignedLimitedNumber(
			ConfinedValue<integral>::value_type val
		) : ConfinedValue<integral>::ConfinedValue(
			[&](long long a) {return a < upperLimit; },
			[&](long long a) { return a > lowerLimit; },
			[&]() {return upperLimit - 1; },
			[&]() {return lowerLimit + 1; },
			val)
		{}
	};

	/**
		\brief The namespace for all aliases for 
		different upper limited systems.
	*/
	namespace numeric
	{
		/**
			\brief Type with upper limit at 10.
		*/
		using Decade = UnsignedLimitedNumber<unsigned short, 10U>;
		
		/**
			\brief Type with upper limit at 100.
		*/
		using Centuary = UnsignedLimitedNumber<unsigned short, 100U>;
		
		/**
			\brief Type with upper limit at 1000.
		*/
		using Kilo = UnsignedLimitedNumber<unsigned short, 1000U>;
		
		/**
			\brief Type with upper limit at 1000000.
		*/
		using Million = UnsignedLimitedNumber<unsigned long, 1000000UL>;

		/**
			\brief Type with upper limit at 1000000000.
		*/
		using Billion = UnsignedLimitedNumber<unsigned long, 1000000000ULL>;
	}

}


#endif