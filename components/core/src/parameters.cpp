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

