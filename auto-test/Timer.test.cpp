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
	template<class Unit, class LowerUnit, unsigned period, unsigned cycles, unsigned error_bounds>
	bool BasicTest()
	{
		enh::timer<period, Unit> timerObject;

		auto start = enh::high_res::now();
		timerObject.wait_for(cycles);
		auto end = enh::high_res::now();
		auto time_elapsed = std::chrono::duration_cast<LowerUnit>(end - start).count();
		auto expected_time = LowerUnit(Unit(period * cycles)).count();
		long double error = time_elapsed - expected_time;
		error = abs(error) / long double(expected_time);
		std::string failMessage = "Error is higher than : 1 in " + std::to_string(error_bounds);
		std::cout << expected_time << " " << time_elapsed << " " <<  error << "\n";
		ASSERT_TEST((error < (1.0 / long double(error_bounds))), failMessage);
	}

	template<class Unit, class LowerUnit, unsigned period, unsigned cycles, unsigned interrupt, unsigned error_bounds>
	bool InterruptTest()
	{
		enh::timer<period, Unit> timerObject;
		std::atomic<bool> stop = false;
		auto expected_time = LowerUnit(Unit(period * interrupt)).count();
		std::thread other([&]() {
			std::this_thread::sleep_for(LowerUnit(expected_time));
			stop = true;
			});
		auto start = enh::high_res::now();
		timerObject.wait_for(cycles, [&]() { return !stop.load(); });
		auto end = enh::high_res::now();
		other.join();
		auto time_elapsed = std::chrono::duration_cast<LowerUnit>(end - start).count();
		expected_time = LowerUnit(Unit(period * interrupt)).count();
		long double error = time_elapsed - expected_time;
		error = abs(error) / long double(expected_time);
		std::string failMessage = "Error is higher than : 1 in " + std::to_string(error_bounds);
		ASSERT_TEST((error < (1.0 / long double(error_bounds))), failMessage);
	}
}

int main()
{
	using micros = std::chrono::microseconds;
	using millis = std::chrono::milliseconds;
	using sec_s = std::chrono::seconds;
	using min_s = std::chrono::minutes;
	REGISTER_TEST((testCase::BasicTest<millis, micros, 20, 10, 10>));
	REGISTER_TEST((testCase::BasicTest<sec_s, micros, 1, 10, 1000>));
	REGISTER_TEST((testCase::BasicTest<min_s, micros, 1, 2, 10000>));

	REGISTER_TEST((testCase::InterruptTest<millis, micros, 20, 10, 5, 10>));
	REGISTER_TEST((testCase::InterruptTest<sec_s, micros, 1, 10, 5, 1000>));
	REGISTER_TEST((testCase::InterruptTest<min_s, micros, 1, 2, 1, 10000>));

	return call_main();
}