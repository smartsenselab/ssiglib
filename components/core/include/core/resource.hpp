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

#ifndef _SSF_CORE_RESOURCE_HPP_
#define _SSF_CORE_RESOURCE_HPP_

#include "core/core_defs.hpp"
#include "core/base_object.hpp"
#include "core/parameters.hpp"
#include "core/resource_info.hpp"

namespace ssf{

	class Resource : public BaseObject{

	public:
		CORE_EXPORT Resource(void);
		CORE_EXPORT virtual ~Resource(void);
		CORE_EXPORT Resource(const Resource& rhs);
		CORE_EXPORT Resource& operator=(const Resource& rhs);

		CORE_EXPORT virtual std::string getName() = 0;
		CORE_EXPORT virtual std::string getType() = 0;
		
		CORE_EXPORT virtual ResourceInfo getInfo();
		CORE_EXPORT virtual void setup(const std::string& paramFile, const std::string& nodeID);
		CORE_EXPORT virtual void setup(const FileHandle& paramFile, const std::string& nodeID);
		CORE_EXPORT virtual void setup(const ParametersSetup& paramSetup);

	protected:		
		CORE_EXPORT virtual void setAuthor(const std::string& author);
		CORE_EXPORT virtual void setDescription(const std::string& description);
		CORE_EXPORT virtual void setAuthorEmail(const std::string& authorEmail);
		CORE_EXPORT virtual void setRequiredVersion(const unsigned short& major, const unsigned short& minor = 0, const unsigned short& patch = 0);
		CORE_EXPORT virtual void setRequiredVersion(const VersionInfo& version);
		CORE_EXPORT virtual void setProperty(const std::string& propertyName, const std::string& propertyValue);

	private:
		ResourceInfo mResourceInfo;

	protected:
		Parameters PARAMETERS;

		
	};

}

#endif // !_SSF_CORE_RESOURCE_HPP_