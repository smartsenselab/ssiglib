#ifndef _SSF_CORE_RESOURCE_THREAD_HPP_
#define _SSF_CORE_RESOURCE_THREAD_HPP_

#include "core/resource.hpp"

namespace boost{
	class thread;
}

namespace ssf{

	class ResourceThread : public Resource{
	
	public:
		CORE_EXPORT ResourceThread(void);
		CORE_EXPORT virtual ~ResourceThread(void);
		CORE_EXPORT ResourceThread(const ResourceThread& rhs);
		CORE_EXPORT ResourceThread& operator=(const ResourceThread& rhs);

		/*CORE_EXPORT virtual void start();
		CORE_EXPORT virtual void stop();
		CORE_EXPORT virtual void join();

		CORE_EXPORT virtual void beforeRun() = 0;
		CORE_EXPORT virtual void run() = 0;
		CORE_EXPORT virtual void afterRun() = 0;*/
		

	//private:
	//	std::shared_ptr<boost::thread> mThread;

	};

}

#endif // !_SSF_CORE_RESOURCE_THREAD_HPP_