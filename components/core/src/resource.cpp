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

		for (auto parameter : this->mParamBook.getParameters()){
			ParameterInfo paramInfo;
			if (parameter.second->getType() == ParameterType::INT)
				paramInfo = ParameterInfo(*(std::dynamic_pointer_cast<ParameterValue<int>, IParameter>(parameter.second)));
			else if (parameter.second->getType() == ParameterType::LONG)
				paramInfo = ParameterInfo(*(std::dynamic_pointer_cast<ParameterValue<long>, IParameter>(parameter.second)));
			else if (parameter.second->getType() == ParameterType::FLOAT)
				paramInfo = ParameterInfo(*(std::dynamic_pointer_cast<ParameterValue<float>, IParameter>(parameter.second)));
			else if (parameter.second->getType() == ParameterType::DOUBLE)
				paramInfo = ParameterInfo(*(std::dynamic_pointer_cast<ParameterValue<double>, IParameter>(parameter.second)));
			else if (parameter.second->getType() == ParameterType::BOOL)
				paramInfo = ParameterInfo(*(std::dynamic_pointer_cast<ParameterValue<bool>, IParameter>(parameter.second)));
			else if (parameter.second->getType() == ParameterType::STRING)
				paramInfo = ParameterInfo(*(std::dynamic_pointer_cast<ParameterValue<std::string>, IParameter>(parameter.second)));
			else if (parameter.second->getType() == ParameterType::FILE_HANDLE)
				paramInfo = ParameterInfo(*(std::dynamic_pointer_cast<ParameterValue<FileHandle>, IParameter>(parameter.second)));
			else if (parameter.second->getType() == ParameterType::DIRECTORY_HANDLE)
				paramInfo = ParameterInfo(*(std::dynamic_pointer_cast<ParameterValue<DirectoryHandle>, IParameter>(parameter.second)));
			info.parametersInfo[paramInfo.getName()] = paramInfo;
		}

		return info;
	}

}

