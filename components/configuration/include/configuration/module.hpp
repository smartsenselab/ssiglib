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

//#ifndef _SSF_API_MODULE_HPP_
//#define _SSF_API_MODULE_HPP_
//
//#include <string>
//#include <core/parameters.hpp>
//
//#include "configuration/configuration_defs.hpp"
//
//namespace ssf{
//
//    class Module{
//        
//	public:
//        CONFIG_EXPORT Module();
//		CONFIG_EXPORT Module(const std::string& moduleName, const std::string& moduleType);
//		CONFIG_EXPORT virtual ~Module(void);
//		CONFIG_EXPORT Module(const Module& rhs);
//		CONFIG_EXPORT Module& operator=(const Module& rhs);
//        
//        CONFIG_EXPORT std::string getName();
//        
//        CONFIG_EXPORT std::string getType();
//        
//        CONFIG_EXPORT size_t getID();
//        
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const int& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const long& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const long long& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const unsigned int& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const unsigned long& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const float& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const double& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const bool& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const char* value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const std::string& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const FileHandle& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const DirectoryHandle& value);
//
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const int& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const long& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const long long& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const unsigned int& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const unsigned long& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const float& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const double& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const bool& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const char* value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const std::string& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const FileHandle& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const DirectoryHandle& value);
//
//	private:
//		template<class T>
//		void genericAddParameter(const std::string& parameterName, const T& value){
//			Parameter param(parameterName, "");
//			param.setValue(value);
//			this->mParameters.addParameter(param);
//		}
//
//		template<class T>
//		void genericSetParameterValue(const std::string& parameterName, const T& value){
//			this->mParameters[parameterName].setValue(value);
//		}
//
//        std::string mModuleName;
//        std::string mModuleType;
//        Parameters mParameters;
//        size_t mID;
//        static size_t count;
//        
//	};
//
//}
//
//#endif // !_SSF_API_MODULE_HPP_PP_