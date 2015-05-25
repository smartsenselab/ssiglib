#ifndef _SSF_CORE_PARAMETER_SETUP_HPP_
#define _SSF_CORE_PARAMETER_SETUP_HPP_

#include <map>
#include <string>
#include <vector>

#include "core/core_defs.hpp"
#include "core/directory_handle.hpp"
#include "core/param_exception.hpp"

namespace cv{
	class FileNode;
}

namespace ssf{

	class ParametersSetup{
		friend class TestParametersSetup;

	public:
		CORE_EXPORT ParametersSetup(const std::string& ID = "");
		CORE_EXPORT ParametersSetup(const std::string& paramFile, const std::string& nodeID);
		CORE_EXPORT ParametersSetup(const FileHandle& paramFile, const std::string& nodeID);
		CORE_EXPORT virtual ~ParametersSetup(void);
		CORE_EXPORT ParametersSetup(const ParametersSetup& rhs);
		CORE_EXPORT ParametersSetup& operator=(const ParametersSetup& rhs);

		CORE_EXPORT void addParameter(const std::string& name, const int& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const double& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const bool& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const char* defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const std::string& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const FileHandle& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const DirectoryHandle& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const std::vector<int>& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const std::vector<double>& defaultValue);
		CORE_EXPORT void addParameter(const std::string& name, const std::vector<std::string>& defaultValue);

		CORE_EXPORT void setValue(const std::string& name, const int& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const double& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const bool& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const char* defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const std::string& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const FileHandle& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const DirectoryHandle& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const std::vector<int>& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const std::vector<double>& defaultValue);
		CORE_EXPORT void setValue(const std::string& name, const std::vector<std::string>& defaultValue);

		CORE_EXPORT std::string getID() const;
		CORE_EXPORT void setID(const std::string& setupID);

		CORE_EXPORT const std::map<std::string, std::vector<std::string>>& getParametersValues() const;

	protected:
		template<class T>
		CORE_EXPORT void _addParameter(const std::string& name, const T& value){
			if (this->mParametersValues.find(name) != this->mParametersValues.end())
				throw ParamException(name, "Already exists a parameter with it name.");
			this->mParametersValues[name] = std::vector<std::string>(1);
			this->setValue(name, value);
		}

		CORE_EXPORT void _setParameter(const std::string& name, const std::vector<std::string>& value);

		CORE_EXPORT void _readParamsFromFile(const std::string& fileName, const std::string& node = "");
		CORE_EXPORT void _converNodeToValue(const cv::FileNode& fileNode);

	private:
		std::map<std::string, std::vector<std::string>> mParametersValues;
		std::string mID;
	};

}

#endif // !_SSF_CORE_PARAMETER_SETUP_HPP_