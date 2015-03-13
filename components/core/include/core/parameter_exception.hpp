#ifndef _SSF_CORE_PARAMETER_EXCEPTION_HPP_
#define _SSF_CORE_PARAMETER_EXCEPTION_HPP_

#include "core/exception.hpp"

namespace ssf{

	class ParameterException : public Exception {

	public:
		ParameterException(const std::string& parameterName, const std::string& message);

		virtual ~ParameterException() throw();

		virtual const char * what() const throw();


	private:
		std::string mParameterName;

	};

}

#endif // !_SSF_CORE_PARAMETER_EXCEPTION_HPP_