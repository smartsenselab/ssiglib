#include "core/params.hpp"

namespace ssf{

	Params::Params(){
		
	}

	Params::~Params(){

	}

	Params::Params(const Params& rhs){
		this->mParameters = rhs.mParameters;
	}

	Params& Params::operator=(const Params& rhs){
		if (this != &rhs){
			this->mParameters = rhs.mParameters;
		}
		return *this;
	}

	void Params::addParameter(const ParamType& type, const std::string& paramName, const std::string& paramDescription){

		if (this->mParameters.find(paramName) != this->mParameters.end()){
			throw ParamException(paramName, "Parameter name already used. Please, try other name.");
		}

		/*std::shared_ptr<IParamValue> iparameter;
		switch (type){
		case ParamType::INT: iparameter = std::make_shared< ParamValue<int> >(type, paramName, paramDescription); break;
		case ParamType::LONG: iparameter = std::make_shared< ParamValue<long> >(type, paramName, paramDescription); break;
		case ParamType::FLOAT: iparameter = std::make_shared< ParamValue<float> >(type, paramName, paramDescription); break;
		case ParamType::DOUBLE: iparameter = std::make_shared< ParamValue<double> >(type, paramName, paramDescription); break;
		case ParamType::BOOL: iparameter = std::make_shared< ParamValue<bool> >(type, paramName, paramDescription); break;
		case ParamType::STRING: iparameter = std::make_shared< ParamValue<std::string> >(type, paramName, paramDescription); break;
		case ParamType::FILE_HANDLE: iparameter = std::make_shared< ParamValue<FileHandle> >(type, paramName, paramDescription); break;
		case ParamType::DIRECTORY_HANDLE: iparameter = std::make_shared< ParamValue<DirectoryHandle> >(type, paramName, paramDescription); break;
		}*/
		
		this->mParameters[paramName] = std::make_shared<Param>(type, paramName, paramDescription);

	}

	ssf::ParamType Params::getType(const std::string& paramName){
		return this->getParamByName(paramName)->getType();
	}

	std::string Params::getName(const std::string& paramName){
		return this->getParamByName(paramName)->getName();
	}

	std::string Params::getDescription(const std::string& paramName){
		return this->getParamByName(paramName)->getDescription();
	}

	bool Params::isNumeric(const std::string& paramName){
		if (this->isIntegral(paramName) || this->isFloating(paramName))
			return true;
		return false;
	}

	bool Params::isIntegral(const std::string& paramName){
		if (this->getParamByName(paramName)->getType() == ParamType::INT)
			return true;
		if (this->getParamByName(paramName)->getType() == ParamType::LONG)
			return true;
		return false;
	}

	bool Params::isFloating(const std::string& paramName){
		if (this->getParamByName(paramName)->getType() == ParamType::FLOAT)
			return true;
		if (this->getParamByName(paramName)->getType() == ParamType::DOUBLE)
			return true;
		return false;
	}

	bool Params::isBoolean(const std::string& paramName){
		return (this->getParamByName(paramName)->getType() == ParamType::BOOL);
	}

	bool Params::isString(const std::string& paramName){
		return (this->getParamByName(paramName)->getType() == ParamType::STRING);
	}

	void Params::setRequired(const std::string& paramName, const bool& required /*= true*/){
		this->getParamByName(paramName)->setRequired(required);
	}

	bool Params::isRequired(const std::string& paramName){
		return this->getParamByName(paramName)->isRequired();
	}
	

	std::shared_ptr<Param> Params::getParamByName(const std::string& paramName){
		if (this->mParameters.find(paramName) == this->mParameters.end())
			throw ParamException(paramName, "There is no parameter with such name.");
		return this->mParameters[paramName];
	}

}

