#include "core/conditional_mutex.hpp"

namespace ssf{

	ConditionalMutex::ConditionalMutex(const bool& ready /*= false*/){
		std::unique_lock<std::mutex> ulk(this->mMutex);
		this->mReadyStatus = ready;
	}

	ConditionalMutex::~ConditionalMutex(){
		//Destructor
	}

	void ConditionalMutex::unready(){
		std::unique_lock<std::mutex> ulk(this->mMutex);
		this->mReadyStatus = false;
		this->mConditionVariable.notify_all();
	}

	void ConditionalMutex::ready(){
		std::unique_lock<std::mutex> ulk(this->mMutex);
		this->mReadyStatus = true;
		this->mConditionVariable.notify_all();
	}

	void ConditionalMutex::waitForReady(){
		std::unique_lock<std::mutex> ulk(this->mMutex);
		while (!this->mReadyStatus)
			this->mConditionVariable.wait(ulk);
	}

}