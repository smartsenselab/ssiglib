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
	
	long Parameters::getMaxValue(const std::string& paramName){
		return this->getParamByName(paramName).getMaxValue();
	}

	void Parameters::setMaxValue(const std::string& paramName, const long& maxValue){
		return this->getParamByName(paramName).setMaxValue(maxValue);
	}

	long Parameters::getMinValue(const std::string& paramName){
		return this->getParamByName(paramName).getMinValue();
	}

	void Parameters::setMinValue(const std::string& paramName, const long& minValue){
		return this->getParamByName(paramName).setMinValue(minValue);
	}

	const std::map<std::string, Parameter>& Parameters::getParameters() const{
		return this->mParameters;
	}

	void Parameters::setup(std::map<std::string, Parameter>& paramsSetup){
		for (auto parameter : this->getParameters()){
			auto setup = paramsSetup.find(parameter.second.getName());
			if (setup != paramsSetup.end() && parameter.second.isRequired()){
				throw ParamException(parameter.second.getName(), "This parameter requires a value.");
			}
			if (parameter.second.getType() != setup->second.getType()){
				std::string message = "Parameter setup type mismatch. Correct type is " + parameter.second.getTypeStr() + ".";
				throw ParamException(parameter.second.getName(), message);
			}

			switch (parameter.second.getType()){
			case ParamType::INT:
				this->getParamByName(parameter.second.getName()).setValue((setup->second).getValue<int>());
				break;
			case ParamType::LONG:
				this->getParamByName(parameter.second.getName()).setValue((setup->second).getValue<long>());
				break;
			case ParamType::FLOAT:
				this->getParamByName(parameter.second.getName()).setValue((setup->second).getValue<float>());
				break;
			case ParamType::DOUBLE:
				this->getParamByName(parameter.second.getName()).setValue((setup->second).getValue<double>());
				break;
			case ParamType::BOOL:
				this->getParamByName(parameter.second.getName()).setValue((setup->second).getValue<bool>());
				break;
			case ParamType::STRING:
				this->getParamByName(parameter.second.getName()).setValue((setup->second).getValue<std::string>());
				break;
			case ParamType::FILE_HANDLE:
				this->getParamByName(parameter.second.getName()).setValue((setup->second).getValue<FileHandle>());
				break;
			case ParamType::DIRECTORY_HANDLE:
				this->getParamByName(parameter.second.getName()).setValue((setup->second).getValue<DirectoryHandle>());
				break;
			}
			
		}
	}

	Parameter& Parameters::getParamByName(const std::string& paramName){
		if (this->mParameters.find(paramName) == this->mParameters.end())
			throw ParamException(paramName, "There is no parameter with such name.");
		return this->mParameters[paramName];
	}

}

