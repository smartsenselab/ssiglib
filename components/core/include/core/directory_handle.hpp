#ifndef _SSF_CORE_DIRECTORY_HANDLE_HPP_
#define _SSF_CORE_DIRECTORY_HANDLE_HPP_

#include <string>
#include <set>
#include <memory>

#include "core/ssfdef.hpp"
#include "core/file_handle.hpp"

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	class DirectoryHandle{

	public:
		SSF_EXPORT DirectoryHandle(void);
		SSF_EXPORT DirectoryHandle(const std::string& directoryPathName);
		SSF_EXPORT virtual ~DirectoryHandle(void);
		SSF_EXPORT DirectoryHandle(const DirectoryHandle& rhs);
		SSF_EXPORT DirectoryHandle& operator=(const DirectoryHandle& rhs);

		SSF_EXPORT bool operator<(const DirectoryHandle& rhs) const;

		SSF_EXPORT std::string getAbsolutePath() const;
		SSF_EXPORT std::string getSimpleName() const;
		SSF_EXPORT std::set<DirectoryHandle> listSubDirectories();
		SSF_EXPORT std::set<FileHandle> listFiles();
		SSF_EXPORT bool isEmpty() const;
		SSF_EXPORT bool erase() const;
		SSF_EXPORT bool exists() const;

		SSF_EXPORT static bool exists(const std::string& directoryPathName);
		SSF_EXPORT static bool erase(const std::string& directoryPathName);
		SSF_EXPORT static DirectoryHandle create(const std::string& directoryPathName);

	private:
		std::shared_ptr<boost::filesystem::path> mPath;
		
	};

}

#endif // !_SSF_CORE_DIRECTORY_HANDLE_HPP_