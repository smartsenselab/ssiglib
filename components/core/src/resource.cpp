#include "core/resource.hpp"

namespace ssf{

	Resource::Resource(){
		this->mName = "";
		this->mAuthor = "Unknown Author";
		this->mDescription = "No description has been set.";
		this->mAuthorEmail = "Unknown Email";
		this->mMajorRequiredVersion = -1;
		this->mMinorRequiredVersion = -1;
	}


	Resource::~Resource(){
		//Destructor
	}

	Resource::Resource(const Resource& rhs){
		this->mName = rhs.mName;
		this->mAuthor = rhs.mAuthor;
		this->mDescription = rhs.mDescription;
		this->mAuthorEmail = rhs.mAuthorEmail;
		this->mMajorRequiredVersion = rhs.mMajorRequiredVersion;
		this->mMinorRequiredVersion = rhs.mMinorRequiredVersion;
	}

	Resource& Resource::operator=(const Resource& rhs){
		if (this != &rhs){
			this->mName = rhs.mName;
			this->mAuthor = rhs.mAuthor;
			this->mDescription = rhs.mDescription;
			this->mAuthorEmail = rhs.mAuthorEmail;
			this->mMajorRequiredVersion = rhs.mMajorRequiredVersion;
			this->mMinorRequiredVersion = rhs.mMinorRequiredVersion;
		}
		return *this;
	}

	ssf::ResourceInfo Resource::getInfo() const{
		ResourceInfo info;
		info.mName = this->mName;
		info.mAuthor = this->mAuthor;
		info.mDescription = this->mDescription;
		info.mAuthorEmail = this->mAuthorEmail;
		info.mMajorRequiredVersion = this->mMajorRequiredVersion;
		info.mMinorRequiredVersion = this->mMinorRequiredVersion;
		/*info.mParams = this->mParams;*/
		
		return info;
	}

}

