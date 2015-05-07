#include "core/VideoCamera.hpp"
#include <iostream>


namespace ssf{


	VideoCamera::VideoCamera(){
		//Constructor
	}

	VideoCamera::~VideoCamera(){
		//Destructor
	}

	VideoCamera::VideoCamera(const VideoCamera& rhs){
		//Constructor Copy
	}

	VideoCamera& VideoCamera::operator=(const VideoCamera& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

