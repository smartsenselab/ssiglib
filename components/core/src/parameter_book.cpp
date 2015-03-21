#include "core/parameter_book.hpp"

namespace ssf{

	ParameterBook::ParameterBook(){
		
	}

	ParameterBook::~ParameterBook(){
		
	}
	
	const std::map< std::string, std::shared_ptr<IParameter> >& ParameterBook::getParameters() const{
		return this->mParameters;
	}

}

