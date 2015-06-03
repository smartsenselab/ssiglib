#ifndef _SSF_API_MODULE_HPP_
#define _SSF_API_MODULE_HPP_
#include <string>
#include "configuration/setup_defs.hpp"

namespace ssf{

    class ModuleSetup{
        
	public:
        CONFIG_EXPORT ModuleSetup();
        CONFIG_EXPORT ModuleSetup(const std::string& moduleName, const std::string& moduleType);
		CONFIG_EXPORT virtual ~ModuleSetup(void);
		CONFIG_EXPORT ModuleSetup(const ModuleSetup& rhs);
        CONFIG_EXPORT ModuleSetup& operator=(const ModuleSetup& rhs);
        CONFIG_EXPORT std::string getName();
        CONFIG_EXPORT std::string getType();
        CONFIG_EXPORT size_t getID();
        CONFIG_EXPORT std::string setParametersID(const std::string& paramtersID);
        CONFIG_EXPORT std::string getParametersID();

	private:
        
        std::string mModuleName;
        std::string mModuleType;
        std::string mParametersID;
        size_t mID;
        static size_t count;
        
	};

}

#endif // !_SSF_API_MODULE_HPP_