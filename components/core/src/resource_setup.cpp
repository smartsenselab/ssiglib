#include "core/resource_setup.hpp"

namespace ssf{

	ResourceSetup::ResourceSetup(const std::string& resourceName /*= ""*/)
		: mResourceName(resourceName){
		
	}

	ResourceSetup::~ResourceSetup(){
		
	}

	ResourceSetup::ResourceSetup(const ResourceSetup& rhs){
		this->mResourceName = rhs.mResourceName;
		this->mParams = rhs.mParams;
	}

	ResourceSetup& ResourceSetup::operator=(const ResourceSetup& rhs){
		if (this != &rhs){
			this->mResourceName = rhs.mResourceName;
			this->mParams = rhs.mParams;
		}
	    return *this;
	}

}

