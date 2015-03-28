#ifndef _SSF_CORE_PARAM_HPP_
#define _SSF_CORE_PARAM_HPP_

#include <string>

#include "core/file_handle.hpp"
#include "core/directory_handle.hpp"
#include "core/param_exception.hpp"

namespace ssf{

	enum class ParamType{
		INT, LONG, FLOAT, DOUBLE, BOOL, STRING, FILE_HANDLE, DIRECTORY_HANDLE
	};

	class Param{
		friend class Params;

	public:
		Param(void);
		Param(const ParamType& parameterType, const std::string& name, const std::string& description);
		virtual ~Param(void);
		Param(const Param& rhs);
		Param& operator=(const Param& rhs);

		ParamType getType() const;
		std::string getName() const;
		std::string getDescription() const;
		bool isRequired() const;
		long long getMaxValue() const;
		long long getMinValue() const;


		template < class T>
		typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, T>::type getValue(){
			T returnValue;
			try{
				switch (this->mType){
				case ParamType::INT: returnValue = this->getNumericValue<T, int>(); break;
				case ParamType::LONG: returnValue = this->getNumericValue<T, long>(); break;
				case ParamType::FLOAT: returnValue = this->getNumericValue<T, float>(); break;
				case ParamType::DOUBLE: returnValue = this->getNumericValue<T, double>(); break;
				case ParamType::BOOL: returnValue = this->getNumericValue<T, bool>(); break;
				default: throw ParamException(this->mName, this->incompatibleResultMessage<T>()); break;
				}
			}
			catch (ParamException* e){
				throw ParamException(e->getParameterName(), e->getMessage());
			}
			return returnValue;
		}

		template < class T>
		typename std::enable_if<std::is_same<T, bool>::value, T>::type getValue(){
			T returnValue;
			try{
				switch (this->mType){
				case ParamType::INT: returnValue = this->getBoolValue<int>(); break;
				case ParamType::LONG: returnValue = this->getBoolValue<long>(); break;
				case ParamType::FLOAT: returnValue = this->getBoolValue<float>(); break;
				case ParamType::DOUBLE: returnValue = this->getBoolValue<double>(); break;
				case ParamType::BOOL: returnValue = this->getBoolValue<bool>(); break;
				default: throw ParamException(this->mName, this->incompatibleResultMessage<T>()); break;
				}
			}
			catch (ParamException* e){
				throw ParamException(e->getParameterName(), e->getMessage());
			}
			return returnValue;
		}

		template < class T>
		typename std::enable_if<std::is_convertible<T, std::string>::value, T>::type getValue(){
			if (this->mType != ParamType::STRING)
				throw ParamException(this->mName, this->incompatibleResultMessage<T>());
			return *((std::string*)this->mValue);
		}

		template < class T>
		typename std::enable_if<std::is_same<T, FileHandle>::value, T>::type getValue(){
			if (this->mType != ParamType::FILE_HANDLE)
				throw ParamException(this->mName, this->incompatibleResultMessage<T>());
			return *((FileHandle*)this->mValue);
		}

		template < class T>
		typename std::enable_if<std::is_same<T, DirectoryHandle>::value, T>::type getValue(){
			if (this->mType != ParamType::DIRECTORY_HANDLE)
				throw ParamException(this->mName, this->incompatibleResultMessage<T>());
			return *((DirectoryHandle*)this->mValue);
		}

	private:

		std::string getTypeStr() const;
		void copy(const Param& rhs);

		void setRequired(const bool& required = true);
		void setMaxValue(const long long& maxValue);
		void setMinValue(const long long& minValue);

		template < class T>
		void setValue(const T& value, typename std::enable_if<std::is_arithmetic<T>::value >::type* = 0){
			try{
				switch (this->mType){
				case ParamType::INT: this->setNumericValue<T, int>(value); break;
				case ParamType::LONG: this->setNumericValue<T, long>(value); break;
				case ParamType::FLOAT: this->setNumericValue<T, float>(value); break;
				case ParamType::DOUBLE: this->setNumericValue<T, double>(value); break;
				case ParamType::BOOL: this->setBoolValue<T>(value); break;
				default: throw ParamException(this->mName, this->incompatibleReceiveMessage<T>()); break;
				}
			}
			catch (ParamException* e){
				throw ParamException(e->getParameterName(), e->getMessage());
			}
		}

		template < class T>
		void setValue(const T& value, typename std::enable_if<std::is_convertible<T, std::string>::value >::type* = 0){
			if (this->mType != ParamType::STRING)
				throw ParamException(this->mName, this->incompatibleReceiveMessage<T>());
			*((std::string*)this->mValue) = value;
		}

		template < class T>
		void setValue(const T& value, typename std::enable_if<std::is_same<T, FileHandle>::value >::type* = 0){
			if (this->mType != ParamType::FILE_HANDLE)
				throw ParamException(this->mName, this->incompatibleReceiveMessage<T>());
			*((FileHandle*)this->mValue) = value;
		}

		template < class T>
		void setValue(const T& value, typename std::enable_if<std::is_same<T, DirectoryHandle>::value >::type* = 0){
			if (this->mType != ParamType::DIRECTORY_HANDLE)
				throw ParamException(this->mName, this->incompatibleReceiveMessage<T>());
			*((DirectoryHandle*)this->mValue) = value;
		}

		template<class T>
		std::string incompatibleReceiveMessage(){
			std::string msg = "This parameter cannot receive " + std::string(typeid(T).name()) + " type value.";
			msg += " The correct type of this parameter is: " + this->getTypeStr();
			return msg;
		}

		template<class T>
		std::string incompatibleResultMessage(){
			std::string msg = "This parameter cannot be converted to " + std::string(typeid(T).name()) + " type.";
			msg += " The correct type of this parameter is: " + this->getTypeStr();
			return msg;
		}

		template<class T, class S>
		void setNumericValue(const T& value){
			if (!std::is_convertible<T, S>::value){
				throw ParamException(this->mName, this->incompatibleReceiveMessage<T>());
			}
			S newValue = static_cast<S>(value);
			*((S*)this->mValue) = newValue;
		}

		template<class T, class S>
		T getNumericValue(){
			if (!std::is_convertible<S, T>::value){
				throw ParamException(this->mName, this->incompatibleResultMessage<T>());
			}
			T newValue = static_cast<T>(*((S*)this->mValue));
			return newValue;
		}


		template<class T>
		void setBoolValue(const T& value){
			if (!std::is_convertible<T, bool>::value){
				throw ParamException(this->mName, this->incompatibleReceiveMessage<T>());
			}
			*((bool*)this->mValue) = (value != 0);
		}

		template<class S>
		bool getBoolValue(){
			if (!std::is_convertible<S, bool>::value){
				throw ParamException(this->mName, this->incompatibleResultMessage<bool>());
			}
			bool newValue = static_cast<bool>(*((S*)this->mValue) != 0);
			return newValue;
		}

	protected:
		ParamType mType;
		std::string mName;
		std::string mDescription;		
		void* mValue;

		bool mRequired;
		long long maxValue;
		long long minValue;
	};

}

#endif // !_SSF_CORE_PARAM_HPP_