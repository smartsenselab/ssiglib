#ifndef _SSF_CORE_RESOURCE_HPP_
#define _SSF_CORE_RESOURCE_HPP_

#include "core/core_defs.hpp"
#include "core/base_object.hpp"
#include "core/parameters.hpp"
#include "core/resource_info.hpp"

namespace ssf{

	class Resource : public BaseObject{

	public:
		CORE_EXPORT Resource(void);
		CORE_EXPORT virtual ~Resource(void);
		CORE_EXPORT Resource(const Resource& rhs);
		CORE_EXPORT Resource& operator=(const Resource& rhs);

		CORE_EXPORT virtual std::string getName() = 0;
		CORE_EXPORT virtual std::string getType() = 0;
		
		CORE_EXPORT virtual ResourceInfo getInfo();
		CORE_EXPORT virtual void setup(const std::string& paramFile, const std::string& nodeID);
		CORE_EXPORT virtual void setup(const FileHandle& paramFile, const std::string& nodeID);
		CORE_EXPORT virtual void setup(const ParametersSetup& paramSetup);

	protected:		
		CORE_EXPORT virtual void setAuthor(const std::string& author);
		CORE_EXPORT virtual void setDescription(const std::string& description);
		CORE_EXPORT virtual void setAuthorEmail(const std::string& authorEmail);
		CORE_EXPORT virtual void setRequiredVersion(const unsigned short& major, const unsigned short& minor = 0, const unsigned short& patch = 0);
		CORE_EXPORT virtual void setRequiredVersion(const VersionInfo& version);
		CORE_EXPORT virtual void setProperty(const std::string& propertyName, const std::string& propertyValue);

	private:
		ResourceInfo mResourceInfo;

	protected:
		Parameters PARAMETERS;

		
	};

}

#endif // !_SSF_CORE_RESOURCE_HPP_
