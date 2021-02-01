/** ***************************************************************************
	\file main.test.cpp

	\brief The file to easily compile individual tests

	Created 16 January 2021

	This file is part of project Enhance C++ Libraries.

	Copyright 2021 Harith Manoj <harithpub@gmail.com>

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

#ifdef ConfinedValueUnitTest
#	include "Confined.test.cpp"
#endif

#ifdef ErrorModuleUnitTest
#	include "Error.test.cpp"
#endif

#ifdef GenericModuleUnitTest
#	include "General.test.cpp"
#endif

#ifdef QueuedHandlerUnitTest
#	include "QueuedHandler.test.cpp"
#endif

#ifdef TimerUnitTest
#	include "Timer.test.cpp"
#endif