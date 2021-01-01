/** ***************************************************************************
	\file Counter.enh.h

	\brief The file to declare Counter class

	Created 29 March 2020	

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

#ifndef COUNTER_ENH_H

#define COUNTER_ENH_H			Counter.enh.h

#include <atomic>
#include <string>
#include <exception>
#include <ostream>
#include <utility>


namespace enh
{
	
	/**
		\brief The class for Counter functionality.

		hasErrorHandlers        = false;\n


		Make sure to compile `counter.cpp` also.

		<h3>Example</h3>

		\include{lineno} counter_ex.cpp

	*/
	class Counter
	{
		/**
			\brief Stores the _seconds state of Counter.

			value < 60.\n\n
		*/
		std::atomic<unsigned> _seconds;

		/**
			\brief Stores the _minutes state of Counter.

			value < 60.\n\n
		*/
		std::atomic<unsigned> _minutes;

		/**
			\brief Stores the _hours state of Counter.

			value < 24.\n\n
		*/
		std::atomic<unsigned> _hours;

		/**
			\brief Stores the _days state of Counter.
		*/
		std::atomic<unsigned long long> _days;

	public:

		/**
			\brief The destructor for the class.
		*/
		inline ~Counter() {}

		/**
			\brief The constructor of the class sets all to 0.
		*/
		inline Counter() noexcept : _seconds(0), _minutes(0), _hours(0), _days(0)
		{}

		/**
			\brief default copy constructor.
		*/
		inline Counter(const Counter& c) noexcept
		{
			_seconds = c._seconds.load();
			_minutes = c._minutes.load();
			_hours = c._hours.load();
			_days = c._days.load();

		}

		/**
			\brief default move constructor.
		*/
		inline Counter(Counter&& c) noexcept
		{
			_seconds = c._seconds.load();
			_minutes = c._minutes.load();
			_hours = c._hours.load();
			_days = c._days.load();
		}

		/**
			\brief constructs using these values.

			Setting of the state is done by ignoring the excess (sec < 60,
			min < 60, hr < 24).\n\n
		*/
		inline Counter(
			unsigned sec /**< : <i>in</i> : The _seconds to be set.*/,
			unsigned min /**< : <i>in</i> : The _minutes to be set.*/,
			unsigned hr /**< : <i>in</i> : The _hours to be set.*/,
			unsigned long long dy /**< : <i>in</i> : The _days to be set.*/
		) noexcept
		{
			set(sec, min, hr, dy);
		}

		/**
			\brief default copy assignment.
		*/
		inline Counter& operator = (const Counter& c) noexcept
		{
			_seconds = c._seconds.load();
			_minutes = c._minutes.load();
			_hours = c._hours.load();
			_days = c._days.load();
			return *this;
		}

		/**
			\brief default copy assignment.
		*/
		inline Counter& operator = (Counter&& c) noexcept
		{
			_seconds = c._seconds.load();
			_minutes = c._minutes.load();
			_hours = c._hours.load();
			_days = c._days.load();
			return *this;
		}

		/**
			\brief Resets state to 0s 0m 0hr 0day.


			<h3>Return</h3>
			Reference to current state.\n

		*/
		inline Counter& reset() noexcept
		{
			_seconds = 0;
			_minutes = 0;
			_hours = 0;
			_days = 0;
			return *this;
		}

		/**
			\brief Resets state to 0s 0m 0hr 0day.


			<h3>Return</h3>
			Reference to current state.\n

		*/
		inline Counter& operator () () noexcept
		{
			return reset();
		}

		/**
			\brief Functon sets the value of state to sec number of _seconds.
			
			Reset is called.
			If sec is more than 60, It is converted to sec, min, hr, day format
			and overwritten over old values.\n\n
		*/
		void setSeconds(
			unsigned long long sec /**< : <i>in</i> : The _seconds to be set.*/
		) noexcept
		{
			reset();
			_seconds = sec;
			if (sec >= 60)
			{
				addMinutes((sec / 60));
				_seconds = sec % 60;
			}
		}

		/**
			\brief Functon adds sec _seconds to the value of state.

			If sec + _seconds is more than 60, value is added to _minutes,
			_hours, _days	also.\n\n
		*/
		void addSeconds(
			unsigned long long sec /**< : <i>in</i> : The _seconds to be added.*/
		) noexcept
		{
			if ((sec + _seconds.load()) >= 60)
			{
				addMinutes((sec + _seconds.load()) / 60);
			}

			_seconds = (_seconds.load() + sec) % 60;
		}

		/**
			\brief Functon sets the value of state to min number of _minutes.

			Reset is called.
			If min is more than 60, It is converted to min, hr, day format
			and overwritten over old values.\n\n
		*/
		void setMinutes(
			unsigned long long min/**< : <i>in</i> : The _minutes to be set.*/
		) noexcept
		{
			reset();
			_minutes = min;
			if (min >= 60)
			{
				addHours((min / 60));
				_minutes = min % 60;
			}

		}

		/**
			\brief Functon adds min _minutes to the value of state.

			If min + _minutes is more than 60, value is added to
			_hours, _days	also.\n\n
		*/
		void addMinutes(
			unsigned long long min /**< : <i>in</i> : The _minutes to be added.*/
		) noexcept
		{
			if ((min + _minutes.load()) >= 60)
				addHours((min + _minutes.load()) / 60);

			_minutes = (_minutes.load() + min) % 60;
		}

		/**
			\brief Functon sets the value of state to hr number of _hours.

			Reset is called.
			If hr is more than 60, It is converted to hr, day format
			and overwritten over old values.\n\n
		*/
		void setHours(
			unsigned long long hr/**< : <i>in</i> : The _hours to be set.*/
		) noexcept
		{
			reset();
			_hours = hr;
			if (hr >= 24)
			{
				addDays((hr / 24));
				_hours = hr % 24;
			}
		}

		/**
			\brief Functon adds hr _hours to the value of state.

			If hr + _hours is more than 24, value is added to _days also.\n\n

		*/
		void addHours(
			unsigned long long hr/**< : <i>in</i> : The _hours to be added.*/
		) noexcept
		{
			if ((hr + _hours.load()) >= 24)
				addDays((hr + _hours.load()) / 24);

			_hours = ((_hours.load() + hr) % 24);
		}

		/**
			\brief Functon sets the value of state to dy number of _days.
		*/
		void setDays(
			unsigned long long dy/**< : <i>in</i> : The _days to be set.*/
		) noexcept
		{
			reset();
			_days = dy;
		}

		/**
			\brief Functon adds dy _days to the value of state.

		*/
		void addDays(
			unsigned long long dy/**< : <i>in</i> : The _days to be added.*/
		) noexcept
		{
			_days += dy;
		}

		/**
			\brief Returns the _seconds part of the state.

			<h3>Return</h3>
			The number of _seconds.\n

		*/
		inline unsigned getSeconds() const noexcept { return _seconds.load();}

		/**
			\brief Returns the _minutes part of the state.

			<h3>Return</h3>
			The number of _minutes.\n

		*/
		inline unsigned getMinutes() const noexcept { return _minutes.load();}

		/**
			\brief Returns the _hours part of the state.

			<h3>Return</h3>
			The number of _hours.\n

		*/
		inline unsigned getHours() const noexcept { return _hours.load();}

		/**
			\brief Returns the _days part of the state.


			<h3>Return</h3>
			The number of _days.\n

		*/
		inline unsigned long long getDays() const noexcept
		{ return _days.load(); }

		/**
			\brief Returns the total _hours elapsed.

			<h3>Return</h3>
			The total _hours elapsed.\n

		*/
		unsigned long long getTotalHours() const noexcept
		{
			unsigned long long tot = (unsigned long long)_hours.load() +
				(_days.load() * 24ULL);
			if ((_minutes >= 45) || ((_minutes >= 44) && (_seconds >= 45)))
				tot += 1;
			return tot;
		}


		/**
			\brief Functon sets the value of state to state input.

			Setting of the state is done by ignoring the excess (sec < 60,
			min < 60, hr < 24).\n\n
		*/
		inline void set(
			unsigned sec /**< : <i>in</i> : The _seconds to be set.*/,
			unsigned min /**< : <i>in</i> : The _minutes to be set.*/,
			unsigned hr /**< : <i>in</i> : The _hours to be set.*/,
			unsigned long long dy /**< : <i>in</i> : The _days to be set.*/
		) noexcept
		{
			_seconds = sec % 60;
			_minutes = min % 60;
			_hours = hr % 24;
			_days = dy;
		}

		/**
			\brief Functon adds inputs to the state.
		*/
		inline void add(
			unsigned sec /**< : <i>in</i> : The _seconds to be added.*/,
			unsigned min /**< : <i>in</i> : The _minutes to be added.*/,
			unsigned hr /**< : <i>in</i> : The _hours to be added.*/,
			unsigned long long dy /**< : <i>in</i> : The _days to be added.*/
		)
		{
			addSeconds(sec);
			addMinutes(min);
			addHours(hr);
			addDays(dy);
		}

		/**
			\brief Returns the information as a string.

			<h3>Return</h3>
			The info formatted as a string.
		*/
		std::string getString() const
		{
			return std::move(std::to_string(getSeconds()) + "s : "
				+ std::to_string(getMinutes()) + "min : "
				+ std::to_string(getHours()) + "hr : "
				+ std::to_string(getDays()) + "days ; "
				+ std::to_string(getTotalHours()) + " total hours");
		}


		/**
			\brief get size of _seconds storage type
		*/
		static constexpr unsigned getSecondsSize()
		{
			return sizeof(unsigned);
		}

		/**
			\brief get size of _minutes storage type
		*/
		static constexpr unsigned getMinutesSize()
		{
			return sizeof(unsigned);
		}


		/**
			\brief get size of _hours storage type
		*/
		static constexpr unsigned getHoursSize()
		{
			return sizeof(unsigned);
		}

		/**
			\brief get size of _days storage type
		*/
		static constexpr unsigned getDaysSize()
		{
			return sizeof(unsigned long long);
		}


		/**
			\brief get size of raw data stream representing this.
		*/
		static constexpr unsigned getRawSize()
		{
			return getSecondsSize() + getMinutesSize() + getHoursSize() + getDaysSize();
		}

		/**
			\brief read raw data from argument to each field.
		*/
		void readRaw(
			const char* raw /**< : <i>in</i> : The raw data stream.*/,
			unsigned size /**< : <i>in</i> : The length of the raw stream. 
						  (should be getRawSize()).*/
		)
		{
			if (size != getRawSize())
				throw std::invalid_argument("raw stream should be " 
					+ std::to_string(getRawSize()) + " bytes long");
			_seconds.store(*reinterpret_cast<const unsigned*>(raw));
			raw = &raw[getSecondsSize()];
			_minutes.store(*reinterpret_cast<const unsigned*>(raw));
			raw = &raw[getMinutesSize()];
			_hours.store(*reinterpret_cast<const unsigned*>(raw));
			raw = &raw[getHoursSize()];
			_days.store(*reinterpret_cast<const unsigned*>(raw));
		}

		/**
			\brief get string holding raw data stream representation of the objects state.
		*/
		std::string getRaw() const
		{
			auto sec = getSeconds();
			auto min = getMinutes();
			auto hr = getHours();
			auto dy = getDays();
			return std::move(
				std::string(reinterpret_cast<char*>(&sec), sizeof(sec))
				+ std::string(reinterpret_cast<char*>(&min), sizeof(min))
				+ std::string(reinterpret_cast<char*>(&hr), sizeof(hr))
				+ std::string(reinterpret_cast<char*>(&dy), sizeof(dy))
			);
		}


		/**
			\brief Checks if current object is at lower time count than
			parameter.

			<h3> Return </h3>
			Returns true if current state is less than
			parameter.
		*/
		bool operator < (
			Counter a /**< : <i>in</i> : The argument to check against.*/
			)  const noexcept
		{
			if (_days.load() < a.getDays())
				return true;
			if (_days.load() > a.getDays())
				return false;
			if (_hours.load() < a.getHours())
				return true;
			if (_hours.load() > a.getHours())
				return false;
			if (_minutes.load() < a.getMinutes())
				return true;
			if (_minutes.load() > a.getMinutes())
				return false;
			if (_seconds.load() < a.getSeconds())
				return true;
			if (_seconds.load() > a.getSeconds())
				return false;
			return false;
		}

		/**
			\brief Checks if current object is at greater time count than 
			parameter.

			<h3> Return </h3>
			Returns true if current state is greater than 
			parameter.
		*/
		bool operator > (
			Counter a /**< : <i>in</i> : The argument to check against.*/
			)  const noexcept
		{
			if (_days.load() > a.getDays())
				return true;
			if (_days.load() < a.getDays())
				return false;
			if (_hours.load() > a.getHours())
				return true;
			if (_hours.load() < a.getHours())
				return false;
			if (_minutes.load() > a.getMinutes())
				return true;
			if (_minutes.load() < a.getMinutes())
				return false;
			if (_seconds.load() > a.getSeconds())
				return true;
			if (_seconds.load() < a.getSeconds())
				return false;
			return false;
		}

		/**
			\brief Checks if current object is at equal time count than parameter.

			<h3> Return </h3>
			Returns true if current state is equal to parameter.
		*/
		bool operator == (
			Counter a /**< : <i>in</i> : The argument to check against.*/
			)  const noexcept
		{
			if (_days.load() == a.getDays())
				if (_hours.load() == a.getHours())
					if (_minutes.load() == a.getMinutes())
						if (_seconds.load() == a.getSeconds())
							return true;
			return false;
		}
		

		/**
			\brief Checks if current object is at lower or equal time count 
			than parameter.

			<h3> Return </h3>
			Returns true if current state is less than or
			 equal parameter.
		*/
		bool operator <= (
			Counter a /**< : <i>in</i> : The argument to check against.*/
			)  const noexcept
		{
			if (_days.load() < a.getDays())
				return true;
			if (_days.load() > a.getDays())
				return false;
			if (_hours.load() < a.getHours())
				return true;
			if (_hours.load() > a.getHours())
				return false;
			if (_minutes.load() < a.getMinutes())
				return true;
			if (_minutes.load() > a.getMinutes())
				return false;
			if (_seconds.load() < a.getSeconds())
				return true;
			if (_seconds.load() > a.getSeconds())
				return false;
			return true;
		}
		

		/**
			\brief Checks if current object is at greater or equal time count
			than parameter.

			<h3> Return </h3>
			Returns true if current state is more than or
			 equal parameter.
		*/
		bool operator >= (
			Counter a /**< : <i>in</i> : The argument to check against.*/
			)  const noexcept
		{
			if (_days.load() > a.getDays())
				return true;
			if (_days.load() < a.getDays())
				return false;
			if (_hours.load() > a.getHours())
				return true;
			if (_hours.load() < a.getHours())
				return false;
			if (_minutes.load() > a.getMinutes())
				return true;
			if (_minutes.load() < a.getMinutes())
				return false;
			if (_seconds.load() > a.getSeconds())
				return true;
			if (_seconds.load() < a.getSeconds())
				return false;
			return true;
		}

	};

	/**
		\brief returns the greater value of the two 

	    <h3>Return</h3>
		The greater value.\n

	*/
	inline Counter max(
		const Counter a /**< : <i>in</i> : first parameter.*/,
		const Counter b /**< : <i>in</i> : _seconds parameter.*/
	) noexcept
	{
		if (a < b)
			return b;
		else
			return a;
	}

	/**
		\brief returns the lesser value of the two

		<h3>Return</h3>
		The lesser value.\n

	*/
	inline Counter min(
		const Counter a /**< : <i>in</i> : first parameter.*/,
		const Counter b /**< : <i>in</i> : _seconds parameter.*/
	) noexcept
	{
		if (a < b)
			return a;
		else
			return b;
	}


	/**
		\brief Stream insertion operator overloaded for the class Counter.

		<h3>Return</h3>
		The reference to stream passed.\n
	*/
	inline std::ostream& operator << (
		std::ostream& out /**< : <i>inout</i> : The stream which to insert.*/,
		Counter ct /**< : <i>in</i> : The cunter object to insert.*/
		) noexcept
	{
		out << ct.getString();
		return out;
	}

}

#endif // !COUNTER_TICK_H
