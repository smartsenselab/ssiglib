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

#ifndef _SSF_CORE_CONDITIONAL_MUTEX_HPP_
#define _SSF_CORE_CONDITIONAL_MUTEX_HPP_

#include <mutex>
#include <condition_variable>

#include "core/core_defs.hpp"

namespace ssf{

	/**
	* @brief	SSF Conditional mutex.
	*
	* @detail	A conditional mutex is able to lock a thread (by waitForReady() function) until user 
	* 			set the mutex status as ready.
	* 			We decided for our own Conditional mutex class because, in future, we could change or
	* 			optimize the mutex implementation without carry big changes on code.
	*/
	class ConditionalMutex{

	public:

		/**
		 * @brief	Initializes a new instance of the ConditionalMutex class.
		 *
		 * @param	ready	Initial condition. If ready is false, the mutex status is lock.
		 */
		CORE_EXPORT ConditionalMutex(const bool& ready = false);

		/**
		 * @brief	Finalizes an instance of the ConditionalMutex class.
		 */
		CORE_EXPORT virtual ~ConditionalMutex(void);

		/**
		 * @brief	Set mutex status as unready, e.g. lock.
		 */
		CORE_EXPORT void unready();

		/**
		 * @brief	Set mutex status as ready, e.g. unlock.
		 */
		CORE_EXPORT void ready();

		/**
		 * @brief	Lock thread until mutex status changes to ready.
		 */
		CORE_EXPORT void waitForReady();


	private:
		ConditionalMutex(const ConditionalMutex& rhs);
		ConditionalMutex& operator=(const ConditionalMutex& rhs);

	private:
		std::mutex mMutex;  ///< The mutex used for lock
		std::condition_variable mConditionVariable; ///< The condition variable used for control
		bool mReadyStatus;  ///< The mutex status, true is ready


	};


}

#endif // !_SSF_CORE_CONDITIONAL_MUTEX_HPP_PP_