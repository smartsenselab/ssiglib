#include "core/parameters.hpp"

namespace ssf{

	Parameters::Parameters(){
		
	}

	Parameters::~Parameters(){

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

	void Parameters::addParameter(const ParamType& type, const std::string& paramName, const std::string& paramDescription){

		if (this->mParameters.find(paramName) != this->mParameters.end()){
			throw ParamException(paramName, "Parameter name already used. Please, try other name.");
		}
		
		this->mParameters[paramName] = Parameter(type, paramName, paramDescription);

	}

	ssf::ParamType Parameters::getType(const std::string& paramName){
		return this->getParamByName(paramName).getType();
	}

	std::string Parameters::getName(const std::string& paramName){
		return this->getParamByName(paramName).getName();
	}

	std::string Parameters::getDescription(const std::string& paramName){
		return this->getParamByName(paramName).getDescription();
	}

	bool Parameters::isNumeric(const std::string& paramName){
		if (this->isIntegral(paramName) || this->isFloating(paramName))
			return true;
		return false;
	}

	bool Parameters::isIntegral(const std::string& paramName){
		if (this->getParamByName(paramName).getType() == ParamType::INT)
			return true;
		if (this->getParamByName(paramName).getType() == ParamType::LONG)
			return true;
		return false;
	}

	bool Parameters::isFloating(const std::string& paramName){
		if (this->getParamByName(paramName).getType() == ParamType::FLOAT)
			return true;
		if (this->getParamByName(paramName).getType() == ParamType::DOUBLE)
			return true;
		return false;
	}

	bool Parameters::isBoolean(const std::string& paramName){
		return (this->getParamByName(paramName).getType() == ParamType::BOOL);
	}

	bool Parameters::isString(const std::string& paramName){
		return (this->getParamByName(paramName).getType() == ParamType::STRING);
	}

	bool Parameters::exists(const std::string& paramName){
		return !(this->mParameters.find(paramName) == this->mParameters.end());
	}

	void Parameters::setRequired(const std::string& paramName, const bool& required /*= true*/){
		this->getParamByName(paramName).setRequired(required);
	}

	bool Parameters::isRequired(const std::string& paramName){
		return this->getParamByName(paramName).isRequired();
	}
	
	const std::map<std::string, Parameter>& Parameters::getParameters() const{
		return this->mParameters;
	}

	void Parameters::setup(const std::map<std::string, Parameter>& paramsSetup){
		for (auto param : this->getParameters()){
			auto paramSetup = paramsSetup.find(param.second.getName());
			if (paramSetup != paramsSetup.end()){

			}
		}
	}

	Parameter& Parameters::getParamByName(const std::string& paramName){
		if (this->mParameters.find(paramName) == this->mParameters.end())
			throw ParamException(paramName, "There is no parameter with such name.");
		return this->mParameters[paramName];
	}

}

