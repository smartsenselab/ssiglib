#include "core/file_info.hpp"

#include <boost/filesystem.hpp>

namespace ssf{

	FileInfo::FileInfo(){
		
	}

	FileInfo::FileInfo(const std::string& fileName){
		boost::filesystem::path path(fileName);
		if (!path.is_absolute())
			this->mPath = new boost::filesystem::path(boost::filesystem::current_path() / fileName);
	}

	FileInfo::~FileInfo(){
		delete this->mPath;
	}

	FileInfo::FileInfo(const FileInfo& rhs)
		: mPath(rhs.mPath){		
	}

	FileInfo& FileInfo::operator=(const FileInfo& rhs){
		*this->mPath = *(rhs.mPath);
	    return *this;
	}

	std::string FileInfo::getAbsoluteFileName() const{
		return this->mPath->string();
	}

	std::string FileInfo::getExtenstion() const{
		return this->mPath->extension().string();
	}

	bool FileInfo::erase(){
		return boost::filesystem::remove(*(this->mPath));
	}

	bool FileInfo::erase(const std::string fileName){
		boost::filesystem::path path(fileName);
		return boost::filesystem::remove(path);
	}

	bool FileInfo::exists(){
		return boost::filesystem::exists(*(this->mPath));
	}

	bool FileInfo::exists(const std::string fileName){
		boost::filesystem::path path(fileName);
		return boost::filesystem::exists(path);
	}

	bool FileInfo::hasExtension(){
		return this->mPath->has_extension();
	}

}

