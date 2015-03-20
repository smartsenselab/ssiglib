#include "core/parameter_info.hpp"

namespace ssf{

	ParameterInfo::ParameterInfo(){

	}

	ParameterInfo::~ParameterInfo(){

	}

	ParameterInfo::ParameterInfo(const ParameterInfo& rhs){
		this->mName = rhs.mName;
		this->mDescription = rhs.mDescription;
		this->mRequired = rhs.mRequired;
		this->mParameterType = rhs.mParameterType;

		this->intDefaultValue = rhs.intDefaultValue;
		this->longDefaultValue = rhs.longDefaultValue;
		this->floatDefaultValue = rhs.floatDefaultValue;
		this->doubleDefaultValue = rhs.doubleDefaultValue;
		this->boolDefaultValue = rhs.boolDefaultValue;
		this->stringDefaultValue = rhs.stringDefaultValue;
		this->fileHandleDefaultValue = rhs.fileHandleDefaultValue;
		this->directoryHandleDefaultValue = rhs.directoryHandleDefaultValue;
	}

	ParameterInfo& ParameterInfo::operator=(const ParameterInfo& rhs){
		if (this != &rhs){
			this->mName = rhs.mName;
			this->mDescription = rhs.mDescription;
			this->mRequired = rhs.mRequired;
			this->mParameterType = rhs.mParameterType;
			
			this->intDefaultValue = rhs.intDefaultValue;
			this->longDefaultValue = rhs.longDefaultValue;
			this->floatDefaultValue = rhs.floatDefaultValue;
			this->doubleDefaultValue = rhs.doubleDefaultValue;
			this->boolDefaultValue = rhs.boolDefaultValue;
			this->stringDefaultValue = rhs.stringDefaultValue;
			this->fileHandleDefaultValue = rhs.fileHandleDefaultValue;
			this->directoryHandleDefaultValue = rhs.directoryHandleDefaultValue;
		}
		return *this;
	}

	std::string ParameterInfo::getName() const{
		return this->mName;
	}

	std::string ParameterInfo::getDescription() const{
		return this->mDescription;
	}

	bool ParameterInfo::getRequired() const{
		return this->mRequired;
	}

	ParameterType ParameterInfo::getParameterType() const{
		return this->mParameterType;
	}

}

