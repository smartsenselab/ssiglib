#ifndef _SSF_CORE_RESOURCE_HPP_
#define _SSF_CORE_RESOURCE_HPP_

#include "core/base_object.hpp"
#include "core/parameter_book.hpp"
#include "core/resource_info.hpp"

namespace ssf{

	class Resource : public BaseObject{

	public:
		Resource(void);
		virtual ~Resource(void);
		Resource(const Resource& rhs);
		Resource& operator=(const Resource& rhs);

		virtual ResourceInfo getInfo() const;
		
		virtual void initialize() = 0;
		

	protected:
		void setName(const std::string& name);
		void setAuthor(const std::string& author);
		void setDescription(const std::string& description);
		void setAuthorEmail(const std::string& authorEmail);
		void setRequiredVersion(const int& majorVersion, const int& minorVersion);

	private:
		ParameterBook mParamCatalog;

		std::string mName;
		std::string mAuthor;
		std::string mDescription;
		std::string mAuthorEmail;

		int mMajorRequiredVersion;
		int mMinorRequiredVersion;

	};

}

#endif // !_SSF_CORE_RESOURCE_HPP_