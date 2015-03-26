#include "core/param_exception.hpp"

namespace ssf{

	ParamException::ParamException(const std::string& parameterName, const std::string& message)
		: mParameterName(parameterName), Exception(message){

	}

	ParamException::~ParamException() throw(){

	}

	const char * ParamException::what() const throw(){
		std::string what_message = mParameterName + ": " + mMessage;
		return what_message.c_str();
	}

	std::string ParamException::getParameterName() const{
		return this->mParameterName;
	}

}

