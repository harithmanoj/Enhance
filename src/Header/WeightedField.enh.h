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
			unsigned weight[2]
		) noexcept : rawValue{ 0 }, fieldWeight{ weight } {}

		constexpr inline WeightedField(
			value_type val[3],
			unsigned weight[2]
		) noexcept : fieldWeight{ weight }, rawValue{ (val[0] % weight[0]) + ((val[1] % weight[1])
			* weight[0]) + (val[2] * weight[1]) } { }

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

		constexpr inline unsigned short getWeight0() const noexcept 
		{ 
			return 1; 
		}
		
		constexpr inline unsigned getweight1() const noexcept
		{
			return fieldWeight[0];
		}

		constexpr inline unsigned getweight2() const noexcept
		{
			return fieldWeight[1];
		}

		constexpr inline unsigned getweights(
			unsigned short value
		) const noexcept
		{
			if (calue == 0)
				return 1;
			return fieldWeight[(value % 3) - 1];
		}

		constexpr inline unsigned getFields(
			unsigned short value
		) const noexcept
		{
			return (rawValue / getweights(value));
		}

		constexpr inline void setRawValue(
			value_type val
		) noexcept { rawValue = val; }

		constexpr inline void setWeights(
			unsigned weight[2]
		) noexcept
		{
			fieldWeight[0] = weight[0];
			fieldWeight[1] = weight[1];
		}

		constexpr inline void setValue(
			value_type val[3]
		) noexcept
		{
			rawValue = val[0] % fieldWeight[0];
			rawValue += (val[1] % fieldWeight[1]) * fieldWeight[0];
			rawValue += val[2] * fieldWeight[1];

		}

		constexpr inline void setValue(
			value_type val[3], 
			unsigned weight[2]
		) noexcept
		{
			setWeights(weight);
			setValue(val);
		}

		constexpr inline WeightedField<value_type> add(
			value_type val
		) const noexcept
		{
			return WeightedField<value_type>{val + getRaw(), fieldWeight};
		}

		constexpr inline WeightedField<value_type>& saveAdd(
			value_type val
		) noexcept
		{
			setRawValue(getRaw() + val);
			return *this;
		}

		constexpr inline WeightedField<value_type> &operator +=(
			value_type &rhs
		)
		{
			return saveAdd(rhs);
		}

		constexpr inline WeightedField<value_type> add(
			const WeightedField<value_type> &rhs
		) const
		{
			if ((fieldWeight[0] != rhs.fieldWeight[0])
				|| (fieldWeight[1] != rhs.fieldWeight[1]))
				throw std::invalid_argument("Operand must be of same weight");
			return add(rhs.getRaw());
		}

		constexpr inline WeightedField<value_type> &saveAdd(
			const WeightedField<value_type> &rhs
		)
		{
			if ((fieldWeight[0] != rhs.fieldWeight[0])
				|| (fieldWeight[1] != rhs.fieldWeight[1]))
				throw std::invalid_argument("Operand must be of same weight");
			return saveAdd(rhs.getRaw());
		}

		constexpr inline WeightedField<value_type> &operator +=(
			const WeightedField<value_type> &rhs
		)
		{
			return saveAdd(rhs);
		}

		constexpr inline WeightedField<value_type> sub(
			value_type val
		) const noexcept
		{
			return WeightedField<value_type>{ getRaw() - val, fieldWeight};
		}

		constexpr inline WeightedField<value_type> &saveSub(
			value_type val
		) noexcept
		{
			setRawValue(getRaw() - val);
			return *this;
		}

		constexpr inline WeightedField<value_type> &operator -=(
			value_type &rhs
		)
		{
			return saveSub(rhs);
		}

		constexpr inline WeightedField<value_type> sub(
			const WeightedField<value_type> &rhs
		) const
		{
			if ((fieldWeight[0] != rhs.fieldWeight[0])
				|| (fieldWeight[1] != rhs.fieldWeight[1]))
				throw std::invalid_argument("Operand must be of same weight");
			return sub(rhs.getRaw());
		}

		constexpr inline WeightedField<value_type> &saveSub(
			const WeightedField<value_type> &rhs
		)
		{
			if ((fieldWeight[0] != rhs.fieldWeight[0])
				|| (fieldWeight[1] != rhs.fieldWeight[1]))
				throw std::invalid_argument("Operand must be of same weight");
			return saveSub(rhs.getRaw());
		}

		constexpr inline WeightedField<value_type> &operator -=(
			const WeightedField<value_type> &rhs
		)
		{
			return saveSub(rhs);
		}

		constexpr inline WeightedField<value_type> addu(
			value_type val,
			value_type type_max = std::numeric_limits<value_type>::max
		) const noexcept;

		constexpr inline WeightedField<value_type> &saveAddu(
			value_type val,
			value_type type_max = std::numeric_limits<value_type>::max
		) noexcept;

		constexpr inline WeightedField<value_type> subu(
			value_type val,
			value_type type_max = std::numeric_limits<value_type>::max
		) const noexcept
		{
			if (val < 0)
				return addu(-val, type_max);

			if (val > getRaw())
				return WeightedField<value_type>{0, fieldWeight};
			else
				return sub(val);
		}

		constexpr inline WeightedField<value_type> &saveSubu(
			value_type val,
			value_type type_max = std::numeric_limits<value_type>::max
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

		constexpr inline WeightedField<value_type> addu(
			value_type val, 
			value_type type_max = std::numeric_limits<value_type>::max
		) const noexcept
		{
			if (val < 0)
				return subu(-val, type_max);

			value_type temp = val + getRaw();
			if ((temp < val) || (temp < getRaw()))
				return WeightedField<value_type>{type_max, fieldWeight};
			else
				return add(val);
		}

		constexpr inline WeightedField<value_type> &saveAddu(
			value_type val,
			value_type type_max = std::numeric_limits<value_type>::max
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

		constexpr inline WeightedField<value_type> addu(
			const WeightedField<value_type> &rhs,
			value_type type_max = std::numeric_limits<value_type>::max
		) const
		{
			if ((fieldWeight[0] != rhs.fieldWeight[0])
				|| (fieldWeight[1] != rhs.fieldWeight[1]))
				throw std::invalid_argument("Operand must be of same weight");
			return addu(rhs.getRaw(), type_max);
		}

		constexpr inline WeightedField<value_type> &saveAddu(
			const WeightedField<value_type> &rhs,
			value_type type_max = std::numeric_limits<value_type>::max
		)
		{
			if ((fieldWeight[0] != rhs.fieldWeight[0])
				|| (fieldWeight[1] != rhs.fieldWeight[1]))
				throw std::invalid_argument("Operand must be of same weight");
			return saveAddu(rhs.getRaw(), type_max);
		}

		constexpr inline WeightedField<value_type> subu(
			const WeightedField<value_type> &rhs,
			value_type type_max = std::numeric_limits<value_type>::max
		) const
		{
			if ((fieldWeight[0] != rhs.fieldWeight[0])
				|| (fieldWeight[1] != rhs.fieldWeight[1]))
				throw std::invalid_argument("Operand must be of same weight");
			return subu(rhs.getRaw(), type_max);
		}

		constexpr inline WeightedField<value_type> &saveSub(
			const WeightedField<value_type> &rhs,
			value_type type_max = std::numeric_limits<value_type>::max
		)
		{
			if ((fieldWeight[0] != rhs.fieldWeight[0])
				|| (fieldWeight[1] != rhs.fieldWeight[1]))
				throw std::invalid_argument("Operand must be of same weight");
			return saveSubu(rhs.getRaw(), type_max);
		}

		constexpr inline WeightedField<value_type> mult(
			value_type multiplier
		) const noexcept
		{
			return WeightedField<value_type>{getRaw() * multiplier, fieldWeight};
		}

		constexpr inline WeightedField<value_type> &saveMult(
			value_type multiplier
		) noexcept
		{
			setRawValue(getRaw() * multiplier);
			return *this;
		}

		constexpr inline WeightedField<value_type> &operator *=(
			value_type multiplier
		) noexcept
		{
			return saveMult(multiplier);
		}

		constexpr inline WeightedField<value_type> div(
			value_type divisor
		) const
		{
			return WeightedField<value_type>{getRaw() / divisor, fieldWeight};
		}

		constexpr inline WeightedField<value_type> &saveDiv(
			value_type divisor
		)
		{
			setRawValue(getRaw() / divisor);
			return *this;
		}

		constexpr inline WeightedField<value_type> &operator /=(
			value_type divisor
		)
		{
			return saveDiv(divisor);
		}
	};

	template<class T>
	constexpr inline WeightedField<T> operator +(
		const WeightField<T> &lhs,
		T rhs
	) const noexcept
	{
		return lhs.add(rhs);
	}

	template<class T>
	constexpr inline WeightedField<T> operator +(
		T lhs,
		const WeightedField<T> &rhs
	) const noexcept
	{
		return rhs.add(lhs);
	}

	template>class T>
	constexpr inline WeightedField<T> operator +(
		const WeightedField<T> &lhs,
		const WeightedField<T> &rhs
	) const
	{
		return rhs.add(lhs);
	}

	template<class T>
	constexpr inline WeightedField<T> operator -(
		const WeightField<T> &lhs,
		T rhs
	) const noexcept
	{
		return lhs.sub(rhs);
	}

	template<class T>
	constexpr inline WeightedField<T> operator -(
		T lhs,
		const WeightedField<T> &rhs
	) const noexcept
	{
		return WeightedField<T>{lhs - rhs.getRaw(), 
			{ rhs.getWeight1(), rhs.getWeight2() }};
	}

	template > class T >
	constexpr inline WeightedField<T> operator -(
		const WeightedField<T> &lhs,
		const WeightedField<T> &rhs
	) const
	{
		return rhs.sub(lhs);
	}

	template<class T>
	constexpr inline WeightedField<T> operator *(
		const WeightField<T> &lhs,
		T rhs
	) const noexcept
	{
		return lhs.mult(rhs);
	}

	template<class T>
	constexpr inline WeightedField<T> operator *(
		T lhs,
		const WeightedField<T> &rhs
	) const noexcept
	{
		return rhs.mult(lhs);
	}

	template<class T>
	constexpr inline WeightedField<T> operator /(
		const WeightField<T> &lhs,
		T rhs
	) const noexcept
	{
		return lhs.div(rhs);
	}
}


#endif

