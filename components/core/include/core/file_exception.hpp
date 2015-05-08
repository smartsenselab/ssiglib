#ifndef _SSF_CORE_FILE_EXCEPTION_HPP_
#define _SSF_CORE_FILE_EXCEPTION_HPP_

#include <string>

#include "core/base.hpp"
#include "core/exception.hpp"

namespace ssf{

	class FileException : public Exception {

	public:
		SSF_EXPORT FileException(const std::string& fileName, const std::string& message);

		SSF_EXPORT virtual ~FileException() throw();

		SSF_EXPORT virtual const char * what() const throw();

		SSF_EXPORT std::string getFileName() const;

	private:
		std::string mFileName;
	
	};

}

#endif // !_SSF_CORE_FILE_EXCEPTION_HPP_