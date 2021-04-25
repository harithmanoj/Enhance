/** ***************************************************************************
	\file TimeStamp.enh.h

	\brief File for time class.

	Created 13 May 2020

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

#ifndef TIME_STAMP_ENH_H

#define TIME_STAMP_ENH_H				time_stamp.enh.h

#include "date.enh.h"

namespace enh
{
	namespace numeric
	{
		/**
			\brief The confined type for seconds.
		*/
		using Seconds = enh::UnsignedLimitedNumber<std::uint8_t, 60>;
		
		/**
			\brief The confined type for minutes.
		*/
		using Minutes = enh::UnsignedLimitedNumber<std::uint8_t, 60>;
		
		/**
			\brief The confined type for hours.
		*/
		using Hours = enh::UnsignedLimitedNumber<std::uint8_t, 24>;
	}

	/**
		\brief Class for time manipulation.

		<h3> Examples </h3>

		\include{lineno} TimeStamp.ex.cpp
	*/
	class TimeStamp
	{
		/**
			\brief The seconds part of time [0,60].
		*/
		numeric::Seconds _seconds;
		
		/**
			\brief The minutes part of time [0,59].
		*/
		numeric::Minutes _minutes;

		/**
			\brief The hours part of time [0,23].
		*/
		numeric::Hours _hours;

	public:

		/**
			\brief Mask for Hours part of raw time.
		*/
		static constexpr std::bitset<20> hourMask = 0x0'00'3fu;

		/**
			\brief Position of Hours in raw time.
		*/
		static constexpr std::uint8_t hourPosition = 0u;

		/**
			\brief Mask for minutes part of raw time.
		*/
		static constexpr std::bitset<20> minuteMask = 0x0'0f'c0u;

		/**
			\brief Position of minutes in raw time.
		*/
		static constexpr std::uint8_t minutePosition = 6u;

		/**
			\brief Mask for seconds part of raw time.
		*/
		static constexpr std::bitset<20> secondsMask = 0x3'f0'00u;

		/**
			\brief Position of seconds in raw time.
		*/
		static constexpr std::uint8_t secondsPosition = 12u;


		/**
			\brief Get the time as a 20 bit stream
			 (for use as bitstream, storage or transmit time).
		*/
		inline std::bitset<20> getTimeRaw() const noexcept
		{
			std::bitset<20> ret;
			ret.reset();

			ret |= static_cast<std::uint32_t>(_hours.get());
			ret |= static_cast<std::uint32_t>(_minutes.get()) << 6;
			ret |= static_cast<std::uint32_t>(_seconds.get()) << 12;
			return ret;
		}

		/**
			\brief Use 20 bit stream Time representation
			( from enh::TimeStamp::getTimeRaw() ) to set Time.
		*/
		inline void setTimeRaw(
			std::bitset<20> data /**< : <i>in</i> : The 20 bit time
							   representation. */
		) noexcept
		{
			_hours.set(		(data & hourMask)							.to_ulong());
			_minutes.set((	(data & minuteMask)		>> minutePosition)	.to_ulong());
			_seconds.set((	(data & secondsMask)	>> secondsPosition)	.to_ulong());
		}

		/**
			\brief Sets the time to the time indicated by arguments.

			<h3>Exception</h3>
			Throws <code>std::invalid_argument</code> if sec, min, hr is
			not within bounds. [0,60], [0,59], [0,23] respectively.
		*/
		constexpr inline void setTime(
			std::uint8_t sec /**< : <i>in</i> : The seconds field [0,59].*/,
			std::uint8_t min /**< : <i>in</i> : The minutes field [0,59].*/,
			std::uint8_t hr  /**< : <i>in</i> : The hours field [0,59].*/
		)
		{
			_seconds.set(sec);
			_minutes.set(min);
			_hours.set(hr);
		}

		/**
			\brief Sets the time to the time indicated by argument.
		*/
		inline void setTime(
			time_t timeStamp /**< : <i>in</i> : The time to set.*/
		)
		{
			tm tm_str = enh::localTime( &timeStamp);
			if (tm_str.tm_sec <= 59)
				setTime(tm_str.tm_sec, tm_str.tm_min, tm_str.tm_hour);
			else
				setTime(59, tm_str.tm_min, tm_str.tm_hour);
		}

		/**
			\brief Sets the time to the current time.
		*/
		inline void setTime()
		{
			setTime(std::time(nullptr));
		}

		/**
			\brief Sets the time to the time indicated by arguments.

			<h3>Exception</h3>
			Throws <code>std::invalid_argument</code> if sec, min, hr is
			not within bounds. [0,60], [0,59], [0,23] respectively.
		*/
		constexpr inline TimeStamp(
			std::uint8_t sec /**< : <i>in</i> : The seconds field [0,60].*/,
			std::uint8_t min /**< : <i>in</i> : The minutes field [0,59].*/,
			std::uint8_t hr  /**< : <i>in</i> : The hours field [0,59].*/
		) : _seconds(sec), _minutes(min), _hours(hr) {}

		/**
			\brief Sets the time to the time indicated by argument.
		*/
		inline TimeStamp(
			time_t timeStamp /**< : <i>in</i> : The time to set.*/
		)
		{
			setTime(timeStamp);
		}

		/**
			\brief Sets the time to the current time.
		*/
		inline TimeStamp()
		{
			setTime();
		}

		/**
			\brief Adds to the hour part of time held.

			<h3>Return</h3>
			Returns the number of days passed (hr/24).

		*/
		constexpr inline std::uint64_t addHours(
			std::uint64_t hr /**< : <i>in</i> : The hours to add.*/
		) noexcept
		{
			return _hours.add(hr);
		}

		/**
			\brief Adds to the minute part of time held (also hour).

			<h3>Return</h3>
			Returns the number of days passed (min/(24*60)).

		*/
		constexpr inline std::uint64_t addMinutes(
			std::uint64_t min /**< : <i>in</i> : The minutes to add.*/
		) noexcept
		{
			return addHours(_minutes.add(min));
		}

		/**
			\brief Adds to the second part of time held (also minute, hour).

			<h3>Return</h3>
			Returns the number of days passed (sec/(24*60*60)).

		*/
		constexpr inline std::uint64_t addSeconds(
			std::uint64_t sec  /**< : <i>in</i> : The seconds to add.*/
		) noexcept
		{
			return addMinutes(_seconds.add(sec));
		}

		/**
			\brief Reduce the hour part of time held.

			<h3>Return</h3>
			Returns the number of days reduced (hr/24).

		*/
		constexpr inline std::uint64_t subHours(
			std::uint64_t hr /**< : <i>in</i> : The hours to reduce.*/
		) noexcept
		{
			return _hours.sub(hr);
		}

		/**
			\brief Reduce the minute part of time held (also hour).

			<h3>Return</h3>
			Returns the number of days passed (min/(24*60)).

		*/
		constexpr inline std::uint64_t subMinutes(
			std::uint64_t min /**< : <i>in</i> : The minutes to reduce.*/
		) noexcept
		{
			return subHours(_minutes.sub(min));
		}

		/**
			\brief Reduces the second part of time held (also hour).

			<h3>Return</h3>
			Returns the number of days passed (sec/(24*60*60)).

		*/
		constexpr inline std::uint64_t subSeconds(
			std::uint64_t sec /**< : <i>in</i> : The seconds to reduce.*/
		) noexcept
		{
			return subMinutes(_seconds.sub(sec));
		}

		/**
			\brief Get Seconds field.
		*/
		constexpr inline std::uint8_t getSeconds() const noexcept { return _seconds.get(); }

		/**
			\brief Get Minutes field.
		*/
		constexpr inline std::uint8_t getMinutes() const noexcept { return _minutes.get(); }

		/**
			\brief Get Hours field.
		*/
		constexpr inline std::uint8_t getHours() const noexcept { return _hours.get(); }

		/**
			\brief Get The time as a string in default format.

			hour:min:sec\n\n

			<h3>Overload</h3>
			-# <code>inline std::string getStringTime(std::string format)
			const;</code>\n
		*/
		inline std::string getStringTime() const
		{
			return signExtendValue(_hours.get(), 2) + " : "
				+ signExtendValue(_minutes.get(), 2) + " : "
				+ signExtendValue(_seconds.get(), 2);
		}

		/**
			\brief Get The time as a string in custom format.

			Pass Argument as a string containing any of the following
			components.

			<b>sec</b> : The seconds.\n
			<b>min</b> : The minutes.\n
			<b>hour</b> : The hours.\n

			Example : <code>"secs minm hourhr"</code> : <code>"25s 25m 10hr"
				</code>\n

			<h3>Overload</h3>
			-# <code>inline std::string getStringTime() const;</code>\n
		*/
		inline std::string getStringTime(
			std::string format /**< : <i>in</i> : The format of date.*/
		) const
		{
			std::size_t psec, pmin, phour;
			psec = format.find("sec");
			if (psec != std::string::npos)
				format.replace(psec, 3, signExtendValue(_seconds.get(), 2));
			
			pmin = format.find("min");
			if (pmin != std::string::npos)
				format.replace(pmin, 3, signExtendValue(_minutes.get(), 2));
			
			phour = format.find("hour");
			if (phour != std::string::npos)
				format.replace(phour, 4, signExtendValue(_hours.get(), 2));

			return format;
		}

		/**
			\brief Checks if argument is equal to this object.

			<h3>Return</h3>
			Returns true if hours, minutes and seconds of argument is equal to
			current object.
		*/
		constexpr inline bool isEqualTo(
			const TimeStamp &dt /**< : <i>in</i> : The TimeStamp to compare with.*/
		) const noexcept
		{
			return (_hours == dt._hours) && (_minutes == dt._minutes) && (_seconds == dt._seconds);
		}

		/**
			\brief Checks if argument is not equal to this object.

			<h3>Return</h3>
			Returns true if hours, minutes and seconds of argument is not equal to
			current object.
		*/
		constexpr inline bool isNotEqualTo(
			const TimeStamp &dt /**< : <i>in</i> : The TimeStamp to compare with.*/
		) const noexcept
		{
			return !isEqualTo(dt);
		}

		/**
			\brief Checks if current TimeStamp is lesser than argument.

			<h3>Return</h3>
			Returns true if current TimeStamp is lesser than argument.
		*/
		constexpr inline bool isLesserThan(
			const TimeStamp &dt /**< : <i>in</i> : The TimeStamp to compare with.*/
		) const noexcept
		{
			if (_hours < dt._hours)
				return true;
			else if (_hours > dt._hours)
				return false;
			else
			{
				if (_minutes < dt._minutes)
					return true;
				else if (_minutes > dt._minutes)
					return false;
				else
				{
					if (_seconds < dt._seconds)
						return true;
					else if (_seconds > dt._seconds)
						return false;
					else
						return false;

				}
			}
		}

		/**
			\brief Checks if current TimeStamp is lesser than or equal to argument.

			<h3>Return</h3>
			Returns true if current TimeStamp is lesser than or equal to argument.
		*/
		constexpr inline bool isLesserThanEq(
			const TimeStamp &dt /**< : <i>in</i> : The TimeStamp to compare with.*/
		) const noexcept
		{
			if (_hours < dt._hours)
				return true;
			else if (_hours > dt._hours)
				return false;
			else
			{
				if (_minutes < dt._minutes)
					return true;
				else if (_minutes > dt._minutes)
					return false;
				else
				{
					if (_seconds < dt._seconds)
						return true;
					else if (_seconds > dt._seconds)
						return false;
					else
						return true;

				}
			}
		}

		/**
			\brief Checks if current TimeStamp is greater than argument.

			<h3>Return</h3>
			Returns true if current TimeStamp is greater than argument.
		*/
		constexpr inline bool isGreaterThan(
			const TimeStamp &dt /**< : <i>in</i> : The TimeStamp to compare with.*/
		) const noexcept
		{
			return !isLesserThanEq(dt);
		}

		/**
			\brief Checks if current TimeStamp is greater than or equal to argument.

			<h3>Return</h3>
			Returns true if current TimeStamp is greater than or equal to argument.
		*/
		constexpr inline bool isGreaterThanEq(
			const TimeStamp &dt /**< : <i>in</i> : The TimeStamp to compare with.*/
		) const noexcept
		{
			return !isLesserThan(dt);
		}
	};

	/**
		\brief Checks if lhs is equal to rhs.
	*/
	constexpr inline bool operator == (
		const TimeStamp &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const TimeStamp &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return lhs.isEqualTo(rhs);
	}

	/**
		\brief Checks if lhs is not equal to rhs.
	*/
	constexpr inline bool operator != (
		const TimeStamp &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const TimeStamp &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return lhs.isNotEqualTo(rhs);
	}

	/**
		\brief Checks if lhs is greater than rhs.
	*/
	constexpr inline bool operator > (
		const TimeStamp &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const TimeStamp &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return rhs.isLesserThan(lhs);
	}

	/**
		\brief Checks if lhs is greater than or equal to rhs.
	*/
	constexpr inline bool operator >= (
		const TimeStamp &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const TimeStamp &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return rhs.isLesserThanEq(lhs);
	}

	/**
		\brief Checks if lhs is lesser than rhs.
	*/
	constexpr inline bool operator < (
		const TimeStamp &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const TimeStamp &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return lhs.isLesserThan(rhs);
	}

	/**
		\brief Checks if lhs is lesser than or equal to rhs.
	*/
	constexpr inline bool operator <= (
		const TimeStamp &lhs /**< : <i>in</i> : The left hand side of the
						expression.*/,
		const TimeStamp &rhs /**< : <i>in</i> : The right hand side of the
						expression.*/
		) noexcept
	{
		return lhs.isLesserThanEq(rhs);
	}
}

#endif