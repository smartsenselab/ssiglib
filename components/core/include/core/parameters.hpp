#ifndef _SSF_CORE_PARAMETER_LIST_HPP_
#define _SSF_CORE_PARAMETER_LIST_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "core/parameter.hpp"
#include "core/file_handle.hpp"

#include "parameters_setup.hpp"
#include "parameter_info.hpp"

namespace ssf{

	class Parameters{

	public:
		CORE_EXPORT Parameters(void);
		CORE_EXPORT virtual ~Parameters(void);
		CORE_EXPORT Parameters(const Parameters& rhs);
		CORE_EXPORT Parameters& operator=(const Parameters& rhs);

		CORE_EXPORT Parameter& operator[](const std::string& parameterName);
		CORE_EXPORT Parameter& getParameter(const std::string& parameterName);
		
		CORE_EXPORT void addParameter(const std::string& paramName, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const int& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const double& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const bool& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const char* defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const std::string& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const FileHandle& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const DirectoryHandle& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const std::vector<int>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const std::vector<double>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const std::string& paramName, const std::vector<std::string>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT void addParameter(const Parameter& parameter);

		CORE_EXPORT void setup(const std::string& paramFile, const std::string& nodeID);
		CORE_EXPORT void setup(const FileHandle& paramFile, const std::string& nodeID);
		CORE_EXPORT void setup(const ParametersSetup& paramSetup);

		CORE_EXPORT bool has(const std::string& paramName);
		CORE_EXPORT std::map<std::string, ParameterInfo> getParametersInfo();

	private:
		std::map<std::string, Parameter> mParameters;
	
	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_