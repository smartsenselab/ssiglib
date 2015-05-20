#ifndef _SSF_CORE_RESOURCE_INFO_HPP_
#define _SSF_CORE_RESOURCE_INFO_HPP_

#include <string>
#include <map>

#include "core/core_defs.hpp"
#include "core/version_info.hpp"
#include "core/parameters.hpp"

namespace ssf{

	class ResourceInfo{		
		friend class Resource;

		ResourceInfo(void);

	public:
		CORE_EXPORT virtual ~ResourceInfo(void);
		CORE_EXPORT ResourceInfo(const ResourceInfo& rhs);
		CORE_EXPORT ResourceInfo& operator=(const ResourceInfo& rhs);
	
		CORE_EXPORT std::string getAuthor() const;
		CORE_EXPORT std::string getDescription() const;
		CORE_EXPORT std::string getAuthorEmail() const;
		CORE_EXPORT VersionInfo getRequiredVersion() const;

		CORE_EXPORT std::string getProperty(const std::string& propertyName);

	protected:
		CORE_EXPORT void setAuthor(const std::string& author);
		CORE_EXPORT void setDescription(const std::string& description);
		CORE_EXPORT void setAuthorEmail(const std::string& email);
		CORE_EXPORT void setRequiredVersion(const VersionInfo& version);

		CORE_EXPORT void setProperty(const std::string& propertyName, const std::string& propertyValue);


	protected:
		std::string mAuthor;
		std::string mDescription;
		std::string mAuthorEmail;
		VersionInfo mRequiredVersion;

		std::map<std::string, std::string> mProperties;

	};

}

#endif // !_SSF_CORE_RESOURCE_INFO_HPP_