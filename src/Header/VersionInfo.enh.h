/** ***************************************************************************
	\file framework.enh.h

	\brief The file to declare version and the version info class

	Created 10 April 2020

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


#ifndef VERSION_INFO_ENH_H

#	define VERSION_INFO_ENH_H						VersionInfo.enh.h

/**
	\brief Convert version numbers to a format that can be taken as argument by 
	`enh::VersionInfo` (beta release).
*/
#	define VERSION_INFO_BETA(mj,mn,re,bl)		mj,mn,re,bl,enh::ReleaseType::BETA,\
											#mj "." #mn "." #re "." #bl ".beta"

/**
	\brief Convert version numbers to a format that can be taken as argument by
	`enh::VersionInfo` (final release).
*/
#	define VERSION_INFO_FIN(mj,mn,re,bl)		mj,mn,re,bl,enh::ReleaseType::RELEASE\
											,#mj "." #mn "." #re "." #bl ".fin"

#	include <string>

/**
	\brief The namespace for all the functions and classes of this library.
*/
namespace enh
{
	/**
		\brief Enumeration to define the release _releaseType.
	*/
	enum class ReleaseType : unsigned {
		BETA = 0,			/**< \brief <i>0</i> : Beta external release.*/
		RELEASE = 1			/**< \brief <i>1</i> : Final external release.*/
	};


	/**
		\brief The class to store version information.

		hasErrorHandlers        = false;\n

		<h3> Usage </h3>

		Declare a constexpr object of this class and give the version as
		parameter, where the last parameter.

		For easy declaration, use macros `VERSION_INFO_BETA` and 
		`VERSION_INFO_FIN` and pass version as arguments.

		Use different getters to use those values in banners and about
		sections of your program.

		<h3>Example</h3>

		\include{lineno} version_info_ex.cpp

	*/
	class VersionInfo
	{
		/**
			\brief The _major version.
		*/
		unsigned _major;
		
		/**
			\brief The _minor version.
		*/
		unsigned _minor;
		
		/**
			\brief The _revision count.
		*/
		unsigned _revision;
		
		/**
			\brief The _build number.
		*/
		unsigned long _build;

		/**
			\brief The release _releaseType.
		*/
		ReleaseType _releaseType;

		/**
			\brief The string representation of the version.
		*/
		std::string_view _constStringRepresentation;
	public:


		/**
			\brief The constructor initialises to 0.0.0.0.beta


			<h3>Overloads</h3>
			-# <code>inline VersionInfo(unsigned, unsigned, unsigned, unsigned,
			 enh::ReleaseType) noexcept;</code>\n
			-# <code>inline VersionInfo(unsigned, unsigned, unsigned, unsigned,
			enh::ReleaseType, std::string_view) noexcept;</code>\n
		*/
		constexpr inline VersionInfo() noexcept :_major(0), _minor(0),
			_revision(0), _build(0), _releaseType(ReleaseType::BETA) { }

		/**
			\brief The constructor initialises to argument passed (no default 
			string).

			<h3>Overloads</h3>
			-# <code>inline VersionInfo() noexcept;</code>\n
			-# <code>inline VersionInfo(unsigned, unsigned, unsigned,
			unsigned, enh::ReleaseType, std::string_view) noexcept;</code>\n
		*/
		constexpr inline VersionInfo(
			unsigned mj /**< : <i>in</i> : _major version.*/,
			unsigned mn /**< : <i>in</i> : _minor version.*/,
			unsigned rv /**< : <i>in</i> : _revision number.*/,
			unsigned long bld /**< : <i>in</i> : _build number.*/,
			ReleaseType tp /**< : <i>in</i> : The release _releaseType.*/
		) noexcept : _major(mj), _minor(mn), _revision(rv), _build(bld), 
			_releaseType(tp), _constStringRepresentation("") { }

		/**
			\brief The constructor initialises to argument passed with compile
			-time string format of version.

			<h3>Overloads</h3>
			-# <code>inline VersionInfo(unsigned, unsigned, unsigned,
			unsigned, enh::ReleaseType) noexcept;</code>\n
			-# <code>inline VersionInfo() noexcept;</code>\n
		*/
		constexpr inline VersionInfo(
			unsigned mj /**< : <i>in</i> : _major version.*/,
			unsigned mn /**< : <i>in</i> : _minor version.*/,
			unsigned rv /**< : <i>in</i> : _revision number.*/,
			unsigned long bld /**< : <i>in</i> : _build number.*/,
			ReleaseType tp /**< : <i>in</i> : The release _releaseType.*/,
			std::string_view rep  /**< : <i>in</i> : The version as a string.*/
		) noexcept : _major(mj), _minor(mn), _revision(rv), _build(bld),
			_releaseType(tp), _constStringRepresentation(rep) { }

		/**
			\brief The get _major version.

			<h3>Return</h3>
			Major version.\n
		*/
		inline constexpr unsigned getMajor() const noexcept { return _major; }

		/**
			\brief The get _minor version.

			<h3>Return</h3>
			Minor version.\n
		*/
		inline constexpr unsigned getMinor() const noexcept { return _minor; }

		/**
			\brief The get _revision number.

			<h3>Return</h3>
			Revision number.\n
		*/
		inline constexpr unsigned getRevision() const noexcept 
		{ return _revision; }

		/**
			\brief The get _build number.

			<h3>Return</h3>
			Build number.\n
		*/
		inline constexpr unsigned long getBuild() const noexcept 
		{ return _build; }

		/**
			\brief The get release _releaseType.

			<h3>Return</h3>
			Release _releaseType.\n
		*/
		inline constexpr ReleaseType getReleaseType() const noexcept 
		{ return _releaseType; }

		/*
			\brief The function to get version as a string.

			<h3>Return</h3>
			The version as a string.\n
		*/
		inline std::string toString() const
		{
			if (!_constStringRepresentation.empty())
				return _constStringRepresentation.data();
			std::string ret = std::to_string(_major) + "." 
				+ std::to_string(_minor) + "." + std::to_string(_revision) 
				+ "." + std::to_string(_build) + ".";

			switch (_releaseType)
			{
			case ReleaseType::BETA:
				ret += "beta";
				break;
			case ReleaseType::RELEASE:
				ret += "fin";
				break;
			default:
				break;
			}
			return ret;
		}

		/**
			\brief Function returns string format of version.

			Works compile time too.

			Only returns if it is set during construction.
		*/
		inline constexpr std::string_view string() const noexcept
		{
			return _constStringRepresentation;
		}
	};

	/**
		\brief The version of enhance library.
	*/
	constexpr VersionInfo enhanceVersion 
		= VersionInfo(VERSION_INFO_FIN(1,3,1,7));
}

#endif