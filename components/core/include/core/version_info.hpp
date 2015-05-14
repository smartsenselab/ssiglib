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

#endif // !_SSF_CORE_VERSION_INFO_HPP_