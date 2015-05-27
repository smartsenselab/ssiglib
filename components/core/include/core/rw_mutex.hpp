//#ifndef _SSF_CORE_RW_MUTEX_HPP_
//#define _SSF_CORE_RW_MUTEX_HPP_
//
//#include <mutex>
//#include <condition_variable>
//
//#include "core/core_defs.hpp"
//
//
////http://stackoverflow.com/questions/27860685/how-to-make-a-multiple-read-single-write-lock-from-more-basic-synchronization-pr
//
//namespace ssf{
//
//	class RWMutex{
//
//	public:
//		CORE_EXPORT RWMutex(void);
//		CORE_EXPORT virtual ~RWMutex(void);
//
//		CORE_EXPORT void lockRead();
//		CORE_EXPORT void unlockRead();
//		CORE_EXPORT void lockWrite();
//		CORE_EXPORT void unlockWrite();
//
//	private:
//		RWMutex(const RWMutex& rhs);
//		RWMutex& operator=(const RWMutex& rhs);
//
//	private:
//		std::mutex mMutext;
//		std::condition_variable mReaderCond, mWriterCond;
//		int mReaders, mWriters, mActiverWriters;
//
//	};
//
//}
//
//#endif // !_SSF_CORE_RW_MUTEX_HPP_