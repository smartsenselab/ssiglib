#include "configuration/configuration_exception.hpp"


namespace ssf{

	ConfigurationException::ConfigurationException(const std::string& moduleName, const std::string& message)
		: Exception(message), mModuleName(moduleName){

	}

	ConfigurationException::~ConfigurationException() throw(){
	}

	const char* ConfigurationException::what() const throw(){
		std::string what_message = mModuleName + ": " + mMessage;
		return what_message.c_str();
	}

	std::string ConfigurationException::getModuleName() const{
		return this->mModuleName;
	}

}

