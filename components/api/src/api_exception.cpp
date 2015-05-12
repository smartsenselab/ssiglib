#include "api/api_exception.hpp"

namespace ssf{

	APIException(const std::string& moduleName, const std::string& message) : Exception(message), mModuleName(moduleName){

	}

	APIException::~APIException() throw(){
	}

	virtual const char* what() const throw(){
		std::string what_message = mModuleName + ": " + mMessage;
		return what_message.c_str();
	}

	std::string getModuleName() const{
		return this->mModuleName;
	}

}

