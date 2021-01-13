/** ***************************************************************************
	\file Error.test.cpp

	\brief The file to test parts of module Error

	Created 06 June 2020

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
#include <ErrorTracker.enh.h>
#include "test.base.h"

namespace testCase
{

	class ErrorTest : public enh::ErrorTracker<std::uint8_t>
	{
	public:
		constexpr static unsigned char CUSTOM = 0x08;
		
		bool BasicTest()
		{
			setErrorFlag(UNKNOWN);
			ASSERT_CONTINUE(getErrorFlag() == UNKNOWN, "error not set");
			clearErrorFlag();
			setErrorFlag(INVALID_ARG);
			ASSERT_LOG_CONTINUE(getErrorFlag() == INVALID_ARG, "error not set", "Basic Test passed");
			clearErrorFlag();
			return true;
		}

		bool CheckFlagTest()
		{
			setErrorFlag(UNKNOWN);
			setErrorFlag(CUSTOM);
			ASSERT_CONTINUE(checkErrorFlag(CUSTOM), "could not detect custom flag");
			ASSERT_LOG_CONTINUE(checkErrorFlag(UNKNOWN), "could not detect UNKNOWN flag", "CheckFlag Test passed");
			clearErrorFlag();
			return true;
		}

		bool ClearFlagTest()
		{
			setErrorFlag(CUSTOM);
			setErrorFlag(UNKNOWN);
			clearErrorFlag(UNKNOWN);
			ASSERT_LOG_CONTINUE(!checkErrorFlag(UNKNOWN), "could not clear flag", "ClearFlag Test passed");
			clearErrorFlag();
			return true;
		}

		inline ErrorTest()
		{
			REGISTER_MEM_TEST(BasicTest);
			REGISTER_MEM_TEST(CheckFlagTest);
			REGISTER_MEM_TEST(ClearFlagTest);
		}
	};
}

int main()
{
	testCase::ErrorTest test;
	return call_main();
}