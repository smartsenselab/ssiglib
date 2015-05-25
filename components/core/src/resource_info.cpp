//#include "core/resource_info.hpp"
//
//#include "core/exception.hpp"
//
//namespace ssf{
//
//	ResourceInfo::ResourceInfo(){
//		this->mAuthor = "Unknown Author";
//		this->mDescription = "Description not available";
//		this->mAuthorEmail = "Unknown Author Email";
//	}
//
//	ResourceInfo::~ResourceInfo(){
//		//Destructor
//	}
//
//	ResourceInfo::ResourceInfo(const ResourceInfo& rhs){
//		this->mAuthor = rhs.mAuthor;
//		this->mDescription = rhs.mDescription;
//		this->mAuthorEmail = rhs.mAuthorEmail;
//		this->mRequiredVersion = rhs.mRequiredVersion;
//		this->mProperties = rhs.mProperties;
//	}
//
//	ResourceInfo& ResourceInfo::operator=(const ResourceInfo& rhs){
//		if (this != &rhs){
//			this->mAuthor = rhs.mAuthor;
//			this->mDescription = rhs.mDescription;
//			this->mAuthorEmail = rhs.mAuthorEmail;
//			this->mRequiredVersion = rhs.mRequiredVersion;
//			this->mProperties = rhs.mProperties;
//		}
//		return *this;
//	}
//
//	std::string ResourceInfo::getAuthor() const{
//		return this->mAuthor;
//	}
//
//	std::string ResourceInfo::getDescription() const{
//		return this->mDescription;
//	}
//
//	std::string ResourceInfo::getAuthorEmail() const{
//		return this->mAuthorEmail;
//	}
//
//	VersionInfo ResourceInfo::getRequiredVersion() const{
//		return this->mRequiredVersion;
//	}
//
//	std::string ResourceInfo::getProperty(const std::string& propertyName){
//		if (this->mProperties.find(propertyName) == this->mProperties.end()){
//			std::string message = "Does not exists a property with name \"" + propertyName + "\".";
//			throw Exception(message);
//		}
//		return this->mProperties[propertyName];
//	}
//
//	void ResourceInfo::setAuthor(const std::string& author){
//		this->mAuthor = author;
//	}
//
//	void ResourceInfo::setDescription(const std::string& description){
//		this->mDescription = description;
//	}
//
//	void ResourceInfo::setAuthorEmail(const std::string& email){
//		this->mAuthorEmail = email;
//	}
//
//	void ResourceInfo::setRequiredVersion(const VersionInfo& version){
//		this->mRequiredVersion = version;
//	}
//
//	void ResourceInfo::setProperty(const std::string& propertyName, const std::string& propertyValue){
//		this->mProperties[propertyName] = propertyValue;
//	}
//
//}
//
