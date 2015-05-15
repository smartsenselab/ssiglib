#ifndef _SSF_CORE_EXCEPTION_HPP_
#define _SSF_CORE_EXCEPTION_HPP_

#include "core/core_defs.hpp"

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

		CORE_EXPORT explicit Exception(const std::string& message);
		CORE_EXPORT virtual ~Exception() throw();

		CORE_EXPORT virtual const char * what() const throw();

		CORE_EXPORT std::string getMessage() const;

	protected:
		std::string mMessage;

	};

}

#endif