#include "configuration/configuration.hpp"

namespace ssf{

	Configuration::Configuration(){
	}

	Configuration::~Configuration(){
	}

	Configuration::Configuration(const Configuration& rhs){
        this->mModules = rhs.mModules;
        this->mStreams = rhs.mStreams;
	}

	Configuration& Configuration::operator=(const Configuration& rhs){
		if (this != &rhs){
            this->mModules = rhs.mModules;
            this->mStreams = rhs.mStreams;
		}
	    return *this;
	}
    
    void Configuration::addModule(const std::string& moduleName, const std::string& moduleType){
        if(mModules.find(moduleName) != mModules.end()){
            throw ConfigurationException(moduleName, "Module already added, try another name.");
        }
        mModules.insert(std::pair<std::string, Module> (moduleName, Module(moduleName, moduleType)));
    }
    
	Module& Configuration::getModule(const std::string& moduleName){
		if (mModules.find(moduleName) == mModules.end()){
			throw ConfigurationException(moduleName, "Module does not exist.");
		}
		return this->mModules[moduleName];
	}

	void Configuration::setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput){
        
        for(std::vector<Stream>::iterator it = mStreams.begin(); it != mStreams.end(); ++it){
            if (it->getModuleIDProvider() == moduleProvider && it->getOutputProvider() == providerOutput && it->getModuleIDReceiver() == moduleReceiver && it->getInputReceiver() == receiverInput){
                throw ConfigurationException(moduleProvider, "Stream already set.");
            }
        }        
        mStreams.push_back(Stream(moduleProvider, providerOutput,  moduleReceiver, receiverInput));
    }
}
