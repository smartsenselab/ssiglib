#ifndef _SSF_CORE_EXCEPTION_HPP_
#define _SSF_CORE_EXCEPTION_HPP_

#include <string>
#include <exception>

namespace ssf{

	/**
	 \class	Exception
	
	 \brief		Default Class for handle all SSF exceptions
	
	 \author	Antonio Carlos
	 \date		3/8/2015
	 */

	class Exception : public std::exception {

	public:

		/**
		 \fn		explicit Exception::Exception(const std::string& message);
		
		 \brief		Constructor.
		
		 \author	Antonio Carlos
		 \date		3/8/2015
		
		 \param	message	The exception message.
		 */

		explicit Exception(const std::string& message);
		virtual ~Exception() throw();

		virtual const char * what() const throw();


	private:
		std::string mMessage;

	};

}

#endif