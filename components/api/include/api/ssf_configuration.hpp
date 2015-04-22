#ifndef _SSF_API_SSF_CONFIGURATION_HPP_
#define _SSF_API_SSF_CONFIGURATION_HPP_

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include "param_temp/param_temp.hpp"

namespace ssf{

	class SSFConfiguration{
	
	public:
		SSFConfiguration(void);
		virtual ~SSFConfiguration(void);
		SSFConfiguration(const SSFConfiguration& rhs);
		SSFConfiguration& operator=(const SSFConfiguration& rhs);
        
        void addModule(const std::string& moduleName, const std::string& moduleType);
        
        template <class type>
        void setParam(const std::string& moduleName, type param);
        
        void setStream(const std::string& moduleGiver, const std::string& giverOut, const std::string& moduleReceiver, const std::string& receiverIn);

	private:
        static std::map< std::string, std::vector< std::string > > modules;
        
        static std::map< std::string, std::vector< std::pair< std::string, ParamTemp<class T> > > > parameters;
        
        static std::map< std::string, std::map< std::string, std::vector< std::pair< std::string, std::string > > > > streams;
        
	};
}

#endif // !_SSF_API_SSF_CONFIGURATION_HPP_