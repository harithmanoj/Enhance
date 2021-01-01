/** ***************************************************************************
	\file Timer.test.cpp

	\brief The file to test parts of module Timer

	Created 05 June 2020

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

#include <iostream>
#include <timer.enh.h>
#include <atomic>
#include "test.base.h"

namespace testCase
{
	bool BasicTest()
	{
		enh::millis<50> timerObject;

		auto start = enh::HighResClock::now();
		timerObject.waitFor(20);		
		auto end = enh::HighResClock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		decltype(elapsed) expected = 20 * 50 * 1000;
		ASSERT_TEST(elapsed > expected, "Timer does not wait for a minimum of given time");
	}

	bool InterruptTest()
	{
		enh::millis<50> timerObject;
		bool stop = false;
		std::thread other([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(10 * 50));
			stop = true;
			});
		auto start = enh::HighResClock::now();
		timerObject.waitFor(20, [&]() {return !stop; });
		auto end = enh::HighResClock::now();
		other.join();
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		decltype(elapsed) expected_full = 20 * 50 * 1000;
		decltype(elapsed) expected = 10 * 50 * 1000;
		ASSERT_TEST((elapsed > expected) && (elapsed < expected_full), "Timer does not wait for a minimum of given time");
	}

	bool RestartTest()
	{
		enh::millis<50> timerObject;
		decltype(std::chrono::milliseconds().count()) elapsed = 0;
		decltype(elapsed) expected;

		{
			auto start = enh::HighResClock::now();
			timerObject.waitFor(20);
			auto end = enh::HighResClock::now();
			elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			expected = 20 * 50 * 1000;
			timerObject.stop();
			timerObject.waitForTimerStop();
		}
		{
			ASSERT_CONTINUE(timerObject.startTimerLoop(), "Timer failed to stop");
			auto start = enh::HighResClock::now();
			timerObject.waitFor(20);
			auto end = enh::HighResClock::now();
			elapsed += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			expected += 20 * 50 * 1000;
		}
		ASSERT_TEST(elapsed > expected, "Timer does not restart");
	}

}

int main()
{
	REGISTER_TEST(testCase::BasicTest);
	REGISTER_TEST(testCase::InterruptTest);
	REGISTER_TEST(testCase::RestartTest);
	return call_main();
}