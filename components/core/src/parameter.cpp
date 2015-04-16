#include "core/parameter.hpp"

namespace ssf{

	Parameter::Parameter(){
		this->mValue = nullptr;
		this->mDefaultValue = nullptr;
	}

	Parameter::Parameter(const ParamType& parameterType, const std::string& name, const std::string& description){
		this->mValue = nullptr;
		this->mDefaultValue = nullptr;
		this->mType = parameterType;
		this->mName = name;
		this->mDescription = description;
		this->mRequired = false;

		switch (parameterType){
		case ParamType::INT:
			this->mValue = new int(0);
			this->mDefaultValue = new int(0);
			this->maxValue = std::numeric_limits<int>::max();
			this->minValue = std::numeric_limits<int>::min();
			break;
		case ParamType::LONG:
			this->mValue = new long(0);
			this->mDefaultValue = new long(0);
			this->maxValue = std::numeric_limits<long>::max();
			this->minValue = std::numeric_limits<long>::min();
			break;
		case ParamType::FLOAT:
			this->mValue = new float(0.0);
			this->mDefaultValue = new float(0.0);
			this->maxValue = static_cast<long>(std::numeric_limits<float>::max());
			this->minValue = static_cast<long>(std::numeric_limits<float>::min());
			break;
		case ParamType::DOUBLE:
			this->mValue = new double(0.0);
			this->mDefaultValue = new double(0.0);
			this->maxValue = static_cast<long>(std::numeric_limits<double>::max());
			this->minValue = static_cast<long>(std::numeric_limits<double>::min());
			break;
		case ParamType::BOOL:
			this->mValue = new bool(false);
			this->mDefaultValue = new bool(false);
			break;
		case ParamType::STRING:
			this->mValue = new std::string("");
			this->mDefaultValue = new std::string("");
			break;
		case ParamType::FILE_HANDLE:
			this->mValue = new FileHandle();
			this->mDefaultValue = new FileHandle();
			break;
		case ParamType::DIRECTORY_HANDLE:
			this->mValue = new DirectoryHandle();
			this->mDefaultValue = new DirectoryHandle();
			break;
		}

	}

	Parameter::~Parameter(){
		if (this->mValue != nullptr){
			this->eraseValues();
		}
		this->mValue = nullptr;
	}

	Parameter::Parameter(const Parameter& rhs){
		this->mValue = nullptr;
		this->copy(rhs);
	}

	Parameter& Parameter::operator=(const Parameter& rhs){
		if (this != &rhs){
			this->copy(rhs);
		}
		return *this;
	}

	ParamType Parameter::getType() const{
		return this->mType;
	}

	std::string Parameter::getName() const{
		return this->mName;
	}

	std::string Parameter::getDescription() const{
		return this->mDescription;
	}

	bool Parameter::isRequired() const{
		return this->mRequired;
	}

	void Parameter::setRequired(const bool& required /*= true*/){
		this->mRequired = required;
	}

	long Parameter::getMaxValue() const{
		return this->maxValue;
	}

	void Parameter::setMaxValue(const long& maxValue){
		this->maxValue = maxValue;
	}

	long Parameter::getMinValue() const{
		return this->minValue;
	}

	void Parameter::setMinValue(const long& minValue){
		this->minValue = minValue;
	}

	std::string Parameter::getTypeStr() const{
		switch (this->mType)
		{
		case ParamType::INT: return "INT";
		case ParamType::LONG: return "LONG";
		case ParamType::FLOAT: return "FLOAT";
		case ParamType::DOUBLE: return "DOUBLE";
		case ParamType::BOOL: return "BOOL";
		case ParamType::STRING: return "STRING";
		case ParamType::FILE_HANDLE: return "FILE_HANDLE";
		case ParamType::DIRECTORY_HANDLE: return "DIRECTORY_HANDLE";
		default: return "UNKNOW TYPE";
		}

	}

	void Parameter::copy(const Parameter& rhs){

		this->mType = rhs.mType;
		this->mName = rhs.mName;
		this->mDescription = rhs.mDescription;
		this->mRequired = rhs.mRequired;

		if (this->mValue != nullptr && this->mDefaultValue != nullptr){
			this->eraseValues();
			this->mValue = nullptr;
		}

		if (rhs.mValue == nullptr && rhs.mDefaultValue != nullptr)
			return;

		switch (rhs.mType){
		case ParamType::INT: 
			this->mValue = new int(*((int*)rhs.mValue)); 
			this->mDefaultValue = new int(*((int*)rhs.mDefaultValue));
			break;
		case ParamType::LONG: 
			this->mValue = new long(*((long*)rhs.mValue));
			this->mDefaultValue = new long(*((long*)rhs.mDefaultValue));
			break;
		case ParamType::FLOAT: 
			this->mValue = new float(*((float*)rhs.mValue));
			this->mDefaultValue = new float(*((float*)rhs.mDefaultValue));
			break;
		case ParamType::DOUBLE: 
			this->mValue = new double(*((double*)rhs.mValue)); 
			this->mDefaultValue = new double(*((double*)rhs.mDefaultValue));
			break;
		case ParamType::BOOL: 
			this->mValue = new bool(*((bool*)rhs.mValue));
			this->mDefaultValue = new bool(*((bool*)rhs.mDefaultValue));
			break;
		case ParamType::STRING: 
			this->mValue = new std::string(*((std::string*)rhs.mValue));
			this->mDefaultValue = new std::string(*((std::string*)rhs.mDefaultValue));
			break;
		case ParamType::FILE_HANDLE: 
			this->mValue = new FileHandle(*((FileHandle*)rhs.mValue));
			this->mDefaultValue = new FileHandle(*((FileHandle*)rhs.mDefaultValue));
			break;
		case ParamType::DIRECTORY_HANDLE: 
			this->mValue = new DirectoryHandle(*((DirectoryHandle*)rhs.mValue)); 
			this->mDefaultValue = new DirectoryHandle(*((DirectoryHandle*)rhs.mDefaultValue));
			break;
		}

	}

	void Parameter::eraseValues(){
		switch (this->mType){
		case ParamType::INT:
			delete ((int*)this->mValue);
			delete ((int*)this->mDefaultValue);
			break;
		case ParamType::LONG:
			delete ((long*)this->mValue);
			delete ((long*)this->mDefaultValue);
			break;
		case ParamType::FLOAT:
			delete ((float*)this->mValue);
			delete ((float*)this->mDefaultValue);
			break;
		case ParamType::DOUBLE:
			delete ((double*)this->mValue);
			delete ((double*)this->mDefaultValue);
			break;
		case ParamType::BOOL:
			delete ((bool*)this->mValue);
			delete ((bool*)this->mDefaultValue);
			break;
		case ParamType::STRING:
			delete ((std::string*)this->mValue);
			delete ((std::string*)this->mDefaultValue);
			break;
		case ParamType::FILE_HANDLE:
			delete ((FileHandle*)this->mValue);
			delete ((FileHandle*)this->mDefaultValue);
			break;
		case ParamType::DIRECTORY_HANDLE: delete ((DirectoryHandle*)this->mValue); break;
		}
	}

}

