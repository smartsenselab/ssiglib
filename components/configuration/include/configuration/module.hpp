//#ifndef _SSF_API_MODULE_HPP_
//#define _SSF_API_MODULE_HPP_
//
//#include <string>
//#include <core/parameters.hpp>
//
//#include "configuration/configuration_defs.hpp"
//
//namespace ssf{
//
//    class Module{
//        
//	public:
//        CONFIG_EXPORT Module();
//		CONFIG_EXPORT Module(const std::string& moduleName, const std::string& moduleType);
//		CONFIG_EXPORT virtual ~Module(void);
//		CONFIG_EXPORT Module(const Module& rhs);
//		CONFIG_EXPORT Module& operator=(const Module& rhs);
//        
//        CONFIG_EXPORT std::string getName();
//        
//        CONFIG_EXPORT std::string getType();
//        
//        CONFIG_EXPORT size_t getID();
//        
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const int& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const long& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const long long& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const unsigned int& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const unsigned long& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const float& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const double& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const bool& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const char* value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const std::string& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const FileHandle& value);
//		CONFIG_EXPORT void addParameter(const std::string& parameterName, const DirectoryHandle& value);
//
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const int& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const long& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const long long& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const unsigned int& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const unsigned long& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const float& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const double& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const bool& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const char* value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const std::string& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const FileHandle& value);
//		CONFIG_EXPORT void setParameterValue(const std::string& parameterName, const DirectoryHandle& value);
//
//	private:
//		template<class T>
//		void genericAddParameter(const std::string& parameterName, const T& value){
//			Parameter param(parameterName, "");
//			param.setValue(value);
//			this->mParameters.addParameter(param);
//		}
//
//		template<class T>
//		void genericSetParameterValue(const std::string& parameterName, const T& value){
//			this->mParameters[parameterName].setValue(value);
//		}
//
//        std::string mModuleName;
//        std::string mModuleType;
//        Parameters mParameters;
//        size_t mID;
//        static size_t count;
//        
//	};
//
//}
//
//#endif // !_SSF_API_MODULE_HPP_