//#include "core/resource.hpp"
//
//namespace ssf{
//
//	Resource::Resource(){
//
//	}
//
//	Resource::~Resource(){
//		//Destructor
//	}
//
//	Resource::Resource(const Resource& rhs){
//		this->mResourceInfo = rhs.mResourceInfo;
//		this->PARAMETERS = rhs.PARAMETERS;		
//	}
//
//	Resource& Resource::operator=(const Resource& rhs){
//		if (this != &rhs){
//			this->mResourceInfo = rhs.mResourceInfo;
//			this->PARAMETERS = rhs.PARAMETERS;
//		}
//		return *this;
//	}
//
//	ssf::ResourceInfo Resource::getInfo(){
//		return this->mResourceInfo;
//	}
//
//	const std::map<std::string, Parameter>& Resource::getParameters() const{
//		return this->PARAMETERS.getParameters();
//	}
//
//	void Resource::setAuthor(const std::string& author){
//		this->mResourceInfo.setAuthor(author);
//	}
//
//	void Resource::setDescription(const std::string& description){
//		this->mResourceInfo.setDescription(description);
//	}
//
//	void Resource::setAuthorEmail(const std::string& authorEmail){
//		this->mResourceInfo.setAuthorEmail(authorEmail);
//	}
//
//	void Resource::setRequiredVersion(const unsigned short& major, const unsigned short& minor /*= 0*/, const unsigned short& patch /*= 0*/){
//		this->mResourceInfo.setRequiredVersion(VersionInfo(major, minor, patch));
//	}
//
//	void Resource::setRequiredVersion(const VersionInfo& version){
//		this->mResourceInfo.setRequiredVersion(version);
//	}
//
//	void Resource::setProperty(const std::string& propertyName, const std::string& propertyValue){
//		this->mResourceInfo.setProperty(propertyName, propertyValue);
//	}
//
//}
//
