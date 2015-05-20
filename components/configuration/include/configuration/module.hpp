#ifndef _SSF_API_MODULE_HPP_
#define _SSF_API_MODULE_HPP_

#include <string>
#include <core/parameters.hpp>

#include "configuration/configuration_defs.hpp"

namespace ssf{

    class Module{
        
	public:
		CONFIG_EXPORT Module(std::string name, std::string moduleType);
		CONFIG_EXPORT virtual ~Module(void);
		CONFIG_EXPORT Module(const Module& rhs);
		CONFIG_EXPORT Module& operator=(const Module& rhs);
        
		CONFIG_EXPORT void addParameter(const ParamType& type, const std::string& name, const std::string& description);
        
        template < class T>
		CONFIG_EXPORT void setValue(const std::string& paramName, const T& value){
            mParameters[paramName].setValue(value);
        }

	private:
        std::string mName;
        std::string mModuleType;
        Parameters mParameters;
        size_t mID;
        static size_t count;
        
	};

}

#endif // !_SSF_API_MODULE_HPP_