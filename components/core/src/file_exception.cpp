#include "core/file_exception.hpp"

namespace ssf{

	FileException::FileException(const std::string& fileName, const std::string& message)
		: Exception(message), mFileName(fileName){

	}

	FileException::~FileException() throw (){

	}


	const char * FileException::what() const throw(){
		std::string what_message = mFileName + ": " + mMessage;
		return what_message.c_str();
	}

	std::string FileException::getFileName() const{
		return this->mFileName;
	}

}

