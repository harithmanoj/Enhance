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
option(ALL_EXAMPLE "build all examples" OFF)
option(ALL_UNIT_TEST "build all unit test" OFF)
option(FORCE_DISABLE_LOGGING "force disable logging regardless of build modes" OFF)

if(ALL_BUILD)
	
	set(ENABLE_DEBUG_LOG "enable ENH_DEBUG_CONTROL and linking to logger compilation" ON)
	set(ENABLE_UNIT_TESTS "enable unit testing" ON)
	set(ENABLE_EXAMPLE "enable example compile test" ON)

	# individual example compile test sets
	set(CONCURRENCY_EX_TEST "enable concurrency example compile test" ON)
	set(GENERIC_EX_TEST "enable generic utility example compile test" ON)
	set(DATE_TIME_EX_TEST "enable Date Time example compile test" ON)
	set(ERROR_EX_TEST "enable Error Handling example compile test" ON)
	set(DIAGNOSTIC_EX_TEST "enable Diagnostics example compile test" ON)


	# individual unit test compile sets
	set(CONFINED_UNIT_TEST "enable ConfinedValue unit test" ON)
	set(ERROR_TRACKER_UNIT_TEST "enable ErrorTracker unit test" ON)
	set(GENERIC_UNIT_TEST "enable Generic Utility unit test" ON)
	set(QUEUED_HANDLER_UNIT_TEST "enable QueuedHandler unit test" ON)
	set(TIMER_UNIT_TEST "enable Timer unit test" ON)
endif()

if(ALL_UNIT_TEST)
	
	set(ENABLE_UNIT_TESTS "enable unit testing" ON)
	
	# individual unit test compile sets
	set(CONFINED_UNIT_TEST "enable ConfinedValue unit test" ON)
	set(ERROR_TRACKER_UNIT_TEST "enable ErrorTracker unit test" ON)
	set(GENERIC_UNIT_TEST "enable Generic Utility unit test" ON)
	set(QUEUED_HANDLER_UNIT_TEST "enable QueuedHandler unit test" ON)
	set(TIMER_UNIT_TEST "enable Timer unit test" ON)
endif()

if(ALL_EXAMPLE)
	
	set(ENABLE_DEBUG_LOG "enable ENH_DEBUG_CONTROL and linking to logger compilation" ON)
	set(ENABLE_EXAMPLE "enable example compile test" ON)

	# individual example compile test sets
	set(CONCURRENCY_EX_TEST "enable concurrency example compile test" ON)
	set(GENERIC_EX_TEST "enable generic utility example compile test" ON)
	set(DATE_TIME_EX_TEST "enable Date Time example compile test" ON)
	set(ERROR_EX_TEST "enable Error Handling example compile test" ON)
	set(DIAGNOSTIC_EX_TEST "enable Diagnostics example compile test" ON)

endif()

if(FORCE_DISABLE_LOGGING)
	set(ENABLE_DEBUG_LOG "enable ENH_DEBUG_CONTROL" OFF)
endif()

if(ALL_BUILD)
	message(STATUS "All build enabled: logging enabled, example compile test, unit test definitions")
endif()
if(ALL_EXAMPLE)
	message(STATUS "All example build enabled: logging enabled, example compile test")
endif()
if(ALL_UNIT_TEST)
	message(STATUS "All Unit test build enabled: unit test definitions")
endif()

if(ENABLE_DEBUG_LOG)
	message(STATUS "	Enable debug logging")
endif()
if(ENABLE_UNIT_TESTS)
	message(STATUS "	Enable Unit test definitions")
endif()
if(ENABLE_EXAMPLE)
	message(STATUS "	Enable example compile test")
endif()

if(CONCURRENCY_EX_TEST)
	message(STATUS "	Enable concurrency example compile test")
endif()
if(GENERIC_EX_TEST)
	message(STATUS "	Enable generic utility example compile test")
endif()
if(DATE_TIME_EX_TEST)
	message(STATUS "	Enable Date time example compile test")
endif()
if(ERROR_EX_TEST)
	message(STATUS "	Enable error handling example compile test")
endif()
if(DIAGNOSTIC_EX_TEST)
	message(STATUS "	Enable Diagnostic example compile test")
endif()

if(CONFINED_UNIT_TEST)
	message(STATUS "	Enable Confined Value Unit Test definitions")
endif()
if(ERROR_TRACKER_UNIT_TEST)
	message(STATUS "	Enable Error Handling Unit Test definitions")
endif()
if(GENERIC_UNIT_TEST)
	message(STATUS "	Enable Generic utility Unit Test definitions")
endif()
if(QUEUED_HANDLER_UNIT_TEST)
	message(STATUS "	Enable Queued Handler Unit Test definitions")
endif()
if(TIMER_UNIT_TEST)
	message(STATUS "	Enable Timer Unit Test definitions")
endif()


add_library(EnhanceCPPLibrary src/logger.cpp)
	
if(ENABLE_DEBUG_LOG)
	message( STATUS "		Compile with logging enabled")
	target_compile_definitions(EnhanceCPPLibrary PUBLIC ENH_DEBUG_CONTROL)
else()
	message( STATUS "		Compile with logging disabled")
	target_compile_definitions(EnhanceCPPLibrary PUBLIC ENH_CLEAR_OP_)
endif()

target_include_directories(EnhanceCPPLibrary INTERFACE ./src/Header/)

if(ENABLE_EXAMPLE)

	function(exampleTest target)
		message( STATUS "	Individual add ${target} example")
		
		add_executable(${target} documentation/examples/main.ex.cpp)
		target_compile_definitions(${target} PUBLIC ${target})
		target_include_directories(${target} PUBLIC src/Header/)
		
	endfunction(exampleTest)
	
	if(CONCURRENCY_EX_TEST) # Concurrency Example
		message( STATUS "	Add all concurrency example")
		
		exampleTest("QueuedHandlerExample")
	endif()
	
	if(GENERIC_EX_TEST)
		message( STATUS "	Add generic utility example")
		
		exampleTest("ConfinedValueExample")		
		exampleTest("VersionInfoExample")
	endif()
	
	if(DATE_TIME_EX_TEST)
		message( STATUS "	Add date time module examples")
		
		exampleTest("CounterExample")		
		exampleTest("DateExample")		
		exampleTest("TimeStampExample")		
		exampleTest("DateTimeExample")		
		exampleTest("TimerExample")
	endif()
	
	if(ERROR_EX_TEST)
		if(ENABLE_DEBUG_LOG)
			message( STATUS "	Add error module examples")
			
			exampleTest("ErrorTrackerExample")
			target_link_libraries("ErrorTrackerExample" PUBLIC EnhanceCPPLibrary)
		else()
			message( FATAL_ERROR "cannot compile diagnostic example without ENABLE_DEBUG_LOG")
		endif()
		
		exampleTest("TristateExample")
	endif()
	
	if(DIAGNOSTIC_EX_TEST)
		if(ENABLE_DEBUG_LOG)
			message( STATUS "	Add diagnostic example")
			
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
enable_testing()
	function(unitTest target)
		message( STATUS "		Individual Unit Test ${target}")
		
		add_executable(${target} auto-test/main.test.cpp)
		target_compile_definitions(${target} PUBLIC ${target})
		target_include_directories(${target} PUBLIC src/Header/)
		
		add_test(NAME ${target}UnitTest COMMAND ${target})
		set_tests_properties( ${target}UnitTest PROPERTIES FAIL_REGULAR_EXPRESSION "FAIL*")
	endfunction(unitTest)

	if(CONFINED_UNIT_TEST)
		message( STATUS "	CONFINED_UNIT_TEST executable")
		unitTest("ConfinedValueUnitTest")
	endif()
	
	if(ERROR_TRACKER_UNIT_TEST)
		message(STATUS "	ERROR_TRACKER_UNIT_TEST executable")
		unitTest("ErrorModuleUnitTest")
	endif()
	
	if(GENERIC_UNIT_TEST)
		message(STATUS "	GENERIC_UNIT_TEST executable")
		unitTest("GenericModuleUnitTest")
	endif()
	
	if(QUEUED_HANDLER_UNIT_TEST)
		message(STATUS "	QUEUED_HANDLER_UNIT_TEST executable")
		unitTest("QueuedHandlerUnitTest")
	endif()
	
	if(TIMER_UNIT_TEST)
		message(STATUS "	TIMER_UNIT_TEST executable")
		unitTest("TimerUnitTest")
	endif()
	
endif()
