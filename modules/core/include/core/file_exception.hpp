/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this license. If you do 
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without modification, are permitted 
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of 
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
*       conditions and the following disclaimer in the documentation and/or other materials 
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
*       endorse or promote products derived from this software without specific prior written 
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#ifndef _SSF_CORE_FILE_EXCEPTION_HPP_

/**
 * @def	_SSF_CORE_FILE_EXCEPTION_HPP_
 *
 * @brief	A macro that defines ssf core file exception hpp.
 */
#define _SSF_CORE_FILE_EXCEPTION_HPP_

#include <string>

#include "core/core_defs.hpp"
#include "core/exception.hpp"

namespace ssf{

	/**
	 * @brief	Exception specialization for signaling file errors.
	 *
	 * @sa	Exception
	 */
	class FileException : public Exception {

	public:

		/**
		 * @brief	Initializes a new instance of the FileException class.
		 *
		 * @param	fileName	Name of the file where the exception happen.
		 * @param	message 	The exception message.
		 */
		CORE_EXPORT FileException(const std::string& fileName = "", const char* message = "");

		/**
		 * @brief	Initializes a new instance of the FileException class.
		 *
		 * @param	fileName	Name of the file where the exception happen.
		 * @param	message 	The exception message.
		 */
		CORE_EXPORT FileException(const std::string& fileName, const std::string& message);

		/**
		 * @brief	Finalizes an instance of the FileException class.
		 */
		CORE_EXPORT virtual ~FileException() throw();

		/**
		 * @brief	Initializes a new instance of the FileException class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT FileException(const FileException& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT FileException& operator=(const FileException& rhs);

		/**
		 * @brief	Gets the what exception message happened.
		 *
		 * @return	Exception message.
		 */
		CORE_EXPORT virtual const char *what() const throw();

		/**
		 * @brief	File name where the exception happen.
		 *
		 * @return	A std::string with file name.
		 */
		CORE_EXPORT std::string fileName() const;

	private:
		std::string mFileName;  ///< Name of the file where the exception happen.

	};

}

#endif // !_SSF_CORE_FILE_EXCEPTION_HPP_PP_