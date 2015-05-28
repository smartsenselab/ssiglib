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

#include "core/parameters.hpp"


#include <iostream>

#include <core/param_exception.hpp>


namespace ssf{

	Parameters::Parameters(){

	}

	Parameters::Parameters(const Parameters& rhs){
		this->mParameters = rhs.mParameters;
	}

	Parameters& Parameters::operator=(const Parameters& rhs){
		if (this != &rhs){
			this->mParameters = rhs.mParameters;
		}
		return *this;
	}

	Parameters::~Parameters(){

	}

	Parameter& Parameters::operator[](const std::string& parameterName){
		return this->getParameter(parameterName);
	}

	Parameter& Parameters::getParameter(const std::string& parameterName){
		if (this->mParameters.find(parameterName) == this->mParameters.end()){
			throw ParamException(parameterName, "Parameter does not exists.");
		}
		return this->mParameters[parameterName];
	}

	void Parameters::addParameter(const std::string& paramName, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, "", description));
		this->getParameter(paramName).setRequired(true);
	}

	void Parameters::addParameter(const std::string& paramName, const int& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const double& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const bool& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const char* defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const std::string& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const FileHandle& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const DirectoryHandle& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const std::vector<int>& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const std::vector<double>& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const std::string& paramName, const std::vector<std::string>& defaultValue, const std::string& description /*= "no description."*/){
		this->addParameter(Parameter(paramName, defaultValue, description));
	}

	void Parameters::addParameter(const Parameter& parameter){
		if (this->mParameters.find(parameter.getName()) != this->mParameters.end()){
			throw ParamException(parameter.getName(), "Parameter name already used. Please, try other name.");
		}
		this->mParameters[parameter.getName()] = parameter;
	}


	void Parameters::setup(const std::string& paramFile, const std::string& nodeID){
		this->setup(ParametersSetup(paramFile, nodeID));
	}

	void Parameters::setup(const FileHandle& paramFile, const std::string& nodeID){
		this->setup(ParametersSetup(paramFile, nodeID));
	}

	void Parameters::setup(const ParametersSetup& paramSetup){
		std::map<std::string, std::vector<std::string>> values = paramSetup.getParametersValues();
		for (auto parameter : this->mParameters){
			std::string paramName = parameter.first;
			if (values.find(paramName) == values.end()){
				if (parameter.second.isRequired()){
					throw ParamException(paramName, "Required parameter value.");
				}
				else{
					continue;
				}
			}
			std::vector<std::string> setupValue = values[paramName];
			ParamType requiredType = parameter.second.getExpectedType();
			switch (requiredType){
			case ParamType::INT:
				if (!Parameter::isInt(setupValue[0]))
					throw ParamException(paramName, "This parameter requires a int value.");
				break;
			case ParamType::DOUBLE:
				if (!Parameter::isDouble(setupValue[0]))
					throw ParamException(paramName, "This parameter requires a double value.");
				break;
			case ParamType::INT_VECTOR:
				if (!Parameter::isIntVector(setupValue))
					throw ParamException(paramName, "This parameter requires a vector of int value.");
				break;
			case ParamType::DOUBLE_VECTOR:
				if (!Parameter::isDoubleVector(setupValue))
					throw ParamException(paramName, "This parameter requires a vector of double value.");
				break;
			default:
				break;
			}
			this->mParameters[paramName].mValue = setupValue;
		}
	}


	bool Parameters::has(const std::string& paramName){
		return (this->mParameters.find(paramName) != this->mParameters.end());
	}

	std::map<std::string, ParameterInfo> Parameters::getParametersInfo(){
		std::map<std::string, ParameterInfo> returnMap;
		for (auto parameter : this->mParameters)
			returnMap[parameter.first] = ParameterInfo(parameter.second);
		return returnMap;
	}

}



