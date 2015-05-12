#ifndef _SSF_API_API_EXCEPTION_HPP_
#define _SSF_API_API_EXCEPTION_HPP_

#include <string>
#include <core/exception.hpp>

#include "configuration/configuration_defs.hpp"

namespace ssf{

	class ConfigurationException : public Exception{
	
	public:
		CONFIG_EXPORT ConfigurationException(const std::string& moduleName, const std::string& message);
		CONFIG_EXPORT virtual ~ConfigurationException() throw();
		CONFIG_EXPORT virtual const char* what() const throw();
		CONFIG_EXPORT std::string getModuleName() const;

	private:
		std::string mModuleName;

	};

}

#endif // !_SSF_API_API_EXCEPTION_HPP_