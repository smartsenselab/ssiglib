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

//#include "configuration/configuration.hpp"
//
//namespace ssf{
//
//	Configuration::Configuration(){
//	}
//
//	Configuration::~Configuration(){
//	}
//
//	Configuration::Configuration(const Configuration& rhs){
//        this->mModules = rhs.mModules;
//        this->mStreams = rhs.mStreams;
//	}
//
//	Configuration& Configuration::operator=(const Configuration& rhs){
//		if (this != &rhs){
//            this->mModules = rhs.mModules;
//            this->mStreams = rhs.mStreams;
//		}
//	    return *this;
//	}
//    
//    void Configuration::addModule(const std::string& moduleName, const std::string& moduleType){
//        if(mModules.find(moduleName) != mModules.end()){
//            throw ConfigurationException(moduleName, "Module already added, try another name.");
//        }
//        mModules.insert(std::pair<std::string, Module> (moduleName, Module(moduleName, moduleType)));
//    }
//    
//	Module& Configuration::getModule(const std::string& moduleName){
//		if (mModules.find(moduleName) == mModules.end()){
//			throw ConfigurationException(moduleName, "Module does not exist.");
//		}
//		return this->mModules[moduleName];
//	}
//
//	void Configuration::setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput){
//        
//        for(std::vector<Stream>::iterator it = mStreams.begin(); it != mStreams.end(); ++it){
//            if (it->getModuleIDProvider() == moduleProvider && it->getOutputProvider() == providerOutput && it->getModuleIDReceiver() == moduleReceiver && it->getInputReceiver() == receiverInput){
//                throw ConfigurationException(moduleProvider, "Stream already set.");
//            }
//        }        
//        mStreams.push_back(Stream(moduleProvider, providerOutput,  moduleReceiver, receiverInput));
//    }
//}
