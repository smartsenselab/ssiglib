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

#ifndef _SSF_CORE_PARAMETER_LIST_HPP_
#define _SSF_CORE_PARAMETER_LIST_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "core/parameter.hpp"
#include "core/file_handle.hpp"

#include "parameters_setup.hpp"
#include "parameter_info.hpp"

namespace ssf{

	class Parameters{

	public:
		CORE_EXPORT Parameters(void);
		CORE_EXPORT virtual ~Parameters(void);
		CORE_EXPORT Parameters(const Parameters& rhs);
		CORE_EXPORT Parameters& operator=(const Parameters& rhs);

		CORE_EXPORT Parameter& operator[](const std::string& parameterName);
		CORE_EXPORT Parameter& getParameter(const std::string& parameterName);
		
		CORE_EXPORT void addParameter(const std::string& paramName, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const int& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const double& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const bool& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const char* defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const std::string& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const FileHandle& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const DirectoryHandle& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const std::vector<int>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const std::vector<double>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const std::vector<std::string>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const Parameter& parameter);

		CORE_EXPORT void setup(const std::string& paramFile, const std::string& nodeID);
		CORE_EXPORT void setup(const FileHandle& paramFile, const std::string& nodeID);
		CORE_EXPORT void setup(const ParametersSetup& paramSetup);

		CORE_EXPORT bool has(const std::string& paramName);
		CORE_EXPORT std::map<std::string, ParameterInfo> getParametersInfo();

	private:
		std::map<std::string, Parameter> mParameters;
	
	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_PP_