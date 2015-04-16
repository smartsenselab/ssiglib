#include "core/parameter_info.hpp"

namespace ssf{

	ParameterInfo::ParameterInfo(){
		//Constructor
	}

	ParameterInfo::~ParameterInfo(){
		//Destructor
	}

	ParameterInfo::ParameterInfo(const ParameterInfo& rhs){
		//Constructor Copy
	}

	ParameterInfo& ParameterInfo::operator=(const ParameterInfo& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

