/** ***************************************************************************
	\file main.ex.cpp

	\brief The file to easily compile individual examples

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

#ifdef ConfinedValueExample
#	include "ConfinedValue.ex.cpp"
#endif

#ifdef CounterExample
#	include "Counter.ex.cpp"
#endif

#ifdef DateExample
#	include "Date.ex.cpp"
#endif

#ifdef DateTimeExample
#	include "DateTime.ex.cpp"
#endif

#ifdef ErrorTrackerExample
#	include "ErrorTracker.ex.cpp"
#endif

#ifdef LoggerNDebugExample
#	include "logger.ndbg.ex.cpp"
#endif

#ifdef LoggerDebugExample
#	include "logger.dbg.ex.cpp"
#endif

#ifdef QueuedHandlerExample
#	include "QueuedHandler.ex.cpp"
#endif

#ifdef TimerExample
#	include "Timer.ex.cpp"
#endif

#ifdef TimeStampExample
#	include "TimeStamp.ex.cpp"
#endif

#ifdef TristateExample
#	include "Tristate.ex.cpp"
#endif

#ifdef VersionInfoExample
#	include "VersionInfo.ex.cpp"
#endif
