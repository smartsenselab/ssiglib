//#include "core/parameter.hpp"
//
//#include <boost/lexical_cast.hpp>
//
//#include "core/param_exception.hpp"
//
//namespace ssf{
//
//	Parameter::Parameter(void){
//		this->mValue = "";
//		this->mType = ParamType::STRING;
//		this->mName = "";
//		this->mDescription = "";
//		this->mRequired = false;
//	}
//
//	Parameter::Parameter(const std::string& name, const std::string& description, const ParamType& type /*= ParamType::STRING*/)
//		: mName(name), mDescription(description), mType(type){
//		this->mRequired = false;
//	}
//
//	int Parameter::toInt() const{
//		double temp_value;
//		int convert_value;
//		try{
//			temp_value = boost::lexical_cast<double>(this->mValue);
//			convert_value = boost::numeric_cast<int>(temp_value);
//		}
//		catch (std::exception e){
//			throw ParamException(this->mName, "Is not possible convert this parameter to int.");
//		}
//		return convert_value;
//	}
//
//	long Parameter::toLong() const{
//		double temp_value;
//		long convert_value;
//		try{
//			temp_value = boost::lexical_cast<double>(this->mValue);
//			convert_value = boost::lexical_cast<long>(temp_value);
//		}
//		catch (std::exception e){
//			throw ParamException(this->mName, "Is not possible convert this parameter to long.");
//		}
//		return convert_value;
//	}
//
//	long long Parameter::toLongLong() const{
//		double temp_value;
//		long long convert_value;
//		try{
//			temp_value = boost::lexical_cast<double>(this->mValue);
//			convert_value = boost::lexical_cast<long long>(temp_value);
//		}
//		catch (std::exception e){
//			throw ParamException(this->mName, "Is not possible convert this parameter to long long.");
//		}
//		return convert_value;
//	}
//
//	unsigned int Parameter::toUnsignedInt() const{
//		double temp_value;
//		unsigned int convert_value;
//		try{
//			temp_value = boost::lexical_cast<double>(this->mValue);
//			convert_value = boost::lexical_cast<unsigned int>(temp_value);
//		}
//		catch (std::exception e){
//			throw ParamException(this->mName, "Is not possible convert this parameter to unsigned int.");
//		}
//		return convert_value;
//	}
//
//	unsigned long Parameter::toUnsignedLong() const{
//		double temp_value;
//		unsigned long convert_value;
//		try{
//			temp_value = boost::lexical_cast<double>(this->mValue);
//			convert_value = boost::lexical_cast<unsigned long>(temp_value);
//		}
//		catch (std::exception e){
//			throw ParamException(this->mName, "Is not possible convert this parameter to unsigned long.");
//		}
//		return convert_value;
//	}
//
//	float Parameter::toFloat() const{
//		float convert_value;
//		try{
//			convert_value = boost::lexical_cast<float>(this->mValue);
//		}
//		catch (std::exception e){
//			throw ParamException(this->mName, "Is not possible convert this parameter to float.");
//		}
//		return convert_value;
//	}
//
//	double Parameter::toDouble() const{
//		double convert_value;
//		try{
//			convert_value = boost::lexical_cast<double>(this->mValue);
//		}
//		catch (std::exception e){
//			throw ParamException(this->mName, "Is not possible convert this parameter to double.");
//		}
//		return convert_value;
//	}
//
//	bool Parameter::toBool() const{
//		int tempValue;
//		try{
//			tempValue = this->toInt();
//		}
//		catch (std::exception e){
//			if (this->mValue == "false")
//				return false;
//		}
//		return (tempValue != 0);
//	}
//
//	std::string Parameter::toString() const{
//		return this->mValue;
//	}
//
//	FileHandle Parameter::toFileHandle() const{
//		return FileHandle(this->mValue);
//	}
//
//	DirectoryHandle Parameter::toDirectoryHandle() const{
//		return DirectoryHandle(this->mValue);
//	}
//
//	void Parameter::setValue(const int& value){
//		this->mValue = std::to_string(value);
//	}
//
//	void Parameter::setValue(const long& value){
//		this->mValue = std::to_string(value);
//	}
//
//	void Parameter::setValue(const long long& value){
//		this->mValue = std::to_string(value);
//	}
//
//	void Parameter::setValue(const unsigned int& value){
//		this->mValue = std::to_string(value);
//	}
//
//	void Parameter::setValue(const unsigned long& value){
//		this->mValue = std::to_string(value);
//	}
//
//	void Parameter::setValue(const float& value){
//		this->mValue = std::to_string(value);
//	}
//	
//	void Parameter::setValue(const double& value){
//		this->mValue = std::to_string(value);
//	}
//
//	void Parameter::setValue(const bool& value){
//		this->mValue = std::to_string(value);
//	}
//
//	void Parameter::setValue(const char* value){
//		std::string strValue(value);
//		this->mValue = strValue;
//	}
//
//	void Parameter::setValue(const std::string& value){
//		this->mValue = value;
//	}
//
//	void Parameter::setValue(const FileHandle& value){
//		this->mValue = value.getAbsoluteFileName();
//	}
//
//	void Parameter::setValue(const DirectoryHandle& value){
//		this->mValue = value.getAbsolutePath();
//	}
//
//	bool Parameter::isEmpty() const{
//		return this->mValue.empty();
//	}
//
//	void Parameter::clearValue(){
//		this->mValue.clear();
//	}
//
//	ssf::ParamType Parameter::getType() const{
//		return this->mType;
//	}
//
//	void Parameter::setType(const ParamType& type){
//		this->mType = type;
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
//	void Parameter::setDescription(const std::string& description){
//		this->mDescription = description;
//	}
//
//	bool Parameter::isRequired() const{
//		return this->mRequired;
//	}
//
//	void Parameter::setRequired(const bool& required){
//		this->mRequired = required;
//	}
//
//}
