/** ***************************************************************************
	\file ErrorTracker.enh.h
	
	\brief The file to declare ErrorTracker class.
 
	Created 24 March 2020	
		

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



#ifndef ERROR_TRACKER_ENH_H

#define ERROR_TRACKER_ENH_H				ErrorTracker.enh.h

#include <atomic>
#include "general.enh.h"
#include "logger.enh.h"
#include "Tristate.enh.h"


/*
	\brief The namespace for all the functions and classes of this library
*/
namespace enh
{
	
	/**
		\brief The class for inheriting error tracking Functionality.


		hasErrorHandlers        = false;\n\n\n

		Value 0x00 is reserved for Safe.\n
		Value 0x01 is reserved for unknown errors.\n
		Value 0x02 is reserved for invalid argument errors.\n\n

		<h3>Template Argument</h3>
		The underlying type to hold error information. (must be integral).

		<h3>Example</h3>

		\include{lineno} ErrorTracker_ex.cpp
	*/
	template<class type>
	class ErrorTracker
	{
	public:

		static_assert(std::is_integral_v<type>, "ErrorTracker should have integral error type");
		
		/**
			\brief The alias to hold constants for error reporting.
		*/
		using UnderlyingErrorType = type;

		/**
			\brief <i>0x00</i> : No error after last clear. 
		*/
		static constexpr UnderlyingErrorType SAFE = 0x00;

		/**
			\brief <i>0x01</i> : Unknown Error. 
		*/
		static constexpr UnderlyingErrorType UNKNOWN = 0x01;

		/**
			\brief <i>0x02</i> : Invalid argument. 
		*/
		static constexpr UnderlyingErrorType INVALID_ARG = 0x02;
	protected:

		/**
			\brief The error if any occured.
		*/
		std::atomic<UnderlyingErrorType> flag;

	public:



		/**
			\brief default constructor, constructs it as SAFE no error.
		*/
		inline ErrorTracker()
		{
			flag = SAFE;
		}

		/**
			\brief The function to clear error flag.

		*/
		inline void clear() noexcept
		{
			flag = SAFE;
		}

		/**
			\brief The function to get error flag.
			
			<h3> Return </h3>
			The error flag.\n
		*/
		inline UnderlyingErrorType getError() const noexcept
		{
			return flag;
		}

		/**
			\brief The function to check if certian error(s) are present.

			<h3> Return</h3>
			Returns true if passed error exists in tag.

		*/
		inline bool checkFlag(
			UnderlyingErrorType check_flag /**< : <i>in</i> : flag to check if raised.*/
		) const noexcept
		{
			return checkBitField(flag.load(), check_flag);
		}

		/**
			\brief The function to check if no error flag(s) are set.

			<h3>Return</h3>
			true if no error flags are set.\n

		*/
		inline bool isSafe() const noexcept
		{
			return (flag.load() == SAFE);
		}

		/*
			\brief All error flag(s) set.

			<h3>Return</h3>
			All error flag(s) set.\n
		*/
		virtual std::string toString() const
		{
			std::string ret = "";
			if (isSafe())
				return "SAFE";
			bool prev = false;
			bool unkwn = checkFlag(UNKNOWN);
			if (unkwn)
			{
				ret = "UNKNOWN";
				prev = true;
			}

			bool inv = checkFlag(INVALID_ARG);	
			if (inv)
			{
				if (prev)
					ret += " + ";
				ret += "INVALID_ARG";
				prev = true;
			}

			return ret;
		}
	protected:
		
		/**
			\brief The function to add the error given as argument to the
			error flag of class.

			For Setting flag while simultaneously return error state.\n\n

			<h3>Return</h3>
			Returns value Tristate::ERROR.\n

		*/
		inline Tristate setFlag(
			UnderlyingErrorType set /**< : <i>in</i> : flag to be added.*/
		) noexcept
		{
			flag |= set;
			return Tristate::ERROR;
		}

		/**
			\brief The function to clear certian fields from error set.

			For clearing certian flags after it has been resolved.\n\n

			<h3>Return</h3>
			Returns value Tristate::ERROR if flag is
			not set, Tristate::GOOD else.\n

		*/
		inline Tristate clearFlag(
			UnderlyingErrorType bitClear /**< : <i>in</i> : flag to be removed.*/
		) noexcept
		{
			if (!checkBitField(flag.load(), bitClear))
				return Tristate::ERROR;
			flag ^= bitClear;
			return Tristate::GOOD;
		}

		

#ifdef ErrorTracker_LOG


		/*
			\brief The name of derived class.

			<h3>Return</h3>
			The name of the class.\n
		*/
		virtual std::string derivedClassName() const noexcept
		{
			return "ErrorTracker";
		}

		
		public:
		
		/**
			\brief Logs value of flag at calling line, function and file to a 
			file indicated by current thread.
		*/
		void log(
			std::string file /**< : <i>in</i> : The file in which logging 
							 code is present.*/,
			std::string function/**< : <i>in</i> : Logging function name.*/,
			unsigned long line /**< : <i>in</i> : The line of file in which
							   logging code is present.*/,
			std::string variable /**< : <i>in</i> : The variable name of 
								 error holder.*/
		) const noexcept
		{
			debug::log(file, function, line, derivedClassName() + " " + variable 
				+ " flag : " + toString());
		}
#endif
	};

	

}

/**
	\brief Log error flags within enhance library.
	x must be a type that inherits publically from ErrorTracker or an object of 
	ErrorTracker.
*/
#define LIB_ERROR_FLAG_LOG(x)		O2_LIB_REPLACE(x.log(INFO_FOR_LOG,#x))

/**
	\brief Log error flags.
	x must be a type that inherits publically from ErrorTracker or an object of
	ErrorTracker.
*/
#define ERROR_FLAG_LOG(x)			O2_REPLACE(x.log(INFO_FOR_LOG,#x))

/**
	\brief Log error flags within enhance library using pointer (in class 
	logging using this pointer).
	x must be a type that inherits publically from ErrorTracker or an object of
	ErrorTracker.
*/
#define LIB_ERROR_FLAG_LOGP(x)		O2_LIB_REPLACE(x->log(INFO_FOR_LOG,#x))

/**
	\brief Log error flags using pointer (in class logging using this pointer).
	x must be a type that inherits publically from ErrorTracker or an object of
	ErrorTracker.
*/
#define ERROR_FLAG_LOGP(x)			O2_REPLACE(x->log(INFO_FOR_LOG,#x))

#endif