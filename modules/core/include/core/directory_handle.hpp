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

#ifndef _SSF_CORE_DIRECTORY_HANDLE_HPP_
#define _SSF_CORE_DIRECTORY_HANDLE_HPP_

#include <string>
#include <set>
#include <memory>

#include "core/core_defs.hpp"
#include "core/file_handle.hpp"

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	/**
	 * @brief	This handles with directories on filesystem level.
	 * 			
	 * @detail	Supports basic operations, such as get absolute file path, verify if a directory
	 * 			exists and create or erase a directory.
	 */
	class DirectoryHandle{

	public:

		/**
		 * @brief	Initializes a new instance of the DirectoryHandle class.
		 *
		 * @param	directoryPathName	Full pathname of the directory file.
		 */
		CORE_EXPORT explicit DirectoryHandle(const std::string& directoryPathName = "");

		/**
		 * @brief	Finalizes an instance of the DirectoryHandle class.
		 */
		CORE_EXPORT virtual ~DirectoryHandle(void);

		/**
		 * @brief	Initializes a new instance of the DirectoryHandle class.
		 *
		 * @param	rhs	The right hand side.
		 */
		CORE_EXPORT DirectoryHandle(const DirectoryHandle& rhs);

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		CORE_EXPORT DirectoryHandle& operator=(const DirectoryHandle& rhs);

		/**
		 * @brief	Less-than comparison operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the first parameter is less than the second.
		 */
		CORE_EXPORT bool operator<(const DirectoryHandle& rhs) const;

		/**
		 * @brief	Equality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are considered equivalent.
		 */
		CORE_EXPORT bool operator==(const DirectoryHandle& rhs) const;

		/**
		 * @brief	Inequality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are not considered equivalent.
		 */
		CORE_EXPORT bool operator!=(const DirectoryHandle& rhs) const;

		/**
		 * @brief	Gets absolute path of directory. For instance <tt>/home/user/directory</tt>
		 *
		 * @return	A string.A string with directory path.
		 */
		CORE_EXPORT std::string absolutePath() const;

		/**
		 * @brief	Gets simple directory name.
		 *
		 * @return	A string with simple directory name.
		 */
		CORE_EXPORT std::string simpleName() const;

		/**
		 * @brief	List all sub directories.
		 *
		 * @return	A set of all sub directories;
		 */
		CORE_EXPORT std::set<DirectoryHandle> listSubDirectories();

		/**
		 * @brief	List all files into directory.
		 *
		 * @return	A set of all files;
		 */
		CORE_EXPORT std::set<FileHandle> listFiles();

		/**
		 * @brief	Query if this directory is empty.
		 *
		 * @return	true if empty, false if not.
		 */
		CORE_EXPORT bool isEmpty() const;

		/**
		 * @brief	Erases this directory.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT bool erase() const;

		/**
		 * @brief	Query if this directory exists.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT bool exists() const;

		/**
		 * @brief	Query if the given directory exists.
		 *
		 * @param	directoryPathName	Full pathname of the directory.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT static bool exists(const std::string& directoryPathName);

		/**
		 * @brief	Erases the given directory.
		 *
		 * @param	directoryPathName	Full pathname of the directory.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT static bool erase(const std::string& directoryPathName);

		/**
		 * @brief	Creates a new directory.
		 *
		 * @param	directoryPathName	Full pathname of the new directory.
		 *
		 * @return	A DirectoryHandle that represents the new directory.
		 */
		CORE_EXPORT static DirectoryHandle create(const std::string& directoryPathName);

	private:
		std::shared_ptr<boost::filesystem::path> mPath; ///< Full pathname of the file
		
	};

}

#endif // !_SSF_CORE_DIRECTORY_HANDLE_HPP_PP_