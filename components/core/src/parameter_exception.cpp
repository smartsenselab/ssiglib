#include "core/parameter_exception.hpp"

namespace ssf{

	ParameterException::ParameterException(const std::string& parameterName, const std::string& message)
		: mParameterName(parameterName), Exception(message){

	}

	ParameterException::~ParameterException() throw(){

	}

	const char * ParameterException::what() const throw(){
		std::string what_message = mParameterName + ": " + mMessage;
		return what_message.c_str();
	}

}

