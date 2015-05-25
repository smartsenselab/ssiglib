#ifndef _SSF_CORE_PARAMETER_HPP_
#define _SSF_CORE_PARAMETER_HPP_

#include <string>
#include <memory>
#include <sstream>
#include <iomanip>
#include <vector>

#include "core/core_defs.hpp"
#include "core/file_handle.hpp"
#include "core/directory_handle.hpp"

#define CHECK_TYPE std::is_arithmetic<T>::value && std::is_convertible<T, std::string>::value

namespace ssf{

	enum class CORE_EXPORT ParamType{
		INT, DOUBLE, BOOL, STRING, FILE_HANDLE, DIRECTORY_HANDLE, INT_VECTOR, DOUBLE_VECTOR, STRING_VECTOR
	};

	class Parameter{
		friend class ParameterInfo;
		friend class Parameters;

	public:
		CORE_EXPORT Parameter(void);
		CORE_EXPORT Parameter(const std::string& name, const int& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const double& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const bool& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const char* defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const std::string& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const FileHandle& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const DirectoryHandle& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const std::vector<int>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const std::vector<double>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT Parameter(const std::string& name, const std::vector<std::string>& defaultValue, const std::string& description = "no description.");
		CORE_EXPORT virtual ~Parameter(void);
		CORE_EXPORT Parameter(const Parameter& rhs);
		CORE_EXPORT Parameter& operator=(const Parameter& rhs);

		CORE_EXPORT int toInt() const;
		CORE_EXPORT double toDouble() const;
		CORE_EXPORT bool toBool() const;
		CORE_EXPORT std::string toString() const;
		CORE_EXPORT FileHandle toFileHandle() const;
		CORE_EXPORT DirectoryHandle toDirectoryHandle() const;
		CORE_EXPORT std::vector<int> toIntVector() const;
		CORE_EXPORT std::vector<double> toDoubleVector() const;
		CORE_EXPORT std::vector<std::string> toStringVector() const;

		CORE_EXPORT bool isInt();
		CORE_EXPORT bool isDouble();
		CORE_EXPORT bool isIntVector();
		CORE_EXPORT bool isDoubleVector();

		CORE_EXPORT static bool isInt(const std::string& stringValue);
		CORE_EXPORT static bool isDouble(const std::string& stringValue);
		CORE_EXPORT static bool isIntVector(const std::vector<std::string> vectorStringValue);
		CORE_EXPORT static bool isDoubleVector(const std::vector<std::string> vectorStringValue);

		CORE_EXPORT std::string getName() const;

		CORE_EXPORT void restoreToDefaultValue();

		CORE_EXPORT ParamType getExpectedType() const;
		CORE_EXPORT void setExpectedType(const ssf::ParamType& expectedType);

		CORE_EXPORT std::string getDescription() const;
		CORE_EXPORT void setDescription(const std::string& description);

		CORE_EXPORT bool isRequired() const;
		CORE_EXPORT void setRequired(const bool& required);

	private:
		std::string mName;
		std::string mDescription;
		ParamType mExpectedType;

		std::vector<std::string> mValue;
		std::vector<std::string> mDefaultValue;

		bool mRequired;
	};

}

#endif // !_SSF_CORE_PARAMETER_HPP_