//#include "core/resource.hpp"
//
//namespace ssf{
//
//	Resource::Resource(){
//		this->mAuthor = "Unknown Author";
//		this->mDescription = "No description has been set.";
//		this->mAuthorEmail = "Unknown Email";
//		this->mMajorRequiredVersion = -1;
//		this->mMinorRequiredVersion = -1;
//	}
//
//
//	Resource::~Resource(){
//		//Destructor
//	}
//
//	Resource::Resource(const Resource& rhs){
//		this->mAuthor = rhs.mAuthor;
//		this->mDescription = rhs.mDescription;
//		this->mAuthorEmail = rhs.mAuthorEmail;
//		this->mMajorRequiredVersion = rhs.mMajorRequiredVersion;
//		this->mMinorRequiredVersion = rhs.mMinorRequiredVersion;
//	}
//
//	Resource& Resource::operator=(const Resource& rhs){
//		if (this != &rhs){
//			this->mAuthor = rhs.mAuthor;
//			this->mDescription = rhs.mDescription;
//			this->mAuthorEmail = rhs.mAuthorEmail;
//			this->mMajorRequiredVersion = rhs.mMajorRequiredVersion;
//			this->mMinorRequiredVersion = rhs.mMinorRequiredVersion;
//		}
//		return *this;
//	}
//
//	ssf::ResourceInfo Resource::getInfo(){
//		ResourceInfo info;
//		info.mName = this->getName();
//		info.mAuthor = this->mAuthor;
//		info.mDescription = this->mDescription;
//		info.mAuthorEmail = this->mAuthorEmail;
//		info.mMajorRequiredVersion = this->mMajorRequiredVersion;
//		info.mMinorRequiredVersion = this->mMinorRequiredVersion;
//		info.mParams = this->parameters;
//		
//		return info;
//	}
//
//	void Resource::setup(const ResourceSetup& setup){
//		
//	}
//
//	void Resource::setAuthor(const std::string& author){
//		this->mAuthor = author;
//	}
//
//	void Resource::setDescription(const std::string& description){
//		this->mDescription = description;
//	}
//
//	void Resource::setAuthorEmail(const std::string& authorEmail){
//		this->mAuthorEmail = authorEmail;
//	}
//
//	void Resource::setRequiredVersion(const int& majorVersion, const int& minorVersion){
//		this->mMajorRequiredVersion = majorVersion;
//		this->mMinorRequiredVersion = minorVersion;
//	}
//
//
//
//}
//
