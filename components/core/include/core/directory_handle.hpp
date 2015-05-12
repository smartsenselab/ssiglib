#ifndef _SSF_CORE_DIRECTORY_HANDLE_HPP_
#define _SSF_CORE_DIRECTORY_HANDLE_HPP_

#include <string>
#include <set>
#include <memory>

#include "core/core_defs.hpp"
#include "core/file_handle.hpp"

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	class DirectoryHandle{

	public:
		CORE_EXPORT DirectoryHandle(void);
		CORE_EXPORT DirectoryHandle(const std::string& directoryPathName);
		CORE_EXPORT virtual ~DirectoryHandle(void);
		CORE_EXPORT DirectoryHandle(const DirectoryHandle& rhs);
		CORE_EXPORT DirectoryHandle& operator=(const DirectoryHandle& rhs);

		CORE_EXPORT bool operator<(const DirectoryHandle& rhs) const;

		CORE_EXPORT std::string getAbsolutePath() const;
		CORE_EXPORT std::string getSimpleName() const;
		CORE_EXPORT std::set<DirectoryHandle> listSubDirectories();
		CORE_EXPORT std::set<FileHandle> listFiles();
		CORE_EXPORT bool isEmpty() const;
		CORE_EXPORT bool erase() const;
		CORE_EXPORT bool exists() const;

		CORE_EXPORT static bool exists(const std::string& directoryPathName);
		CORE_EXPORT static bool erase(const std::string& directoryPathName);
		CORE_EXPORT static DirectoryHandle create(const std::string& directoryPathName);

	private:
		std::shared_ptr<boost::filesystem::path> mPath;
		
	};

}

#endif // !_SSF_CORE_DIRECTORY_HANDLE_HPP_