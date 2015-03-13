#include "core/parameter_manager.hpp"

namespace ssf{

	ParameterManager::ParameterManager(){
		//Constructor
	}

	ParameterManager::~ParameterManager(){
		//Destructor
	}

	ParameterManager::ParameterManager(const ParameterManager& rhs){
		//Constructor Copy
	}

	ParameterManager& ParameterManager::operator=(const ParameterManager& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

