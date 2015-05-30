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

#ifndef _SSF_CORE_RESOURCE_INFO_HPP_
#define _SSF_CORE_RESOURCE_INFO_HPP_

#include <string>
#include <map>

#include "core/core_defs.hpp"
#include "core/version_info.hpp"
#include "core/parameters.hpp"
#include "core/parameter_info.hpp"

namespace ssf{

	/**
	 * @brief	Information about a Resource Class.
	 */
	class ResourceInfo{		
		friend class Resource;

	public:

		/**
		 * @brief	Initializes a new instance of the ResourceInfo class.
		 */
		CORE_EXPORT ResourceInfo(void);

		/**
		 * @brief	Finalizes an instance of the ResourceInfo class.
		 */
		CORE_EXPORT virtual ~ResourceInfo(void);

		/**
		 * @brief	Initializes a new instance of the ResourceInfo class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT ResourceInfo(const ResourceInfo& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT ResourceInfo& operator=(const ResourceInfo& rhs);

		/**
		 * @brief	Gets the resource author.
		 *
		 * @return	A string with the author name.
		 */
		CORE_EXPORT std::string author() const;

		/**
		 * @brief	Gets the resource description.
		 *
		 * @return	A string with the resource description.
		 */
		CORE_EXPORT std::string description() const;

		/**
		 * @brief	Gets the email of resource author.
		 *
		 * @return	A string with the author email.
		 */
		CORE_EXPORT std::string authorEmail() const;

		/**
		 * @brief	Gets the minimum version required by resource.
		 *
		 * @return	A VersionInfo with the required version.
		 */
		CORE_EXPORT VersionInfo requiredVersion() const;

		/**
		 * @brief	Gets a resource property value.
		 *
		 * @param	propertyName	Name of the property.
		 *
		 * @return	A string with the property value.
		 */
		CORE_EXPORT std::string propertyValue(const std::string& propertyName);

		/**
		 * @brief	The information describing the parameters
		 *
		 * @return	A std::map&lt;std::string,ParameterInfo&gt;&amp with ParameterInfo;
		 */
		CORE_EXPORT const std::map<std::string, ParameterInfo>& parametersInfo();

	protected:

		/**
		 * @brief	Sets the resource author.
		 *
		 * @param	author	The author name.
		 */
		CORE_EXPORT void setAuthor(const std::string& author);

		/**
		 * @brief	Sets the resource description.
		 *
		 * @param	description	The description text.
		 */
		CORE_EXPORT void setDescription(const std::string& description);

		/**
		 * @brief	Sets the email of resource author.
		 *
		 * @param	email	The email of author.
		 */
		CORE_EXPORT void setAuthorEmail(const std::string& email);

		/**
		 * @brief	Sets minimum required SSF version.
		 *
		 * @param	version	The required version.
		 */
		CORE_EXPORT void setRequiredVersion(const VersionInfo& version);

		/**
		 * @brief	Sets a property value.
		 *
		 * @param	propertyName 	Name of the property.
		 * @param	propertyValue	The property value.
		 */
		CORE_EXPORT void setProperty(const std::string& propertyName, const std::string& propertyValue);


	protected:
		std::string mAuthor;	///< The resource author
		std::string mDescription;   ///< The resource description
		std::string mAuthorEmail;   ///< The author email
		VersionInfo mRequiredVersion;   ///< The minimum required version

		std::map<std::string, std::string> mProperties; ///< The properties
		std::map<std::string, ParameterInfo> mParametersInfo;   ///< Information describing the parameters

	};

}

#endif // !_SSF_CORE_RESOURCE_INFO_HPP_PP_