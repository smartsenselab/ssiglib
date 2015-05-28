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

//#include "configuration/module.hpp"
//#include <string>
//#include <core/parameters.hpp>
//
//namespace ssf{
//    
//    size_t Module::count = 0;
//    
//    Module::Module(){
//        
//    }
//
//	Module::Module(const std::string& moduleName, const std::string& moduleType){
//        this->mModuleName = moduleName;
//        this->mModuleType = moduleType;
//        ++count;
//        mID = count;
//	}
//
//	Module::~Module(){
//	}
//
//	Module::Module(const Module& rhs){
//        this->mModuleName = rhs.mModuleName;
//        this->mModuleType = rhs.mModuleType;
//        mID = count;
//    }
//
//	Module& Module::operator=(const Module& rhs){
//		if (this != &rhs){
//            this->mModuleName = rhs.mModuleName;
//            this->mModuleType = rhs.mModuleType;
//            mID = count;
//		}
//	    return *this;
//	}
//    
//    std::string Module::getName(){
//        return this->mModuleName;
//    }
//    
//    std::string Module::getType(){
//        return this->mModuleType;
//    }
//    
//    size_t Module::getID(){
//        return this->mID;
//    }
//    
//	void Module::addParameter(const std::string& parameterName, const int& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const long& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const long long& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const unsigned int& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const unsigned long& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const float& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const double& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const bool& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const char* value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const std::string& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const FileHandle& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const DirectoryHandle& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const int& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const long& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const long long& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const unsigned int& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const unsigned long& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const float& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const double& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const bool& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const char* value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const std::string& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const FileHandle& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const DirectoryHandle& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//}
//
