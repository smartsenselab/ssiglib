#include "core/numeric_parameter.hpp"

namespace ssf{

	IntegerParameter::IntegerParameter(const long long& defaultValue, const std::string& name, const std::string& description, const bool& required)
		: NumericParameter(defaultValue, name, description, required){
		
	}

	IntegerParameter::~IntegerParameter(){
		//Destructor
	}

	IntegerParameter::IntegerParameter(const IntegerParameter& rhs)
		:NumericParameter(rhs){
	}

	IntegerParameter& IntegerParameter::operator=(const IntegerParameter& rhs){
		if (this != &rhs){
			NumericParameter::operator=(rhs);
		}
	    return *this;
	}

	ParamTypeID IntegerParameter::getParamType() const{
		return ParamTypeID::INTEGER;
	}



	RealParameter::RealParameter(const double& defaultValue, const std::string& name, const std::string& description, const bool& required)
		: NumericParameter(defaultValue, name, description, required){
	}

	RealParameter::~RealParameter(){
		//Destructor
	}

	RealParameter::RealParameter(const RealParameter& rhs)
		:NumericParameter(rhs){
	}

	RealParameter& RealParameter::operator=(const RealParameter& rhs){
		if (this != &rhs){
			NumericParameter::operator=(rhs);
		}
		return *this;
	}

	ParamTypeID RealParameter::getParamType() const{
		return ParamTypeID::REAL;
	}
}

