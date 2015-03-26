#ifndef _SSF_CORE_PARAMETER_EXCEPTION_HPP_
#define _SSF_CORE_PARAMETER_EXCEPTION_HPP_

#include "core/exception.hpp"

namespace ssf{

	class ParamException : public Exception {

	public:
		ParamException(const std::string& parameterName, const std::string& message);

		virtual ~ParamException() throw();

		virtual const char * what() const throw();

		std::string getParameterName() const;

	private:
		std::string mParameterName;

	};

}

#endif // !_SSF_CORE_PARAMETER_EXCEPTION_HPP_