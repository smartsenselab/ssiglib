#ifndef _SSF_SETUP_EXCEPTION_HPP_
#define _SSF_SETUP_EXCEPTION_HPP_

#include <string>
#include <core/exception.hpp>
#include "configuration/setup_defs.hpp"

namespace ssf{

	class SetupException : public Exception{
	
	public:
		CONFIG_EXPORT SetupException(const std::string& moduleName, const std::string& message);
		CONFIG_EXPORT virtual ~SetupException() throw();
		CONFIG_EXPORT virtual const char* what() const throw();
		CONFIG_EXPORT std::string getModuleName() const;

	private:
		std::string mModuleName;

	};

}

#endif // !_SSF_SETUP_EXCEPTION_HPP_