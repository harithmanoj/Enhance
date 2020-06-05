/** ***************************************************************************
	\file test.base.h

	\brief The file to declare testing framework

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

#ifndef TEST_BASE_ENH_H

#define TEST_BASE_ENH_H									test.base.h

#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace testBase
{
	std::vector<std::function<bool()>> allTestCases;

	bool assertTest(bool condition, std::string conditionString, std::string failMessage, std::string function, std::string file)
	{
		if (condition)
			std::cout << "PASS : " << file << " : " << function << "\n";
		else
			std::cerr << "FAIL : " << file << " : " << function << " : condition " << conditionString << " : " << failMessage << "\n";
		return condition;
	}
}

inline int call_main()
{
	bool ret_val = 0;
	for (auto &i : testBase::allTestCases)
	{
		if (!i())
			ret_val = 1;
	}

	return ret_val;
}

#define CONCAT(x,y)								x##y

#define REGISTER_TEST(function)					testBase::allTestCases.push_back(function)

#define REGISTER_MEM_TEST(function)				testBase::allTestCases.push_back([this](){return function();})

#define ASSERT_TEST(condition, fail_message)	return testBase::assertTest(condition, #condition, fail_message, __func__, __FILE__ )
												


#endif