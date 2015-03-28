#include "core/resource_info.hpp"

namespace ssf{

	ResourceInfo::ResourceInfo(){
		
	}

	ResourceInfo::~ResourceInfo(){
		//Destructor
	}

	ResourceInfo::ResourceInfo(const ResourceInfo& rhs){
		this->mName = rhs.mName;
		this->mAuthor = rhs.mAuthor;
		this->mDescription = rhs.mDescription;
		this->mAuthorEmail = rhs.mAuthorEmail;
		this->mMajorRequiredVersion = rhs.mMajorRequiredVersion;
		this->mMinorRequiredVersion = rhs.mMinorRequiredVersion;
		this->mParams = rhs.mParams;
	}

	ResourceInfo& ResourceInfo::operator=(const ResourceInfo& rhs){
		if (this != &rhs){
			this->mName = rhs.mName;
			this->mAuthor = rhs.mAuthor;
			this->mDescription = rhs.mDescription;
			this->mAuthorEmail = rhs.mAuthorEmail;
			this->mMajorRequiredVersion = rhs.mMajorRequiredVersion;
			this->mMinorRequiredVersion = rhs.mMinorRequiredVersion;
			this->mParams = rhs.mParams;
		}
		return *this;
	}	

	std::string ResourceInfo::getName() const{
		return this->mName;
	}

	std::string ResourceInfo::getAuthor() const{
		return this->mAuthor;
	}

	std::string ResourceInfo::getDescription() const{
		return this->mDescription;
	}

	std::string ResourceInfo::getAuthorEmail() const{
		return this->mAuthorEmail;
	}
	
	std::string ResourceInfo::getRequiredVersion() const{
		return (std::to_string(this->mMajorRequiredVersion) + "." + std::to_string(this->mMinorRequiredVersion));
	}

	int ResourceInfo::getMajorRequiredVersion() const{
		return this->mMajorRequiredVersion;
	}

	int ResourceInfo::getMinorRequiredVersion() const{
		return this->mMinorRequiredVersion;
	}

	std::map<std::string, Param> ResourceInfo::getParams() const{
		return this->mParams.getParameters();
	}

}

