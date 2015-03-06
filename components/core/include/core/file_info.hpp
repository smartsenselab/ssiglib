#ifndef _SSF_CORE_FILE_UTIL_HPP_
#define _SSF_CORE_FILE_UTIL_HPP_

#include <string>

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	class FileInfo{

	public:
		FileInfo();
		FileInfo(const std::string& fileName);
		
		virtual ~FileInfo(void);
		
		FileInfo(const FileInfo& rhs);
		FileInfo& operator=(const FileInfo& rhs);

		std::string getAbsoluteFileName() const;
		std::string getExtenstion() const;
		
		bool erase();
		static bool erase(const std::string fileName);

		bool exists();
		static bool exists(const std::string fileName);

		bool hasExtension();

	private:
		boost::filesystem::path* mPath;

	};

}

#endif // !_SSF_CORE_FILE_UTIL_HPP_