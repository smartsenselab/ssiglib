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

#include "core/resource_info.hpp"

#include "core/exception.hpp"

namespace ssf{

	ResourceInfo::ResourceInfo(){
		this->mAuthor = "Unknown Author";
		this->mDescription = "Description not available";
		this->mAuthorEmail = "Unknown Author Email";
	}

	ResourceInfo::~ResourceInfo(){
		//Destructor
	}

	ResourceInfo::ResourceInfo(const ResourceInfo& rhs){
		this->mAuthor = rhs.mAuthor;
		this->mDescription = rhs.mDescription;
		this->mAuthorEmail = rhs.mAuthorEmail;
		this->mRequiredVersion = rhs.mRequiredVersion;
		this->mProperties = rhs.mProperties;
		this->mParametersInfo = rhs.mParametersInfo;
	}

	ResourceInfo& ResourceInfo::operator=(const ResourceInfo& rhs){
		if (this != &rhs){
			this->mAuthor = rhs.mAuthor;
			this->mDescription = rhs.mDescription;
			this->mAuthorEmail = rhs.mAuthorEmail;
			this->mRequiredVersion = rhs.mRequiredVersion;
			this->mProperties = rhs.mProperties;
			this->mParametersInfo = rhs.mParametersInfo;
		}
		return *this;
	}

	std::string ResourceInfo::getAuthor() const{
		return this->mAuthor;
	}

	std::string ResourceInfo::getDescription() const{
		return this->mDescription;
	}

	std::string ResourceInfo::getAuthorEmail() const{
		return this->mAuthorEmail;
	}

	VersionInfo ResourceInfo::getRequiredVersion() const{
		return this->mRequiredVersion;
	}

	std::string ResourceInfo::getProperty(const std::string& propertyName){
		if (this->mProperties.find(propertyName) == this->mProperties.end()){
			std::string message = "Does not exists a property with name \"" + propertyName + "\".";
			throw Exception(message);
		}
		return this->mProperties[propertyName];
	}

	const std::map<std::string, ParameterInfo>& ResourceInfo::getParametersInfo(){
		return this->mParametersInfo;
	}

	void ResourceInfo::setAuthor(const std::string& author){
		this->mAuthor = author;
	}

	void ResourceInfo::setDescription(const std::string& description){
		this->mDescription = description;
	}

	void ResourceInfo::setAuthorEmail(const std::string& email){
		this->mAuthorEmail = email;
	}

	void ResourceInfo::setRequiredVersion(const VersionInfo& version){
		this->mRequiredVersion = version;
	}

	void ResourceInfo::setProperty(const std::string& propertyName, const std::string& propertyValue){
		this->mProperties[propertyName] = propertyValue;
	}

}



