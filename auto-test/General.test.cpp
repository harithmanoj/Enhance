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
				ASSERT_CONTINUE(ret == 1, "constexpr signum function should return 1 for positive numbers");
			}
			{
				constexpr arithmetic base = 0;
				constexpr auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE(ret == 0, "constexpr signum function should return 0 for 0");
			}

			if (!std::is_unsigned_v<arithmetic>)
			{
				constexpr arithmetic base = -25;
				constexpr auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE(ret == -1, "constexpr signum function should return -1 for negative numbers");
			}


			{
				arithmetic base = 25;
				auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE(ret == 1, "signum function should return 1 for positive numbers");
			}
			{
				arithmetic base = 0;
				auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE(ret == 0, "signum function should return 0 for 0");
			}

			if (!std::is_unsigned_v<arithmetic>)
			{
				arithmetic base = -25;
				auto ret = enh::signum_fn(base);
				ASSERT_CONTINUE((ret == -1), "signum function should return -1 for negative numbers");
			}

			return true;
		}

		template<class integral>
		bool incl_ratioTest()
		{
			{
				constexpr integral numerator = 25;
				constexpr integral denominator = 5;
				constexpr auto ret = enh::incl_ratio(numerator, denominator);
				ASSERT_CONTINUE(ret == 5, "constexpr simple Divide failed");
			}
			{
				constexpr integral numerator = 26;
				constexpr integral denominator = 5;
				constexpr auto ret = enh::incl_ratio(numerator, denominator);
				ASSERT_CONTINUE(ret == 6, "constexpr divide with remainder 1 did not round up");
			}
			{
				constexpr integral numerator = 29;
				constexpr integral denominator = 5;
				constexpr auto ret = enh::incl_ratio(numerator, denominator);
				ASSERT_CONTINUE(ret == 6, "constexpr divide with remainder 4 did not round up");
			}

			{
				integral numerator = 25;
				integral denominator = 5;
				auto ret = enh::incl_ratio(numerator, denominator);
				ASSERT_CONTINUE(ret == 5, "simple Divide failed");
			}
			{
				integral numerator = 26;
				integral denominator = 5;
				auto ret = enh::incl_ratio(numerator, denominator);
				ASSERT_CONTINUE(ret == 6, "divide with remainder 1 did not round up");
			}
			{
				integral numerator = 29;
				integral denominator = 5;
				auto ret = enh::incl_ratio(numerator, denominator);
				ASSERT_CONTINUE(ret == 6, "divide with remainder 4 did not round up");
			}

			return true;
		}

		template<class type>
		bool isConfinedTest()
		{
			{
				constexpr type unchecked = type(30);
				constexpr type lbound = type(10);
				constexpr type ubound = type(50);
				constexpr bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(ni_ret, "constexpr bound check in middle, non-inclusive");

				constexpr bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(ui_ret, "constexpr bound check in middle, upper inclusive");

				constexpr bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(li_ret, "constexpr bound check in middle, lower inclusive");

				constexpr bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "constexpr bound check in middle, inclusive");
			}

			{
				constexpr type unchecked = type(11);
				constexpr type lbound = type(10);
				constexpr type ubound = type(50);
				constexpr bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(ni_ret, "constexpr bound check aproaching lower, non-inclusive");

				constexpr bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(ui_ret, "constexpr bound check aproaching lower, upper inclusive");

				constexpr bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(li_ret, "constexpr bound check aproaching lower, lower inclusive");

				constexpr bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "constexpr bound check aproaching lower, inclusive");
			}

			{
				constexpr type unchecked = type(49);
				constexpr type lbound = type(10);
				constexpr type ubound = type(50);
				constexpr bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(ni_ret, "constexpr bound check aproaching upper, non-inclusive");

				constexpr bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(ui_ret, "constexpr bound check aproaching upper, upper inclusive");

				constexpr bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(li_ret, "constexpr bound check aproaching upper, lower inclusive");

				constexpr bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "constexpr bound check aproaching upper, inclusive");
			}

			{
				constexpr type unchecked = type(10);
				constexpr type lbound = type(10);
				constexpr type ubound = type(50);
				constexpr bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(!ni_ret, "constexpr bound check lower, non-inclusive");

				constexpr bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(!ui_ret, "constexpr bound check lower, upper inclusive");

				constexpr bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(li_ret, "constexpr bound check lower, lower inclusive");

				constexpr bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "constexpr bound check lower, inclusive");
			}

			{
				constexpr type unchecked = type(50);
				constexpr type lbound = type(10);
				constexpr type ubound = type(50);
				constexpr bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(!ni_ret, "constexpr bound check upper, non-inclusive");

				constexpr bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(ui_ret, "constexpr bound check upper, upper inclusive");

				constexpr bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(!li_ret, "constexpr bound check upper, lower inclusive");

				constexpr bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "constexpr bound check upper, inclusive");
			}


			{
				type unchecked = type(30);
				type lbound = type(10);
				type ubound = type(50);
				bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(ni_ret, "bound check in middle, non-inclusive");

				bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(ui_ret, "bound check in middle, upper inclusive");

				bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(li_ret, "bound check in middle, lower inclusive");

				bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "bound check in middle, inclusive");
			}

			{
				type unchecked = type(11);
				type lbound = type(10);
				type ubound = type(50);
				bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(ni_ret, "bound check aproaching lower, non-inclusive");

				bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(ui_ret, "bound check aproaching lower, upper inclusive");

				bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(li_ret, "bound check aproaching lower, lower inclusive");

				bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "bound check aproaching lower, inclusive");
			}

			{
				type unchecked = type(49);
				type lbound = type(10);
				type ubound = type(50);
				bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(ni_ret, "bound check aproaching upper, non-inclusive");

				bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(ui_ret, "bound check aproaching upper, upper inclusive");

				bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(li_ret, "bound check aproaching upper, lower inclusive");

				bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "bound check aproaching upper, inclusive");
			}

			{
				type unchecked = type(10);
				type lbound = type(10);
				type ubound = type(50);
				bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(!ni_ret, "bound check lower, non-inclusive");

				bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(!ui_ret, "bound check lower, upper inclusive");

				bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(li_ret, "bound check lower, lower inclusive");

				bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "bound check lower, inclusive");
			}

			{
				type unchecked = type(50);
				type lbound = type(10);
				type ubound = type(50);
				bool ni_ret = enh::isConfined(unchecked, lbound, ubound, false, false);
				ASSERT_CONTINUE(!ni_ret, "bound check upper, non-inclusive");

				bool ui_ret = enh::isConfined(unchecked, lbound, ubound, false, true);
				ASSERT_CONTINUE(ui_ret, "bound check upper, upper inclusive");

				bool li_ret = enh::isConfined(unchecked, lbound, ubound, true, false);
				ASSERT_CONTINUE(!li_ret, "bound check upper, lower inclusive");

				bool i_ret = enh::isConfined(unchecked, lbound, ubound, true, true);
				ASSERT_CONTINUE(i_ret, "bound check upper, inclusive");
			}

			return true;
		}

	}

	bool isConfinedAll()
	{
		bool ret_unsigned = nouse::isConfinedTest<unsigned>();
		ASSERT_CONTINUE(ret_unsigned, "isConfined Failed for unsigned instantiation");

		bool ret_char = nouse::isConfinedTest<char>();
		ASSERT_CONTINUE(ret_char, "isConfined Failed for char instantiation");

		bool ret_unsigned_char = nouse::isConfinedTest<unsigned char>();
		ASSERT_CONTINUE(ret_unsigned_char, "isConfined Failed for unsigned char instantiation");

		bool ret_long = nouse::isConfinedTest<long>();
		ASSERT_CONTINUE(ret_long, "isConfined Failed for long instantiation");


		ASSERT_TEST(/*ret_char &&*/ ret_unsigned && ret_unsigned_char, "isConfined Failed");
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

	bool incl_ratioAll()
	{
		bool ret_unsigned = nouse::incl_ratioTest<unsigned>();
		ASSERT_CONTINUE(ret_unsigned, "incl_ratio Failed for unsigned instantiation");

		bool ret_char = nouse::incl_ratioTest<char>();
		ASSERT_CONTINUE(ret_char, "incl_ratio Failed for char instantiation");

		bool ret_unsigned_char = nouse::incl_ratioTest<unsigned char>();
		ASSERT_CONTINUE(ret_unsigned_char, "incl_ratio Failed for unsigned char instantiation");

		ASSERT_TEST(ret_char && ret_unsigned && ret_unsigned_char, "incl_ratio Failed");
	}


	bool signExtendAll()
	{
		bool positive = enh::signExtend("25", 10) == "0000000025";
		bool negative = enh::signExtend("-25", 10) == "-000000025";
		bool zero = enh::signExtend("0", 10) == "0000000000";
		ASSERT_CONTINUE(positive, "sign Extend could not extend positive values");
		ASSERT_CONTINUE(negative, "sign Extend could not extend negative values");
		ASSERT_CONTINUE(zero, "sign Extend could not extend zero");
		ASSERT_TEST(positive && negative && zero, "signExtend check failed");
	}
}


int main()
{
	REGISTER_TEST(testCase::CheckFieldAll);
	REGISTER_TEST(testCase::signum_fnAll);
	REGISTER_TEST(testCase::incl_ratioAll);
	REGISTER_TEST(testCase::isConfinedAll);
	REGISTER_TEST(testCase::signExtendAll);
	return call_main();
}