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


#	define WEIGHTED_FIELD_ENH_H							WeightedField.enh.h

#	include <type_traits>
#	include <stdexcept>
#	include <array>
#	include <algorithm>
#	include <execution>

namespace enh
{

	/**
		\brief Class to represent number distributed in many weighted fields.

		<h3>template</h3>
		<code>integral</code> : The underlying type to store data.\n
		<code>unsigned field_c </code> : The Number of weighted fields.\n


	*/
	template<class integral, unsigned field_c>
	class WeightedField
	{
		// Underlying type must be integral.
		static_assert(std::is_integral_v<integral>, "underlying type for "
			"WeightedField must be integral");

		// Cannot have field size < 2 
		static_assert(field_c >= 2, "field count must be minimum of 2");
	public:

		/**
			\brief The underlying value type used.
		*/
		using value_type = integral;

		/**
			\brief The number of fields present.
		*/
		constexpr static unsigned fieldCount = field_c;

		/**
			\brief The number of weights, not including first (implied 1).
		*/
		constexpr static unsigned weightCount = field_c - 1;

	private:

		/**
			\brief Underlying value stored as compounded weighted sum of all 
			fields.
		*/
		value_type _rawValue;

		/**
			\brief Weights of all fields (compounded excluding the implied 
			lowest weight 1.

			Index 0 will have lowest weight, with compounded weights as 
			index increases.

			1(implied) , 10, 20 will mean that it is a 3 field value with 
			lowest weight
			of 1, middle 10 and highest 200. 
		*/
		std::array<unsigned, weightCount> _fieldWeight;

		/**
			\brief Verify validity of weights (must be greater than 1).
		*/
		constexpr inline bool verifyWeights() const noexcept
		{
			for (auto i : _fieldWeight)
				if (i <= 1)
					return false;
			return true;
		}

		/**
			\brief Sets fieldWeights to default value (10).
		*/
		constexpr inline void setDefaultWeights() noexcept
		{
			for (auto &i : _fieldWeight)
				i = 10;
		}

	public:

		/**
			\brief Sets the raw value (compounded weighted sum)
		*/
		constexpr inline void setRawValue(
			value_type val /**< : <i>in</i> : The value to set.*/
		) noexcept
		{
			_rawValue = val;
		}

		/**
			\brief Sets weights to given weights.

			Throws <code>std::invalid_argument</code> if invalid weights are
			provided.
		*/
		constexpr inline void setWeights(
			std::array<unsigned, weightCount> weight /**< : <i>in</i> : 
									 The weights to set.*/
		) noexcept
		{
			_fieldWeight = std::move(weight);
			if (!verifyWeights())
			{
				setDefaultWeights();
				throw std::invalid_argument("Field Weights must be "
					"greater than 1");
			}
		}

		/**
			\brief Sets value to compounded weighted sum of given values.
		*/
		constexpr inline void setValue(
			const std::array<value_type, fieldCount> &val /**< : <i>in</i> 
											: The values for each field.*/
		) noexcept
		{
			unsigned long incremental = 1;
			auto next = val.begin();
			for (auto i : _fieldWeight)
			{
				_rawValue += ((*next) % i) * incremental;
				incremental *= i;
				++next;
			}

			_rawValue += (*next) * incremental;
		}

		/**
			\brief Sets weights and value.

			Throws <code>std::invalid_argument</code> if invalid weights are
			provided.
		*/
		constexpr inline void setValue(
			std::array<value_type, fieldCount> val /**< : <i>in</i> 
											: The values for each field.*/,
			std::array<unsigned, weightCount> weight /**< : <i>in</i> : 
									 The weights to set.*/
		) noexcept
		{
			setWeights(std::move(weight));
			setValue(std::move(val));
		}

		/**
			\brief Constructs with initial value 0 and decade weights.
		*/
		constexpr inline WeightedField() noexcept : _rawValue{ 0 }, 
			_fieldWeight{ 0 } { setDefaultWeights(); }

		/**
			\brief Constructs with initial value as parameter and decade 
			weights.
		*/
		explicit constexpr inline WeightedField(
			value_type val /**< : <i>in</i> : The initial value of the 
						   object.*/
		) noexcept : _rawValue{ val }, _fieldWeight{ 0 }
		{ setDefaultWeights(); }

		/**
			\brief Constructs with initial value given and weights provided.

			Throws <code>std::invalid_argument</code> if invalid weights are 
			provided.
		*/
		constexpr inline WeightedField(
			value_type val /**< : <i>in</i> : The initial value of the 
						   object. */,
			std::array<unsigned, weightCount> weight /**< : <i>in</i> : 
							The weights to be set (index 0 is the lowest 
							level after implicit weight 1. */
		) : _rawValue{ val }, _fieldWeight{ std::move(weight) } 
		{
			if (!verifyWeights())
			{
				setDefaultWeights();
				throw std::invalid_argument("Field Weights must be greater "
					"than 1");
			}
		}

		/**
			\brief Constructs with initial value 0 and weights provided.

			Throws <code>std::invalid_argument</code> if invalid weights are 
			provided.
		*/
		explicit constexpr inline WeightedField(
			std::array<unsigned, weightCount> weight /**< : <i>in</i> :
							The weights to be set (index 0 is the lowest
							level after implicit weight 1. */
		) noexcept : _rawValue{ 0 }, _fieldWeight{ std::move(weight) }
		{
			if (!verifyWeights())
			{
				setDefaultWeights();
				throw std::invalid_argument("Field Weights must be greater "
					"than 1");
			}
		}

		/**
			\brief Constructs with initial value as weighted sum of first 
			parameter and weights given.

			Throws <code>std::invalid_argument</code> if invalid weights are 
			provided.
		*/
		constexpr inline WeightedField(
			std::array<value_type, fieldCount> val /**< : <i>in</i> : The 
							values of each field as an array.*/,
			std::array<unsigned, weightCount> weight /**< : <i>in</i> :
							The weights to be set (index 0 is the lowest
							level after implicit weight 1. */
		) noexcept : _fieldWeight{ std::move(weight) }, _rawValue{ 0 }
		{
			if (!verifyWeights())
			{
				setDefaultWeights();
				throw std::invalid_argument("Field Weights must be greater "
					"than 1");
			}
			setValue(std::move(val));
		}

		/**
			\brief Returns the raw Value.

			<h3>Return</h3>
			Returns the raw Value (compounded weighted sum of all fields).
		*/
		constexpr inline value_type getRaw() const noexcept 
		{ 
			return _rawValue; 
		}

		/**
			\brief Returns weight of value'th field with respect to last field.

			<h3>Return</h3>
			Returns the relative weight associated with that field.

		*/
		constexpr inline unsigned getWeights(
			unsigned short value
		) const noexcept
		{
			if (value == 0)
				return 1;
			return _fieldWeight[(value % fieldCount) - 1];
		}

		/**
			\brief Returns The absolute (compounded ) weight of a field.

			<h3>Return</h3>
			(relative to lowest field with absolute weight of 1).

		*/
		constexpr inline unsigned long getAbsoluteWeights(
			unsigned short value /**< : <i>in</i> : The index of field.*/
		) const noexcept
		{
			unsigned long ret = 1;
			for (int i = 0; i < (value % fieldCount); ++i)
				ret *= _fieldWeight[i];
			return ret;
		}

		/**
			\brief Returns The relative weights as an array.

			<h3>Return</h3>
			Returns the relative weights as an const reference to an array.
		*/
		constexpr inline const auto& getWeights() const noexcept
		{
			return _fieldWeight;
		}

		/**
			\brief Returns The absolute weights as an array.

			<h3>Return</h3>
			Returns the absolute weights as an array.
		*/
		constexpr inline auto getAbsoluteWeights() const noexcept
		{
			std::array<unsigned, fieldCount> absWeight;
			absWeight[0] = 1;
			
			for (unsigned i = 0; i < weightCount; ++i)
				absWeight[i + 1] = absWeight[i] * _fieldWeight[i];

			return absWeight;
		}

		/**
			\brief Get the value of certian field.
		*/
		constexpr inline unsigned getFields(
			unsigned short value /**< : <i>in</i> : The index of the field.*/
		) const noexcept
		{
			if (value == weightCount)
				return (_rawValue / getAbsoluteWeights(value));
			else
				return (_rawValue / getAbsoluteWeights(value)) 
				% getWeights(value + 1);
		}

		
		/**
			\brief Returns sum of raw value and current object.

			<h3>Return</h3>
			Returns the sum.
		*/
		constexpr inline WeightedField<value_type, fieldCount> add(
			value_type val /**< : <i>in</i> : The value to be added.*/
		) const noexcept
		{
			return WeightedField<value_type, fieldCount>{val + getRaw(), 
				std::move(_fieldWeight)};
		}

		/**
			\brief Adds raw value to current objects.

			<h3>Return</h3>
			Returns the sum.
		*/
		constexpr inline WeightedField<value_type, fieldCount>& saveAdd(
			value_type val /**< : <i>in</i> : The value to be added.*/
		) noexcept
		{
			setRawValue(getRaw() + val);
			return (*this);
		}

		/**
			\brief operator overloaded to add and save.

			<h3>Return</h3>
			Returns reference to current object.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &operator +=(
			value_type rhs /**< : <i>in</i> : The value to be added.*/
		)
		{
			return saveAdd(std::move(rhs));
		}

		/**
			\brief Returns sum of current object and parameter.

			<h3>Return</h3>
			Sum of current object and paramater.

			<h3>Exception</h3>
			Throws if weights are not same.
		*/
		constexpr inline WeightedField<value_type, fieldCount> add(
			const WeightedField<value_type, fieldCount> &rhs  /**< : <i>in</i> 
													: The object to be added.*/
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return add(rhs.getRaw());
		}

		/**
			\brief Adds parameter to current object.

			<h3>Return</h3>
			Reference to current object.

			<h3>Exception</h3>
			Throws if weights are not same.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveAdd(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
													: The object to be added.*/
		)
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return saveAdd(rhs.getRaw());
		}

		/**
			\brief Adds parameter to current object.

			<h3>Return</h3>
			Reference to current object.

			<h3>Exception</h3>
			Throws if weights are not same.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &operator +=(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
													: The object to be added.*/
		)
		{
			return saveAdd(rhs);
		}

		/**
			\brief Returns difference of raw value and current object.

			<h3>Return</h3>
			Returns the difference.
		*/
		constexpr inline WeightedField<value_type, fieldCount> sub(
			value_type val /**< : <i>in</i> : The value to be subtracted.*/
		) const noexcept
		{
			return WeightedField<value_type, fieldCount>{ getRaw() - val,
				_fieldWeight};
		}

		/**
			\brief Returns difference of raw value and current object.

			<h3>Return</h3>
			Returns the difference.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveSub(
			value_type val /**< : <i>in</i> : The value to be subtracted.*/
		) noexcept
		{
			setRawValue(getRaw() - val);
			return (*this);
		}

		/**
			\brief operator overloaded to subtract and save.

			<h3>Return</h3>
			Returns reference to current object.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &operator -=(
			value_type rhs /**< : <i>in</i> : The value to be subtracted.*/
		)
		{
			return saveSub(std::move(rhs));
		}

		/**
			\brief Returns sum of current object and parameter.

			<h3>Return</h3>
			Sum of current object and paramater.

			<h3>Exception</h3>
			Throws if weights are not same.
		*/
		constexpr inline WeightedField<value_type, fieldCount> sub(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
											: The object to be subtracted.*/
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return sub(rhs.getRaw());
		}

		/**
			\brief subtracts parameter from object.

			<h3>Return</h3>
			Sum of current object and paramater.

			<h3>Exception</h3>
			Throws if weights are not same.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveSub(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
											: The object to be subtracted.*/
		)
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return saveSub(rhs.getRaw());
		}

		/**
			\brief subtracts parameter from object.

			<h3>Return</h3>
			Sum of current object and paramater.

			<h3>Exception</h3>
			Throws if weights are not same.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &operator -=(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
											: The object to be subtracted.*/
		)
		{
			return saveSub(rhs);
		}

		/**
			\brief Returns difference with no overflow or underflow.

			<h3>Return</h3>
			The difference between current object and parameter.
		*/
		constexpr inline WeightedField<value_type, fieldCount> subu(
			value_type val /**< : <i>in</i> : The value to be subtracted.*/,
			value_type type_max = std::numeric_limits<value_type>::max() 
								/**< : <i>in</i> : The maximum value for the 
									value_type.*/
		) const noexcept
		{
			if (val < 0)
				return addu(-val, type_max);
			else if (val > getRaw())
				return WeightedField<value_type, fieldCount>{0, _fieldWeight};
			else
				return sub(val);
		}

		/**
			\brief subtracts parameter with no overflow or underflow.

			<h3>Return</h3>
			Reference to current object.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveSubu(
			value_type val /**< : <i>in</i> : The value to be subtracted.*/,
			value_type type_max = std::numeric_limits<value_type>::max()
								/**< : <i>in</i> : The maximum value for the
									value_type.*/
		) noexcept
		{
			if (val < 0)
				return saveAddu(-val, type_max);
			else if (val > getRaw())
				setRawValue(0);
			else
				setRawValue(getRaw() - val);

			return (*this);
		}

		/**
			\brief Returns sum with no overflow or underflow.

			<h3>Return</h3>
			The sum of current object and parameter.
		*/
		constexpr inline WeightedField<value_type, fieldCount> addu(
			value_type val /**< : <i>in</i> : The value to be added.*/,
			value_type type_max = std::numeric_limits<value_type>::max()
								/**< : <i>in</i> : The maximum value for the
									value_type.*/
		) const noexcept
		{
			if (val < 0)
				return subu(-val, type_max);

			value_type temp = val + getRaw();
			if ((temp < val) || (temp < getRaw()))
				return WeightedField<value_type, fieldCount>{type_max,
				_fieldWeight};
			else
				return add(val);
		}

		/**
			\brief Adds parameter to object with no overflow or underflow.

			<h3>Return</h3>
			The Reference to current object.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveAddu(
			value_type val /**< : <i>in</i> : The value to be added.*/,
			value_type type_max = std::numeric_limits<value_type>::max()
								/**< : <i>in</i> : The maximum value for the
									value_type.*/
		) noexcept
		{
			if (val < 0)
				return saveSubu(-val, type_max);

			value_type temp = val + getRaw();

			if ((temp < val) || (temp < getRaw()))
				setRawValue(type_max);
			else
				setRawValue(val + getRaw());

			return (*this);
		}

		/**
			\brief Returns sum with no overflow or underflow.

			<h3>Return</h3>
			The sum of current object and parameter.
		*/
		constexpr inline WeightedField<value_type, fieldCount> addu(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
												: The value to be added.*/,
			value_type type_max = std::numeric_limits<value_type>::max()
								/**< : <i>in</i> : The maximum value for the
									value_type.*/
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return addu(rhs.getRaw(), type_max);
		}

		/**
			\brief Adds parameter to object with no overflow or underflow.

			<h3>Return</h3>
			The Reference to current object.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveAddu(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
												: The value to be added.*/,
			value_type type_max = std::numeric_limits<value_type>::max()
								/**< : <i>in</i> : The maximum value for the
														value_type.*/
		)
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return saveAddu(rhs.getRaw(), type_max);
		}

		/**
			\brief Returns difference with no overflow or underflow.

			<h3>Return</h3>
			The difference between current object and parameter.
		*/
		constexpr inline WeightedField<value_type, fieldCount> subu(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
											: The value to be subtracted.*/,
			value_type type_max = std::numeric_limits<value_type>::max()
								/**< : <i>in</i> : The maximum value for the
														value_type.*/
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return subu(rhs.getRaw(), type_max);
		}

		/**
			\brief subtracts parameter with no overflow or underflow.

			<h3>Return</h3>
			Reference to current object.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveSubu(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
											: The value to be subtracted.*/,
			value_type type_max = std::numeric_limits<value_type>::max()
								/**< : <i>in</i> : The maximum value for the
									value_type.*/
		)
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return saveSubu(rhs.getRaw(), type_max);
		}

		/**
			\brief Returns product of current object and value with a 
			weight of 1.

			<h3>Return</h3>
			Returns the product of multiplier and raw Value.
		*/
		constexpr inline WeightedField<value_type, fieldCount> mult(
			value_type multiplier /**< : <i>in</i> : The number to be 
								  multiplied by.*/
		) const noexcept
		{
			return WeightedField<value_type, fieldCount>{getRaw() * multiplier,
				_fieldWeight};
		}

		/**
			\brief multiplies current object with value with a
			weight of 1.

			<h3>Return</h3>
			Returns reference to current objects.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveMult(
			value_type multiplier /**< : <i>in</i> : The number to be 
								  multiplied by.*/
		) noexcept
		{
			setRawValue(getRaw() * multiplier);
			return (*this);
		}

		/**
			\brief multiplies current object with value with a
			weight of 1.

			<h3>Return</h3>
			Returns reference to current objects.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &operator *=(
			value_type multiplier /**< : <i>in</i> : The number to be 
								  multiplied by.*/
		) noexcept
		{
			return saveMult(multiplier);
		}

		/**
			\brief Returns quotient of current object devided by value with a
			weight of 1.

			<h3>Return</h3>
			Returns the quotient of current object devided by divisor.
		*/
		constexpr inline WeightedField<value_type, fieldCount> div(
			value_type divisor /**< : <i>in</i> : The number to be 
								  divided by.*/
		) const
		{
			return WeightedField<value_type, fieldCount>{getRaw() / divisor,
				_fieldWeight};
		}

		/**
			\brief Sets current object to quotient of current object devided 
			by value with a weight of 1.

			<h3>Return</h3>
			Returns reference to current object.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &saveDiv(
			value_type divisor /**< : <i>in</i> : The number to be 
								  divided by.*/
		)
		{
			setRawValue(getRaw() / divisor);
			return (*this);
		}

		/**
			\brief Sets current object to quotient of current object devided
			by value with a weight of 1.

			<h3>Return</h3>
			Returns reference to current object.
		*/
		constexpr inline WeightedField<value_type, fieldCount> &operator /=(
			value_type divisor /**< : <i>in</i> : The number to be 
								  divided by.*/
		)
		{
			return saveDiv(divisor);
		}

		/**
			\brief Checks whether object is less than parameter.

			<h3>Return</h3>
			True if lhs less than rhs.
		*/
		constexpr inline bool operator < (
			value_type val /**< : <i>in</i> : Value to compare with.*/
		) const noexcept
		{
			return (getRaw() < val);
		}

		/**
			\brief Checks whether object is less than parameter.

			<h3>Return</h3>
			True if lhs less than rhs.

			<h3>Exceptions</h3>
			Throws if they dont have same weights.
		*/
		constexpr inline bool operator < (
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
												: Value to compare with.*/
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return (getRaw() < rhs.getRaw());
		}

		/**
			\brief Checks whether object is less than or equal to parameter.

			<h3>Return</h3>
			True if lhs less than or equal to rhs.
		*/
		constexpr inline bool operator <= (
			value_type val /**< : <i>in</i> : Value to compare with.*/
		) const noexcept
		{
			return (getRaw() <= val);
		}

		/**
			\brief Checks whether object is less than or equal to parameter.

			<h3>Return</h3>
			True if lhs less than or equal to rhs.

			<h3>Exceptions</h3>
			Throws if they dont have same weights.
		*/
		constexpr inline bool operator <= (
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
												: Value to compare with.*/
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return (getRaw() <= rhs.getRaw());
		}

		/**
			\brief Checks whether object is greater than parameter.

			<h3>Return</h3>
			True if lhs greater than rhs.
		*/
		constexpr inline bool operator > (
			value_type val /**< : <i>in</i> : Value to compare with.*/
		) const noexcept
		{
			return (getRaw() > val);
		}

		/**
			\brief Checks whether object is greater than parameter.

			<h3>Return</h3>
			True if lhs greater than rhs.

			<h3>Exceptions</h3>
			Throws if they dont have same weights.
		*/
		constexpr inline bool operator > (
			const WeightedField<value_type, fieldCount> &rhs/**< : <i>in</i> 
												: Value to compare with.*/
			) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return (getRaw() > rhs.getRaw());
		}

		/**
			\brief Checks whether object is greater than or equal to parameter.

			<h3>Return</h3>
			True if lhs greater than or equal to rhs.
		*/
		constexpr inline bool operator >= (
			value_type val  /**< : <i>in</i> : Value to compare with.*/
		) const noexcept
		{
			return (getRaw() > val);
		}

		/**
			\brief Checks whether object is greater than or equal to parameter.

			<h3>Return</h3>
			True if lhs greater than or equal to rhs.

			<h3>Exceptions</h3>
			Throws if they dont have same weights.
		*/
		constexpr inline bool operator >= (
			const WeightedField<value_type, fieldCount> &rhs/**< : <i>in</i> 
												: Value to compare with.*/
			) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					throw std::invalid_argument("Operand must be of same "
						"weight");
			return (getRaw() >= rhs.getRaw());
		}

		/**
			\brief Checks whether object is equal to parameter.

			<h3>Return</h3>
			True if lhs equal to rhs.
		*/
		constexpr inline bool operator == (
			value_type val  /**< : <i>in</i> : Value to compare with.*/
		) const noexcept
		{
			return (getRaw() == val);
		}

		/**
			\brief Checks whether object is equal to parameter.

			Weights must be same as well.

			<h3>Return</h3>
			True if lhs equal to rhs.
		*/
		constexpr inline bool operator == (
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
												: Value to compare with.*/
			) const noexcept
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					return false;
			return (getRaw() == rhs.getRaw());
		}

		/**
			\brief Checks whether object is not equal to parameter.

			Weights is checked as well.

			<h3>Return</h3>
			True if lhs equal to rhs.
		*/
		constexpr inline bool operator != (
			value_type val /**< : <i>in</i> : Value to compare with.*/
		) const noexcept
		{
			return (getRaw() != val);
		}


		/**
			\brief Checks whether object is not equal to parameter.

			Weights is checked as well.

			<h3>Return</h3>
			True if lhs equal to rhs.
		*/
		constexpr inline bool operator != (
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i> 
												: Value to compare with.*/
		) const noexcept
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
				return true;
			return (getRaw() != rhs.getRaw());
		}

		/**
			\brief Checks if weights are same.

			<h3>Return</h3>
			Returns true if weights are same.
		*/
		constexpr inline bool isSameWeights(
			const WeightedField<value_type, fieldCount> &rhs /**< : <i>in</i>
												: Value to compare with.*/

		) const noexcept
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (_fieldWeight[i] != rhs._fieldWeight[i])
					return false;
			return true;
		}
	};

	/**
		\brief operator + overloaded for WeightedField class.

		Adds both parameters.
	*/
	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator +(
		const WeightedField<T,n> &lhs,
		T rhs
	) noexcept
	{
		return lhs.add(rhs);
	}

	/**
		\brief operator + overloaded for WeightedField class.

		Adds both parameters.
	*/
	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator +(
		T lhs,
		const WeightedField<T,n> &rhs
	) noexcept
	{
		return rhs.add(lhs);
	}

	/**
		\brief operator + overloaded for WeightedField class.

		Adds both parameters.

		<h3>Exception</h3>
		Throws if weights are not same.
	*/
	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator +(
		const WeightedField<T,n> &lhs,
		const WeightedField<T,n> &rhs
	)
	{
		return rhs.add(lhs);
	}

	/**
		\brief operator - overloaded for WeightedField class.

		subtracts rhs from lhs.
	*/
	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator -(
		const WeightedField<T, n> &lhs,
		T rhs
	) noexcept
	{
		return lhs.sub(rhs);
	}

	/**
		\brief operator - overloaded for WeightedField class.

		subtracts rhs from lhs.
	*/
	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator -(
		T lhs,
		const WeightedField<T,n> &rhs
	) noexcept
	{
		return WeightedField<T,n>{lhs - rhs.getRaw(), 
			{ rhs.getWeight1(), rhs.getWeight2() }};
	}

	/**
		\brief operator - overloaded for WeightedField class.

		subtracts rhs from lhs.

		<h3>Exception</h3>
		Throws if weights are not same.
	*/
	template < class T , unsigned n>
	constexpr inline WeightedField<T,n> operator -(
		const WeightedField<T,n> &lhs,
		const WeightedField<T,n> &rhs
	)
	{
		return rhs.sub(lhs);
	}

	/**
		\brief operator * overloaded for WeightedField class.

		multiplies both parameters.
	*/
	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator *(
		const WeightedField<T, n>  &lhs,
		T rhs
	) noexcept
	{
		return lhs.mult(rhs);
	}

	/**
		\brief operator * overloaded for WeightedField class.

		multiplies both parameters.
	*/
	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator *(
		T lhs,
		const WeightedField<T,n> &rhs
	) noexcept
	{
		return rhs.mult(lhs);
	}

	/**
		\brief operator / overloaded for WeightedField class.

		divides lhs by rhs and returns quotient.
	*/
	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator /(
		const WeightedField<T, n> &lhs,
		T rhs
	) noexcept
	{
		return lhs.div(rhs);
	}

	
}


#endif

