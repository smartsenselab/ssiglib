#include "core/rw_mutex.hpp"

namespace ssf{

	RWMutex::RWMutex()
		: mReaders(0), mWriters(0), mActiverWriters(0){

	}

	RWMutex::~RWMutex(){
		//Destructor
	}

	void RWMutex::lockRead(){
		std::unique_lock<std::mutex> lck(mMutext);
		while (!(mWriters == 0))
			mReaderCond.wait(lck);
		++mReaders;
		lck.unlock();
	}

	void RWMutex::unlockRead(){
		std::unique_lock<std::mutex> lck(mMutext);
		mReaders--;
		lck.unlock();
		mWriterCond.notify_one();
	}

	void RWMutex::lockWrite(){
		std::unique_lock<std::mutex> lck(mMutext);
		mWriters++;
		while (!((mReaders == 0) && (mActiverWriters == 0)))
			mWriterCond.wait(lck);
		mActiverWriters++;
		lck.unlock();
	}

	void RWMutex::unlockWrite(){
		std::unique_lock<std::mutex> lck(mMutext);
		mWriters--;
		mActiverWriters--;
		if (mWriters > 0) {
			mWriterCond.notify_one();
		}
		else {
			mReaderCond.notify_all();
		}
		lck.unlock();
	}

}