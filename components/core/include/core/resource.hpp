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

#ifndef _SSF_CORE_RESOURCE_HPP_

/**
 * @brief	A macro that defines ssf core resource hpp.
 */
#define _SSF_CORE_RESOURCE_HPP_

#include "core/core_defs.hpp"
#include "core/base_object.hpp"
#include "core/parameters.hpp"
#include "core/resource_info.hpp"

namespace ssf{

	/**
	 * @brief	A Resource is a base class for other SSF objects that need parameters.
	 *
	 * @sa	BaseObject
	 */
	class Resource : public BaseObject{

	public:

		/**
		 * @brief	Initializes a new instance of the Resource class.
		 */
		CORE_EXPORT Resource(void);

		/**
		 * @brief	Finalizes an instance of the Resource class.
		 */
		CORE_EXPORT virtual ~Resource(void);

		/**
		 * @brief	Initializes a new instance of the Resource class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT Resource(const Resource& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT Resource& operator=(const Resource& rhs);

		/**
		 * @brief	Gets the resource name.
		 *
		 * @return	A string with the resource name.
		 */
		CORE_EXPORT virtual std::string name() = 0;

		/**
		 * @brief	Gets the resource type.
		 *
		 * @return	A string with the resource type.
		 */
		CORE_EXPORT virtual std::string type() = 0;

		/**
		 * @brief	Gets the information about the resource.
		 *
		 * @return	A ResourceInfo.
		 */
		CORE_EXPORT virtual ResourceInfo info();

		/**
		 * @brief	Setups parameters values of resource by a parameter file.
		 *
		 * @param	paramFile	The parameter file.
		 * @param	nodeID   	Identifier for the node.
		 */
		CORE_EXPORT virtual void setup(const std::string& paramFile, const std::string& nodeID);

		/**
		 * @brief	Setups parameters values of resource by a parameter file.
		 *
		 * @param	paramFile	The parameter file.
		 * @param	nodeID   	Identifier for the node.
		 */
		CORE_EXPORT virtual void setup(const FileHandle& paramFile, const std::string& nodeID);

		/**
		 * @brief	Setups parameters values of resource by a ParametersSetup object.
		 *
		 * @param	paramSetup	The ParametersSetup.
		 */
		CORE_EXPORT virtual void setup(const ParametersSetup& paramSetup);

	protected:		

		/**
		 * @brief	Sets an author.
		 *
		 * @param	author	The author.
		 */
		CORE_EXPORT virtual void setAuthor(const std::string& author);

		/**
		 * @brief	Sets a description.
		 *
		 * @param	description	The description.
		 */
		CORE_EXPORT virtual void setDescription(const std::string& description);

		/**
		 * @brief	Sets author email.
		 *
		 * @param	authorEmail	The author email.
		 */
		CORE_EXPORT virtual void setAuthorEmail(const std::string& authorEmail);

		/**
		 * @brief	Sets the minimum required version of SSF.
		 *
		 * @param	major	The major version.
		 * @param	minor	The minor version.
		 * @param	patch	The patch version.
		 */
		CORE_EXPORT virtual void setRequiredVersion(const unsigned short& major, const unsigned short& minor = 0, const unsigned short& patch = 0);

		/**
		 * @brief	Sets required version.Sets the minimum required version of SSF.
		 *
		 * @param	version	The version.
		 */
		CORE_EXPORT virtual void setRequiredVersion(const VersionInfo& version);

		/**
		 * @brief	Sets a string property.
		 *
		 * @param	propertyName 	Name of the property.
		 * @param	propertyValue	The property value.
		 */
		CORE_EXPORT virtual void setProperty(const std::string& propertyName, const std::string& propertyValue);

	private:
		ResourceInfo mResourceInfo; ///< Information describing the resource

	protected:
		Parameters PARAMETERS;  ///< Options for controlling the operation

		
	};

}

#endif // !_SSF_CORE_RESOURCE_HPP_