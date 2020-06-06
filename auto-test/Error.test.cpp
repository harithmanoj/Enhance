/** ***************************************************************************
	\file Error.test.cpp

	\brief The file to test parts of module Error

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
#include <error_base.enh.h>
#include "test.base.h"

namespace testCase
{

	class ErrorTest : public enh::error_base<unsigned char>
	{
	public:
		constexpr static unsigned char CUSTOM = 0x08;
		
		bool BasicTest()
		{
			setFlag(UNKNOWN);
			ASSERT_CONTINUE(getError() == UNKNOWN, "error not set");
			clear();
			setFlag(INVALID_ARG);
			ASSERT_LOG_CONTINUE(getError() == INVALID_ARG, "error not set", "Basic Test passed");
			clear();
			return true;
		}

		bool CheckFlagTest()
		{
			setFlag(UNKNOWN);
			setFlag(CUSTOM);
			ASSERT_CONTINUE(checkFlag(CUSTOM), "could not detect custom flag");
			ASSERT_LOG_CONTINUE(checkFlag(UNKNOWN), "could not detect UNKNOWN flag", "CheckFlag Test passed");
			clear();
			return true;
		}

		bool ClearFlagTest()
		{
			setFlag(CUSTOM);
			setFlag(UNKNOWN);
			clearFlag(UNKNOWN);
			ASSERT_LOG_CONTINUE(!checkFlag(UNKNOWN), "could not clear flag", "ClearFlag Test passed");
			clear();
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