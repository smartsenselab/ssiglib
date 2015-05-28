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

//#ifndef _SSF_API_SSF_CONFIGURATION_HPP_
//#define _SSF_API_SSF_CONFIGURATION_HPP_
//
//#include <string>
//#include <vector>
//#include <tuple>
//#include <map>
//#include <core/parameters.hpp>
//
//#include "configuration/stream.hpp"
//#include "configuration/module.hpp"
//#include "configuration/configuration_exception.hpp"
//
//namespace ssf{
//    
//    class Configuration{
//	
//	public:
//		CONFIG_EXPORT Configuration(void);
//		CONFIG_EXPORT virtual ~Configuration(void);
//		CONFIG_EXPORT Configuration(const Configuration& rhs);
//		CONFIG_EXPORT Configuration& operator=(const Configuration& rhs);
//        
//		CONFIG_EXPORT void addModule(const std::string& moduleName, const std::string& moduleType);
//		CONFIG_EXPORT Module& getModule(const std::string& moduleName);
//        
//
//		//COMENTAR O PROBLEMA DE ATRIBUTO DESNECESSARIO COM O ROMULO
//        /*template<class T>
//		CONFIG_EXPORT void setParameter(const std::string& moduleType, const std::string& moduleName, const std::string& paramName, ParamType type, T value){
//            if(modules.find(moduleName) == modules.end()){
//                throw ConfigurationException(moduleName, "Module does not exist, create it first before adding parameters to it.");
//            }
//            modules[moduleName].addParameter(type, paramName, "");
//            modules[moduleName].setValue(paramName, value);
//        };*/
//        
//        
//		CONFIG_EXPORT void setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput);
//
//	private:
//        
//        std::map<std::string, Module> mModules;
//        
//        std::vector<Stream>  mStreams;
//        
//	};
//}
//
//#endif // !_SSF_API_SSF_CONFIGURATION_HPP_PP_