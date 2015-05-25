#include "core/parameter_info.hpp"

namespace ssf{

	ParameterInfo::ParameterInfo(){
		
	}

	ParameterInfo::ParameterInfo(const Parameter& parameter)
		: mParameter(parameter){

	}

	ParameterInfo::~ParameterInfo(){
		//Destructor
	}

	ParameterInfo::ParameterInfo(const ParameterInfo& rhs){
		this->mParameter = rhs.mParameter;
	}

	ParameterInfo& ParameterInfo::operator=(const ParameterInfo& rhs){
		if (this != &rhs){
			this->mParameter = rhs.mParameter;
		}
	    return *this;
	}

	std::string ParameterInfo::getName() const{
		return this->mParameter.getName();
	}

	std::string ParameterInfo::getDescription() const{
		return this->mParameter.getDescription();
	}

	ParamType ParameterInfo::getExpectedType() const{
		return this->mParameter.getExpectedType();
	}

	bool ParameterInfo::isRequired() const{
		return this->mParameter.isRequired();
	}

	std::string ParameterInfo::getDefaultValue() const{
		std::string strRet = this->mParameter.mDefaultValue[0];
		for (size_t i = 1; i < this->mParameter.mDefaultValue.size(); i++)
			strRet += ", " + this->mParameter.mDefaultValue[i];
		return strRet;
	}

	std::string ParameterInfo::getValue() const{
		std::string strRet = this->mParameter.mValue[0];
		for (size_t i = 1; i < this->mParameter.mValue.size(); i++)
			strRet += ", " + this->mParameter.mValue[i];
		return strRet;
	}

	std::vector<std::string> ParameterInfo::getDefaultVectorValue() const{
		return this->mParameter.mDefaultValue;
	}

	std::vector<std::string> ParameterInfo::getVectorValue() const{
		return this->mParameter.mValue;
	}

}

