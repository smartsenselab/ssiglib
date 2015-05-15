//#ifndef _SSF_CORE_RESOURCE_HPP_
//#define _SSF_CORE_RESOURCE_HPP_
//
//#include "core/core_defs.hpp"
//#include "core/base_object.hpp"
//#include "core/parameters.hpp"
//#include "core/resource_info.hpp"
//#include "core/resource_setup.hpp"
//
//namespace ssf{
//
//	class Resource : public BaseObject{
//
//	public:
//		CORE_EXPORT Resource(void);
//		CORE_EXPORT virtual ~Resource(void);
//		CORE_EXPORT Resource(const Resource& rhs);
//		CORE_EXPORT Resource& operator=(const Resource& rhs);
//
//		CORE_EXPORT virtual ResourceInfo getInfo();
//		CORE_EXPORT virtual void setup(const ResourceSetup& setup);
//		
//		CORE_EXPORT virtual void initialize() = 0;
//		CORE_EXPORT virtual std::string getName() = 0;
//		
//
//	protected:		
//		CORE_EXPORT void setAuthor(const std::string& author);
//		CORE_EXPORT void setDescription(const std::string& description);
//		CORE_EXPORT void setAuthorEmail(const std::string& authorEmail);
//		CORE_EXPORT void setRequiredVersion(const int& majorVersion, const int& minorVersion);
//
//	private:
//		std::string mAuthor;
//		std::string mDescription;
//		std::string mAuthorEmail;
//
//		int mMajorRequiredVersion;
//		int mMinorRequiredVersion;
//
//	protected:
//		Parameters parameters;
//
//		
//	};
//
//}
//
//#endif // !_SSF_CORE_RESOURCE_HPP_