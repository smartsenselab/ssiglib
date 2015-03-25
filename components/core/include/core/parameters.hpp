#ifndef _SSF_CORE_PARAMETER_LIST_HPP_
#define _SSF_CORE_PARAMETER_LIST_HPP_

#include <string>
#include <map>
#include <memory>

#include "core/parameter_value.hpp"

namespace ssf{

	class Parameters{

	public:
		Parameters(void);
		virtual ~Parameters(void);
		Parameters(const Parameters& rhs);
		Parameters& operator=(const Parameters& rhs);

		void addParameter(const ParameterType& type, const std::string& name, const std::string& description);

		ParameterType getType(const std::string& paramName);
		std::string getName(const std::string& paramName);
		std::string getDescription(const std::string& paramName);

		bool isNumeric(const std::string& paramName);
		bool isIntegral(const std::string& paramName);
		bool isFloating(const std::string& paramName);
		bool isBoolean(const std::string& paramName);
		bool isString(const std::string& paramName);

		void setRequired(const std::string& paramName, const bool& required = true);
		bool isRequired(const std::string& paramName);

		template < class T>
		void setValue(const std::string& paramName, const T& value, typename std::enable_if<std::is_arithmetic<T>::value >::type* = 0){
			try{
				switch (this->getType(paramName)){
				case ParameterType::INT: this->setNumericValue<T, int>(paramName, value); break;
				case ParameterType::LONG: this->setNumericValue<T, long>(paramName, value); break;
				case ParameterType::FLOAT: this->setNumericValue<T, float>(paramName, value); break;
				case ParameterType::DOUBLE: this->setNumericValue<T, double>(paramName, value); break;
				case ParameterType::BOOL: this->setBoolValue<T>(paramName, value); break;
				default: throw ParameterException(paramName, this->incompatibleReceiveMessage<T>(paramName)); break;
				}
			}
			catch (ParameterException* e){
				throw ParameterException(e->getParameterName(), e->getMessage());
			}
		}

		template < class T>
		void setValue(const std::string& paramName, const T& value, typename std::enable_if<std::is_convertible<T, std::string>::value >::type* = 0){
			if (this->getType(paramName) != ParameterType::STRING)
				throw ParameterException(paramName, this->incompatibleReceiveMessage<T>(paramName));
			this->getTypedParamValue<std::string>(paramName)->setValue(value);
		}

		template < class T>
		void setValue(const std::string& paramName, const T& value, typename std::enable_if<std::is_same<T, FileHandle>::value >::type* = 0){
			if (this->getType(paramName) != ParameterType::FILE_HANDLE)
				throw ParameterException(paramName, this->incompatibleReceiveMessage<T>(paramName));
			this->getTypedParamValue<FileHandle>(paramName)->setValue(value);

		}

		template < class T>
		void setValue(const std::string& paramName, const T& value, typename std::enable_if<std::is_same<T, DirectoryHandle>::value >::type* = 0){
			if (this->getType(paramName) != ParameterType::DIRECTORY_HANDLE)
				throw ParameterException(paramName, this->incompatibleReceiveMessage<T>(paramName));
			this->getTypedParamValue<DirectoryHandle>(paramName)->setValue(value);

		}

		template < class T>
		typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, T>::type getValue(const std::string& paramName){
			T returnValue;
			try{
				switch (this->getType(paramName)){
				case ParameterType::INT: returnValue = this->getNumericValue<T, int>(paramName); break;
				case ParameterType::LONG: returnValue = this->getNumericValue<T, long>(paramName); break;
				case ParameterType::FLOAT: returnValue = this->getNumericValue<T, float>(paramName); break;
				case ParameterType::DOUBLE: returnValue = this->getNumericValue<T, double>(paramName); break;
				case ParameterType::BOOL: returnValue = this->getNumericValue<T, bool>(paramName); break;
				default: throw ParameterException(paramName, this->incompatibleResultMessage<T>(paramName)); break;
				}
			}
			catch (ParameterException* e){
				throw ParameterException(e->getParameterName(), e->getMessage());
			}
			return returnValue;
		}

		template < class T>
		typename std::enable_if<std::is_same<T, bool>::value, T>::type getValue(const std::string& paramName){
			T returnValue;
			try{
				switch (this->getType(paramName)){
				case ParameterType::INT: returnValue = this->getBoolValue<int>(paramName); break;
				case ParameterType::LONG: returnValue = this->getBoolValue<long>(paramName); break;
				case ParameterType::FLOAT: returnValue = this->getBoolValue<float>(paramName); break;
				case ParameterType::DOUBLE: returnValue = this->getBoolValue<double>(paramName); break;
				case ParameterType::BOOL: returnValue = this->getBoolValue<bool>(paramName); break;
				default: throw ParameterException(paramName, this->incompatibleResultMessage<T>(paramName)); break;
				}
			}
			catch (ParameterException* e){
				throw ParameterException(e->getParameterName(), e->getMessage());
			}
			return returnValue;
		}

		template < class T>
		typename std::enable_if<std::is_convertible<T, std::string>::value, T>::type getValue(const std::string& paramName){
			if (this->getType(paramName) != ParameterType::STRING)
				throw ParameterException(paramName, this->incompatibleResultMessage<T>(paramName));
			return this->getTypedParamValue<std::string>(paramName)->getValue();
		}

		template < class T>
		typename std::enable_if<std::is_same<T, FileHandle>::value, T>::type getValue(const std::string& paramName){
			if (this->getType(paramName) != ParameterType::FILE_HANDLE)
				throw ParameterException(paramName, this->incompatibleResultMessage<T>(paramName));
			return this->getTypedParamValue<FileHandle>(paramName)->getValue();
		}

		template < class T>
		typename std::enable_if<std::is_same<T, DirectoryHandle>::value, T>::type getValue(const std::string& paramName){
			if (this->getType(paramName) != ParameterType::DIRECTORY_HANDLE)
				throw ParameterException(paramName, this->incompatibleResultMessage<T>(paramName));
			return this->getTypedParamValue<DirectoryHandle>(paramName)->getValue();
		}



	private:
		std::shared_ptr<IParameterValue> getParamValue(const std::string& paramName);

		template<class T>
		std::shared_ptr< ParameterValue<T> > getTypedParamValue(const std::string& paramName){
			if (this->mParameters.find(paramName) == this->mParameters.end())
				throw ParameterException(paramName, "There is no parameter with such name.");
			std::shared_ptr< ssf::ParameterValue<T> > parameterValue = std::dynamic_pointer_cast<ssf::ParameterValue<T>, ssf::IParameterValue>(this->mParameters[paramName]);
			if (parameterValue == nullptr)
				throw ParameterException(paramName, "Write this exception");
			return parameterValue;
		}

		template<class T>
		std::string incompatibleReceiveMessage(const std::string& paramNam){
			std::string msg = "This parameter cannot receive " + std::string(typeid(T).name()) + " type value.";
			msg += " The correct type of this parameter is: " + this->getParamValue(paramNam)->getTypeStr();
			return msg;
		}

		template<class T>
		std::string incompatibleResultMessage(const std::string& paramNam){
			std::string msg = "This parameter cannot be converted to " + std::string(typeid(T).name()) + " type.";
			msg += " The correct type of this parameter is: " + this->getParamValue(paramNam)->getTypeStr();
			return msg;
		}

		template<class T, class S>
		void setNumericValue(const std::string& paramName, const T& value){
			if (!std::is_convertible<T, S>::value){
				throw ParameterException(paramName, this->incompatibleReceiveMessage<T>(paramName));
			}
			S intValue = static_cast<S>(value);
			this->getTypedParamValue<S>(paramName)->setValue(intValue);
		}

		template<class T, class S>
		T getNumericValue(const std::string& paramName){
			if (!std::is_convertible<S, T>::value){
				throw ParameterException(paramName, this->incompatibleResultMessage<T>(paramName));
			}
			T newValue = static_cast<T>(this->getTypedParamValue<S>(paramName)->getValue());
			return newValue;
		}


		template<class T>
		void setBoolValue(const std::string& paramName, const T& value){
			if (!std::is_convertible<T, bool>::value){
				throw ParameterException(paramName, this->incompatibleReceiveMessage<T>(paramName));
			}
			this->getTypedParamValue<bool>(paramName)->setValue(value != 0);
		}

		template<class S>
		bool getBoolValue(const std::string& paramName){
			if (!std::is_convertible<S, bool>::value){
				throw ParameterException(paramName, this->incompatibleResultMessage<bool>(paramName));
			}
			bool newValue = static_cast<bool>(this->getTypedParamValue<S>(paramName)->getValue() != 0);
			return newValue;
		}


	private:
		std::map<std::string, std::shared_ptr<IParameterValue>> mParameters;

	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_