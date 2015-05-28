#include "cameras/ip_camera.hpp"
#include <iostream>

namespace ssf{

	//Constructor
	IPCamera::IPCamera(void){

	}

	IPCamera::~IPCamera(){
		//Destructor
	}

	IPCamera::IPCamera(const IPCamera& rhs){
		//Constructor Copy
	}

	IPCamera& IPCamera::operator=(const IPCamera& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

