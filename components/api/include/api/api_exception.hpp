#ifndef _SSF_API_API_EXCEPTION_HPP_
#define _SSF_API_API_EXCEPTION_HPP_

#include <string>
#include "core/exception.hpp"

namespace ssf{

	class APIException : public Exception{
	
	public:
		APIException(const std::string& moduleName, const std::string& message);
		virtual ~APIException() throw();
		virtual const char* what() const throw();
		std::string getModuleName() const;

	private:
		std::string mModuleName;

	};

}

#endif // !_SSF_API_API_EXCEPTION_HPP_