/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this license. If you do 
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without modification, are permitted 
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of 
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
*       conditions and the following disclaimer in the documentation and/or other materials 
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
*       endorse or promote products derived from this software without specific prior written 
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#ifndef _SSF_CORE_VERSION_INFO_HPP_
#define _SSF_CORE_VERSION_INFO_HPP_

#include <string>

#include "core/core_defs.hpp"

namespace ssf{

	/**
	 * @brief	Class to store a version.
	 */
	class CORE_EXPORT VersionInfo{

	public:

		/**
		 * @brief	Initializes a new instance of the VersionInfo class.
		 *
		 * @param	major	The major version.
		 * @param	minor	The minor version.
		 * @param	patch	The patch version.
		 */
		VersionInfo(const unsigned short& major = 0, const unsigned short& minor = 0, const unsigned short& patch = 0);

		/**
		 * @brief	Initializes a new instance of the VersionInfo class.
		 *
		 * @param	version	The version as string.
		 */
		explicit VersionInfo(const std::string& version);

		/**
		 * @brief	Finalizes an instance of the VersionInfo class.
		 */
		virtual ~VersionInfo(void);

		/**
		 * @brief	Initializes a new instance of the VersionInfo class.
		 *
		 * @param	rhs	The right hand side.
		 */
		VersionInfo(const VersionInfo& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		VersionInfo& operator=(const VersionInfo& rhs);

		/**
		 * @brief	Gets the major.
		 *
		 * @return	The major.
		 */
		unsigned short major() const;

		/**
		 * @brief	Sets a major.
		 *
		 * @param	major	The major.
		 */
		void setMajor(const unsigned short& major);

		/**
		 * @brief	Gets the minor.
		 *
		 * @return	The minor.
		 */
		unsigned short minor() const;

		/**
		 * @brief	Sets a minor.
		 *
		 * @param	minor	The minor.
		 */
		void setMinor(const unsigned short& minor);

		/**
		 * @brief	Gets the patch.
		 *
		 * @return	The patch.
		 */
		unsigned short patch() const;

		/**
		 * @brief	Sets a patch.
		 *
		 * @param	patch	The patch.
		 */
		void setPatch(const unsigned short& patch);

		/**
		 * @brief	Sets.
		 *
		 * @param	major	The major.
		 * @param	minor	The minor.
		 * @param	patch	The patch.
		 */
		void set(const unsigned short& major = 0, const unsigned short& minor = 0, const unsigned short& patch = 0);

		/**
		 * @brief	Sets the given version.
		 *
		 * @param	version	The version to set as string.
		 */
		void set(const std::string& version);

		/**
		 * @brief	Convert this object into a string representation.
		 *
		 * @return	A std::string that represents this object.
		 */
		std::string toString() const;

		/**
		 * @brief	Equality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are considered equivalent.
		 */
		bool operator== (const VersionInfo& rhs);

		/**
		 * @brief	Inequality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are not considered equivalent.
		 */
		bool operator!= (const VersionInfo& rhs);

		/**
		 * @brief	Less-than comparison operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the first parameter is less than the second.
		 */
		bool operator< (const VersionInfo& rhs);

		/**
		 * @brief	Greater-than comparison operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the first parameter is greater than to the second.
		 */
		bool operator> (const VersionInfo& rhs);		

		/**
		 * @brief	Less-than-or-equal comparison operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the first parameter is less than or equal to the second.
		 */
		bool operator<= (const VersionInfo& rhs);

		/**
		 * @brief	Greater-than-or-equal comparison operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the first parameter is greater than or equal to the second.
		 */
		bool operator>= (const VersionInfo& rhs);
	

	private:

		
		unsigned short mMajor; ///< The major
		unsigned short mMinor; ///< The minor
		unsigned short mPatch; ///< The patch

	};

}

#endif // !_SSF_CORE_VERSION_INFO_HPP_PP_