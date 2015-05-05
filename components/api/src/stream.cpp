#include "api/stream.hpp"
#include <string>

namespace ssf{

	Stream::Stream(const std::string& moduleIDProvider, const std::string& outputProvider, const std::string& moduleIDReceiver, const std::string inputReceiver){
        this->mModuleIDProvider = moduleIDProvider;
        this->mModuleIDReceiver = moduleIDReceiver;
        this->mOutputProvider = outputProvider;
        this->mInputReceiver = inputReceiver;
	}

	Stream::~Stream(){
		//Destructor
	}

	Stream::Stream(const Stream& rhs){
		//Constructor Copy
	}

	Stream& Stream::operator=(const Stream& rhs){
		if (this != &rhs){
			//code here
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

