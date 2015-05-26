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

	Mutex::Mutex(const Mutex& rhs){
		//code here
	}

	Mutex& Mutex::operator=(const Mutex& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

