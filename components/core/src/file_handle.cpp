/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                              License Agreement
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

#include "core/file_handle.hpp"

#include <boost/filesystem.hpp>

#include "core/file_exception.hpp"

namespace ssf{

	FileHandle::FileHandle(){
		this->mPath = std::make_shared<boost::filesystem::path>();
	}

	FileHandle::FileHandle(const std::string& fileName){
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



