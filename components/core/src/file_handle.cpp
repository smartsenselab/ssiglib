#include "core/file_handle.hpp"

#include <boost/filesystem.hpp>

#include "core/file_exception.hpp"

namespace ssf{

	FileHandle::FileHandle(){
		this->mPath = std::make_shared<boost::filesystem::path>();
	}

	FileHandle::FileHandle(const std::string& fileName){
		if (!boost::filesystem::exists(fileName))
			throw FileException(fileName, "File not found!");

		boost::filesystem::path tempPath(fileName);
		if (tempPath.is_absolute())
			this->mPath = std::make_shared<boost::filesystem::path>(fileName);
		else
			this->mPath = std::make_shared<boost::filesystem::path>(boost::filesystem::current_path() / fileName);

	}

	FileHandle::~FileHandle(){

	}

	FileHandle::FileHandle(const FileHandle& rhs)
		: mPath(rhs.mPath){
	}

	FileHandle& FileHandle::operator=(const FileHandle& rhs){
		if (this != &rhs){
			*(this->mPath) = *(rhs.mPath);
		}
		return *this;
	}

	bool FileHandle::operator<(const FileHandle& rhs) const{
		return this->mPath->string() < rhs.mPath->string();
	}

	std::string FileHandle::getAbsoluteFileName() const{
		return this->mPath->string();
	}

	std::string FileHandle::getSimpleName() const{
		return this->mPath->stem().string();
	}

	std::string FileHandle::getExtenstion() const{
		return this->mPath->extension().string();
	}

	bool FileHandle::erase(){
		return boost::filesystem::remove(*(this->mPath));
	}

	bool FileHandle::hasExtension() const{
		return this->mPath->has_extension();
	}

	bool FileHandle::erase(const std::string& fileName){
		boost::filesystem::path path(fileName);
		return boost::filesystem::remove(path);
	}

	bool FileHandle::exists(const std::string& fileName){
		boost::filesystem::path path(fileName);
		return boost::filesystem::exists(path);
	}


}

