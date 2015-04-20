#ifndef _SSF_API_SSF_CONFIGURATION_HPP_
#define _SSF_API_SSF_CONFIGURATION_HPP_

#include <string>
#include <vector>
#include <tuple>
#include <map>

enum typeValue{
    INT, FLOAT, DOUBLE, LONG, BOOL, STRING
};

struct parameter{
    
    int value1;
    float value2;
    double value3;
    long value4;
    bool value5;
    std::string value6;
};

namespace ssf{

	class SSFConfiguration{
	
	public:
		SSFConfiguration(void);
		virtual ~SSFConfiguration(void);
		SSFConfiguration(const SSFConfiguration& rhs);
		SSFConfiguration& operator=(const SSFConfiguration& rhs);
        
        void addModule(const std::string& moduleName, const std::string& moduleType);
        

	private:
        std::map<std::string, std::vector< std::pair< std::string, struct parameter > > > mModules;
	};

}
















#endif // !_SSF_API_SSF_CONFIGURATION_HPP_