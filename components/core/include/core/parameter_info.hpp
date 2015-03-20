#ifndef _SSF_CORE_PARAMETER_INFO_HPP_
#define _SSF_CORE_PARAMETER_INFO_HPP_

#include <string>
#include <memory>

#include "core/parameter.hpp"

namespace ssf{

	class ParameterInfo{

	public:

		template<class T> ParameterInfo(const Parameter<T> parameter){
			this->mName = parameter.getName();
			this->mDescription = parameter.getDescription();
			this->mRequired = parameter.getRequired();
			this->mParameterType = parameter.getType();
			this->setDefaultValue(parameter.getValue());
		}

		ParameterInfo(void);
		virtual ~ParameterInfo(void);
		ParameterInfo(const ParameterInfo& rhs);
		ParameterInfo& operator=(const ParameterInfo& rhs);

		std::string getName() const;
		std::string getDescription() const;
		bool getRequired() const;
		ParameterType getParameterType() const;

		/*template<class T> T getDefaultValue() const{			
			return this->getDefaultValue<T>();
		}*/
	
		template<class T>
		typename std::enable_if<std::is_same<T, int>::value, int>::type
		getDefaultValue() const{
			if (this->getParameterType() != ParameterType::INT)
				throw ParameterException(this->mName, "This parameter is not int");
			return this->intDefaultValue;
		}

		template<class T>
		typename std::enable_if<std::is_same<T, long>::value, long>::type
			getDefaultValue() const{
			if (this->getParameterType() != ParameterType::LONG)
				throw ParameterException(this->mName, "This parameter is not long");
			return this->longDefaultValue;
		}

		template<class T>
		typename std::enable_if<std::is_same<T, float>::value, float>::type
			getDefaultValue() const{
			if (this->getParameterType() != ParameterType::FLOAT)
				throw ParameterException(this->mName, "This parameter is not float");
			return this->floatDefaultValue;
		}

		template<class T>
		typename std::enable_if<std::is_same<T, double>::value, double>::type
			getDefaultValue() const{
			if (this->getParameterType() != ParameterType::DOUBLE)
				throw ParameterException(this->mName, "This parameter is not double");
			return this->doubleDefaultValue;
		}

		template<class T>
		typename std::enable_if<std::is_same<T, bool>::value, bool>::type
			getDefaultValue() const{
			if (this->getParameterType() != ParameterType::BOOL)
				throw ParameterException(this->mName, "This parameter is not bool");
			return this->boolDefaultValue;
		}

		template<class T>
		typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type
			getDefaultValue() const{
			if (this->getParameterType() != ParameterType::STRING)
				throw ParameterException(this->mName, "This parameter is not std::string");
			return this->stringDefaultValue;
		}

		template<class T>
		typename std::enable_if<std::is_same<T, FileHandle>::value, FileHandle>::type
			getDefaultValue() const{
			if (this->getParameterType() != ParameterType::FILE_HANDLE)
				throw ParameterException(this->mName, "This parameter is not FileHandle");
			return this->fileHandleDefaultValue;
		}

		template<class T>
		typename std::enable_if<std::is_same<T, DirectoryHandle>::value, DirectoryHandle>::type
			getDefaultValue() const{
			if (this->getParameterType() != ParameterType::DIRECTORY_HANDLE)
				throw ParameterException(this->mName, "This parameter is not DirectoryHandle");
			return this->directoryHandleDefaultValue;
		}

	private:
		template<class T> void setDefaultValue(const T& defaultValue){
			this->setDefaultValue<T>(defaultValue);
		}

		template<> void setDefaultValue(const int& defaultValue){
			this->intDefaultValue = defaultValue;
		}

		template<> void setDefaultValue(const long& defaultValue){
			this->longDefaultValue = defaultValue;
		}

		template<> void setDefaultValue(const float& defaultValue){
			this->floatDefaultValue = defaultValue;
		}

		template<> void setDefaultValue(const double& defaultValue){
			this->doubleDefaultValue = defaultValue;
		}

		template<> void setDefaultValue(const bool& defaultValue){
			this->boolDefaultValue = defaultValue;
		}

		template<> void setDefaultValue(const std::string& defaultValue){
			this->stringDefaultValue = defaultValue;
		}

		template<> void setDefaultValue(const FileHandle& defaultValue){
			this->fileHandleDefaultValue = defaultValue;
		}

		template<> void setDefaultValue(const DirectoryHandle& defaultValue){
			this->directoryHandleDefaultValue = defaultValue;
		}

	private:
		std::string mName;
		std::string mDescription;
		bool mRequired;
		ParameterType mParameterType;

		int intDefaultValue;
		long longDefaultValue;
		float floatDefaultValue;
		double doubleDefaultValue;
		bool boolDefaultValue;
		std::string stringDefaultValue;
		ssf::FileHandle fileHandleDefaultValue;
		ssf::DirectoryHandle directoryHandleDefaultValue;

	};
}
#endif // !_SSF_CORE_PARAMETER_INFO_HPP_