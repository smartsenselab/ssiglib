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
        modules.insert(std::pair<std::string, Module> (moduleName, Module(moduleName, moduleType)));
        
    }
    
    void SSFConfiguration::setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput){
        streams.push_back(Stream(moduleProvider, providerOutput,  moduleReceiver, receiverInput));
    }
}
