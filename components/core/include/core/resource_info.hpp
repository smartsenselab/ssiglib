#ifndef _SSF_CORE_RESOURCE_INFO_HPP_
#define _SSF_CORE_RESOURCE_INFO_HPP_

#include <string>
#include <map>

namespace ssf{

	class ResourceInfo{		
		friend class Resource;

	public:
		ResourceInfo(void);
		virtual ~ResourceInfo(void);
		ResourceInfo(const ResourceInfo& rhs);
		ResourceInfo& operator=(const ResourceInfo& rhs);

		std::string getName() const;
		std::string getAuthor() const;
		std::string getDescription() const;
		std::string getAuthorEmail() const;
		std::string getRequiredVersion() const;
		int getMajorRequiredVersion() const;
		int getMinorRequiredVersion() const;

	protected:
		std::string mName;
		std::string mAuthor;
		std::string mDescription;
		std::string mAuthorEmail;

		int mMajorRequiredVersion;
		int mMinorRequiredVersion;

		/*Params mParams;*/

	};

}

#endif // !_SSF_CORE_RESOURCE_INFO_HPP_

#include <iostream>

using namespace std;




template <class tr>
struct test
{
	typedef typename tr::tipo tipo;
	tipo a;
	void useless(){ a.use(); }


};