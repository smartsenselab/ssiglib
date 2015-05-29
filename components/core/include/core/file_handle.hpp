/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                   Software License Agreement (BSD License)
*                      For Smart Surveillance Framework
*                        http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, 
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright 
*       notice, this list of conditions and the following disclaimer in the 
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its 
*       contributors may be used to endorse or promote products derived from 
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
*  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#ifndef _SSF_CORE_FILE_UTIL_HPP_
#define _SSF_CORE_FILE_UTIL_HPP_

#include <string>
#include <memory>

#include "core/core_defs.hpp"
#include "core/base_object.hpp"

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	/**
	 * @brief	This handles with files on filesystem level.
	 * 			
	 * @detail	Supports basic operations, such as get absolute file path, verify if a file
	 * 			exists or erase a file.
	 *
	 * @sa	BaseObject
	 */
	class FileHandle : public BaseObject{

	public:

		/**
		 * @brief	Initializes a new instance of the FileHandle class.
		 *
		 * @param	fileName	name of the file.
		 */
		CORE_EXPORT explicit FileHandle(const std::string& fileName = "");

		/**
		 * @brief	Finalizes an instance of the FileHandle class.
		 */
		CORE_EXPORT virtual ~FileHandle(void);

		/**
		 * @brief	Initializes a new instance of the FileHandle class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT FileHandle(const FileHandle& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT FileHandle& operator=(const FileHandle& rhs);

		/**
		 * @brief	Less-than comparison operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the first parameter is less than the second.
		 */
		CORE_EXPORT bool operator<(const FileHandle& rhs) const;

		/**
		 * @brief	Equality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are considered equivalent.
		 */
		CORE_EXPORT bool operator==(const FileHandle& rhs) const;

		/**
		 * @brief	Inequality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are not considered equivalent.
		 */
		CORE_EXPORT bool operator!=(const FileHandle& rhs) const;

		/**
		 * @brief	Gets absolute path of file. For instance <tt>/home/user/file.txt</tt>
		 *
		 * @return	A string with file path.
		 */
		CORE_EXPORT std::string absolutePath() const;

		/**
		 * @brief	Gets simple file name (without extension).
		 *
		 * @return	A string with simple file name.
		 */
		CORE_EXPORT std::string simpleName() const;

		/**
		 * @brief	Gets the extension of file, for instance <i>txt</i>
		 *
		 * @return	A string with extension.
		 */
		CORE_EXPORT std::string extension() const;

		/**
		 * @brief	Erases the file.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT bool erase();

		/**
		 * @brief	Query if this file has extension.
		 *
		 * @return	true if extension, false if not.
		 */
		CORE_EXPORT bool hasExtension() const;

		/**
		 * @brief	Erases the given file.
		 *
		 * @param	fileName	name of the file.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT static bool erase(const std::string& fileName);

		/**
		 * @brief	Query if the given file exists.
		 *
		 * @param	fileName	name of the file.
		 *
		 * @return	true if it exists, false if it not exists.
		 */
		CORE_EXPORT static bool exists(const std::string& fileName);

	private:
		std::shared_ptr<boost::filesystem::path> mPath ;	///< Full pathname of the file

	};
}

#endif // !_SSF_CORE_FILE_UTIL_HPP_PP_