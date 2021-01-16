#
#	File for information about library
#
#	Created 16 January 2021
#
#	This file is part of project Enhance C++ Libraries.
#
#	Copyright 2021 Harith Manoj <harithpub@gmail.com>
#	
#	Licensed under the Apache License, Version 2.0 (the "License");
#	you may not use this file except in compliance with the License.
#	You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
#	Unless required by applicable law or agreed to in writing, software
#	distributed under the License is distributed on an "AS IS" BASIS,
#	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#	See the License for the specific language governing permissions and
#	limitations under the License.
#
cmake_minimum_required(VERSION 3.10)

project(EnhanceCPPLibrary VERSION 2.0.0.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_DEBUG_LOG "enable ENH_DEBUG_CONTROL and linking to logger compilation" OFF)
option(ENABLE_UNIT_TESTS "enable unit testing" OFF)
option(ENABLE_EXAMPLE "enable example compile test" OFF)


#	individual example compile test options
option(CONCURRENCY_EX_TEST "enable concurrency example compile test" OFF)
option(GENERIC_EX_TEST "enable generic utility example compile test" OFF)
option(DATE_TIME_EX_TEST "enable Date Time example compile test" OFF)
option(ERROR_EX_TEST "enable Error Handling example compile test" OFF)
option(DIAGNOSTIC_EX_TEST "enable Diagnostics example compile test" OFF)



if(ENABLE_DEBUG_LOG)
	message( STATUS "add header + logger.cpp")
	add_library(EnhanceCPPLibrary src/logger.cpp)
	target_compile_definitions(EnhanceCPPLibrary PUBLIC ENH_DEBUG_CONTROL)
else()
	message( STATUS "add header only library")
	add_library(EnhanceCPPLibrary INTERFACE)
endif()

target_include_directories(EnhanceCPPLibrary INTERFACE src/Header/)

if(ENABLE_EXAMPLE)
	if(CONCURRENCY_EX_TEST) # Concurrency Example
		message( STATUS "add concurrency example")
		
		# QueuedHandler example
		add_executable(ConcurrencyExample documentation/examples/QueuedHandler.ex.cpp)
		target_include_directories(ConcurrencyExample PUBLIC src/Header/)
		
	endif()
	
	if(DIAGNOSTIC_EX_TEST)
		if(ENABLE_DEBUG_LOG)
			message( STATUS "add diagnostic example")
			
			# Debug logging with logging explicitely unset example
			add_executable(NDebugLoggerExample documentation/examples/logger.ndbg.ex.cpp)
			target_include_directories(NDebugLoggerExample PUBLIC src/Header/)
			target_link_libraries(NDebugLoggerExample PUBLIC EnhanceCPPLibrary)
			
			# Debug logging example
			add_executable(DebugLoggerExample documentation/examples/logger.dbg.ex.cpp)
			target_include_directories(DebugLoggerExample PUBLIC src/Header/)
			target_link_libraries(DebugLoggerExample PUBLIC EnhanceCPPLibrary)
		else()
			message( FATAL_ERROR "cannot compile diagnostic example without ENABLE_DEBUG_LOG")
		endif()
	endif()
	
endif()
