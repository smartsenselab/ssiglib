#include "cameras/video_camera.hpp"

#include <iostream>


namespace ssf{

	VideoCamera::VideoCamera(){
		this->mAddress = "";
	}

	VideoCamera::~VideoCamera(){
		//Destructor
	}

	VideoCamera::VideoCamera(const VideoCamera& rhs){
		this->mAddress = rhs.mAddress;
	}

	VideoCamera& VideoCamera::operator=(const VideoCamera& rhs){
		if (this != &rhs){
			this->mAddress = rhs.mAddress;
		}
		return *this;
	}

	void VideoCamera::setAddress(std::string IP){
		this->mAddress = IP;
	}

	std::string VideoCamera::getAddress(){
		return this->mAddress;
	}

}

