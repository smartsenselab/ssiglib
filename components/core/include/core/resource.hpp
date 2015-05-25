#ifndef _SSF_CORE_RESOURCE_HPP_
#define _SSF_CORE_RESOURCE_HPP_

#include <string> 

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

		//CORE_EXPORT virtual ResourceInfo getInfo();
		
		CORE_EXPORT virtual void initialize() = 0;
		CORE_EXPORT virtual std::string getName() = 0;
		CORE_EXPORT virtual std::string getType() = 0;
		
		//CORE_EXPORT const std::map<std::string, Parameter>& getParameters() const;

	//protected:		
	//	CORE_EXPORT void setAuthor(const std::string& author);
	//	CORE_EXPORT void setDescription(const std::string& description);
	//	CORE_EXPORT void setAuthorEmail(const std::string& authorEmail);
	//	CORE_EXPORT void setRequiredVersion(const unsigned short& major, const unsigned short& minor = 0, const unsigned short& patch = 0);
	//	CORE_EXPORT void setRequiredVersion(const VersionInfo& version);
	//	CORE_EXPORT void setProperty(const std::string& propertyName, const std::string& propertyValue);

	//private:
	//	ResourceInfo mResourceInfo;

	//protected:
	//	Parameters PARAMETERS;

		
	};

}

#endif // !_SSF_CORE_RESOURCE_HPP_