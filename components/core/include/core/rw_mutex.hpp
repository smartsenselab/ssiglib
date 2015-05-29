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

#ifndef _SSF_CORE_RW_MUTEX_HPP_
#define _SSF_CORE_RW_MUTEX_HPP_

#include <mutex>
#include <condition_variable>

#include "core/core_defs.hpp"

namespace ssf{

	/**
	 * @brief	A reader and writer mutex.
	 * 			
	 * @detail	The ReaderWriterMutex concept extends the Mutex Concept to include the notion of reader-writer locks.
	 * 			This implementation was based on <a href="http://stackoverflow.com/a/28121513"><i>qqibrow</i> suggestion in StackOverflow</a>.
	 */
	class RWMutex{

	public:

		/**
		 * @brief	Initializes a new instance of the RWMutex class.
		 */
		CORE_EXPORT RWMutex(void);

		/**
		 * @brief	Finalizes an instance of the RWMutex class.
		 */
		CORE_EXPORT virtual ~RWMutex(void);

		/**
		 * @brief	Lock mutex for read operations.
		 */
		CORE_EXPORT void lockRead();

		/**
		 * @brief	Unlock mutex for read operations.
		 */
		CORE_EXPORT void unlockRead();

		/**
		 * @brief	Lock mutex for write operations.
		 */
		CORE_EXPORT void lockWrite();

		/**
		 * @brief	Unlock mutex for write operations.
		 */
		CORE_EXPORT void unlockWrite();

	private:
		RWMutex(const RWMutex& rhs);
		RWMutex& operator=(const RWMutex& rhs);

	private:
		std::mutex mMutex;  ///< The mutex use for lock
		std::condition_variable mReaderCond, mWriterCond; ///< The condition variables used for control
		int mReaders, mWriters, mActiverWriters; ///< Counters for write and read locks

	};

}

#endif // !_SSF_CORE_RW_MUTEX_HPP_PP_