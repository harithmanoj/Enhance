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
#include <confined.enh.h>
#include "test.base.h"

namespace testCase
{
	namespace nouse
	{
		template<class integral>
		bool basicAdd()
		{
			enh::confined_base<long> conf(
				[](long long a) {return a < 200; },
				[](long long a) {return a >= 100; },
				[]() {return 199; },
				[]() {return 100; }
			);

			conf.set(199);
			conf.add(1);

			ASSERT_CONTINUE(conf.get() == 100, "add failed to cycle back");
			return true;
		}

		template<class integral>
		bool basicSub()
		{
			enh::confined_base<long> conf(
				[](long long a) {return a < 200; },
				[](long long a) {return a >= 100; },
				[]() {return 199; },
				[]() {return 100; }
			);

			conf.set(100);
			conf.sub(1);
			ASSERT_CONTINUE(conf.get() == 199, "sub failed to cycle back");
			return true;
		}

		template<class integral>
		bool multiAdd()
		{
			enh::confined_base<long> conf(
				[](long long a) {return a < 200; },
				[](long long a) {return a >= 100; },
				[]() {return 199; },
				[]() {return 100; }
			);

			conf.set(179);
			conf.add(21);

			ASSERT_CONTINUE(conf.get() == 100, "add failed to cycle back");
			return true;
		}

		template<class integral>
		bool multiSub()
		{
			enh::confined_base<long> conf(
				[](long long a) {return a < 200; },
				[](long long a) {return a >= 100; },
				[]() {return 199; },
				[]() {return 100; }
			);

			conf.set(120);
			conf.sub(21);
			ASSERT_CONTINUE(conf.get() == 199, "sub failed to cycle back");
			return true;
		}
	}

	bool basicAddall()
	{
		bool ret_uchar = nouse::basicAdd<unsigned char>();
		bool ret_u = nouse::basicAdd<unsigned>();
		bool ret_l = nouse::basicAdd<long>();
		bool ret_ul = nouse::basicAdd<unsigned long>();
		ASSERT_CONTINUE(ret_uchar, "unsigned char instantiation failed");
		ASSERT_CONTINUE(ret_u, "unsigned instantiation failed");
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		ASSERT_CONTINUE(ret_ul, "unsigned long instantiation failed");

		ASSERT_TEST(ret_u && ret_l && ret_uchar && ret_ul, "basicAdd failed");
	}

	bool basicSuball()
	{
		bool ret_uchar = nouse::basicSub<unsigned char>();
		bool ret_u = nouse::basicSub<unsigned>();
		bool ret_l = nouse::basicSub<long>();
		bool ret_ul = nouse::basicSub<unsigned long>();
		ASSERT_CONTINUE(ret_uchar, "unsigned char instantiation failed");
		ASSERT_CONTINUE(ret_u, "unsigned instantiation failed");
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		ASSERT_CONTINUE(ret_ul, "unsigned long instantiation failed");

		ASSERT_TEST(ret_u && ret_l && ret_uchar && ret_ul, "basicSub failed");
	}

	bool multiAddall()
	{
		bool ret_uchar = nouse::multiAdd<unsigned char>();
		bool ret_u = nouse::multiAdd<unsigned>();
		bool ret_l = nouse::multiAdd<long>();
		bool ret_ul = nouse::multiAdd<unsigned long>();
		ASSERT_CONTINUE(ret_uchar, "unsigned char instantiation failed");
		ASSERT_CONTINUE(ret_u, "unsigned instantiation failed");
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		ASSERT_CONTINUE(ret_ul, "unsigned long instantiation failed");

		ASSERT_TEST(ret_u && ret_l && ret_uchar && ret_ul, "multiAdd failed");
	}

	bool multiSuball()
	{
		bool ret_uchar = nouse::multiSub<unsigned char>();
		bool ret_u = nouse::multiSub<unsigned>();
		bool ret_l = nouse::multiSub<long>();
		bool ret_ul = nouse::multiSub<unsigned long>();
		ASSERT_CONTINUE(ret_uchar, "unsigned char instantiation failed");
		ASSERT_CONTINUE(ret_u, "unsigned instantiation failed");
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		ASSERT_CONTINUE(ret_ul, "unsigned long instantiation failed");

		ASSERT_TEST(ret_u && ret_l && ret_uchar && ret_ul, "multiSub failed");
	}
}

int main()
{
	REGISTER_TEST(testCase::basicAddall);
	REGISTER_TEST(testCase::basicSuball);
	REGISTER_TEST(testCase::multiAddall);
	REGISTER_TEST(testCase::multiSuball);
	return call_main();
}