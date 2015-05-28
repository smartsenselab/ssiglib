/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                   Software License Agreement (BSD License)
*                      For Smart Surveillance Framework
*                        http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, 
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright 
*       notice, this list of conditions and the following disclaimer in the 
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its 
*       contributors may be used to endorse or promote products derived from 
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
*  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#ifndef _SSF_CORE_RESOURCE_INFO_HPP_
#define _SSF_CORE_RESOURCE_INFO_HPP_

#include <string>
#include <map>

#include "core/core_defs.hpp"
#include "core/version_info.hpp"
#include "core/parameters.hpp"
#include "core/parameter_info.hpp"

namespace ssf{

	class ResourceInfo{		
		friend class Resource;

	public:
		CORE_EXPORT ResourceInfo(void);
		CORE_EXPORT virtual ~ResourceInfo(void);
		CORE_EXPORT ResourceInfo(const ResourceInfo& rhs);
		CORE_EXPORT ResourceInfo& operator=(const ResourceInfo& rhs);
	
		CORE_EXPORT std::string getAuthor() const;
		CORE_EXPORT std::string getDescription() const;
		CORE_EXPORT std::string getAuthorEmail() const;
		CORE_EXPORT VersionInfo getRequiredVersion() const;

		CORE_EXPORT std::string getProperty(const std::string& propertyName);
		CORE_EXPORT const std::map<std::string, ParameterInfo>& getParametersInfo();

	protected:
		CORE_EXPORT void setAuthor(const std::string& author);
		CORE_EXPORT void setDescription(const std::string& description);
		CORE_EXPORT void setAuthorEmail(const std::string& email);
		CORE_EXPORT void setRequiredVersion(const VersionInfo& version);

		CORE_EXPORT void setProperty(const std::string& propertyName, const std::string& propertyValue);


	protected:
		std::string mAuthor;
		std::string mDescription;
		std::string mAuthorEmail;
		VersionInfo mRequiredVersion;

		std::map<std::string, std::string> mProperties;
		std::map<std::string, ParameterInfo> mParametersInfo;

	};

}

#endif // !_SSF_CORE_RESOURCE_INFO_HPP_PP_