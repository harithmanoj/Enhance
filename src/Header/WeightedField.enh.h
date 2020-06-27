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
#include <stdexcept>
#include <array>

namespace enh
{

	template<class integral, unsigned field_c>
	class WeightedField
	{
		static_assert(std::is_integral_v<integral>, "underlying type for "
			"WeightedField must be integral");
		static_assert(field_c >= 2, "field count must be minimum of 2");
	public:

		/**
			\brief The underlying value type used.
		*/
		using value_type = integral;

		constexpr static unsigned fieldCount = field_c;
		constexpr static unsigned weightCount = field_c - 1;

	private:

		value_type rawValue;

		std::array<unsigned, weightCount> fieldWeight;

	public:

		constexpr inline WeightedField() noexcept : rawValue{ 0 }, fieldWeight{ 1 } { }

		explicit constexpr inline WeightedField(
			value_type val
		) noexcept : rawValue{ val }, fieldWeight{ 1 } { }

		constexpr inline WeightedField(
			value_type val,
			std::array<unsigned, weightCount> weight
		) noexcept : rawValue{ val }, fieldWeight{ std::move(weight) } {}

		explicit constexpr inline WeightedField(
			std::array<unsigned, weightCount> weight
		) noexcept : rawValue{ 0 }, fieldWeight{ std::move(weight) } {}

		constexpr inline WeightedField(
			std::array<value_type, fieldCount> val,
			std::array<unsigned, weightCount> weight
		) noexcept : fieldWeight{ std::move(weight) }, rawValue{ (val[0] % static_cast<long>(weight[0])) }
		{ 
			for(unsigned i = 0; i < weightCount - 1; ++i)
				rawValue += (val[i + 1U] % weight[i + 1U]) * weight[i];

			rawValue += val[weightCount] * weight[weightCount - 1U];
		}

		constexpr inline value_type getRaw() const noexcept 
		{ 
			return rawValue; 
		}

		constexpr inline unsigned getWeights(
			unsigned short value
		) const noexcept
		{
			if (value == 0)
				return 1;
			return fieldWeight[(value % 3) - 1];
		}

		constexpr inline const auto& getWeights() const noexcept
		{
			return fieldWeight;
		}

		constexpr inline unsigned getFields(
			unsigned short value
		) const noexcept
		{
			value = value % fieldCount;
			value_type ret = rawValue;
			if (value == 0)
				return ret % fieldWeight[0];
			for (int i = 0; i < value; ++i)
				ret /= fieldWeight[i];
			if (value == weightCount)
				return ret;
			ret = ret % fieldWeight[value];
			return ret;
		}

		constexpr inline void setRawValue(
			value_type val
		) noexcept { rawValue = val; }

		constexpr inline void setWeights(
			std::array<unsigned, weightCount> weight
		) noexcept
		{
			for (unsigned i = 0; i < weightCount; ++i)
				fieldWeight[i] = weight[i];
		}

		constexpr inline void setValue(
			std::array<value_type, fieldCount> val
		) noexcept
		{
			rawValue = (val[0] % static_cast<long>(fieldWeight[0]));
			for (unsigned i = 0; i < weightCount - 1; ++i)
				rawValue += (val[i + 1] % fieldWeight[i + 1]) * fieldWeight[i];

			rawValue += val[weightCount] * fieldWeight[weightCount - 1];

		}

		constexpr inline void setValue(
			std::array<value_type, fieldCount> val,
			std::array<unsigned, weightCount> weight
		) noexcept
		{
			setWeights(std::move(weight));
			setValue(std::move(val));
		}

		constexpr inline WeightedField<value_type, fieldCount> add(
			value_type val
		) const noexcept
		{
			return WeightedField<value_type, fieldCount>{val + getRaw(), std::move(fieldWeight)};
		}

		constexpr inline WeightedField<value_type, fieldCount>& saveAdd(
			value_type val
		) noexcept
		{
			setRawValue(getRaw() + val);
			return *this;
		}

		constexpr inline WeightedField<value_type, fieldCount> &operator +=(
			value_type rhs
		)
		{
			return saveAdd(std::move(rhs));
		}

		constexpr inline WeightedField<value_type, fieldCount> add(
			const WeightedField<value_type, fieldCount> &rhs
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return add(rhs.getRaw());
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveAdd(
			const WeightedField<value_type, fieldCount> &rhs
		)
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return saveAdd(rhs.getRaw());
		}

		constexpr inline WeightedField<value_type, fieldCount> &operator +=(
			const WeightedField<value_type, fieldCount> &rhs
		)
		{
			return saveAdd(rhs);
		}

		constexpr inline WeightedField<value_type, fieldCount> sub(
			value_type val
		) const noexcept
		{
			return WeightedField<value_type, fieldCount>{ getRaw() - val, fieldWeight};
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveSub(
			value_type val
		) noexcept
		{
			setRawValue(getRaw() - val);
			return *this;
		}

		constexpr inline WeightedField<value_type, fieldCount> &operator -=(
			value_type rhs
		)
		{
			return saveSub(std::move(rhs));
		}

		constexpr inline WeightedField<value_type, fieldCount> sub(
			const WeightedField<value_type, fieldCount> &rhs
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return sub(rhs.getRaw());
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveSub(
			const WeightedField<value_type, fieldCount> &rhs
		)
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return saveSub(rhs.getRaw());
		}

		constexpr inline WeightedField<value_type, fieldCount> &operator -=(
			const WeightedField<value_type, fieldCount> &rhs
		)
		{
			return saveSub(rhs);
		}

		constexpr inline WeightedField<value_type, fieldCount> subu(
			value_type val,
			value_type type_max = std::numeric_limits<value_type>::max()
		) const noexcept
		{
			if (val < 0)
				return addu(-val, type_max);

			if (val > getRaw())
				return WeightedField<value_type, fieldCount>{0, fieldWeight};
			else
				return sub(val);
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveSubu(
			value_type val,
			value_type type_max = std::numeric_limits<value_type>::max()
		) noexcept
		{
			if (val < 0)
				return saveAddu(-val, type_max);

			if (val > getRaw())
				setRawValue(0);
			else
				setRawValue(getRaw() - val);

			return *this;
		}

		constexpr inline WeightedField<value_type, fieldCount> addu(
			value_type val, 
			value_type type_max = std::numeric_limits<value_type>::max()
		) const noexcept
		{
			if (val < 0)
				return subu(-val, type_max);

			value_type temp = val + getRaw();
			if ((temp < val) || (temp < getRaw()))
				return WeightedField<value_type, fieldCount>{type_max, fieldWeight};
			else
				return add(val);
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveAddu(
			value_type val,
			value_type type_max = std::numeric_limits<value_type>::max()
		) noexcept
		{
			if (val < 0)
				return saveSubu(-val, type_max);

			value_type temp = val + getRaw();

			if ((temp < val) || (temp < getRaw()))
				setRawValue(type_max);
			else
				setRawValue(val + getRaw());

			return *this;
		}

		constexpr inline WeightedField<value_type, fieldCount> addu(
			const WeightedField<value_type, fieldCount> &rhs,
			value_type type_max = std::numeric_limits<value_type>::max()
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return addu(rhs.getRaw(), type_max);
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveAddu(
			const WeightedField<value_type, fieldCount> &rhs,
			value_type type_max = std::numeric_limits<value_type>::max()
		)
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return saveAddu(rhs.getRaw(), type_max);
		}

		constexpr inline WeightedField<value_type, fieldCount> subu(
			const WeightedField<value_type, fieldCount> &rhs,
			value_type type_max = std::numeric_limits<value_type>::max()
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return subu(rhs.getRaw(), type_max);
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveSubu(
			const WeightedField<value_type, fieldCount> &rhs,
			value_type type_max = std::numeric_limits<value_type>::max()
		)
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return saveSubu(rhs.getRaw(), type_max);
		}

		constexpr inline WeightedField<value_type, fieldCount> mult(
			value_type multiplier
		) const noexcept
		{
			return WeightedField<value_type, fieldCount>{getRaw() * multiplier, fieldWeight};
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveMult(
			value_type multiplier
		) noexcept
		{
			setRawValue(getRaw() * multiplier);
			return *this;
		}

		constexpr inline WeightedField<value_type, fieldCount> &operator *=(
			value_type multiplier
		) noexcept
		{
			return saveMult(multiplier);
		}

		constexpr inline WeightedField<value_type, fieldCount> div(
			value_type divisor
		) const
		{
			return WeightedField<value_type, fieldCount>{getRaw() / divisor, fieldWeight};
		}

		constexpr inline WeightedField<value_type, fieldCount> &saveDiv(
			value_type divisor
		)
		{
			setRawValue(getRaw() / divisor);
			return *this;
		}

		constexpr inline WeightedField<value_type, fieldCount> &operator /=(
			value_type divisor
		)
		{
			return saveDiv(divisor);
		}


		constexpr inline bool operator < (
			value_type val
		) const noexcept
		{
			return (getRaw() < val);
		}

		constexpr inline bool operator < (
			const WeightedField<value_type, fieldCount> &rhs
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return (getRaw() < rhs.getRaw());
		}

		constexpr inline bool operator <= (
			value_type val
		) const noexcept
		{
			return (getRaw() <= val);
		}

		constexpr inline bool operator <= (
			const WeightedField<value_type, fieldCount> &rhs
		) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return (getRaw() <= rhs.getRaw());
		}

		constexpr inline bool operator > (
			value_type val
		) const noexcept
		{
			return (getRaw() > val);
		}

		constexpr inline bool operator > (
			const WeightedField<value_type, fieldCount> &rhs
			) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return (getRaw() > rhs.getRaw());
		}

		constexpr inline bool operator >= (
			value_type val
		) const noexcept
		{
			return (getRaw() > val);
		}

		constexpr inline bool operator >= (
			const WeightedField<value_type, fieldCount> &rhs
			) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					throw std::invalid_argument("Operand must be of same weight");
			return (getRaw() >= rhs.getRaw());
		}

		constexpr inline bool operator == (
			value_type val
		) const noexcept
		{
			return (getRaw() == val);
		}

		constexpr inline bool operator == (
			const WeightedField<value_type, fieldCount> &rhs
			) const noexcept
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
					return false;
			return (getRaw() == rhs.getRaw());
		}

		constexpr inline bool operator != (
			value_type val
		) const noexcept
		{
			return (getRaw() != val);
		}

		constexpr inline bool operator != (
			const WeightedField<value_type, fieldCount> &rhs
			) const
		{
			for (unsigned i = 0; i < weightCount; ++i)
				if (fieldWeight[i] != rhs.fieldWeight[i])
				return true;
			return (getRaw() != rhs.getRaw());
		}
	};

	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator +(
		const WeightedField<T,n> &lhs,
		T rhs
	) noexcept
	{
		return lhs.add(rhs);
	}

	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator +(
		T lhs,
		const WeightedField<T,n> &rhs
	) noexcept
	{
		return rhs.add(lhs);
	}

	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator +(
		const WeightedField<T,n> &lhs,
		const WeightedField<T,n> &rhs
	)
	{
		return rhs.add(lhs);
	}

	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator -(
		const WeightedField<T, n> &lhs,
		T rhs
	) noexcept
	{
		return lhs.sub(rhs);
	}

	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator -(
		T lhs,
		const WeightedField<T,n> &rhs
	) noexcept
	{
		return WeightedField<T,n>{lhs - rhs.getRaw(), 
			{ rhs.getWeight1(), rhs.getWeight2() }};
	}

	template < class T , unsigned n>
	constexpr inline WeightedField<T,n> operator -(
		const WeightedField<T,n> &lhs,
		const WeightedField<T,n> &rhs
	)
	{
		return rhs.sub(lhs);
	}

	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator *(
		const WeightedField<T, n>  &lhs,
		T rhs
	) noexcept
	{
		return lhs.mult(rhs);
	}

	template<class T, unsigned n>
	constexpr inline WeightedField<T,n> operator *(
		T lhs,
		const WeightedField<T,n> &rhs
	) noexcept
	{
		return rhs.mult(lhs);
	}

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

