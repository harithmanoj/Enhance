/** ***************************************************************************
	\file General.test.cpp

	\brief The file to test parts of module General

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
#include <general.enh.h>
#include "test.base.h"

namespace testCase
{
	namespace nouse
	{
		template<class enumT>
		bool CheckFieldTest()
		{
			{
				constexpr enumT base = enumT(0xf0);
				constexpr bool resultA = enh::checkField(enumT(base | 0x04), base);
				ASSERT_CONTINUE(resultA, "constexpr assert failed, base is present in base | any value");
			}
			{
				enumT bd = 0x5f;
				bool resultB = enh::checkField(enumT(bd | 0xf0), bd);
				ASSERT_CONTINUE(resultB, "assert failed, base is present in base | any value");
			}
			{
				constexpr enumT base = enumT(0xf0);
				constexpr bool resultA = enh::checkField(base, enumT(base | 0x04));
				ASSERT_CONTINUE(!resultA, "constexpr assert failed, base | value should not be present in base");
			}
			{
				enumT bd = 0x5f;
				bool resultB = enh::checkField(bd, enumT(bd | 0xf0));
				ASSERT_CONTINUE(!resultB, "assert failed, base | value should not be present in base");
			}

			return true;
		}

		template<class arithmetic>
		bool signumFnTest()
		{
			{
				constexpr arithmetic base = 25;
				constexpr auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE((ret == 1), "constexpr signum function should return 1 for positive numbers");
			}
			{
				constexpr arithmetic base = 0;
				constexpr auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE((ret == 0), "constexpr signum function should return 0 for 0");
			}

			if (!std::is_unsigned_v<arithmetic>)
			{
				constexpr arithmetic base = -25;
				constexpr auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE((ret == -1), "constexpr signum function should return -1 for negative numbers");
			}


			{
				arithmetic base = 25;
				auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE((ret == 1), "signum function should return 1 for positive numbers");
			}
			{
				arithmetic base = 0;
				auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE((ret == 0), "signum function should return 0 for 0");
			}

			if (!std::is_unsigned_v<arithmetic>)
			{
				arithmetic base = -25;
				auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE((ret == -1), "signum function should return -1 for negative numbers");
			}

			return true;
		}
	}

	bool CheckFieldAll()
	{
		bool ret_unsigned = nouse::CheckFieldTest<unsigned>();
		ASSERT_CONTINUE(ret_unsigned, "CheckField Failed for unsigned instantiation");

		bool ret_char = nouse::CheckFieldTest<char>();
		ASSERT_CONTINUE(ret_char, "CheckField Failed for char instantiation");

		bool ret_unsigned_char = nouse::CheckFieldTest<unsigned char>();
		ASSERT_CONTINUE(ret_unsigned_char, "CheckField Failed for unsigned char instantiation");

		
		ASSERT_TEST(ret_char &&ret_unsigned &&ret_unsigned_char, "CheckField Failed");
	}

	bool signum_fnAll()
	{
		bool ret_unsigned = nouse::signumFnTest<unsigned>();
		ASSERT_CONTINUE(ret_unsigned, "signum_fn Failed for unsigned instantiation");

		bool ret_char = nouse::signumFnTest<char>();
		ASSERT_CONTINUE(ret_char, "signum_fn Failed for char instantiation");

		bool ret_unsigned_char = nouse::signumFnTest<unsigned char>();
		ASSERT_CONTINUE(ret_unsigned_char, "signum_fn Failed for unsigned char instantiation");

		ASSERT_TEST(ret_char && ret_unsigned && ret_unsigned_char, "signum_fn Failed");
	}

}


int main()
{
	REGISTER_TEST(testCase::CheckFieldAll);
	REGISTER_TEST(testCase::signum_fnAll);
	return call_main();
}