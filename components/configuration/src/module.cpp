#include "configuration/module.hpp"
#include <string>
#include <core/parameters.hpp>

namespace ssf{
    
    size_t Module::count = 0;
    
    Module::Module(){
        
    }

	Module::Module(const std::string& name, const std::string& moduleType){
        this->mName = name;
        this->mModuleType = moduleType;
        ++count;
        mID = count;
	}

	Module::~Module(){
	}

	Module::Module(const Module& rhs){
        this->mName = rhs.mName;
        this->mModuleType = rhs.mModuleType;
        mID = count;
    }

	Module& Module::operator=(const Module& rhs){
		if (this != &rhs){
            this->mName = rhs.mName;
            this->mModuleType = rhs.mModuleType;
            mID = count;
		}
	    return *this;
	}
    
    std::string Module::getName(){
        return this->mName;
    }
    
    std::string Module::getType(){
        return this->mModuleType;
    }
    
    size_t Module::getID(){
        return this->mID;
    }
    
    void Module::addParameter(const ParamType& type, const std::string& name, const std::string& description){
        this->mParameters.addParameter(type, name, description);
    }

}

