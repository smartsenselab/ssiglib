#include "core/base_object.hpp"

namespace ssf{

	BaseObject::BaseObject(){
		//Constructor
	}

	BaseObject::~BaseObject(){
		//Destructor
	}

	BaseObject::BaseObject(const BaseObject& rhs){
		//Constructor Copy
	}

	BaseObject& BaseObject::operator=(const BaseObject& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

