//#ifndef _SSF_API_SSF_CONFIGURATION_HPP_
//#define _SSF_API_SSF_CONFIGURATION_HPP_
//
//#include <string>
//#include <vector>
//#include <tuple>
//#include <map>
//#include <core/parameters.hpp>
//
//#include "configuration/stream.hpp"
//#include "configuration/module.hpp"
//#include "configuration/configuration_exception.hpp"
//
//namespace ssf{
//    
//    class Configuration{
//	
//	public:
//		CONFIG_EXPORT Configuration(void);
//		CONFIG_EXPORT virtual ~Configuration(void);
//		CONFIG_EXPORT Configuration(const Configuration& rhs);
//		CONFIG_EXPORT Configuration& operator=(const Configuration& rhs);
//        
//		CONFIG_EXPORT void addModule(const std::string& moduleName, const std::string& moduleType);
//		CONFIG_EXPORT Module& getModule(const std::string& moduleName);
//        
//
//		//COMENTAR O PROBLEMA DE ATRIBUTO DESNECESSARIO COM O ROMULO
//        /*template<class T>
//		CONFIG_EXPORT void setParameter(const std::string& moduleType, const std::string& moduleName, const std::string& paramName, ParamType type, T value){
//            if(modules.find(moduleName) == modules.end()){
//                throw ConfigurationException(moduleName, "Module does not exist, create it first before adding parameters to it.");
//            }
//            modules[moduleName].addParameter(type, paramName, "");
//            modules[moduleName].setValue(paramName, value);
//        };*/
//        
//        
//		CONFIG_EXPORT void setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput);
//
//	private:
//        
//        std::map<std::string, Module> mModules;
//        
//        std::vector<Stream>  mStreams;
//        
//	};
//}
//
//#endif // !_SSF_API_SSF_CONFIGURATION_HPP_