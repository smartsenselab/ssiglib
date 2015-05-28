/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                              License Agreement
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

#include "core/resource.hpp"

namespace ssf{

	Resource::Resource(){

	}

	Resource::~Resource(){
		//Destructor
	}

	Resource::Resource(const Resource& rhs){
		this->mResourceInfo = rhs.mResourceInfo;
		this->PARAMETERS = rhs.PARAMETERS;		
	}

	Resource& Resource::operator=(const Resource& rhs){
		if (this != &rhs){
			this->mResourceInfo = rhs.mResourceInfo;
			this->PARAMETERS = rhs.PARAMETERS;
		}
		return *this;
	}

	ssf::ResourceInfo Resource::getInfo(){
		ResourceInfo retResourceInfo = this->mResourceInfo;
		retResourceInfo.mParametersInfo = this->PARAMETERS.getParametersInfo();
		return retResourceInfo;
	}

	void Resource::setup(const std::string& paramFile, const std::string& nodeID){
		this->setup(ParametersSetup(paramFile, nodeID));
	}

	void Resource::setup(const FileHandle& paramFile, const std::string& nodeID){
		this->setup(ParametersSetup(paramFile, nodeID));
	}

	void Resource::setup(const ParametersSetup& paramsSetup){
		this->PARAMETERS.setup(paramsSetup);
	}

	void Resource::setAuthor(const std::string& author){
		this->mResourceInfo.setAuthor(author);
	}

	void Resource::setDescription(const std::string& description){
		this->mResourceInfo.setDescription(description);
	}

	void Resource::setAuthorEmail(const std::string& authorEmail){
		this->mResourceInfo.setAuthorEmail(authorEmail);
	}

	void Resource::setRequiredVersion(const unsigned short& major, const unsigned short& minor, const unsigned short& patch){
		this->mResourceInfo.setRequiredVersion(VersionInfo(major, minor, patch));
	}

	void Resource::setRequiredVersion(const VersionInfo& version){
		this->mResourceInfo.setRequiredVersion(version);
	}

	void Resource::setProperty(const std::string& propertyName, const std::string& propertyValue){
		this->mResourceInfo.setProperty(propertyName, propertyValue);
	}

}



