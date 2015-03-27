#include "core/exception.hpp"

namespace ssf{


	Exception::Exception(const std::string& message)
		: mMessage(message){
		
	}

	Exception::~Exception() throw(){

	}

	const char* Exception::what() const throw(){
		return this->mMessage.c_str();
	}

	std::string Exception::getMessage() const{
		return this->mMessage;
	}

}