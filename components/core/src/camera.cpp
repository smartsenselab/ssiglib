#include "core/camera.hpp"

namespace ssf{

	Camera::Camera(){
		//Constructor
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

