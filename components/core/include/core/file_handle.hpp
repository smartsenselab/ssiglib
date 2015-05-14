#ifndef _SSF_CORE_FILE_UTIL_HPP_
#define _SSF_CORE_FILE_UTIL_HPP_

#include <string>
#include <memory>

#include "core/core_defs.hpp"

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	class FileHandle{

	public:
		CORE_EXPORT FileHandle();
		CORE_EXPORT explicit FileHandle(const std::string& fileName);
		CORE_EXPORT virtual ~FileHandle(void);
		CORE_EXPORT FileHandle(const FileHandle& rhs);
		CORE_EXPORT FileHandle& operator=(const FileHandle& rhs);

		CORE_EXPORT bool operator<(const FileHandle& rhs) const;

		CORE_EXPORT std::string getAbsoluteFileName() const;
		CORE_EXPORT std::string getSimpleName() const;
		CORE_EXPORT std::string getExtenstion() const;
		
		CORE_EXPORT bool erase();
		CORE_EXPORT bool hasExtension() const;

		CORE_EXPORT static bool erase(const std::string& fileName);
		CORE_EXPORT static bool exists(const std::string& fileName);

	private:
		std::shared_ptr<boost::filesystem::path> mPath ;

	};

}

#endif // !_SSF_CORE_FILE_UTIL_HPP_