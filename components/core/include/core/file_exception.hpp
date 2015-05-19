#ifndef _SSF_CORE_FILE_EXCEPTION_HPP_
#define _SSF_CORE_FILE_EXCEPTION_HPP_

#include <string>

#include "core/core_defs.hpp"
#include "core/exception.hpp"

namespace ssf{

	class FileException : public Exception {

	public:
		CORE_EXPORT FileException(const std::string& fileName, const std::string& message);

		CORE_EXPORT virtual ~FileException() throw();

		CORE_EXPORT virtual const char * what() const throw();

		CORE_EXPORT std::string getFileName() const;

	private:
		std::string mFileName;
	
	};

}

#endif // !_SSF_CORE_FILE_EXCEPTION_HPP_