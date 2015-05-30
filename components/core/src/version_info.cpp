/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this license. If you do 
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without modification, are permitted 
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of 
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
*       conditions and the following disclaimer in the documentation and/or other materials 
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
*       endorse or promote products derived from this software without specific prior written 
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#include "core/version_info.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "core/util.hpp"
#include "core/exception.hpp"

namespace ssf{

	VersionInfo::VersionInfo(const unsigned short& major /*= 0*/, const unsigned short& minor /*= 0*/, const unsigned short& patch /*= 0*/)
		: mMajor(major), mMinor(minor), mPatch(patch){
	}

	VersionInfo::VersionInfo(const std::string& version){
		this->set(version);
	}

	VersionInfo::~VersionInfo(){
	}

	VersionInfo::VersionInfo(const VersionInfo& rhs){
		this->mMajor = rhs.mMajor;
		this->mMinor = rhs.mMinor;
		this->mPatch = rhs.mPatch;
	}

	VersionInfo& VersionInfo::operator=(const VersionInfo& rhs){
		if (this != &rhs){
			this->mMajor = rhs.mMajor;
			this->mMinor = rhs.mMinor;
			this->mPatch = rhs.mPatch;
		}
		return *this;
	}

	unsigned short VersionInfo::major() const{
		return this->mMajor;
	}

	void VersionInfo::setMajor(const unsigned short& major){
		this->mMajor = major;
	}

	unsigned short VersionInfo::minor() const{
		return this->mMinor;
	}

	void VersionInfo::setMinor(const unsigned short& minor){
		this->mMinor = minor;
	}

	unsigned short VersionInfo::patch() const{
		return this->mPatch;
	}

	void VersionInfo::setPatch(const unsigned short& patch){
		this->mPatch = patch;
	}

	void VersionInfo::set(const std::string& version){
		std::vector<std::string> tokens;
		boost::algorithm::split(tokens, version, boost::algorithm::is_any_of(".,"));

		if (tokens.size() == 0 || tokens.size() > 3)
			throw Exception("Invalid Version Format");

		int major = 0, minor = 0, patch = 0;

		try{
			if (tokens.size() >= 3){
				tokens[2] = Util::trim(tokens[2]);
				patch = std::stoi(tokens[2]);
			}

			if (tokens.size() >= 2){
				tokens[1] = Util::trim(tokens[1]);
				minor = std::stoi(tokens[1]);
			}

			if (tokens.size() >= 1){
				tokens[0] = Util::trim(tokens[0]);
				major = std::stoi(tokens[0]);
			}
		}
		catch (const boost::exception& /*e*/){
			throw Exception("Invalid Version Format");
		}
		catch (const std::exception& /*e*/){
			throw Exception("Invalid Version Format");
		}


		this->mMajor = major;
		this->mMinor = minor;
		this->mPatch = patch;

	}

	void VersionInfo::set(const unsigned short& major /*= 0*/, const unsigned short& minor /*= 0*/, const unsigned short& patch /*= 0*/){
		this->mMajor = major;
		this->mMinor = minor;
		this->mPatch = patch;
	}

	std::string VersionInfo::toString() const{
		return std::to_string(this->mMajor) + "." + std::to_string(this->mMinor) + "." + std::to_string(this->mPatch);
	}

	bool VersionInfo::operator==(const VersionInfo& rhs){
		return this->mMajor == rhs.mMajor
			&& this->mMinor == rhs.mMinor
			&& this->mPatch == rhs.mPatch;
	}

	bool VersionInfo::operator!=(const VersionInfo& rhs){
		return !(*(this) == rhs);
	}

	bool VersionInfo::operator<(const VersionInfo& rhs){
		if (this->mMajor < rhs.mMajor)
			return true;
		else if (this->mMajor > rhs.mMajor)
			return false;
		else{
			if (this->mMinor < rhs.mMinor)
				return true;
			else if (this->mMinor > rhs.mMinor)
				return false;
			else
			{
				if (this->mPatch < rhs.mPatch)
					return true;
				else
					return false;
			}
		}
	}

	bool VersionInfo::operator>(const VersionInfo& rhs){
		if (this->mMajor > rhs.mMajor)
			return true;
		else if (this->mMajor < rhs.mMajor)
			return false;
		else
		{
			if (this->mMinor > rhs.mMinor)
				return true;
			else if (this->mMinor < rhs.mMinor)
				return false;
			else
			{
				if (this->mPatch > rhs.mPatch)
					return true;
				else
					return false;
			}
		}
	}

	bool VersionInfo::operator>=(const VersionInfo& rhs){
		return !((*this) < rhs);
	}

	bool VersionInfo::operator<=(const VersionInfo& rhs){
		return !((*this) > rhs);
	}

}



