#ifndef _SSF_CORE_CONDITIONAL_MUTEX_HPP_
#define _SSF_CORE_CONDITIONAL_MUTEX_HPP_

#include <mutex>
#include <condition_variable>

#include "core/core_defs.hpp"

namespace ssf{

	class ConditionalMutex{

	public:
		CORE_EXPORT ConditionalMutex(const bool& ready = false);
		CORE_EXPORT virtual ~ConditionalMutex(void);

		CORE_EXPORT void unready();
		CORE_EXPORT void ready();
		CORE_EXPORT void waitForReady();


	private:
		ConditionalMutex(const ConditionalMutex& rhs);
		ConditionalMutex& operator=(const ConditionalMutex& rhs);

	private:
		std::mutex mMutex;
		std::condition_variable mConditionVariable;
		bool mReadyStatus;


	};


}

#endif // !_SSF_CORE_CONDITIONAL_MUTEX_HPP_