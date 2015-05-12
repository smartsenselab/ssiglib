#ifndef _SSF_CORE_PARAMETER_EXCEPTION_HPP_
#define _SSF_CORE_PARAMETER_EXCEPTION_HPP_

#include "core/ssfdef.hpp"
#include "core/exception.hpp"

namespace ssf{

	class ParamException : public Exception {

	public:
		SSF_EXPORT ParamException(const std::string& parameterName, const std::string& message);

		SSF_EXPORT virtual ~ParamException() throw();

		SSF_EXPORT virtual const char * what() const throw();

		SSF_EXPORT std::string getParameterName() const;

	private:
		std::string mParameterName;

	};

}

#endif // !_SSF_CORE_PARAMETER_EXCEPTION_HPP_