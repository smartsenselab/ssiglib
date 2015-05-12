#ifndef _SSF_API_SSF_CONFIGURATION_HPP_
#define _SSF_API_SSF_CONFIGURATION_HPP_

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <core/parameters.hpp>
#include "api/stream.hpp"
#include "api/module.hpp"

namespace ssf{
    
    class SSFConfiguration{
	
	public:
		SSFConfiguration(void);
		virtual ~SSFConfiguration(void);
		SSFConfiguration(const SSFConfiguration& rhs);
		SSFConfiguration& operator=(const SSFConfiguration& rhs);
        
        void addModule(const std::string& moduleName, const std::string& moduleType);
        
        template<class T>
        void setParameter(const std::string& moduleType, const std::string& moduleName, const std::string& paramName, ParamType type, T value){
            if(modules.find(moduleName) == modules.end()){
                APIException(moduleName, "Module does not exist, create it first before adding parameters to it.");
            }
            modules[moduleName].addParameter(type, paramName, "");
            modules[moduleName].setValue(paramName, value);
        };
        
        
        void setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput);

	private:
        
        std::map<std::string, Module> modules;
        
        std::vector<Stream>  streams;
        
	};
}

#endif // !_SSF_API_SSF_CONFIGURATION_HPP_