/** ***************************************************************************
	\file ConfinedValue.enh.h

	\brief The file to declare class for confined counts

	Created 16 May 2020

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

#ifndef CONFINED_ENH_H

#define CONFINED_ENH_H							ConfinedValue.enh.h

#include <functional>
#include <stdexcept>


namespace enh
{
	/**
		\brief Define an Integral type that is confined to an interval.

		The interval is specified by two functions set during construction.
		The interval check is done by other function set during construction.

		<h3>template</h3>
		<code>Integral</code> : The Integral type of the _value.

		<h3>Example</h3>

		\include{lineno} confined_base_ex.cpp

	*/
	template<class Integral>
	class ConfinedValue
	{
	public:

		/**
			\brief An alias of the Integral type.
		*/
		using value_type = Integral;

		/**
			\brief The function type of limit checker.
		*/
		using PredicateType = std::function<bool(long long)>;

		/**
			\brief The function type of the limit getter.
		*/
		using limitGetterType = std::function<value_type()>;
	private:

		static_assert(std::is_integral_v<Integral>, "underlying type for "
			"enh::ConfinedValue must be integral");

		/**
			\brief The data.
		*/
		value_type _value;

		/**
			\brief The upper limit checker.
		*/
		PredicateType _upperLimitPredicate;

		/**
			\brief The lower limit checker.
		*/
		PredicateType _lowerLimitPredicate;

		/**
			\brief The upper limit.
		*/
		limitGetterType _upperLimitGetter;

		/**
			\brief The lower limit.
		*/
		limitGetterType _lowerLimitGetter;
	public:

		/**
			\brief Returns upper limit.
		*/
		constexpr inline value_type getUpperLimit() const noexcept
		{
			return _upperLimitGetter();
		}

		/**
			\brief Returns lower limit.
		*/
		constexpr inline value_type getLowerLimit() const noexcept
		{
			return _lowerLimitGetter();
		}

		/**
			\brief Returns upper checking function.
		*/
		constexpr inline PredicateType getUpperPredicate() const noexcept
		{
			return _upperLimitPredicate;
		}
		
		/**
			\brief Returns lower checking function.
		*/
		constexpr inline PredicateType getLowerPredicate() const noexcept
		{
			return _lowerLimitPredicate;
		}

		/**
			\brief Construct the object.

			<h3>Exceptions</h3>
			Throws <code>std::invalid_argument</code> if _value passed fails 
			upper and lower predicate.
			Throws <code>std::invalid_argument</code> if ulimit is less than llimit.
		*/
		constexpr inline ConfinedValue(
			PredicateType upperPredicate /**< : <i>in</i> : The upper bounds 
								  checker.*/,
			PredicateType lowerPredicate /**< : <i>in</i> : The lower bounds
								  checker.*/,
			limitGetterType upperLimit /**< : <i>in</i> : Get the upper bounds.*/,
			limitGetterType lowerLimit /**< : <i>in</i> : Get the lower bounds.*/,
			value_type value /**< : <i>in</i> : The _value to be set.*/
		) :_upperLimitPredicate(upperPredicate), _lowerLimitPredicate(lowerPredicate), _value(value),
			_upperLimitGetter(upperLimit), _lowerLimitGetter(lowerLimit)
		{
			if (_upperLimitGetter() < _lowerLimitGetter())
				throw std::invalid_argument("upper limit should be greater than lower");
			if (!_upperLimitPredicate(value) || !_lowerLimitPredicate(value))
			{
				_value = _lowerLimitGetter() + (_upperLimitGetter() - _lowerLimitGetter()) / 2;
				throw std::invalid_argument("value not within limits");
			}
		}

		/**
			\brief Construct the object, _value as set as lower limit.

			<h3>Exceptions</h3>
			Throws <code>std::invalid_argument</code> if ulimit is less than llimit.
		*/
		constexpr inline ConfinedValue(
			PredicateType upperPredicate /**< : <i>in</i> : The upper bounds
								  checker.*/,
			PredicateType lowerPredicate /**< : <i>in</i> : The lower bounds
								  checker.*/,
			limitGetterType upperLimit /**< : <i>in</i> : Get the upper bounds.*/,
			limitGetterType lowerLimit /**< : <i>in</i> : Get the lower bounds.*/
		) :_upperLimitPredicate(upperPredicate), _lowerLimitPredicate(lowerPredicate),
			_upperLimitGetter(upperLimit), _lowerLimitGetter(lowerLimit), _value(0)
		{
			if (_upperLimitGetter() < _lowerLimitGetter())
				throw std::invalid_argument("upper limit should be greater than"
					" lower");
			_value = _lowerLimitGetter();
		}

		/**
			\brief Sets the _value.

			<h3>Exception</h3>
			Throws <code>std::invalid_argument</code> if _value is not within
			limits.
		*/
		constexpr inline void set(
			const value_type &val /**< : <i>in</i> : The _value to be set.*/
		)
		{
			if (!_upperLimitPredicate(val) || !_lowerLimitPredicate(val))
			{
				throw std::invalid_argument("value not within limits");
			}
			_value = val;
		}

		/**
			\brief Returns the _value held.
		*/
		constexpr inline value_type get() const noexcept { return _value; }

		/**
			\brief Adds single unit to the _value held.

			<h3>Return</h3>
			Returns 1 if _value goes above upper limit and _value is set to 
			lower limit.
		*/
		constexpr inline unsigned add() noexcept
		{
			++_value;
			if (!_upperLimitPredicate(_value))
			{
				_value = _lowerLimitGetter();
				return 1;
			}
			return 0;
		}

		/**
			\brief Adds to the _value held.

			<h3>Return</h3>
			Returns the number of times interval was exceded if _value goes 
			above upper limit.

			for confining between 2 and 9 (inclusive),
			from  _value 6, add(20) will return 3 and sets _value to 5.
		*/
		constexpr inline unsigned long long add(
			unsigned long long additional /**< : <i>in</i> : The number of units to
								  add.*/
		) noexcept
		{
			if (additional == 0)
				return 0;
			unsigned long long rem = additional % (_upperLimitGetter() - _lowerLimitGetter());
			unsigned long long ret = additional / (_upperLimitGetter() - _lowerLimitGetter());

			if (!_upperLimitPredicate((unsigned long long)(_value) + rem))
			{
				_value = _value + rem + _lowerLimitGetter() - _upperLimitGetter() - 1;
				++ret;
			}
			else
				_value += rem;
			return ret;
		}

		/**
			\brief Adds single unit to the _value held.

			<h3>Return</h3>
			Reference to current object.
		*/
		constexpr inline ConfinedValue<value_type> &operator ++() noexcept
		{
			add();
			return *this;
		}

		/**
			\brief Adds single unit to the _value held.

			<h3>Return</h3>
			Previous state of object.
		*/
		constexpr inline ConfinedValue<value_type> operator ++(int) noexcept
		{
			ConfinedValue<value_type> temp = *this;
			add();
			return temp;
		}
		
		/**
			\brief Adds to current object and returns reference to the 
			current object.
		*/
		constexpr inline ConfinedValue<value_type> &operator += (
			unsigned long long val /**< : <i>in</i> : The number of units to
								  add.*/
		)
		{
			add(val);
			return *this;
		}

		/**
			\brief Subtracts one unit from the _value held.

			<h3>Return</h3>
			Returns 1 if _value goes below lower limit and _value is set to
			upper limit.
		*/
		constexpr inline unsigned sub() noexcept
		{
			--_value;
			if (!_lowerLimitPredicate(_value))
			{
				_value = _upperLimitGetter();
				return 1;
			}
			return 0;
		}

		/**
			\brief Subtracts from the _value held.

			<h3>Return</h3>
			Returns the number of times interval was removed from if _value goes
			above upper limit.

			for confining between 2 and 9 (inclusive),
			from  _value 6, sub(20) will return 3 and set _value to 7.
		*/
		constexpr inline unsigned long long sub(
			unsigned long long difference /**< : <i>in</i> : The number of units to
								 subtract.*/
		) noexcept
		{
			if (difference == 0)
				return 0;
		    unsigned long long rem = difference % (_upperLimitGetter() - _lowerLimitGetter());
			unsigned long long ret = difference / (_upperLimitGetter() - _lowerLimitGetter());

			if (!_lowerLimitPredicate(_value - rem))
			{
				_value = _value - rem + _upperLimitGetter() - _lowerLimitGetter() + 1;
				++ret;
			}
			else
				_value = _value - rem;
			return ret;
		}

		/**
			\brief Subtracts single unit from the _value held.

			<h3>Return</h3>
			Reference to current object.
		*/
		constexpr inline ConfinedValue<value_type> &operator --() noexcept
		{
			sub();
			return *this;
		}

		/**
			\brief Subtracts single unit from the _value held.

			<h3>Return</h3>
			Previous state of object.
		*/
		constexpr inline ConfinedValue<value_type> operator --(int) noexcept
		{
			ConfinedValue<value_type> temp = *this;
			sub();
			return temp;
		}

		/**
			\brief Subtracts from the current object and returns reference 
			to the current object.
		*/
		constexpr inline ConfinedValue<value_type> &operator -= (
			unsigned long long val /**< : <i>in</i> : The number of units to
								  subtract.*/
		)
		{
			sub(val);
			return *this;
		}

		/**
			\brief Re-evaluates _value according to predicate if anything 
			changed.

			Sets _value to ulimit if exceeding upper, llimit if lower then lower limit.

			This is used if the predicate changes according to other values,

			Like if the predicate depends on a global variable or if it is a 
			lambda that captures by reference.

			<h3>Return</h3>
			Returns true if any change happend.
		*/
		constexpr inline bool reValidateValue() noexcept
		{
			if (!_upperLimitPredicate(_value))
			{
				_value = _upperLimitGetter();
				return true;
			}
			if (!_lowerLimitPredicate(_value))
			{
				_value = _lowerLimitGetter();
				return true;
			}
			return false;
		}

	};

	/**
		\brief Adds rhs to a copy of lhs then returns the sum. 
	*/
	template<class Integral>
	constexpr inline ConfinedValue<Integral> operator +(
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : LHS argument 
										   of operator.*/,
		const unsigned long long &rhs /**< : <i>in</i> : RHS argument of operator.*/
	) noexcept
	{
		auto t =(lhs);
		t.add(rhs);
		return t;
	}

	/**
		\brief Adds lhs to a copy of rhs then returns the sum.
	*/
	template<class Integral>
	constexpr inline ConfinedValue<Integral> operator +(
		const unsigned long long &lhs  /**< : <i>in</i> : LHS argument of operator.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : RHS argument
										   of operator.*/
	) noexcept
	{
		auto t = (rhs);
		t.add(lhs);
		return t;
	}

	/**
		\brief Subtracts rhs to a copy of lhs then returns the difference.
	*/
	template<class Integral>
	constexpr inline ConfinedValue<Integral> operator -(
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : LHS argument
										   of operator.*/,
		const unsigned long long &rhs /**< : <i>in</i> : RHS argument of operator.*/
		) noexcept
	{
		auto t = (lhs);
		t.sub(rhs);
		return t;
	}

	/**
		\brief Subtracts lhs to a copy of rhs then returns the difference.
	*/
	template<class Integral>
	constexpr inline ConfinedValue<Integral> operator -(
		const unsigned long long &lhs  /**< : <i>in</i> : LHS argument of operator.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : RHS argument
										   of operator.*/
		) noexcept
	{
		auto t = (rhs);
		t.sub(lhs);
		return t;
	}

	


	/**
		\brief Checks if lhs is equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator == (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand 
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() == rhs.get());
	}

	/**
		\brief Checks if lhs is not equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator != (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() != rhs.get());
	}

	/**
		\brief Checks if lhs is greater than rhs.
	*/
	template<class Integral>
	constexpr inline bool operator > (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() > rhs.get());
	}

	/**
		\brief Checks if lhs is greater than or equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator >= (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() >= rhs.get());
	}

	/**
		\brief Checks if lhs is lesser than rhs.
	*/
	template<class Integral>
	constexpr inline bool operator < (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() < rhs.get());
	}

	/**
		\brief Checks if lhs is lesser than or equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator <= (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() < rhs.get());
	}




	/**
		\brief Checks if lhs is equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator == (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const long long &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() == rhs);
	}

	/**
		\brief Checks if lhs is not equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator != (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const long long &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() != rhs);
	}

	/**
		\brief Checks if lhs is greater than rhs.
	*/
	template<class Integral>
	constexpr inline bool operator > (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const long long &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() > rhs);
	}

	/**
		\brief Checks if lhs is greater than or equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator >= (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const long long &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() >= rhs);
	}

	/**
		\brief Checks if lhs is lesser than rhs.
	*/
	template<class Integral>
	constexpr inline bool operator < (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const long long &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() < rhs);
	}

	/**
		\brief Checks if lhs is lesser than or equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator <= (
		const ConfinedValue<Integral> &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const long long &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs.get() < rhs);
	}



	/**
		\brief Checks if lhs is equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator == (
		const long long &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs == rhs.get());
	}

	/**
		\brief Checks if lhs is not equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator != (
		const long long &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs != rhs.get());
	}

	/**
		\brief Checks if lhs is greater than rhs.
	*/
	template<class Integral>
	constexpr inline bool operator > (
		const long long &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs > rhs.get());
	}

	/**
		\brief Checks if lhs is greater than or equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator >= (
		const long long &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs >= rhs.get());
	}

	/**
		\brief Checks if lhs is lesser than rhs.
	*/
	template<class Integral>
	constexpr inline bool operator < (
		const long long &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs < rhs.get());
	}

	/**
		\brief Checks if lhs is lesser than or equal to rhs.
	*/
	template<class Integral>
	constexpr inline bool operator <= (
		const long long &lhs /**< : <i>in</i> : The left hand
										   side of the expression.*/,
		const ConfinedValue<Integral> &rhs /**< : <i>in</i> : The right hand
										   side of the expression.*/
		) noexcept
	{
		return (lhs < rhs.get());
	}

}



#endif