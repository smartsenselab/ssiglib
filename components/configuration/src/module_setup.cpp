#include "configuration/module_setup.hpp"
#include <string>

namespace ssf{
    
    size_t ModuleSetup::count = 0;
    
    ModuleSetup::ModuleSetup(){
        
    }

    ModuleSetup::ModuleSetup(const std::string& moduleName, const std::string& moduleType){
        this->mModuleName = moduleName;
        this->mModuleType = moduleType;
        this->mParametersID = "";
        ++count;
        mID = count;
	}

	ModuleSetup::~ModuleSetup(){
	}

	ModuleSetup::ModuleSetup(const ModuleSetup& rhs){
        this->mModuleName = rhs.mModuleName;
        this->mModuleType = rhs.mModuleType;
        this->mParametersID = rhs.mParametersID;
        mID = count;
    }

	ModuleSetup& ModuleSetup::operator=(const ModuleSetup& rhs){
		if (this != &rhs){
            this->mModuleName = rhs.mModuleName;
            this->mModuleType = rhs.mModuleType;
            this->mParametersID = rhs.mParametersID;
            mID = count;
		}
	    return *this;
	}
    
    std::string ModuleSetup::getName(){
        return this->mModuleName;
    }
    
    std::string ModuleSetup::getType(){
        return this->mModuleType;
    }
    
    size_t ModuleSetup::getID(){
        return this->mID;
    }
    
    std::string ModuleSetup::setParametersID(const std::string& parametersID){
        return this->mParametersID = parametersID;
    }
    
    std::string ModuleSetup::getParametersID(){
        return this->mParametersID;
    }
}

