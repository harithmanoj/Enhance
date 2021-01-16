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

option(ENABLE_DEBUG_LOG 
		"enable ENH_DEBUG_CONTROL and linking to logger compilation" OFF)
option(ENABLE_UNIT_TESTS "enable unit testing" OFF)
option(ENABLE_EXAMPLE "enable example compile test" OFF)


# individual example compile test options
option(CONCURRENCY_EX_TEST "enable concurrency example compile test" OFF)
option(GENERIC_EX_TEST "enable generic utility example compile test" OFF)
option(DATE_TIME_EX_TEST "enable Date Time example compile test" OFF)
option(ERROR_EX_TEST "enable Error Handling example compile test" OFF)
option(DIAGNOSTIC_EX_TEST "enable Diagnostics example compile test" OFF)

# individual unit test compile options
option(CONFINED_UNIT_TEST "enable ConfinedValue unit test" OFF)
option(ERROR_TRACKER_UNIT_TEST "enable ErrorTracker unit test" OFF)
option(GENERIC_UNIT_TEST "enable Generic Utility unit test" OFF)
option(QUEUED_HANDLER_UNIT_TEST "enable QueuedHandler unit test" OFF)
option(TIMER_UNIT_TEST "enable Timer unit test" OFF)

# configure model options
option(ALL_BUILD "build all" OFF)   # build with ENH_DEBUG_CONTROL enabled 
									# and build all examples, execute all tests


if(ALL_BUILD)
	
	set(ENABLE_DEBUG_LOG "enable ENH_DEBUG_CONTROL and linking to logger compilation" ON)
	set(ENABLE_UNIT_TESTS "enable unit testing" ON)
	set(ENABLE_EXAMPLE "enable example compile test" ON)


	# individual unit test compile sets
	set(CONFINED_UNIT_TEST "enable ConfinedValue unit test" ON)
	set(ERROR_TRACKER_UNIT_TEST "enable ErrorTracker unit test" ON)
	set(GENERIC_UNIT_TEST "enable Generic Utility unit test" ON)
	set(QUEUED_HANDLER_UNIT_TEST "enable QueuedHandler unit test" ON)
	set(TIMER_UNIT_TEST "enable Timer unit test" ON)
endif()

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

	function(exampleTest target)
		message(STATUS "add ${target} example")
		
		add_executable(${target} documentation/examples/main.ex.cpp)
		target_compile_definitions(${target} PUBLIC ${target})
		target_include_directories(${target} PUBLIC src/Header/)
		
	endfunction(exampleTest)
	
	if(CONCURRENCY_EX_TEST) # Concurrency Example
		message( STATUS "add all concurrency example")
		
		exampleTest("QueuedHandlerExample")
	endif()
	
	if(GENERIC_EX_TEST)
		message( STATUS "add generic utility example")
		
		exampleTest("ConfinedValueExample")		
		exampleTest("VersionInfoExample")
	endif()
	
	if(DATE_TIME_EX_TEST)
		message( STATUS "add date time module examples")
		
		exampleTest("CounterExample")		
		exampleTest("DateExample")		
		exampleTest("TimeStampExample")		
		exampleTest("DateTimeExample")		
		exampleTest("TimerExample")
	endif()
	
	if(ERROR_EX_TEST)
		if(ENABLE_DEBUG_LOG)
			message( STATUS "add error module examples")
			
			exampleTest("ErrorTrackerExample")
			target_link_libraries("ErrorTrackerExample" PUBLIC EnhanceCPPLibrary)
		else()
			message( FATAL_ERROR "cannot compile diagnostic example without ENABLE_DEBUG_LOG")
		endif()
		
		exampleTest("TristateExample")
	endif()
	
	if(DIAGNOSTIC_EX_TEST)
		if(ENABLE_DEBUG_LOG)
			message( STATUS "add diagnostic example")
			
			exampleTest("LoggerNDebugExample")
			target_link_libraries("LoggerNDebugExample" PUBLIC EnhanceCPPLibrary)
			exampleTest("LoggerDebugExample")
			target_link_libraries("LoggerDebugExample" PUBLIC EnhanceCPPLibrary)
		else()
			message( FATAL_ERROR "cannot compile diagnostic example without ENABLE_DEBUG_LOG")
		endif()
	endif()
	
endif()


if(ENABLE_UNIT_TESTS)

	if(CONFINED_UNIT_TEST)
		message( STATUS "CONFINED_UNIT_TEST executable")
		add_executable(ConfinedValueUnitTest auto-test/Confined.test.cpp)
		target_include_directories(ConfinedValueUnitTest PUBLIC src/Header/)
	endif()
	
	if(ERROR_TRACKER_UNIT_TEST)
		message(STATUS "ERROR_TRACKER_UNIT_TEST executable")
		add_executable(ErrorTrackerUnitTest auto-test/Error.test.cpp)
		target_include_directories(ErrorTrackerUnitTest PUBLIC src/Header/)
	endif()
	
	if(GENERIC_UNIT_TEST)
		message(STATUS "GENERIC_UNIT_TEST executable")
		add_executable(GenericUnitTest auto-test/General.test.cpp)
		target_include_directories(GenericUnitTest PUBLIC src/Header/)
	endif()
	
	if(QUEUED_HANDLER_UNIT_TEST)
		message(STATUS "QUEUED_HANDLER_UNIT_TEST executable")
		add_executable(QueuedHandlerUnitTest auto-test/QueuedHandler.test.cpp)
		target_include_directories(QueuedHandlerUnitTest PUBLIC src/Header/)
	endif()
	
	if(TIMER_UNIT_TEST)
		message(STATUS "TIMER_UNIT_TEST executable")
		add_executable(TimerUnitTest auto-test/Timer.test.cpp)
		target_include_directories(TimerUnitTest PUBLIC src/Header/)
	endif()
	
	enable_testing()
	
	function(unit_test target)
		add_test(NAME ${target}UnitTest COMMAND ${target})
		set_tests_properties( ${target}UnitTest PROPERTIES FAIL_REGULAR_EXPRESSION "*FAIL*")
	endfunction(unit_test)
	
	if(CONFINED_UNIT_TEST)
		unit_test(ConfinedValueUnitTest)
	endif()
	
	if(ERROR_TRACKER_UNIT_TEST)
		unit_test(ErrorTrackerUnitTest)
	endif()
	
	if(GENERIC_UNIT_TEST)
		unit_test(GenericUnitTest)
	endif()
	
	if(QUEUED_HANDLER_UNIT_TEST)
		unit_test(QueuedHandlerUnitTest)
	endif()
	
	if(TIMER_UNIT_TEST)
		unit_test(TimerUnitTest)
	endif()
	
endif()
