#ifndef _SSF_CORE_RESOURCE_INFO_HPP_
#define _SSF_CORE_RESOURCE_INFO_HPP_

#include <string>
#include <map>

#include "core/ssfdef.hpp"
#include "core/parameters.hpp"

namespace ssf{

	class ResourceInfo{		
		friend class Resource;

		ResourceInfo(void);

	public:
		SSF_EXPORT virtual ~ResourceInfo(void);
		SSF_EXPORT ResourceInfo(const ResourceInfo& rhs);
		SSF_EXPORT ResourceInfo& operator=(const ResourceInfo& rhs);
	
		SSF_EXPORT std::string getName() const;
		SSF_EXPORT std::string getAuthor() const;
		SSF_EXPORT std::string getDescription() const;
		SSF_EXPORT std::string getAuthorEmail() const;
		SSF_EXPORT std::string getRequiredVersion() const;
		SSF_EXPORT int getMajorRequiredVersion() const;
		SSF_EXPORT int getMinorRequiredVersion() const;
		SSF_EXPORT const std::map<std::string, Parameter>& getParams() const;

	protected:
		std::string mName;
		std::string mAuthor;
		std::string mDescription;
		std::string mAuthorEmail;

		int mMajorRequiredVersion;
		int mMinorRequiredVersion;

		Parameters mParams;

	};

}

#endif // !_SSF_CORE_RESOURCE_INFO_HPP_