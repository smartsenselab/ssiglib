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

	void Parameters::addParameter(const ParameterType& type, const std::string& paramName, const std::string& paramDescription){

		if (this->mParameters.find(paramName) != this->mParameters.end()){
			throw ParameterException(paramName, "Parameter name already used. Please, try other name.");
		}

		std::shared_ptr<IParameterValue> iparameter;
		switch (type){
		case ParameterType::INT: iparameter = std::make_shared< ParameterValue<int> >(type, paramName, paramDescription); break;
		case ParameterType::LONG: iparameter = std::make_shared< ParameterValue<long> >(type, paramName, paramDescription); break;
		case ParameterType::FLOAT: iparameter = std::make_shared< ParameterValue<float> >(type, paramName, paramDescription); break;
		case ParameterType::DOUBLE: iparameter = std::make_shared< ParameterValue<double> >(type, paramName, paramDescription); break;
		case ParameterType::BOOL: iparameter = std::make_shared< ParameterValue<bool> >(type, paramName, paramDescription); break;
		case ParameterType::STRING: iparameter = std::make_shared< ParameterValue<std::string> >(type, paramName, paramDescription); break;
		case ParameterType::FILE_HANDLE: iparameter = std::make_shared< ParameterValue<FileHandle> >(type, paramName, paramDescription); break;
		case ParameterType::DIRECTORY_HANDLE: iparameter = std::make_shared< ParameterValue<DirectoryHandle> >(type, paramName, paramDescription); break;
		}
		
		this->mParameters[paramName] = iparameter;

	}

	ssf::ParameterType Parameters::getType(const std::string& paramName){
		return this->getParamValue(paramName)->getType();
	}

	std::string Parameters::getName(const std::string& paramName){
		return this->getParamValue(paramName)->getName();
	}

	std::string Parameters::getDescription(const std::string& paramName){
		return this->getParamValue(paramName)->getDescription();
	}

	bool Parameters::isNumeric(const std::string& paramName){
		if (this->isIntegral(paramName) || this->isFloating(paramName))
			return true;
		return false;
	}

	bool Parameters::isIntegral(const std::string& paramName){
		if (this->getParamValue(paramName)->getType() == ParameterType::INT)
			return true;
		if (this->getParamValue(paramName)->getType() == ParameterType::LONG)
			return true;
		return false;
	}

	bool Parameters::isFloating(const std::string& paramName){
		if (this->getParamValue(paramName)->getType() == ParameterType::FLOAT)
			return true;
		if (this->getParamValue(paramName)->getType() == ParameterType::DOUBLE)
			return true;
		return false;
	}

	bool Parameters::isBoolean(const std::string& paramName){
		return (this->getParamValue(paramName)->getType() == ParameterType::BOOL);
	}

	bool Parameters::isString(const std::string& paramName){
		return (this->getParamValue(paramName)->getType() == ParameterType::STRING);
	}

	void Parameters::setRequired(const std::string& paramName, const bool& required /*= true*/){
		this->getParamValue(paramName)->setRequired(required);
	}

	bool Parameters::isRequired(const std::string& paramName){
		return this->getParamValue(paramName)->isRequired();
	}
	

	std::shared_ptr<IParameterValue> Parameters::getParamValue(const std::string& paramName){
		if (this->mParameters.find(paramName) == this->mParameters.end())
			throw ParameterException(paramName, "There is no parameter with such name.");
		return this->mParameters[paramName];
	}

}

