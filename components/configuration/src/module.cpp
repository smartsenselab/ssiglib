#include "configuration/module.hpp"
#include <string>
#include <core/parameters.hpp>

namespace ssf{
    
    size_t Module::count = 0;

	Module::Module(std::string name, std::string moduleType){
        this->mName = name;
        this->mModuleType = moduleType;
        ++count;
        mID = count;
	}

	Module::~Module(){
		//Destructor
	}

	Module::Module(const Module& rhs){
		//Constructor Copy
	}

	Module& Module::operator=(const Module& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}
    
    void Module::addParameter(const ParamType& type, const std::string& name, const std::string& description){
        this->mParameters.addParameter(type, name, description);
    }

}

