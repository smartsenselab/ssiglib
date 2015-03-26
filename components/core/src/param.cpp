#include "core/param.hpp"

namespace ssf{

	Param::Param(){
		this->mValue = nullptr;
	}

	Param::Param(const ParamType& parameterType, const std::string& name, const std::string& description){
		this->mType = parameterType;
		this->mName = name;
		this->mDescription = description;
		this->mRequired = false;

		switch (parameterType){
		case ParamType::INT: mValue = new int(); break;
		case ParamType::LONG: mValue = new long(); break;
		case ParamType::FLOAT: mValue = new float(); break;
		case ParamType::DOUBLE: mValue = new double(); break;
		case ParamType::BOOL: mValue = new bool(); break;
		case ParamType::STRING: mValue = new std::string(); break;
		case ParamType::FILE_HANDLE: mValue = new FileHandle(); break;
		case ParamType::DIRECTORY_HANDLE: mValue = new DirectoryHandle(); break;
		}

	}

	Param::~Param(){
		if (this->mValue != nullptr)
			delete this->mValue;
	}

	Param::Param(const Param& rhs){
		this->copy(rhs);
	}

	Param& Param::operator=(const Param& rhs){
		if (this != &rhs){
			this->copy(rhs);
		}
	    return *this;
	}

	ParamType Param::getType() const{
		return this->mType;
	}

	std::string Param::getName() const{
		return this->mName;
	}

	std::string Param::getDescription() const{
		return this->mDescription;
	}

	bool Param::isRequired() const{
		return this->mRequired;
	}

	void Param::setRequired(const bool& required /*= true*/){
		this->mRequired = required;
	}

	std::string Param::getTypeStr() const{
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

	void Param::copy(const Param& rhs){

		this->mType = rhs.mType;
		this->mName = rhs.mName;
		this->mDescription = rhs.mDescription;
		this->mRequired = rhs.mRequired;

		if (this->mValue != nullptr){
			delete this->mValue;
			this->mValue = nullptr;
		}
		
		if (rhs.mValue == nullptr)
			return;

		switch (rhs.mType){
		case ParamType::INT: mValue = new int(*((int*)rhs.mValue)); break;
		case ParamType::LONG: mValue = new long(*((long*)rhs.mValue)); break;
		case ParamType::FLOAT: mValue = new float(*((float*)rhs.mValue)); break;
		case ParamType::DOUBLE: mValue = new double(*((double*)rhs.mValue)); break;
		case ParamType::BOOL: mValue = new bool(*((bool*)rhs.mValue)); break;
		case ParamType::STRING: mValue = new std::string(*((std::string*)rhs.mValue)); break;
		case ParamType::FILE_HANDLE: mValue = new FileHandle(*((FileHandle*)rhs.mValue)); break;
		case ParamType::DIRECTORY_HANDLE: mValue = new DirectoryHandle(*((DirectoryHandle*)rhs.mValue)); break;
		}

	}

}

