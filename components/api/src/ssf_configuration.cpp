#include "api/ssf_configuration.hpp"

namespace ssf{

	SSFConfiguration::SSFConfiguration(){
		//Constructor
	}

	SSFConfiguration::~SSFConfiguration(){
		//Destructor
	}

	SSFConfiguration::SSFConfiguration(const SSFConfiguration& rhs){
		//Constructor Copy
	}

	SSFConfiguration& SSFConfiguration::operator=(const SSFConfiguration& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}
    
    void SSFConfiguration::addModule(const std::string& moduleName, const std::string& moduleType){
        if(modules.find(moduleName) != modules.end()){
            APIException(moduleName, "Module already added, try another name.");
        }
        
        modules.insert(std::pair<std::string, Module> (moduleName, Module(moduleName, moduleType)));

        
    }
    
    void SSFConfiguration::setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput){
        
        for(std::vector<Stream>::iterator it = streams.begin(); it != streams.end(); ++it){
            if (it->getModuleIDProvider() == moduleProvider && it->getOutputProvider() == providerOutput && it->getModuleIDReceiver() == moduleReceiver && it->getInputReceiver() == receiverInput){
                APIException(moduleProvider, "Stream already set.");
            }
        }
        streams.push_back(Stream(moduleProvider, providerOutput,  moduleReceiver, receiverInput));
    }
}
