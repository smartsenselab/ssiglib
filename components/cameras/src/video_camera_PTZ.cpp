#include <iostream>
#include "cameras/video_camera_PTZ.hpp"

namespace ssf{

	VideoCameraPTZ::VideoCameraPTZ(const std::string& address)
		: VideoCamera(address){
		this->mMaxTilt = 0;
		this->mMaxZoom = 0;
	}

	VideoCameraPTZ::~VideoCameraPTZ(){
		//Destructor
	}

	VideoCameraPTZ::VideoCameraPTZ(const VideoCameraPTZ& rhs){
		this->mMaxTilt = rhs.mMaxTilt;
		this->mMaxZoom = rhs.mMaxZoom;
	}

	VideoCameraPTZ& VideoCameraPTZ::operator=(const VideoCameraPTZ& rhs){
		if (this != &rhs){
			this->mMaxTilt = rhs.mMaxTilt;
			this->mMaxZoom = rhs.mMaxZoom;
		}
	    return *this;
	}

	float VideoCameraPTZ::getMaxZoom(){
		return this->mMaxZoom;
	}
	
	float VideoCameraPTZ::getMaxTilt(){
		return this->mMaxTilt;
	}

}