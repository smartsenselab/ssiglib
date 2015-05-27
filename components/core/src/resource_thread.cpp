//#include "core/resource_thread.hpp"
//
//#include <boost/thread.hpp>
//#include <boost/chrono.hpp>
//#include <iostream>
//
//namespace ssf{
//
//	ResourceThread::ResourceThread(){
//		this->mThread = nullptr;
//	}
//
//	ResourceThread::~ResourceThread(){
//		//Destructor
//	}
//
//	ResourceThread::ResourceThread(const ResourceThread& rhs){
//		//Constructor Copy
//	}
//
//	ResourceThread& ResourceThread::operator=(const ResourceThread& rhs){
//		if (this != &rhs){
//			//code here
//		}
//	    return *this;
//	}
//
//	void ResourceThread::start(){
//		this->mThread = std::make_shared<boost::thread>(boost::bind(&ResourceThread::run, this));
//	}
//	
//	void ResourceThread::stop(){
//		this->mThread->interrupt();
//	}
//
//	void ResourceThread::join(){
//		this->mThread->join();
//	}
//
//	
//
//}
//
