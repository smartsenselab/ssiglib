#include "cameras/ip_video_camera_PTZ.hpp"
#include <iostream>


namespace ssf{

	IPVideoCameraPTZ::IPVideoCameraPTZ(const std::string& address)
		: IPVideoCamera(address){
		this->mMaxTilt = 0;
		this->mMaxZoom = 0;
	}

	IPVideoCameraPTZ::~IPVideoCameraPTZ(){
		//Destructor
	}

	IPVideoCameraPTZ::IPVideoCameraPTZ(const IPVideoCameraPTZ& rhs){
		this->mMaxTilt = rhs.mMaxTilt;
		this->mMaxZoom = rhs.mMaxZoom;
	}

	IPVideoCameraPTZ& IPVideoCameraPTZ::operator=(const IPVideoCameraPTZ& rhs){
		if (this != &rhs){
			this->mMaxTilt = rhs.mMaxTilt;
			this->mMaxZoom = rhs.mMaxZoom;
		}
	    return *this;
	}

	float IPVideoCameraPTZ::getMaxZoom(){
		return this->mMaxZoom;
	}
	
	float IPVideoCameraPTZ::getMaxTilt(){
		return this->mMaxTilt;
	}

}