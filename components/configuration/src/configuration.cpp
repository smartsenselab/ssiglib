#include "configuration/configuration.hpp"

namespace ssf{

	Configuration::Configuration(){
	}

	Configuration::~Configuration(){
	}

	Configuration::Configuration(const Configuration& rhs){
        this->modules = rhs.modules;
        this->streams = rhs.streams;
	}

	Configuration& Configuration::operator=(const Configuration& rhs){
		if (this != &rhs){
            this->modules = rhs.modules;
            this->streams = rhs.streams;
		}
	    return *this;
	}
    
    void Configuration::addModule(const std::string& moduleName, const std::string& moduleType){
        if(modules.find(moduleName) != modules.end()){
            throw ConfigurationException(moduleName, "Module already added, try another name.");
        }
        modules.insert(std::pair<std::string, Module> (moduleName, Module(moduleName, moduleType)));
    }
    
    void Configuration::setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput){
        
        for(std::vector<Stream>::iterator it = streams.begin(); it != streams.end(); ++it){
            if (it->getModuleIDProvider() == moduleProvider && it->getOutputProvider() == providerOutput && it->getModuleIDReceiver() == moduleReceiver && it->getInputReceiver() == receiverInput){
                throw ConfigurationException(moduleProvider, "Stream already set.");
            }
        }
        
        streams.push_back(Stream(moduleProvider, providerOutput,  moduleReceiver, receiverInput));
    }
}
