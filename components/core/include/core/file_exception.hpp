#ifndef _SSF_CORE_FILE_EXCEPTION_HPP_
#define _SSF_CORE_FILE_EXCEPTION_HPP_

#include <string>

#include "core/exception.hpp"

namespace ssf{

	class FileException : public Exception {

	public:
		FileException(const std::string& fileName, const std::string& message);

		virtual ~FileException() throw();

		virtual const char * what() const throw();


	private:
		std::string mFileName;

	};

}

#endif // !_SSF_CORE_FILE_EXCEPTION_HPP_