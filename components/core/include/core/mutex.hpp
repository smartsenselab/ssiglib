#ifndef _SSF_CORE_MUTEX_HPP_
#define _SSF_CORE_MUTEX_HPP_

#include <mutex>

namespace boost{
	class mutex;
}

namespace ssf{

	class Mutex{
	
	public:
		Mutex(void);
		virtual ~Mutex(void);

		void lock();
		void unlock();

	private:
		Mutex(const Mutex& rhs);
		Mutex& operator=(const Mutex& rhs);

	private:
		std::unique_lock<std::mutex> mLock;

	};

}

#endif // !_SSF_CORE_MUTEX_HPP_