#include "core/int_parameter.hpp"

namespace ssf{

	IntParameter::IntParameter(const int& defaultValue, const std::string& description)
		: Parameter(defaultValue, description){
		
	}

	IntParameter::~IntParameter(){
		//Destructor
	}

	IntParameter::IntParameter(const IntParameter& rhs)
		:Parameter(rhs){
	}

	IntParameter& IntParameter::operator=(const IntParameter& rhs){
		if (this != &rhs){
			Parameter::operator=(rhs);
		}
	    return *this;
	}

	ParamType IntParameter::getParamType(){
		return ParamType::INT;
	}

}

