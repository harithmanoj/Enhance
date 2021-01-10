/** ***************************************************************************
	\file logger.enh.h

	\brief The file for logging functionality

	Created 26 April 2020

	This file is part of project Enhance C++ Libraries.

	Copyright 2020-2021 Harith Manoj <harithpub@gmail.com>
	
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.



	<h3> How To Use</h3>
	- Include file `logger.enh.h`

	- Make sure to add `logger.cpp` to compilation

	- Use the macros `O#_LOG_LINE, O#_LOG_DESC, O#_LOG_VAL where # in [1,5]` in
	code at specific logging points.
		- `O#_LOG_LINE where # in [1,5]` takes no arguments and logs the 
	completion of that line in that function.
		- `O#_LOG_DESC where # in [1,5]` takes one argument that is a string
	and logs the value of the string and current line and function. 
		- `O#_LOG_VAL where # in [1,5]` takes one argument. The argument must 
	be a type accepted by stream insertion operator. The evaluated value and 
	literal text converted form of passed expresion is logged.

	- When compiling, define `ENH_OPTIMISATION` above the include directive as
	a value between 0 and 5.

	- Higher the optimisation the lower the number of logging, that is for 
	optimisation 0, all logging O5, O4, O3, O2, O1 is active but for 
	optimisation 5 none is active.

	- Define `ENH_CLEAR_OP_` to use no logging (automatic if `_DEBUG` is not
	defined).

	- Define `IGNORE_ENHANCE_DIAGNOSTICS` to remove all logging calls from 
	enhance library classes and functions.

	- Use `ERROR_FLAG_LOG` to log errors managed by `common::ErrorTracker` 
	class template, Pass the object with which ErrorTracker methods can be 
	called.

	- Use `REPLACE` for expressions to be evaluated only during debug.

	- Use `REPLACE_AS` for expression with different values during debug and
	release.

	<h4> Examples </h4>
	
	Debug active :

	\include{lineno} logger_dbg_ex.cpp

	Debug not active :

	\include{lineno} logger_ndbg_ex.cpp


******************************************************************************/

#ifndef LOGGER_ENH_H

#define LOGGER_ENH_H				logger.enh.h

#include <filesystem>
#include <thread>
#include <string>
#include <sstream>
#include <iomanip>



#ifdef _DEBUG
#ifndef ENH_DEBUG_CONTROL
#define ENH_DEBUG_CONTROL				true
#endif	// !ENH_DEBUG_CONTROL

#ifdef ENH_CLEAR_OP_

#ifdef ENH_DEBUG_CONTROL 
#undef ENH_DEBUG_CONTROL
#endif //ENH_DEBUG_CONTROL

#ifdef ENH_OPTIMISATION
#undef ENH_OPTIMISATION
#endif //ENH_OPTIMISATION

#define ENH_OPTIMISATION				10

#endif // ENH_CLEAR_OP_

#endif // _DEBUG


#if defined(ENH_DEBUG_CONTROL) && !defined(IGNORE_ENHANCE_DIAGNOSTICS)

#define ERROR_BASE_LOG

#endif // defined(ENH_DEBUG_CONTROL) && !defined(IGNORE_ENHANCE_DIAGNOSTICS)

#if  defined(ENH_DEBUG_CONTROL)
/**
	\brief The namespace for diagnostics
*/
namespace debug
{


	/**
		\brief The file to get which file to log into.

		<h3>Return</h3>
		The path of file.

	*/
	std::filesystem::path getLoggingFilePath(
		std::thread::id id /**< : <i>in</i> : The calling thread id.*/,
		std::string function /**< : <i>in</i> : Logging function name.*/
	);


	/**
		\brief Logs a string to a file indicated byt current thread.

		The function which logs the string should be passed to function.
	*/
	void log(
		std::string msg /**< : <i>in</i> : The string to log.*/,
		std::string function /**< : <i>in</i> : Logging function name.*/
	);

	/**
		\brief Logs calling line, function and file to a file indicated by 
		current thread.
	*/
	void log(
		std::string file /**< : <i>in</i> : The file in which logging code is 
						 present.*/,
		std::string function/**< : <i>in</i> : Logging function name.*/,
		unsigned long line /**< : <i>in</i> : The line of file in which 
						   logging code is present.*/,
		char type /**< : <i>in</i> : The type of log E, I, W, F */
	);

	/**
		\brief Logs calling line, function, file and a description to a file 
		indicated by current thread.
	*/
	void log(
		std::string file /**< : <i>in</i> : The file in which logging code is 
						 present.*/,
		std::string function /**< : <i>in</i> : Logging function name.*/,
		unsigned long line /**< : <i>in</i> : The line of file in which 
						   logging code is present.*/,
		std::string descr /**< : <i>in</i> : The string to log.*/,
		char type /**< : <i>in</i> : The type of log E, I, W, F */
	);

	/**
		\brief Logs calling line, function, file and a value to a file
		indicated by current thread.

		The type should be accepted by the stream insertion operator.
	*/
	template<class T>
	void log(
		std::string file /**< : <i>in</i> : The file in which logging code is 
						 present.*/,
		std::string function /**< : <i>in</i> : Logging function name.*/,
		unsigned long line /**< : <i>in</i> : The line of file in which 
						   logging code is present.*/,
		std::string var /**< : <i>in</i> : The name of variable.*/,
		const T& val /**< : <i>in</i> : The value of the variable.*/,
		char type /**< : <i>in</i> : The type of log E, I, W, F */
	)
	{
		std::ostringstream out;
		out << " " << type << "/: " << std::setw(20) << function << "/" 
			<< std::setw(80) << file << "(" << std::setw(6) 
			<< line << ") : " << var << " = " << var;
		log(out.str(),function);
	}

}
#endif defined(ENH_DEBUG_CONTROL)


#ifdef ENH_DEBUG_CONTROL

/**
	\brief The Macro to execute a statement only in debug mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE(x)			x

/**
	\brief The Macro to execute a statement in debug mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS(x,y)		x


/**
	\brief The non-diagnostic version of REPLACE(x).
*/
#define NDBG_REPLACE(x)	

/**
	\brief The non-diagnostic version of REPLACE_AS(x,y).
*/
#define NDBG_REPLACE_AS(x,y)		y


/**
	\brief The info that is commonly passed to all logging functions.
*/
#define INFO_FOR_LOG		__FILE__,__func__,__LINE__

/**
	\brief The Macro to log line completion in debug mode.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_LINE(t)			debug::log(INFO_FOR_LOG, t)

/**
	\brief The Macro to log a string in debug mode.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_DESC(x, t)		debug::log(INFO_FOR_LOG,x,t)

/**
	\brief The Macro to log a variable state in debug mode.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_VAL(x, t)			debug::log(INFO_FOR_LOG,#x,x, t)

#else

/**
	\brief The Macro to execute a statement only in debug mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE(x)		

/**
	\brief The Macro to execute a statement in debug mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS(x,y)		y


/**
	\brief The non-diagnostic version of REPLACE(x).
*/
#define NDBG_REPLACE(x)	

/**
	\brief The non-diagnostic version of REPLACE_AS(x,y).
*/
#define NDBG_REPLACE_AS(x,y)		y

/**
	\brief The Macro to log line completion in debug mode.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_LINE(t)			

/**
	\brief The Macro to log a string in debug mode.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_DESC(x, t)			

/**
	\brief The Macro to log a variable state in debug mode.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_VAL(x, t)			

#endif // ENH_DEBUG_CONTROL


#if !defined(IGNORE_ENHANCE_DIAGNOSTICS) && defined(ENH_DEBUG_CONTROL)

/**
	\brief The Macro to execute a statement only in debug mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE(x)			x

/**
	\brief The Macro to execute a statement in debug mode and another if not, 
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if 
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS(x,y)		x


#else

/**
	\brief The Macro to execute a statement only in debug mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE(x)		

/**
	\brief The Macro to execute a statement in debug mode and another if not, library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS(x,y)		y


/**
	\brief The non-diagnostic version of LIB_REPLACE(x).
*/
#define NDBG_LIB_REPLACE(x)	

/**
	\brief The non-diagnostic version of LIB_REPLACE_AS(x,y).
*/
#define NDBG_LIB_REPLACE_AS(x,y)		y
	

#endif  //!defined(IGNORE_ENHANCE_DIAGNOSTICS) && defined(ENH_DEBUG_CONTROL)


#ifndef DISABLE_ERROR_LOGS

/**
	\brief The Macro to execute a statement only in debug-error mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_E(x)				REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-error mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS_E(x, y)			REPLACE_AS(x, y)

/**
	\brief The Macro to execute a statement only in debug-error mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_E(x)			LIB_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-error mode and another if not,
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS_E(x, y)		LIB_REPLACE_AS(x,y)

#else

/**
	\brief The Macro to execute a statement only in debug-error mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_E(x)				NDBG_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-error mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS_E(x, y)			NDBG_REPLACE_AS(x, y)


/**
	\brief The Macro to execute a statement only in debug-error mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_E(x)			NDBG_LIB_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-error mode and another if not,
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS_E(x, y)		NDBG_LIB_REPLACE_AS(x,y)


#endif // !DISABLE_ERROR_LOGS

#ifndef DISABLE_WARNING_LOGS

/**
	\brief The Macro to execute a statement only in debug-warning mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/

#define REPLACE_W(x)				REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-warning mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS_W(x, y)			REPLACE_AS(x, y)


/**
	\brief The Macro to execute a statement only in debug-warning mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_W(x)			LIB_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-warning mode and another if not,
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS_W(x, y)		LIB_REPLACE_AS(x,y)


#else

/**
	\brief The Macro to execute a statement only in debug-warning mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_W(x)				NDBG_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-warning mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS_W(x, y)			NDBG_REPLACE_AS(x, y)


/**
	\brief The Macro to execute a statement only in debug-warning mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_W(x)			NDBG_LIB_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-warning mode and another if not,
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS_W(x, y)		NDBG_LIB_REPLACE_AS(x,y)


#endif // !DISABLE_WARNING_LOGS

#ifndef DISABLE_INFO_FLAGS

/**
	\brief The Macro to execute a statement only in debug-info mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_I(x)				REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-info mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS_I(x, y)			REPLACE_AS(x, y)


/**
	\brief The Macro to execute a statement only in debug-info mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_I(x)			LIB_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-info mode and another if not,
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS_I(x, y)		LIB_REPLACE_AS(x,y)
#else

/**
	\brief The Macro to execute a statement only in debug-info mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_I(x)				NDBG_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-info mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS_I(x, y)			NDBG_REPLACE_AS(x, y)



/**
	\brief The Macro to execute a statement only in debug-info mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_W(x)			NDBG_LIB_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-info mode and another if not,
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS_W(x, y)		NDBG_LIB_REPLACE_AS(x,y)

#endif // !DISABLE_INFO_FLAGS

#ifndef DISABLE_FATAL_FLAGS

/**
	\brief The Macro to execute a statement only in debug-fatal-error mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_FE(x)				REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-fatal-error mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS_FE(x, y)			REPLACE_AS(x, y)

/**
	\brief The Macro to execute a statement only in debug-fatal-error mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_FE(x)			LIB_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-fatal-error mode and another if not,
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS_FE(x, y)		LIB_REPLACE_AS(x,y)

#else

/**
	\brief The Macro to execute a statement only in debug-fatal-error mode.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_FE(x)				NDBG_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-fatal-error mode and another if not.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined.
*/
#define REPLACE_AS_FE(x, y)			NDBG_REPLACE_AS(x, y)



/**
	\brief The Macro to execute a statement only in debug-fatal-error mode, library call.

	Evaluates to the macro argument passed if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined
	or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_FE(x)			NDBG_LIB_REPLACE(x)

/**
	\brief The Macro to execute a statement in debug-fatal-error mode and another if not,
	library call.

	Evaluates to the first macro argument passed if DEBUG is defined.\n\n
	Evaluates to seconds macro argument if DEBUG is not defined or if
	ENH_CLEAR_OP_ is defined or if IGNORE_ENHANCE_DIAGNOSTICS is defined.
*/
#define LIB_REPLACE_AS_FE(x, y)		NDBG_LIB_REPLACE_AS(x,y)
#endif // !DISABLE_FATAL_FLAGS

/**
	\brief The Macro to log line completion in debug-error mode.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_LINE_E					REPLACE_E(LOG_LINE('E'))

/**
	\brief The Macro to log a string in debug-error mode.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_DESC_E(x)				REPLACE_E(LOG_DESC(x,'E'))

/**
	\brief The Macro to log a variable state in debug-error mode.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_VALUE_E(x)				REPLACE_E(LOG_VAL(x,'E'))

/**
	\brief The Macro to log line completion in debug-error mode for library 
	functions.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_LINE_E				LIB_REPLACE_E(LOG_LINE('E'))

/**
	\brief The Macro to log a string in debug-error mode for library 
	functions.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_DESC_E(x)			LIB_REPLACE_E(LOG_DESC(x,'E'))

/**
	\brief The Macro to log a variable state in debug-error mode for library 
	functions.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_VALUE_E(x)			LIB_REPLACE_E(LOG_VAL(x,'E'))


/**
	\brief The Macro to log line completion in debug-warning mode.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_LINE_W					REPLACE_W(LOG_LINE('W'))

/**
	\brief The Macro to log a string in debug-warning mode.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_DESC_W(x)				REPLACE_W(LOG_DESC(x,'W'))

/**
	\brief The Macro to log a variable state in debug-warning mode.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_VALUE_W(x)				REPLACE_W(LOG_VAL(x,'W'))

/**
	\brief The Macro to log line completion in debug-warning mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_LINE_W				LIB_REPLACE_W(LOG_LINE('W'))

/**
	\brief The Macro to log a string in debug-warning mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_DESC_W(x)			LIB_REPLACE_W(LOG_DESC(x,'W'))

/**
	\brief The Macro to log a variable state in debug-warning mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_VALUE_W(x)			LIB_REPLACE_W(LOG_VAL(x,'W'))


/**
	\brief The Macro to log line completion in debug-info mode.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_LINE_I					REPLACE_I(LOG_LINE('I'))

/**
	\brief The Macro to log a string in debug-info mode.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_DESC_I(x)				REPLACE_I(LOG_DESC(x,'I'))

/**
	\brief The Macro to log a variable state in debug-info mode.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_VALUE_I(x)				REPLACE_I(LOG_VAL(x,'I'))

/**
	\brief The Macro to log line completion in debug-info mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_LINE_I				LIB_REPLACE_I(LOG_LINE('I'))

/**
	\brief The Macro to log a string in debug-info mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_DESC_I(x)			LIB_REPLACE_I(LOG_DESC(x,'I'))

/**
	\brief The Macro to log a variable state in debug-info mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_VALUE_I(x)			LIB_REPLACE_I(LOG_VAL(x,'I'))


/**
	\brief The Macro to log line completion in debug-fatal-error mode.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_LINE_FE					REPLACE_FE(LOG_LINE('F'))

/**
	\brief The Macro to log a string in debug-fatal-error mode.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_DESC_FE(x)				REPLACE_FE(LOG_DESC(x,'F'))

/**
	\brief The Macro to log a variable state in debug-fatal-error mode.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LOG_VALUE_FE(x)				REPLACE_FE(LOG_VAL(x,'F'))

/**
	\brief The Macro to log line completion in debug-fatal-error mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_LINE_FE				LIB_REPLACE_FE(LOG_LINE('F'))

/**
	\brief The Macro to log a string in debug-fatal-error mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_DESC_FE(x)			LIB_REPLACE_FE(LOG_DESC(x,'F'))

/**
	\brief The Macro to log a variable state in debug-fatal-error mode for library
	functions.

	Evaluates to debug::log(INFO_FOR_LOG,#x,x) if DEBUG is defined.\n\n
	Evaluates to blank if DEBUG is not defined or if ENH_CLEAR_OP_ is defined.
*/
#define LIB_LOG_VALUE_FE(x)			LIB_REPLACE_FE(LOG_VAL(x,'F'))

#endif // !LOGGER_ENH_H


