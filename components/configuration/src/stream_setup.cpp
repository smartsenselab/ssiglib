#include "configuration/stream_setup.hpp"
#include <string>

namespace ssf{
    
    StreamSetup::StreamSetup(){
        
    }

	StreamSetup::StreamSetup(const std::string& moduleIDProvider, const std::string& outputProvider, const std::string& moduleIDReceiver, const std::string inputReceiver){
        this->mModuleIDProvider = moduleIDProvider;
        this->mModuleIDReceiver = moduleIDReceiver;
        this->mOutputProvider = outputProvider;
        this->mInputReceiver = inputReceiver;
	}

	StreamSetup::~StreamSetup(){
	}

	StreamSetup::StreamSetup(const StreamSetup& rhs){
        this->mModuleIDProvider = rhs.mModuleIDProvider;
        this->mModuleIDReceiver = rhs.mModuleIDReceiver;
        this->mOutputProvider = rhs.mOutputProvider;
        this->mInputReceiver = rhs.mInputReceiver;

	}

	StreamSetup& StreamSetup::operator=(const StreamSetup& rhs){
		if (this != &rhs){
            this->mModuleIDProvider = rhs.mModuleIDProvider;
            this->mModuleIDReceiver = rhs.mModuleIDReceiver;
            this->mOutputProvider = rhs.mOutputProvider;
            this->mInputReceiver = rhs.mInputReceiver;
            
		}
	    return *this;
	}
    
    std::string StreamSetup::getModuleIDProvider(){
        return mModuleIDProvider;
    }
    std::string StreamSetup::getModuleIDReceiver(){
        return mModuleIDReceiver;
    }
    std::string StreamSetup::getOutputProvider(){
        return mOutputProvider;
    }
    std::string StreamSetup::getInputReceiver(){
        return mInputReceiver;
    }

}

