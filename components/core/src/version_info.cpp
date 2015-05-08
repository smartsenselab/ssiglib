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

	unsigned short VersionInfo::getMajor() const{
		return this->mMajor;
	}

	void VersionInfo::setMajor(const unsigned short& major){
		this->mMajor = major;
	}

	unsigned short VersionInfo::getMinor() const{
		return this->mMinor;
	}

	void VersionInfo::setMinor(const unsigned short& minor){
		this->mMinor = minor;
	}

	unsigned short VersionInfo::getPatch() const{
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

		int major, minor, patch = 0;

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

