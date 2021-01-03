/** ***************************************************************************
	\file timer.enh.h

	\brief File to declare functions and classes related to timer 
	functionality.

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

#ifndef TIMER_ENH_H

#define TIMER_ENH_H						timer.enh.h


#include <chrono>
#include <type_traits>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>

namespace enh
{
	/**
		\brief Alias for the standard high resolution clock for easy access.
	*/
	using HighResClock = std::chrono::high_resolution_clock;

	/**
		\brief Alias for easily declaring complex time stamp type.
	*/
	using TimePoint = decltype(HighResClock::now());



	/**
		\brief Template type to assertian whether a type can be used to instanciate
		the class @ref enh::Timer.

		<h3>Template Parameter</h3>
		-#  <code>T</code> : The type to check.

		<h3>Values </h3>
		<code>true</code> for <code>std::chrono::milliseconds, std::chrono::seconds,
		std::chrono::minutes, std::chrono::hours.</code>\n
		false for all else.\n
	*/
	template<class T>
	constexpr bool isGoodTimer = false; // evaluates to false unless explicitely specified.

	//explicitely specifies that milliseconds is fine.
	template<>
	constexpr bool isGoodTimer<std::chrono::milliseconds> = true;

	//explicitely specifies that seconds is fine.
	template<>
	constexpr bool isGoodTimer<std::chrono::seconds> = true;

	//explicitely specifies that minutes is fine.
	template<>
	constexpr bool isGoodTimer<std::chrono::minutes> = true;

	//explicitely specifies that hours is fine.
	template<>
	constexpr bool isGoodTimer<std::chrono::hours> = true;

	/**
		\brief Template type to assertian whether a type can be used to instanciate
		the template of class @ref enh::Timer.

		<h3>Template Parameter</h3>
		-#  <code>T</code> : The type to check.

		<h3>Values </h3>
		<code>true</code> for <code>std::chrono::milliseconds, std::chrono::seconds,
		std::chrono::minutes, std::chrono::hours, std:chrono::microseconds,
		 std:chrono::nanoseconds.</code>\n
		false for all else.\n


		<b>Note : </b> Not all of these type can be used to make an object of that class.
	*/
	template<class T>
	constexpr bool isGoodTimerType = isGoodTimer<T>;

	template<>
	constexpr bool isGoodTimerType<std::chrono::nanoseconds> = true;

	template<>
	constexpr bool isGoodTimerType<std::chrono::microseconds> = true;


	/**
		\brief The class to create a Timer that notifies all clients periodically.

		The class will start a Timer on instanciation and starts notifying 
		all client threads, periodically.
		

		The period is determined by the template arguments.

		The period cannot be less than 5 if TimeUnit is milliseconds for accuracy.

		The class cannot be instanciated using any other type than 
		milliseconds, seconds, minutes and hours.

		But the template can be instanciated with nanoseconds and microseconds,
		but object cannot be created.


		hasErrorHandlers        = false;\n
		
		<h3>template</h3>
		-#  <code>unsigned periodPassed</code> : The period of time between each notification.\n
		-#  <code>TimeUnit</code> : The TimeUnit of time of period.\n

		<h3>Example</h3>

		\include{lineno} timer_ex.cpp

	*/
	template<unsigned periodPassed = 50U, class TimeUnitPassed = std::chrono::milliseconds>
	class Timer
	{
	
	public:

		/**
			\brief The period of Timer.
		*/
		static constexpr unsigned period = periodPassed;

		/**
			\brief The TimeUnit of measurement.
		*/
		using TimeUnit = TimeUnitPassed;

	private:


		//fails if not time TimeUnit.
		static_assert(isGoodTimerType<TimeUnit>, "TimeUnit type must be time type");
		//fails if period < 5ms
		static_assert(!(std::is_same_v<std::chrono::milliseconds, TimeUnit> && (period < 5)),
			"Precision cannot be achieved lower than 5ms");


		/**
			\brief The variable that is initialized at the begining of program
			to the time at that point. Approximately the program begining time.
		*/
		static TimePoint _programStartTimePoint;

		/**
			\brief The variable that is initialized at the begining of Timer
			thread start, the begining time point of the Timer.
		*/
		TimePoint _timerStartPoint;

		/**
			\brief The time at which next notification is to be sent.

			Value is @ref _timerStartPoint + period*@ref _elapsedCycles.
		*/
		TimePoint _nextTimerPoint;


		/**
			\brief The mutex to hold ownership over @ref _elapsedCycles and
			the notifier.
		*/
		std::mutex _elapsedCyclesSyncMutex;

		/**
			\brief The condition_variable to notify all client threads about 
			the end of that period.
		*/
		std::condition_variable _notifyTimerPeriodEnd;

		/**
			\brief The variable to signal the end of the Timer loop, set by 
			any control thread and read by the Timer thread to stop execution
			and return.
		*/
		std::atomic<bool> _shouldStopTimer;

		/**
			\brief The variable that tracks the cycles elapsed since Timer
			start.

			The product of this and period gives time elapsed.
		*/
		unsigned long long _elapsedCycles;


		/**
			\brief the thread handle to the thread running the Timer function.
		*/
		std::thread _timerThread;

		/**
			\brief true if Timer thread is running.
		*/
		bool _isTimerActive;



		/**
			\brief Blocks execution till the time point described in 
			_nextTimerPoint.

			And then notifies the waiting threads.
		*/
		inline void singlePeriodSleep() noexcept
		{
			std::this_thread::sleep_until(_nextTimerPoint);
			{
				std::lock_guard<std::mutex> lock(_elapsedCyclesSyncMutex);
				++_elapsedCycles;
				_nextTimerPoint += TimeUnit(period);
			}
			_notifyTimerPeriodEnd.notify_all();
		}


		/**
			\brief keeps on executing singlePeriodSleep until the time when 
			_shouldStopTimer is set.
		*/
		void timerLoop() noexcept
		{
			clearStopSignal();
			_elapsedCycles = 0;
			_timerStartPoint = HighResClock::now();
			_nextTimerPoint = _timerStartPoint + TimeUnit(period);
			while (!_shouldStopTimer.load())
			{
				singlePeriodSleep();
			}
		}

	public:

		/**
			\brief The constructor of the class.


			The Timer constructor also invokes enh::Timer::startTimerLoop.

			Constructor fails assert if it is not a time type > ms.
		*/
		inline Timer() noexcept
		{
			static_assert(isGoodTimer<TimeUnit>, "TimeUnit type must be std::chrono::milliseconds, seconds or hours");
			_isTimerActive = false;
			clearStopSignal();
			_elapsedCycles = 0;
			startTimerLoop();
		}
		

		/**
			\brief destructor of the class.

			invokes enh::Timer::immediateTimerJoin, waits till the Timer Thread joins.
		*/
		inline ~Timer() noexcept
		{
			immediateTimerJoin();
		}

		/**
			\brief The Functions blocks execution till the number of cycles 
			elapsed is greater than or equal to the expected value.

			Invokes enh::Timer::startTimerLoop if Timer is not active.

			<h3>Return</h3>
			The difference between elapsed 
			cycles and expected (the "overshoot").\n
		*/
		inline unsigned long long wait(
			unsigned long long expected /**< : <i>in</i> : The expected cycle 
										count to wait till.*/
		) noexcept
		{
			if (!_isTimerActive)
				startTimerLoop();
			std::unique_lock<std::mutex> lock(_elapsedCyclesSyncMutex);
			_notifyTimerPeriodEnd.wait(lock,
				[expected, this]() {
					return _elapsedCycles >= expected;
				});
			return (_elapsedCycles - expected);
		}

		/**
			\brief The Functions blocks execution till the number of cycles
			elapsed is greater than or equal to the current elapsed cycles 
			+ 1.

			<h3>Return</h3>
			The difference between elapsed
			cycles and expected (the "overshoot").\n
		*/
		inline unsigned long long wait() noexcept
		{
			return wait(_elapsedCycles + 1);
		}

		/**
			\brief The function blocks for a certian cycles unless the
			condition becomes false.

			The functions waits for a cycle then checks the condition passed 
			through condition, and if it returns false, the function exits.

			<h3>Return</h3>
			-1 if the condition fails. The overshoot 
			if it doesnt.


		*/
		inline long long waitFor(
			unsigned mult_count /**< : <i>in</i> : The amount of cycles to 
								wait.*/,
			std::function<bool()> condition /**< : <i>in</i> : The condition
											to exit immediately.*/
		) noexcept
		{
			unsigned long long expected = _elapsedCycles + mult_count;
			while (_elapsedCycles < expected)
			{
				if (!condition())
					return -1;
				wait();
			}
			return _elapsedCycles - expected;
		}
		
		/**
			\brief sets _shouldStopTimer to true.
		*/
		inline void stop() noexcept { _shouldStopTimer = true; }

		/**
			\brief sets _shouldStopTimer to false.
		*/
		inline void clearStopSignal() noexcept { _shouldStopTimer = false; }

		/**
			\brief returns the start @ref TimePoint of the program.
		*/
		inline static TimePoint logProgramStartPoint() noexcept 
		{ return _programStartTimePoint; }

		/**
			\brief Returns the duration elapsed from program start in the type 
			passed through the template.
		*/
		inline static TimeUnit getProgramTimeElapsed() noexcept
		{
			return std::chrono::duration_cast<TimeUnit>(HighResClock::now()
				- _programStartTimePoint);
		}

		/**
			\brief Returns the number of cycles elapsed from Timer start.
		*/
		inline unsigned long long getElapsedCycles() noexcept { return _elapsedCycles; }

		/**
			\brief blocks function execution for mult_count number of cycles.

			Returns the overshoot from the expected value.
		*/
		inline unsigned long long waitFor(
			unsigned long mult_count /**< : <i>in</i> : The cycles to wait for.*/
		)noexcept
		{
			return wait(_elapsedCycles + mult_count);
		}

		/**
			\brief Checks if Timer is running.

			<h3>Return</h3>
			If Timer is running it returns true.
			Else it returns false;
		*/
		inline bool isTimerCounting()
		{
			if (_isTimerActive)
			{
				// isTimer Active is true, thread has finished but thread has 
				// not been joined.
				if (_timerThread.joinable())
				{
					_timerThread.join();
					_isTimerActive = false;
					return false;
				}
				else
					return true;
			}
			else
				return false;
		}

		/**
			\brief The function to start Timer.

			The function clears the _shouldStopTimer flag, sets _elapsedCycles to 
			0 and then allocates a thread for the Timer.

			<h3>Return</h3>
			Returns false if Timer is already running.
		*/
		inline bool startTimerLoop() noexcept
		{
			if (isTimerCounting())
				return false;
			O3_LIB_LOG_LINE;
			clearStopSignal();
			_elapsedCycles = 0;
			_timerThread = std::thread(&Timer<period, TimeUnit>::timerLoop, this);
			_isTimerActive = true;
			return true;
		}

		/**
			\brief overloaded operator !, returns true if the Timer Thread 
			is not allocated.
		*/
		inline bool operator !() noexcept
		{
			return !isTimerCounting();
		}

		/**
			\brief Waits till _timerThread finishes execution.

			The function blocks till the Timer Thread joins.
			
			If the Timer Thread is empty, it returns immediately.
		*/
		inline void waitForTimerStop() noexcept
		{
			if (isTimerCounting())
			{
				_timerThread.join();
				_isTimerActive = false;
			}
		}

		/**
			\brief sets _shouldStopTimer flag to true, then waits for thread to 
			join via enh::Timer::waitForTimerStop.
		*/
		inline void immediateTimerJoin() noexcept
		{
			stop();
			waitForTimerStop();
			return ;
		}
	};

	template<unsigned a, class b>
	TimePoint Timer<a,b>::_programStartTimePoint = HighResClock::now();

	/**
		\brief The enh::Timer class with TimeUnit <code>std::chrono::
		nanoseconds</code> 
		
		
		The alias of a Timer class template instanciated with 
		<code>std::chrono::nanoseconds</code> to measure time elapsed in 
		nanoseconds from program start.

		<b>NOTE : </b> An object of this type cannot be created, it would 
		fail an assert in the constructor.
	*/
	using nanos = Timer<50, std::chrono::nanoseconds>;

	/**
		\brief The enh::Timer class with TimeUnit <code>std::chrono::
		microseconds</code>


		The alias of a Timer class template instanciated with
		<code>std::chrono::microseconds</code> to measure time elapsed in
		microseconds from program start.

		<b>NOTE : </b> An object of this type cannot be created, it would
		fail an assert in the constructor.
	*/
	using micros = Timer<50, std::chrono::microseconds>;

	/**
		\brief The enh::Timer class with TimeUnit <code>std::chrono::
		milliseconds</code>


		The alias of a Timer class template instanciated with
		<code>std::chrono::milliseconds</code>.

		<b>NOTE : </b> An instance of this template cannot be created with 
		period less than 5, it would fail an assert during template 
		instanciation.

		<h3>Template</h3>
		<code>unsigned period</code> : The period of one cycle in the Timer, 
		cannot be less than 5, default value 50.
	*/
	template<unsigned period = 50U>
	using millis = Timer<period, std::chrono::milliseconds>;

	/**
		\brief The enh::Timer class with TimeUnit <code>std::chrono::
		seconds</code>


		The alias of a Timer class template instanciated with
		<code>std::chrono::seconds</code>.

		<h3>Template</h3>
		<code>unsigned period</code> : The period of one cycle in the Timer,
		default value 50.
	*/
	template<unsigned period = 50U>
	using seconds = Timer<period, std::chrono::seconds>;

	/**
		\brief The enh::Timer class with TimeUnit <code>std::chrono::
		minutes</code>


		The alias of a Timer class template instanciated with
		<code>std::chrono::minutes</code>.

		<h3>Template</h3>
		<code>unsigned period</code> : The period of one cycle in the Timer,
		default value 50.
	*/
	template<unsigned period = 50U>
	using minutes = Timer<period, std::chrono::minutes>;

	/**
		\brief The enh::Timer class with TimeUnit <code>std::chrono::
		hours</code>


		The alias of a Timer class template instanciated with
		<code>std::chrono::hours</code>.

		<h3>Template</h3>
		<code>unsigned period</code> : The period of one cycle in the Timer,
		default value 50.
	*/
	template<unsigned period = 50U>
	using hours = Timer<period, std::chrono::hours>;

}


#endif // !TIMER_TICK_H
