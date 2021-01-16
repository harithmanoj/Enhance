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


option(ENABLE_DEBUG_LOG "enable ENH_DEBUG_CONTROL and linking to logger compilation" ON)
option(ENABLE_UNIT_TESTS "enable unit testing" ON)
option(ENABLE_EXAMPLE "enable example compile test" ON)

