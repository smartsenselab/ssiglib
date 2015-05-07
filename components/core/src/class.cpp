#include "core/class.hpp"

namespace ssf{

	Class::Class(){
		//Constructor
	}

	Class::~Class(){
		//Destructor
	}

	Class::Class(const Class& rhs){
		//Constructor Copy
	}

	Class& Class::operator=(const Class& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

