#include "configuration/setup.hpp"
#include "opencv2/opencv.hpp"
#include <map>
#include <vector>

namespace ssf{

	Setup::Setup(){
	}

	Setup::~Setup(){
    }

	Setup::Setup(const Setup& rhs){
        this->mModules = rhs.mModules;
        this->mStreams = rhs.mStreams;
	}

	Setup& Setup::operator=(const Setup& rhs){
		if (this != &rhs){
            this->mModules = rhs.mModules;
            this->mStreams = rhs.mStreams;
		}
	    return *this;
	}
    
    void Setup::addModule(const std::string& moduleName, const std::string& moduleType){
       if(mModules.find(moduleName) != mModules.end()){
            throw SetupException(moduleName, "Module already added, try another name.");
        }
        mModules.insert(std::pair<std::string, ModuleSetup> (moduleName, ModuleSetup(moduleName, moduleType)));
    }
    
	ModuleSetup& Setup::getModule(const std::string& moduleName){
		if (mModules.find(moduleName) == mModules.end()){
			throw SetupException(moduleName, "Module does not exist.");
		}
		return this->mModules[moduleName];
	}

	void Setup::setStream(const std::string& moduleProvider, const std::string& providerOutput, const std::string& moduleReceiver, const std::string& receiverInput){
        
        for(std::vector<StreamSetup>::iterator it = mStreams.begin(); it != mStreams.end(); ++it){
            if (it->getModuleIDProvider() == moduleProvider && it->getOutputProvider() == providerOutput && it->getModuleIDReceiver() == moduleReceiver && it->getInputReceiver() == receiverInput){
                throw SetupException(moduleProvider, "Stream already set.");
            }
        }
        mStreams.push_back(StreamSetup(moduleProvider, providerOutput,  moduleReceiver, receiverInput));
    }
    
    void Setup::writeToFile(const std::string& fileName){
        cv::FileStorage out(fileName + ".yml", cv::FileStorage::WRITE);
        
        out << "modules" << "[";
        for(std::map<std::string, ModuleSetup>::iterator it = mModules.begin(); it != mModules.end(); ++it){
            
            out << "{:" << "name" << it->first << "type" << it->second.getType();
            out << "}";
        }
        out << "]";
        
        out<< "streams" << "[";
        for(std::vector<StreamSetup>::iterator it2 = mStreams.begin(); it2 != mStreams.end(); ++it2){
            
            out << "{:" << "provider" << it2->getModuleIDProvider() << "receiver" << it2->getModuleIDReceiver() << "output/input" << "[:";
            out << it2->getOutputProvider() << it2->getInputReceiver();
            out << "]" << "}";
        }
        
        out << "]";
    }
}
