/** ***************************************************************************
	\file QueuedHandler.test.cpp

	\brief The file to test parts of module QProc

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
#include <QueuedHandler.enh.h>
#include "test.base.h"

namespace testCase
{
	bool basicTest()
	{
		unsigned t = 0;
		enh::QueuedHandler<unsigned> tQ;
		tQ.registerHandlerFunction(
			[&](unsigned a) -> enh::Tristate {
				t += a; 
				return enh::Tristate::GOOD;
			}
		);
		tQ.startDispatcherExecution();
		unsigned exp = 0;

		for (unsigned i = 0; i < 5; ++i)
		{
			exp += i;
			tQ.postMessage(i);
		}

		tQ.joinAfterQueueEmpty(std::chrono::milliseconds(1));

		ASSERT_TEST(t == exp, "Not evaluating all messages");
	}

	bool forceStopTest()
	{
		unsigned t = 0;
		enh::QueuedHandler<unsigned> tQ;
		tQ.registerHandlerFunction(
			[&](unsigned a) -> enh::Tristate {
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				t += a;
				return enh::Tristate::GOOD; 
			}
		);
		tQ.startDispatcherExecution();
		unsigned exp = 0;

		for (unsigned i = 0; i < 10; ++i)
		{
			tQ.postMessage(i);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5 * 5));

		exp = 0 + 1 + 2 + 3 + 4;

		tQ.forceImmediateJoin();

		ASSERT_TEST(t <= exp, "Evaluating even after force stop");
	}

	bool restartTest()
	{
		unsigned t = 0;
		enh::QueuedHandler<unsigned> tQ;
		tQ.registerHandlerFunction(
			[&](unsigned a) -> enh::Tristate {
				t += a; 
				return enh::Tristate::GOOD; 
			}
		);
		tQ.startDispatcherExecution();
		unsigned exp = 0;

		for (unsigned i = 0; i < 5; ++i)
		{
			exp += i;
			tQ.postMessage(i);
		}

		tQ.joinAfterQueueEmpty(std::chrono::milliseconds(1));

		tQ.startDispatcherExecution();
		for (unsigned i = 0; i < 5; ++i)
		{
			exp += i;
			tQ.postMessage(i);
		}

		tQ.joinAfterQueueEmpty(std::chrono::milliseconds(1));

		ASSERT_TEST(t == exp, "Restart queue failed");
	}
}

int main()
{
	REGISTER_TEST(testCase::basicTest);
	REGISTER_TEST(testCase::forceStopTest);
	REGISTER_TEST(testCase::restartTest);
	return call_main();
}