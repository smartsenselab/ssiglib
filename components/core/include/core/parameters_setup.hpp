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

#ifndef _SSF_CORE_PARAMETER_SETUP_HPP_
#define _SSF_CORE_PARAMETER_SETUP_HPP_

#include <map>
#include <string>
#include <vector>

#include "core/core_defs.hpp"
#include "core/directory_handle.hpp"
#include "core/param_exception.hpp"

namespace cv{
	class FileNode;
}

namespace ssf{

	class ParametersSetup{
		friend class TestParametersSetup;

	public:
		CORE_EXPORT ParametersSetup(const std::string& ID = "");
		CORE_EXPORT ParametersSetup(const std::string& paramFile, const std::string& nodeID);
		CORE_EXPORT ParametersSetup(const FileHandle& paramFile, const std::string& nodeID);
		CORE_EXPORT virtual ~ParametersSetup(void);
		CORE_EXPORT ParametersSetup(const ParametersSetup& rhs);
		CORE_EXPORT ParametersSetup& operator=(const ParametersSetup& rhs);

		CORE_EXPORT void addParameter(const std::string& name, const int& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const double& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const bool& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const char* defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const std::string& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const FileHandle& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const DirectoryHandle& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const std::vector<int>& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const std::vector<double>& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const std::vector<std::string>& defaultValue);

		CORE_EXPORT void setValue(const std::string& name, const int& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const double& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const bool& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const char* defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const std::string& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const FileHandle& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const DirectoryHandle& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const std::vector<int>& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const std::vector<double>& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const std::vector<std::string>& defaultValue);

		CORE_EXPORT std::string getID() const;
		CORE_EXPORT void setID(const std::string& setupID);

		CORE_EXPORT const std::map<std::string, std::vector<std::string>>& getParametersValues() const;

	protected:
		template<class T>
		CORE_EXPORT void _addParameter(const std::string& name, const T& value){
			if (this->mParametersValues.find(name) != this->mParametersValues.end())
				throw ParamException(name, "Already exists a parameter with it name.");
			this->mParametersValues[name] = std::vector<std::string>(1);
			this->setValue(name, value);
		}

		CORE_EXPORT void _setParameter(const std::string& name, const std::vector<std::string>& value);

		CORE_EXPORT void _readParamsFromFile(const std::string& fileName, const std::string& node = "");
		CORE_EXPORT void _converNodeToValue(const cv::FileNode& fileNode);

	private:
		std::map<std::string, std::vector<std::string>> mParametersValues;
		std::string mID;
	};

}

#endif // !_SSF_CORE_PARAMETER_SETUP_HPP_PP_