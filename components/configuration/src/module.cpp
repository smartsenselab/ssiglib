//#include "configuration/module.hpp"
//#include <string>
//#include <core/parameters.hpp>
//
//namespace ssf{
//    
//    size_t Module::count = 0;
//    
//    Module::Module(){
//        
//    }
//
//	Module::Module(const std::string& moduleName, const std::string& moduleType){
//        this->mModuleName = moduleName;
//        this->mModuleType = moduleType;
//        ++count;
//        mID = count;
//	}
//
//	Module::~Module(){
//	}
//
//	Module::Module(const Module& rhs){
//        this->mModuleName = rhs.mModuleName;
//        this->mModuleType = rhs.mModuleType;
//        mID = count;
//    }
//
//	Module& Module::operator=(const Module& rhs){
//		if (this != &rhs){
//            this->mModuleName = rhs.mModuleName;
//            this->mModuleType = rhs.mModuleType;
//            mID = count;
//		}
//	    return *this;
//	}
//    
//    std::string Module::getName(){
//        return this->mModuleName;
//    }
//    
//    std::string Module::getType(){
//        return this->mModuleType;
//    }
//    
//    size_t Module::getID(){
//        return this->mID;
//    }
//    
//	void Module::addParameter(const std::string& parameterName, const int& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const long& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const long long& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const unsigned int& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const unsigned long& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const float& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const double& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const bool& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const char* value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const std::string& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const FileHandle& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::addParameter(const std::string& parameterName, const DirectoryHandle& value){
//		this->genericAddParameter(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const int& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const long& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const long long& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const unsigned int& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const unsigned long& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const float& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const double& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const bool& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const char* value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const std::string& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const FileHandle& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//	void Module::setParameterValue(const std::string& parameterName, const DirectoryHandle& value){
//		this->genericSetParameterValue(parameterName, value);
//	}
//
//}
//
