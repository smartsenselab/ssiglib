#include "core/directory_handle.hpp"

#include <boost/filesystem.hpp>

#include "core/file_exception.hpp"

namespace ssf{

	DirectoryHandle::DirectoryHandle(){
		this->mPath = std::make_shared<boost::filesystem::path>();
	}

	DirectoryHandle::DirectoryHandle(const std::string& directoryPathName){
		if (!boost::filesystem::exists(directoryPathName))
			throw FileException(directoryPathName, "Directory not found!");

		if (!boost::filesystem::is_directory(directoryPathName))
			throw FileException(directoryPathName, "This isn't a directory!");

		boost::filesystem::path tempPath(directoryPathName);
		if (tempPath.is_absolute())
			this->mPath = std::make_shared<boost::filesystem::path>(directoryPathName);
		else
			this->mPath = std::make_shared<boost::filesystem::path>(boost::filesystem::current_path() / directoryPathName);
	}

	DirectoryHandle::~DirectoryHandle(){
		//destructor
	}

	DirectoryHandle::DirectoryHandle(const DirectoryHandle& rhs)
		: mPath(rhs.mPath){
	}

	DirectoryHandle& DirectoryHandle::operator=(const DirectoryHandle& rhs){
		if (this != &rhs){
			*this->mPath = *(rhs.mPath);
		}
		return *this;
	}

	bool DirectoryHandle::operator<(const DirectoryHandle& rhs) const{
		return this->mPath->string() < rhs.mPath->string();
	}

	std::string DirectoryHandle::getAbsolutePath() const{
		return this->mPath->string();
	}

	std::string DirectoryHandle::getSimpleName() const{
		return this->mPath->stem().string();
	}

	std::set<DirectoryHandle> DirectoryHandle::listSubDirectories(){
		std::set<DirectoryHandle> list;

		boost::filesystem::directory_iterator end_itr;
		if (boost::filesystem::is_directory(*(this->mPath))) {
			for (boost::filesystem::directory_iterator i(*(this->mPath)); i != end_itr; ++i){
				if (!boost::filesystem::is_directory(i->path()))
					continue;
				list.insert(DirectoryHandle(i->path().string()));
			}
		}

		return list;
	}

	std::set<FileHandle> DirectoryHandle::listFiles(){
		std::set<FileHandle> list;

		boost::filesystem::directory_iterator end_itr;
		if (boost::filesystem::is_directory(*(this->mPath))) {
			for (boost::filesystem::directory_iterator i(*(this->mPath)); i != end_itr; ++i){
				if (!boost::filesystem::is_regular_file(i->path()))
					continue;
				std::string t = i->path().string();
				FileHandle te = FileHandle(i->path().string());
				list.insert(te);
			}
		}

		return list;
	}

	bool DirectoryHandle::isEmpty() const{
		return boost::filesystem::is_empty(*(this->mPath));
	}

	bool DirectoryHandle::erase() const{
		return boost::filesystem::remove(*(this->mPath));
	}

	bool DirectoryHandle::exists(const std::string& directoryPathName){
		return (boost::filesystem::exists(directoryPathName) && boost::filesystem::is_directory(directoryPathName));
	}

	bool DirectoryHandle::erase(const std::string& directoryPathName){
		return boost::filesystem::remove(directoryPathName);
	}

	ssf::DirectoryHandle DirectoryHandle::create(const std::string& directoryPathName){
		boost::filesystem::path tempPath(directoryPathName);
		if (!tempPath.is_absolute()){			
			tempPath = boost::filesystem::current_path();
			tempPath /= directoryPathName;
		}
		boost::filesystem::create_directory(tempPath);
		return DirectoryHandle(directoryPathName);
	}

}

