/** ***************************************************************************
	\file Confined.test.cpp

	\brief The file to test parts of module Error

	Created 07 June 2020

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
		bool confinedbasicAdd()
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
		bool confinedbasicSub()
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
		bool confinedmultiAdd()
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
		bool confinedmultiSub()
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


		template<class integral>
		bool confinedNegLimitBasicAdd()
		{
			enh::confined_base<long> conf(
				[](long long a) {return a < 200; },
				[](long long a) {return a >= -100; },
				[]() {return 199; },
				[]() {return -100; }
			);

			conf.set(199);
			conf.add(1);

			ASSERT_CONTINUE(conf.get() == -100, "add failed to cycle back");
			return true;
		}

		template<class integral>
		bool confinedNegLimitBasicSub()
		{
			enh::confined_base<long> conf(
				[](long long a) {return a < 200; },
				[](long long a) {return a >= -100; },
				[]() {return 199; },
				[]() {return -100; }
			);

			conf.set(-100);
			conf.sub(1);
			ASSERT_CONTINUE(conf.get() == 199, "sub failed to cycle back");
			return true;
		}

		template<class integral>
		bool confinedNegLimitMultiAdd()
		{
			enh::confined_base<long> conf(
				[](long long a) {return a < 200; },
				[](long long a) {return a >= -100; },
				[]() {return 199; },
				[]() {return -100; }
			);

			conf.set(179);
			conf.add(21);

			ASSERT_CONTINUE(conf.get() == -100, "add failed to cycle back");
			return true;
		}

		template<class integral>
		bool confinedNegLimitMultiSub()
		{
			enh::confined_base<long> conf(
				[](long long a) {return a < 200; },
				[](long long a) {return a >= -100; },
				[]() {return 199; },
				[]() {return -100; }
			);

			conf.set(-80);
			conf.sub(21);
			ASSERT_CONTINUE(conf.get() == 199, "sub failed to cycle back");
			return true;
		}
	}

	bool confinedbasicAddall()
	{
		bool ret_uchar = nouse::confinedbasicAdd<unsigned char>();
		ASSERT_CONTINUE(ret_uchar, "unsigned char instantiation failed");
		bool ret_u = nouse::confinedbasicAdd<unsigned>();
		ASSERT_CONTINUE(ret_u, "unsigned instantiation failed");
		bool ret_l = nouse::confinedbasicAdd<long>();
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		bool ret_ul = nouse::confinedbasicAdd<unsigned long>();
		ASSERT_CONTINUE(ret_ul, "unsigned long instantiation failed");

		ASSERT_TEST(ret_u && ret_l && ret_uchar && ret_ul, "confinedbasicAdd failed");
	}

	bool confinedbasicSuball()
	{
		bool ret_uchar = nouse::confinedbasicSub<unsigned char>();
		ASSERT_CONTINUE(ret_uchar, "unsigned char instantiation failed");
		bool ret_u = nouse::confinedbasicSub<unsigned>();
		ASSERT_CONTINUE(ret_u, "unsigned instantiation failed");
		bool ret_l = nouse::confinedbasicSub<long>();
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		bool ret_ul = nouse::confinedbasicSub<unsigned long>();
		ASSERT_CONTINUE(ret_ul, "unsigned long instantiation failed");

		ASSERT_TEST(ret_u && ret_l && ret_uchar && ret_ul, "confinedbasicSub failed");
	}

	bool confinedmultiAddall()
	{
		bool ret_uchar = nouse::confinedmultiAdd<unsigned char>();
		ASSERT_CONTINUE(ret_uchar, "unsigned char instantiation failed");
		bool ret_u = nouse::confinedmultiAdd<unsigned>();
		ASSERT_CONTINUE(ret_u, "unsigned instantiation failed");
		bool ret_l = nouse::confinedmultiAdd<long>();
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		bool ret_ul = nouse::confinedmultiAdd<unsigned long>();
		ASSERT_CONTINUE(ret_ul, "unsigned long instantiation failed");

		ASSERT_TEST(ret_u && ret_l && ret_uchar && ret_ul, "confinedmultiAdd failed");
	}

	bool confinedmultiSuball()
	{
		bool ret_uchar = nouse::confinedmultiSub<unsigned char>();
		ASSERT_CONTINUE(ret_uchar, "unsigned char instantiation failed");
		bool ret_u = nouse::confinedmultiSub<unsigned>();
		ASSERT_CONTINUE(ret_u, "unsigned instantiation failed");
		bool ret_l = nouse::confinedmultiSub<long>();
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		bool ret_ul = nouse::confinedmultiSub<unsigned long>();
		ASSERT_CONTINUE(ret_ul, "unsigned long instantiation failed");

		ASSERT_TEST(ret_u && ret_l && ret_uchar && ret_ul, "confinedmultiSub failed");
	}

	bool confinedNegLimitBasicAddall()
	{
		bool ret_l = nouse::confinedNegLimitBasicAdd<long>();
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		bool ret_ll = nouse::confinedNegLimitBasicAdd<long long>();
		ASSERT_CONTINUE(ret_ll, "long long instantiation failed");

		ASSERT_TEST(ret_l && ret_ll, "confinedNegLimitBasicAdd failed");
	}

	bool confinedNegLimitBasicSuball()
	{
		bool ret_l = nouse::confinedNegLimitBasicSub<long>();
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		bool ret_ll = nouse::confinedNegLimitBasicSub<long long>();
		ASSERT_CONTINUE(ret_ll, "long long instantiation failed");

		ASSERT_TEST(ret_l && ret_ll, "confinedNegLimitBasicSub failed");
	}

	bool confinedNegLimitMultiAddall()
	{
		bool ret_l = nouse::confinedNegLimitMultiAdd<long>();
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		bool ret_ll = nouse::confinedNegLimitMultiAdd<long long>();
		ASSERT_CONTINUE(ret_ll, "long long instantiation failed");

		ASSERT_TEST(ret_l && ret_ll, "confinedNegLimitMultiAdd failed");
	}

	bool confinedNegLimitMultiSuball()
	{
		bool ret_l = nouse::confinedNegLimitMultiSub<long>();
		ASSERT_CONTINUE(ret_l, "long instantiation failed");
		bool ret_ll = nouse::confinedNegLimitMultiSub<long long>();
		ASSERT_CONTINUE(ret_ll, "long long instantiation failed");

		ASSERT_TEST(ret_l && ret_ll, "confinedNegLimitMultiSub failed");
	}
}

int main()
{
	REGISTER_TEST(testCase::confinedbasicAddall);
	REGISTER_TEST(testCase::confinedbasicSuball);
	REGISTER_TEST(testCase::confinedmultiAddall);
	REGISTER_TEST(testCase::confinedmultiSuball);
	REGISTER_TEST(testCase::confinedNegLimitBasicAddall);
	REGISTER_TEST(testCase::confinedNegLimitBasicSuball);
	REGISTER_TEST(testCase::confinedNegLimitMultiAddall);
	REGISTER_TEST(testCase::confinedNegLimitMultiSuball);
	return call_main();
}