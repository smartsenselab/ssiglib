#ifndef _SSF_CORE_FILE_UTIL_HPP_
#define _SSF_CORE_FILE_UTIL_HPP_

#include <string>
#include <memory>

#include "core/base.hpp"

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	class FileHandle{

	public:
		SSF_EXPORT FileHandle();
		SSF_EXPORT explicit FileHandle(const std::string& fileName);
		SSF_EXPORT virtual ~FileHandle(void);
		SSF_EXPORT FileHandle(const FileHandle& rhs);
		SSF_EXPORT FileHandle& operator=(const FileHandle& rhs);

		SSF_EXPORT bool operator<(const FileHandle& rhs) const;

		SSF_EXPORT std::string getAbsoluteFileName() const;
		SSF_EXPORT std::string getSimpleName() const;
		SSF_EXPORT std::string getExtenstion() const;
		
		SSF_EXPORT bool erase();
		SSF_EXPORT bool hasExtension() const;

		SSF_EXPORT static bool erase(const std::string& fileName);
		SSF_EXPORT static bool exists(const std::string& fileName);

	private:
		std::shared_ptr<boost::filesystem::path> mPath ;

	};

}

#endif // !_SSF_CORE_FILE_UTIL_HPP_