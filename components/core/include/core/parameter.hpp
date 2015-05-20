#ifndef _SSF_CORE_PARAM_HPP_
#define _SSF_CORE_PARAM_HPP_

#include <string>
#include <memory>
#include <sstream>
#include <iomanip>

#include "core/core_defs.hpp"
#include "core/file_handle.hpp"
#include "core/directory_handle.hpp"

#define CHECK_TYPE std::is_arithmetic<T>::value && std::is_convertible<T, std::string>::value

namespace ssf{

	enum class CORE_EXPORT ParamType{
		INTEGER, REAL, BOOL, STRING, FILE_HANDLE, DIRECTORY_HANDLE
	};

	class Parameter{
	public:
		CORE_EXPORT Parameter(void);
		CORE_EXPORT Parameter(const std::string& name, const std::string& description, const ParamType& type = ParamType::STRING);

		CORE_EXPORT int toInt() const;
		CORE_EXPORT long toLong() const;
		CORE_EXPORT long long toLongLong() const;
		CORE_EXPORT unsigned int toUnsignedInt() const;
		CORE_EXPORT unsigned long toUnsignedLong() const;
		CORE_EXPORT float toFloat() const;
		CORE_EXPORT double toDouble() const;
		CORE_EXPORT bool toBool() const;
		CORE_EXPORT std::string toString() const;
		CORE_EXPORT FileHandle toFileHandle() const;
		CORE_EXPORT DirectoryHandle toDirectoryHandle() const;

		CORE_EXPORT void setValue(const int& value);
		CORE_EXPORT void setValue(const long& value);
		CORE_EXPORT void setValue(const long long& value);
		CORE_EXPORT void setValue(const unsigned int& value);
		CORE_EXPORT void setValue(const unsigned long& value);
		CORE_EXPORT void setValue(const float& value);
		CORE_EXPORT void setValue(const double& value);		
		CORE_EXPORT void setValue(const bool& value);
		CORE_EXPORT void setValue(const char* value);
		CORE_EXPORT void setValue(const std::string& value);
		CORE_EXPORT void setValue(const FileHandle& value);
		CORE_EXPORT void setValue(const DirectoryHandle& value);

		CORE_EXPORT bool isEmpty() const;
		CORE_EXPORT void clearValue();
			
		CORE_EXPORT ParamType getType() const;
		CORE_EXPORT void setType(const ssf::ParamType& requiredType);
		CORE_EXPORT std::string getName() const;
		CORE_EXPORT std::string getDescription() const;
		CORE_EXPORT void setDescription(const std::string& description);
		CORE_EXPORT bool isRequired() const;
		CORE_EXPORT void setRequired(const bool& required);

	private:
		std::string mValue;

		ParamType mType;
		std::string mName;
		std::string mDescription;
		bool mRequired;
	};

}

#endif // !_SSF_CORE_PARAM_HPP_