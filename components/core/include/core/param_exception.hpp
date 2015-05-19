#ifndef _SSF_CORE_PARAMETER_EXCEPTION_HPP_
#define _SSF_CORE_PARAMETER_EXCEPTION_HPP_

#include "core/core_defs.hpp"
#include "core/exception.hpp"

namespace ssf{

	class ParamException : public Exception {

	public:
		CORE_EXPORT ParamException(const std::string& parameterName, const std::string& message);

		CORE_EXPORT virtual ~ParamException() throw();

		CORE_EXPORT virtual const char * what() const throw();

		CORE_EXPORT std::string getParameterName() const;

	private:
		std::string mParameterName;

	};

}

#endif // !_SSF_CORE_PARAMETER_EXCEPTION_HPP_