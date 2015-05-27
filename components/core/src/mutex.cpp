#include "core/mutex.hpp"

namespace ssf{

	Mutex::Mutex(){
		//Constructor
	}

	Mutex::~Mutex(){
		//Destructor
	}

	void Mutex::lock(){
		this->mLock.lock();
	}

	void Mutex::unlock(){
		this->mLock.unlock();
	}

}

