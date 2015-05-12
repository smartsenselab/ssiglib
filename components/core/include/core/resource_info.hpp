#ifndef _SSF_CORE_RESOURCE_INFO_HPP_
#define _SSF_CORE_RESOURCE_INFO_HPP_

#include <string>
#include <map>

#include "core/core_defs.hpp"
#include "core/parameters.hpp"

namespace ssf{

	class ResourceInfo{		
		friend class Resource;

		ResourceInfo(void);

	public:
		CORE_EXPORT virtual ~ResourceInfo(void);
		CORE_EXPORT ResourceInfo(const ResourceInfo& rhs);
		CORE_EXPORT ResourceInfo& operator=(const ResourceInfo& rhs);
	
		CORE_EXPORT std::string getName() const;
		CORE_EXPORT std::string getAuthor() const;
		CORE_EXPORT std::string getDescription() const;
		CORE_EXPORT std::string getAuthorEmail() const;
		CORE_EXPORT std::string getRequiredVersion() const;
		CORE_EXPORT int getMajorRequiredVersion() const;
		CORE_EXPORT int getMinorRequiredVersion() const;
		CORE_EXPORT const std::map<std::string, Parameter>& getParams() const;

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