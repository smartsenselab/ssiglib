#ifndef _SSF_API_SSF_CONFIGURATION_HPP_
#define _SSF_API_SSF_CONFIGURATION_HPP_
#include <string>
#include <vector>
#include <map>
#include "configuration/stream_setup.hpp"
#include "configuration/module_setup.hpp"
#include "configuration/setup_exception.hpp"

namespace ssf{
    
    class Setup{
        public:
        CONFIG_EXPORT Setup(void);
		CONFIG_EXPORT virtual ~Setup(void);
        CONFIG_EXPORT Setup(const Setup& rhs);
        CONFIG_EXPORT Setup& operator=(const Setup& rhs);
        
        CONFIG_EXPORT void addModule(const std::string& moduleName, const std::string& moduleType);
        
        CONFIG_EXPORT ModuleSetup& getModule(const std::string& moduleName);
        
        CONFIG_EXPORT void setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput);
        
        CONFIG_EXPORT void writeToFile(const std::string& fileName);
        
        CONFIG_EXPORT void readFromFile();

	private:
        std::map<std::string, ModuleSetup> mModules;
        std::vector<StreamSetup>  mStreams;
	};
}

#endif // !_SSF_API_SSF_CONFIGURATION_HPP_