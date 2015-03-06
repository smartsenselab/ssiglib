#ifndef _SSF_CORE_DIRECTORY_HANDLE_HPP_
#define _SSF_CORE_DIRECTORY_HANDLE_HPP_

#include <string>
#include <set>

#include "core/file_handle.hpp"

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	class DirectoryHandle{

	public:
		DirectoryHandle(void);
		DirectoryHandle(const std::string& directoryPathName);
		virtual ~DirectoryHandle(void);
		DirectoryHandle(const DirectoryHandle& rhs);
		DirectoryHandle& operator=(const DirectoryHandle& rhs);

		bool operator<(const DirectoryHandle& rhs) const{
			return true;
		}

		std::string getAbsolutePath() const;
		std::string getSimpleName() const;
		std::set<DirectoryHandle> listSubDirectories();
		std::set<FileHandle> listFiles();
		bool isEmpty() const;
		bool countFiles() const;
		bool countDirectories() const;

		static bool exists(const std::string& directoryPathName);
		static DirectoryHandle create(const std::string& directoryPathName);

	private:
		boost::filesystem::path* mPath;

	};

}

#endif // !_SSF_CORE_DIRECTORY_HANDLE_HPP_