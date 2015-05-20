#include "configuration/stream.hpp"
#include <string>

namespace ssf{
    
    Stream::Stream(){
        
    }

	Stream::Stream(const std::string& moduleIDProvider, const std::string& outputProvider, const std::string& moduleIDReceiver, const std::string inputReceiver){
        this->mModuleIDProvider = moduleIDProvider;
        this->mModuleIDReceiver = moduleIDReceiver;
        this->mOutputProvider = outputProvider;
        this->mInputReceiver = inputReceiver;
	}

	Stream::~Stream(){
	}

	Stream::Stream(const Stream& rhs){
        this->mModuleIDProvider = rhs.mModuleIDProvider;
        this->mModuleIDReceiver = rhs.mModuleIDReceiver;
        this->mOutputProvider = rhs.mOutputProvider;
        this->mInputReceiver = rhs.mInputReceiver;

	}

	Stream& Stream::operator=(const Stream& rhs){
		if (this != &rhs){
            this->mModuleIDProvider = rhs.mModuleIDProvider;
            this->mModuleIDReceiver = rhs.mModuleIDReceiver;
            this->mOutputProvider = rhs.mOutputProvider;
            this->mInputReceiver = rhs.mInputReceiver;
            
		}
	    return *this;
	}
    
    std::string Stream::getModuleIDProvider(){
        return mModuleIDProvider;
    }
    std::string Stream::getModuleIDReceiver(){
        return mModuleIDReceiver;
    }
    std::string Stream::getOutputProvider(){
        return mOutputProvider;
    }
    std::string Stream::getInputReceiver(){
        return mInputReceiver;
    }

}

