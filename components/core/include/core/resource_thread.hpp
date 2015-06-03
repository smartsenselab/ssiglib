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

#ifndef _SSF_CORE_RESOURCE_THREAD_HPP_
#define _SSF_CORE_RESOURCE_THREAD_HPP_

#include "core/resource.hpp"

namespace boost{
	class thread;
}

namespace ssf{

	/**
	 * @brief	A resource thread is a specialization of Resource which executes in a different thread.
	 *
	 * @sa	Resource
	 */
	class ResourceThread : public Resource{
	
	public:

		/**
		 * @brief	Initializes a new instance of the ResourceThread class.
		 */
		CORE_EXPORT ResourceThread(void);

		/**
		 * @brief	Finalizes an instance of the ResourceThread class.
		 */
		CORE_EXPORT virtual ~ResourceThread(void);

		/**
		 * @brief	Starts the ResouceThread. In other words, execute the virtual function run() in a different thread
		 */
		CORE_EXPORT virtual void start();

		/**
		 * @brief	Interrupts the execution of Resource Thread.
		 */
		CORE_EXPORT virtual void stop();

		/**
		 * @brief	Blocks the calling thread until a thread terminates.
		 */
		CORE_EXPORT virtual void join();

		/**
		 * @brief	Pre-processing before call run() function.
		 */
		CORE_EXPORT virtual void beforeRun() = 0;

		/**
		 * @brief	Function which will be executed in an another thread.
		 */
		CORE_EXPORT virtual void run() = 0;

		/**
		 * @brief	Pos-processing after call run() function.
		 */
		CORE_EXPORT virtual void afterRun() = 0;
		

	private:
		ResourceThread(const ResourceThread& rhs);
		ResourceThread& operator=(const ResourceThread& rhs);

		std::shared_ptr<boost::thread> mThread; ///< The thread

	};

}

#endif // !_SSF_CORE_RESOURCE_THREAD_HPP_PP_