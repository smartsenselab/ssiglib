#ifndef _SSF_CORE_FILE_UTIL_HPP_
#define _SSF_CORE_FILE_UTIL_HPP_

#include <string>
#include <memory>

namespace boost{
	namespace filesystem{
		class path;
	}
}

namespace ssf{

	class FileHandle{

	public:
		FileHandle();
		explicit FileHandle(const std::string& fileName);
		virtual ~FileHandle(void);		
		FileHandle(const FileHandle& rhs);
		FileHandle& operator=(const FileHandle& rhs);

		bool operator<(const FileHandle& rhs) const;

		std::string getAbsoluteFileName() const;
		std::string getSimpleName() const;
		std::string getExtenstion() const;
		
		bool erase();
		bool hasExtension() const;

		static bool erase(const std::string& fileName);
		static bool exists(const std::string& fileName);

	private:
		std::shared_ptr<boost::filesystem::path> mPath ;

	};

}

#endif // !_SSF_CORE_FILE_UTIL_HPP_