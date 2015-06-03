#include "configuration/setup_exception.hpp"


namespace ssf{

	SetupException::SetupException(const std::string& moduleName, const std::string& message)
		: Exception(message), mModuleName(moduleName){

	}

	SetupException::~SetupException() throw(){
	}

	const char* SetupException::what() const throw(){
		std::string what_message = mModuleName + ": " + mMessage;
        return what_message.c_str();
	}

	std::string SetupException::getModuleName() const{
		return this->mModuleName;
	}

}

