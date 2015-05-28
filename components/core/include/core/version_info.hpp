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

#ifndef _SSF_CORE_VERSION_INFO_HPP_
#define _SSF_CORE_VERSION_INFO_HPP_

#include <string>

#include "core/core_defs.hpp"

namespace ssf{

	class CORE_EXPORT VersionInfo{

	public:
		VersionInfo(const unsigned short& major = 0, const unsigned short& minor = 0, const unsigned short& patch = 0);
		explicit VersionInfo(const std::string& version);
		virtual ~VersionInfo(void);
		VersionInfo(const VersionInfo& rhs);
		VersionInfo& operator=(const VersionInfo& rhs);

		unsigned short getMajor() const;
		void setMajor(const unsigned short& major);
		unsigned short getMinor() const;
		void setMinor(const unsigned short& minor);
		unsigned short getPatch() const;
		void setPatch(const unsigned short& patch);

		void set(const unsigned short& major = 0, const unsigned short& minor = 0, const unsigned short& patch = 0);
		void set(const std::string& version);
		std::string toString() const;

		bool operator== (const VersionInfo& rhs);
		bool operator!= (const VersionInfo& rhs);
		bool operator< (const VersionInfo& rhs);
		bool operator> (const VersionInfo& rhs);		
		bool operator<= (const VersionInfo& rhs);
		bool operator>= (const VersionInfo& rhs);
		

	private:
		std::string trim(std::string const& str){
			if (str.empty())
				return str;

			std::size_t first = str.find_first_not_of(' ');
			std::size_t last = str.find_last_not_of(' ');
			return str.substr(first, last - first + 1);
		}

	private:
		unsigned short mMajor;
		unsigned short mMinor;
		unsigned short mPatch;

	};

}

#endif // !_SSF_CORE_VERSION_INFO_HPP_PP_