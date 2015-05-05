#ifndef _SSF_API_MODULE_HPP_
#define _SSF_API_MODULE_HPP_

#include <string>
#include <core/parameters.hpp>

namespace ssf{

    class Module{
        
	public:
        Module(std::string name, std::string moduleType);
		virtual ~Module(void);
		Module(const Module& rhs);
		Module& operator=(const Module& rhs);
        
        void addParameter(const ParamType& type, const std::string& name, const std::string& description);
        
        template < class T>
        void setValue(const std::string& paramName, const T& value){
            mParameters.setValue(paramName, value);
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