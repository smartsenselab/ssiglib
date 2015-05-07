#include "core/camera.hpp"
#include <iostream>

namespace ssf{

	//Constructor
	Camera::Camera(void){

	}

	Camera::~Camera(){
		//Destructor
	}

	Camera::Camera(const Camera& rhs){
		//Constructor Copy
	}

	Camera& Camera::operator=(const Camera& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

