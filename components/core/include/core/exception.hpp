#ifndef _SSF_CORE_EXCEPTION_HPP_
#define _SSF_CORE_EXCEPTION_HPP_

#include <string>
#include <exception>

namespace ssf{

	class Exception : public std::exception {
	
	public:
		explicit Exception(const std::string& message);
		virtual ~Exception() throw();

		virtual const char * what() const throw();


	private:
		std::string mMessage;

	};

}

#endif