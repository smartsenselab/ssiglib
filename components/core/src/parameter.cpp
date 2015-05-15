#include "core/parameter.hpp"

#include <sstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>

#include "core/param_exception.hpp"

//#include <limits>
//
//namespace ssf{
//
//	Parameter::Parameter(){
//		this->mValue = nullptr;
//		this->mDefaultValue = nullptr;
//	}
//
//	Parameter::Parameter(const ParamType& parameterType, const std::string& name, const std::string& description){
//		this->mValue = nullptr;
//		this->mDefaultValue = nullptr;
//		this->mType = parameterType;
//		this->mName = name;
//		this->mDescription = description;
//		this->mRequired = false;
//
//		switch (parameterType){
//		case ParamType::INT:
//			this->mValue = new int(0);
//			this->mDefaultValue = new int(0);
//			this->maxValue = std::numeric_limits<int>::max();
//			this->minValue = std::numeric_limits<int>::min();
//			break;
//		case ParamType::LONG:
//			this->mValue = new long(0);
//			this->mDefaultValue = new long(0);
//			this->maxValue = std::numeric_limits<long>::max();
//			this->minValue = std::numeric_limits<long>::min();
//			break;
//		case ParamType::FLOAT:
//			this->mValue = new float(0.0);
//			this->mDefaultValue = new float(0.0);
//			this->maxValue = static_cast<long>(std::numeric_limits<float>::max());
//			this->minValue = static_cast<long>(std::numeric_limits<float>::min());
//			break;
//		case ParamType::DOUBLE:
//			this->mValue = new double(0.0);
//			this->mDefaultValue = new double(0.0);
//			this->maxValue = static_cast<long>(std::numeric_limits<double>::max());
//			this->minValue = static_cast<long>(std::numeric_limits<double>::min());
//			break;
//		case ParamType::BOOL:
//			this->mValue = new bool(false);
//			this->mDefaultValue = new bool(false);
//			break;
//		case ParamType::STRING:
//			this->mValue = new std::string("");
//			this->mDefaultValue = new std::string("");
//			break;
//		case ParamType::FILE_HANDLE:
//			this->mValue = new FileHandle();
//			this->mDefaultValue = new FileHandle();
//			break;
//		case ParamType::DIRECTORY_HANDLE:
//			this->mValue = new DirectoryHandle();
//			this->mDefaultValue = new DirectoryHandle();
//			break;
//		}
//
//	}
//
//	Parameter::~Parameter(){
//		if (this->mValue != nullptr){
//			this->eraseValues();
//		}
//		this->mValue = nullptr;
//	}
//
//	Parameter::Parameter(const Parameter& rhs){
//		this->mValue = nullptr;
//		this->copy(rhs);
//	}
//
//	Parameter& Parameter::operator=(const Parameter& rhs){
//		if (this != &rhs){
//			this->copy(rhs);
//		}
//		return *this;
//	}
//
//	ParamType Parameter::getType() const{
//		return this->mType;
//	}
//
//	std::string Parameter::getName() const{
//		return this->mName;
//	}
//
//	std::string Parameter::getDescription() const{
//		return this->mDescription;
//	}
//
//	bool Parameter::isRequired() const{
//		return this->mRequired;
//	}
//
//	void Parameter::setRequired(const bool& required /*= true*/){
//		this->mRequired = required;
//	}
//
//	long Parameter::getMaxValue() const{
//		return this->maxValue;
//	}
//
//	void Parameter::setMaxValue(const long& maxValue){
//		switch (this->mType){
//		case ParamType::INT:
//			this->maxValue = static_cast<long>((maxValue > std::numeric_limits<int>::max()) ? std::numeric_limits<int>::max():maxValue);
//			break;
//		case ParamType::LONG:
//			this->maxValue = static_cast<long>((maxValue > std::numeric_limits<long>::max()) ? std::numeric_limits<long>::max() : maxValue);
//			break;
//		case ParamType::FLOAT:
//			this->maxValue = static_cast<long>((maxValue > std::numeric_limits<float>::max()) ? std::numeric_limits<float>::max() : maxValue);
//			break;
//		case ParamType::DOUBLE:
//			this->maxValue = static_cast<long>((maxValue > std::numeric_limits<double>::max()) ? std::numeric_limits<double>::max() : maxValue);
//			break;
//		default:
//			break;
//		}
//	}
//
//	long Parameter::getMinValue() const{
//		return this->minValue;
//	}
//
//	void Parameter::setMinValue(const long& minValue){
//		switch (this->mType){
//		case ParamType::INT:
//			this->minValue = static_cast<long>((minValue < std::numeric_limits<int>::min()) ? std::numeric_limits<int>::min() : minValue);
//			break;
//		case ParamType::LONG:
//			this->minValue = static_cast<long>((minValue < std::numeric_limits<long>::min()) ? std::numeric_limits<long>::min() : minValue);
//			break;
//		case ParamType::FLOAT:
//			this->minValue = static_cast<long>((minValue < std::numeric_limits<float>::min()) ? std::numeric_limits<float>::min() : minValue);
//			break;
//		case ParamType::DOUBLE:
//			this->minValue = static_cast<long>((minValue < std::numeric_limits<double>::min()) ? std::numeric_limits<double>::min() : minValue);
//			break;
//		default:
//			break;
//		}
//	}
//
//	std::string Parameter::getTypeStr() const{
//		switch (this->mType)
//		{
//		case ParamType::INT: return "INT";
//		case ParamType::LONG: return "LONG";
//		case ParamType::FLOAT: return "FLOAT";
//		case ParamType::DOUBLE: return "DOUBLE";
//		case ParamType::BOOL: return "BOOL";
//		case ParamType::STRING: return "STRING";
//		case ParamType::FILE_HANDLE: return "FILE_HANDLE";
//		case ParamType::DIRECTORY_HANDLE: return "DIRECTORY_HANDLE";
//		default: return "UNKNOW TYPE";
//		}
//
//	}
//
//	void Parameter::copy(const Parameter& rhs){
//
//		this->mType = rhs.mType;
//		this->mName = rhs.mName;
//		this->mDescription = rhs.mDescription;
//		this->mRequired = rhs.mRequired;
//
//		if (this->mValue != nullptr && this->mDefaultValue != nullptr){
//			this->eraseValues();
//			this->mValue = nullptr;
//		}
//
//		if (rhs.mValue == nullptr && rhs.mDefaultValue != nullptr)
//			return;
//
//		switch (rhs.mType){
//		case ParamType::INT: 
//			this->mValue = new int(*((int*)rhs.mValue)); 
//			this->mDefaultValue = new int(*((int*)rhs.mDefaultValue));
//			break;
//		case ParamType::LONG: 
//			this->mValue = new long(*((long*)rhs.mValue));
//			this->mDefaultValue = new long(*((long*)rhs.mDefaultValue));
//			break;
//		case ParamType::FLOAT: 
//			this->mValue = new float(*((float*)rhs.mValue));
//			this->mDefaultValue = new float(*((float*)rhs.mDefaultValue));
//			break;
//		case ParamType::DOUBLE: 
//			this->mValue = new double(*((double*)rhs.mValue)); 
//			this->mDefaultValue = new double(*((double*)rhs.mDefaultValue));
//			break;
//		case ParamType::BOOL: 
//			this->mValue = new bool(*((bool*)rhs.mValue));
//			this->mDefaultValue = new bool(*((bool*)rhs.mDefaultValue));
//			break;
//		case ParamType::STRING: 
//			this->mValue = new std::string(*((std::string*)rhs.mValue));
//			this->mDefaultValue = new std::string(*((std::string*)rhs.mDefaultValue));
//			break;
//		case ParamType::FILE_HANDLE: 
//			this->mValue = new FileHandle(*((FileHandle*)rhs.mValue));
//			this->mDefaultValue = new FileHandle(*((FileHandle*)rhs.mDefaultValue));
//			break;
//		case ParamType::DIRECTORY_HANDLE: 
//			this->mValue = new DirectoryHandle(*((DirectoryHandle*)rhs.mValue)); 
//			this->mDefaultValue = new DirectoryHandle(*((DirectoryHandle*)rhs.mDefaultValue));
//			break;
//		}
//
//	}
//
//	void Parameter::eraseValues(){
//		switch (this->mType){
//		case ParamType::INT:
//			delete ((int*)this->mValue);
//			delete ((int*)this->mDefaultValue);
//			break;
//		case ParamType::LONG:
//			delete ((long*)this->mValue);
//			delete ((long*)this->mDefaultValue);
//			break;
//		case ParamType::FLOAT:
//			delete ((float*)this->mValue);
//			delete ((float*)this->mDefaultValue);
//			break;
//		case ParamType::DOUBLE:
//			delete ((double*)this->mValue);
//			delete ((double*)this->mDefaultValue);
//			break;
//		case ParamType::BOOL:
//			delete ((bool*)this->mValue);
//			delete ((bool*)this->mDefaultValue);
//			break;
//		case ParamType::STRING:
//			delete ((std::string*)this->mValue);
//			delete ((std::string*)this->mDefaultValue);
//			break;
//		case ParamType::FILE_HANDLE:
//			delete ((FileHandle*)this->mValue);
//			delete ((FileHandle*)this->mDefaultValue);
//			break;
//		case ParamType::DIRECTORY_HANDLE: delete ((DirectoryHandle*)this->mValue); break;
//		}
//	}
//
//}
//

namespace ssf{

	Parameter::Parameter(void){
	}

	Parameter::Parameter(const std::string& name, const std::string& description, const ParamType& requiredType /*= ParamType::STRING*/)
		: mName(name), mDescription(description), mRequiredType(requiredType){

	}

	int Parameter::toInt() const{
		double temp_value;
		int convert_value;
		try{
			temp_value = boost::lexical_cast<double>(this->mValue);
			convert_value = boost::numeric_cast<int>(temp_value);
		}
		catch (std::exception e){
			throw ParamException(this->mName, "Is not possible convert this parameter to int.");
		}
		return convert_value;
	}

	long Parameter::toLong() const{
		double temp_value;
		long convert_value;
		try{
			temp_value = boost::lexical_cast<double>(this->mValue);
			convert_value = boost::lexical_cast<long>(temp_value);
		}
		catch (std::exception e){
			throw ParamException(this->mName, "Is not possible convert this parameter to long.");
		}
		return convert_value;
	}

	long long Parameter::toLongLong() const{
		double temp_value;
		long long convert_value;
		try{
			temp_value = boost::lexical_cast<double>(this->mValue);
			convert_value = boost::lexical_cast<long long>(temp_value);
		}
		catch (std::exception e){
			throw ParamException(this->mName, "Is not possible convert this parameter to long long.");
		}
		return convert_value;
	}

	unsigned int Parameter::toUnsignedInt() const{
		double temp_value;
		unsigned int convert_value;
		try{
			temp_value = boost::lexical_cast<double>(this->mValue);
			convert_value = boost::lexical_cast<unsigned int>(temp_value);
		}
		catch (std::exception e){
			throw ParamException(this->mName, "Is not possible convert this parameter to unsigned int.");
		}
		return convert_value;
	}

	unsigned long Parameter::toUnsignedLong() const{
		double temp_value;
		unsigned long convert_value;
		try{
			temp_value = boost::lexical_cast<double>(this->mValue);
			convert_value = boost::lexical_cast<unsigned long>(temp_value);
		}
		catch (std::exception e){
			throw ParamException(this->mName, "Is not possible convert this parameter to unsigned long.");
		}
		return convert_value;
	}

	float Parameter::toFloat() const{
		float convert_value;
		try{
			convert_value = boost::lexical_cast<float>(this->mValue);
		}
		catch (std::exception e){
			throw ParamException(this->mName, "Is not possible convert this parameter to float.");
		}
		return convert_value;
	}

	double Parameter::toDouble() const{
		double convert_value;
		try{
			convert_value = boost::lexical_cast<double>(this->mValue);
		}
		catch (std::exception e){
			throw ParamException(this->mName, "Is not possible convert this parameter to double.");
		}
		return convert_value;
	}

	std::string Parameter::toString() const{
		return this->mValue;
	}

	FileHandle Parameter::toFileHandle() const{
		return FileHandle(this->mValue);
	}

	DirectoryHandle Parameter::toDirectoryHandle() const{
		return DirectoryHandle(this->mValue);
	}

	void Parameter::setValue(const int& value){
		this->mValue = std::to_string(value);
	}

	void Parameter::setValue(const long& value){
		this->mValue = std::to_string(value);
	}

	void Parameter::setValue(const long long& value){
		this->mValue = std::to_string(value);
	}

	void Parameter::setValue(const unsigned int& value){
		this->mValue = std::to_string(value);
	}

	void Parameter::setValue(const unsigned long& value){
		this->mValue = std::to_string(value);
	}

	void Parameter::setValue(const float& value){
		this->mValue = std::to_string(value);
	}
	
	void Parameter::setValue(const double& value){
		this->mValue = std::to_string(value);
	}

	void Parameter::setValue(const bool& value){
		this->mValue = std::to_string(value);
	}

	void Parameter::setValue(const char* value){
		std::string strValue(value);
		this->mValue = strValue;
	}

	void Parameter::setValue(const std::string& value){
		this->mValue = value;
	}

	void Parameter::setValue(const FileHandle& value){
		this->mValue = value.getAbsoluteFileName();
	}

	void Parameter::setValue(const DirectoryHandle& value){
		this->mValue = value.getAbsolutePath();
	}

	bool Parameter::isEmpty() const{
		return this->mValue.empty();
	}

	void Parameter::clearValue(){
		this->mValue.clear();
	}

	ssf::ParamType Parameter::getRequiredType() const{
		return this->mRequiredType;
	}

	void Parameter::setRequiredType(const ParamType& requiredType){
		this->mRequiredType = requiredType;
	}

}
