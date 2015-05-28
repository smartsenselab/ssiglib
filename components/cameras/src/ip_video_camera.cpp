#include "cameras/ip_video_camera.hpp"
#include <iostream>

namespace ssf{

	IPVideoCamera::IPVideoCamera(const std::string& address /*=localhost*/)
		: mAddress(address){

	}

	IPVideoCamera::~IPVideoCamera(){
		//Destructor
	}

	IPVideoCamera::IPVideoCamera(const IPVideoCamera& rhs){
		this->mAddress = rhs.mAddress;
	}

	IPVideoCamera& IPVideoCamera::operator=(const IPVideoCamera& rhs){
		if (this != &rhs){
			this->mAddress = rhs.mAddress;
		}
		return *this;
	}

	void IPVideoCamera::setAddress(std::string IP){
		this->mAddress = IP;
	}

	std::string IPVideoCamera::getAddress(){
		return this->mAddress;
	}

}

