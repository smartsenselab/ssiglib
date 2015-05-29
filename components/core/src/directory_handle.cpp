/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                   Software License Agreement (BSD License)
*                      For Smart Surveillance Framework
*                        http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, 
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright 
*       notice, this list of conditions and the following disclaimer in the 
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its 
*       contributors may be used to endorse or promote products derived from 
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
*  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#include "core/directory_handle.hpp"

#include <boost/filesystem.hpp>

#include "core/file_exception.hpp"

namespace ssf{

	DirectoryHandle::DirectoryHandle(const std::string& directoryPathName /*= "" */){	
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

	bool DirectoryHandle::operator==(const DirectoryHandle& rhs) const{
		return *(this->mPath) == *(rhs.mPath);
	}

	bool DirectoryHandle::operator!=(const DirectoryHandle& rhs) const{
		return *(this->mPath) != *(rhs.mPath);
	}

	std::string DirectoryHandle::absolutePath() const{
		return this->mPath->string();
	}

	std::string DirectoryHandle::simpleName() const{
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

		if (!this->exists())
			throw FileException(this->mPath->string(), "This directory does not exists.");

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

	bool DirectoryHandle::exists() const{
		return (boost::filesystem::exists(*(this->mPath)) && boost::filesystem::is_directory(*(this->mPath)));
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



