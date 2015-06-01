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

#ifndef _SSF_CORE_CONCURRENT_QUEUE_HPP_
#define _SSF_CORE_CONCURRENT_QUEUE_HPP_

#include <core/moodycamel_concurrent_queue.hpp>
#include "core/core_defs.hpp"


namespace ssf{

	/**
	 * @brief	Concurrent Queue Structure (Thread Safe).
	 *
	 * @tparam	T	Generic type parameter.
	 * 				
	 * @detail	This class uses the 
	 * 			<a href="https://github.com/cameron314/concurrentqueue"><i>Cameron's Concurrent Queue implementation</i>
	 */
	template<class T>
	class ConcurrentQueue{

	public:

		/**
		 * @brief	Initializes a new instance of the ConcurrentQueue class.
		 */
		CORE_EXPORT ConcurrentQueue(void){

			//this->mInternalQueue.
		}

		/**
		 * @brief	Finalizes an instance of the ConcurrentQueue class.
		 */
		CORE_EXPORT virtual ~ConcurrentQueue(void){
			//Destructor
		}

		/**
		 * @brief	Pushes an object onto this queue.
		 *
		 * @param	data	The data.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT bool push(T const& data){
			return this->mInternalQueue.enqueue(data);
		}

		/**
		 * @brief	Removes and returns the first queue object.
		 *
		 * @param	data	The data to pop.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		CORE_EXPORT bool pop(T& data){
			return this->mInternalQueue.try_dequeue(data);
		}

		/**
		 * @brief	Gets the size.
		 *
		 * @return	The size of queue.
		 */
		CORE_EXPORT size_t size(){
			return this->mInternalQueue.size_approx();
		}

		/**
		 * @brief	Clears this object to its blank/initial state.
		 */
		CORE_EXPORT void clear(){
			T dummyData;
			while (this->mInternalQueue.try_dequeue(dummyData));
		}


		ConcurrentQueue(const ConcurrentQueue& rhs) SSF_DELETE_FUNCTION;
		ConcurrentQueue& operator=(const ConcurrentQueue& rhs) SSF_DELETE_FUNCTION;

	private:
		moodycamel::ConcurrentQueue<T> mInternalQueue;  ///< Internal Concurrent Queue implementation

	};

}

#endif // !_SSF_CORE_CONCURRENT_QUEUE_HPP_