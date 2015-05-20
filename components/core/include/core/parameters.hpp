#ifndef _SSF_CORE_PARAMETER_LIST_HPP_
#define _SSF_CORE_PARAMETER_LIST_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "core/parameter.hpp"
#include "core/file_handle.hpp"

namespace cv{
	class FileNode;
}

namespace ssf{

	class Parameters{

	public:
		CORE_EXPORT Parameters(void);
		CORE_EXPORT virtual ~Parameters(void);
		CORE_EXPORT Parameters(const FileHandle& fileHandle, const std::string& node = "");
		CORE_EXPORT Parameters(const std::string& fileName, const std::string& node = "");
		CORE_EXPORT Parameters(const Parameters& rhs);
		CORE_EXPORT Parameters& operator=(const Parameters& rhs);

		CORE_EXPORT Parameter& operator[](const std::string& parameterName);
		
		CORE_EXPORT void addParameter(const std::string& name, const std::string& description = "", const ParamType& type = ParamType::STRING);
		CORE_EXPORT void addParameter(const Parameter& parameter);

		CORE_EXPORT const std::map<std::string, Parameter>& getParameters() const;


	private:		
		void readParamsFromFile(const std::string& fileName, const std::string& node = "");
		Parameter converNodeToParameter(const cv::FileNode& fileNode);

	private:
		std::map<std::string, Parameter> mParameters;

	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_