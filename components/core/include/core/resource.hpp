#ifndef _SSF_CORE_RESOURCE_HPP_
#define _SSF_CORE_RESOURCE_HPP_

#include "core/base_object.hpp"
#include "core/params.hpp"
#include "core/resource_info.hpp"

namespace ssf{

	class Resource : public BaseObject{

	public:
		Resource(void);
		virtual ~Resource(void);
		Resource(const Resource& rhs);
		Resource& operator=(const Resource& rhs);

		virtual ResourceInfo getInfo();
		
		virtual void initialize() = 0;
		virtual std::string getName() = 0;
		

	protected:		
		void setAuthor(const std::string& author);
		void setDescription(const std::string& description);
		void setAuthorEmail(const std::string& authorEmail);
		void setRequiredVersion(const int& majorVersion, const int& minorVersion);
		Params PARAMETERS;

	private:
		std::string mAuthor;
		std::string mDescription;
		std::string mAuthorEmail;

		int mMajorRequiredVersion;
		int mMinorRequiredVersion;

		
	};

}

#endif // !_SSF_CORE_RESOURCE_HPP_