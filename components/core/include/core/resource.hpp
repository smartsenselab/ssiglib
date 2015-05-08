#ifndef _SSF_CORE_RESOURCE_HPP_
#define _SSF_CORE_RESOURCE_HPP_

#include "core/base.hpp"
#include "core/base_object.hpp"
#include "core/parameters.hpp"
#include "core/resource_info.hpp"
#include "core/resource_setup.hpp"

namespace ssf{

	class Resource : public BaseObject{

	public:
		SSF_EXPORT Resource(void);
		SSF_EXPORT virtual ~Resource(void);
		SSF_EXPORT Resource(const Resource& rhs);
		SSF_EXPORT Resource& operator=(const Resource& rhs);

		SSF_EXPORT virtual ResourceInfo getInfo();
		SSF_EXPORT virtual void setup(const ResourceSetup& setup);
		
		SSF_EXPORT virtual void initialize() = 0;
		SSF_EXPORT virtual std::string getName() = 0;
		

	protected:		
		SSF_EXPORT void setAuthor(const std::string& author);
		SSF_EXPORT void setDescription(const std::string& description);
		SSF_EXPORT void setAuthorEmail(const std::string& authorEmail);
		SSF_EXPORT void setRequiredVersion(const int& majorVersion, const int& minorVersion);

	private:
		std::string mAuthor;
		std::string mDescription;
		std::string mAuthorEmail;

		int mMajorRequiredVersion;
		int mMinorRequiredVersion;

	protected:
		Parameters parameters;

		
	};

}

#endif // !_SSF_CORE_RESOURCE_HPP_