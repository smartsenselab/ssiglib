#ifndef _SSF_CORE_PARAMETER_VALUE_HPP_
#define _SSF_CORE_PARAMETER_VALUE_HPP_

#include <string>
#include <memory>

#include "core/parameter_exception.hpp"
#include "core/file_handle.hpp"
#include "core/directory_handle.hpp"


namespace ssf{

	enum class ParameterType{
		INT, LONG, FLOAT, DOUBLE, BOOL, STRING, FILE_HANDLE, DIRECTORY_HANDLE
	};


	class IParameterValue{
	
	public:
		IParameterValue(void){}

		IParameterValue(const ParameterType& parameterType, const std::string& name, const std::string& description){
			this->mType = parameterType;
			this->mName = name;
			this->mDescription = description;
			this->mRequired = false;
		}

		virtual ~IParameterValue(void){}

		IParameterValue(const IParameterValue& rhs){
			this->mType = rhs.mType;
			this->mName = rhs.mName;
			this->mDescription = rhs.mDescription;
			this->mRequired = rhs.mRequired;
		}

		IParameterValue& operator=(const IParameterValue& rhs){
			if (this != &rhs){
				this->mType = rhs.mType;
				this->mName = rhs.mName;
				this->mDescription = rhs.mDescription;
				this->mRequired = rhs.mRequired;
			}
			return *this;
		}

		ParameterType getType() const{
			return this->mType;
		}

		std::string getName() const{
			return this->mName;
		}

		std::string getDescription() const{
			return this->mDescription;
		}

		bool isRequired() const{
			return this->mRequired;
		}

		void setRequired(const bool& required = true){
			this->mRequired = required;
		}

		virtual std::string getTypeStr() const = 0;

	protected:
		ParameterType mType;
		std::string mName;
		std::string mDescription;
		bool mRequired;

	};


	template<class T>
	class ParameterValue : public IParameterValue {

	public:
		ParameterValue(void) : IParameterValue(){}

		ParameterValue(const ParameterType& parameterType, const std::string& name, const std::string& description)
			: IParameterValue(parameterType, name, description){

		}

		virtual ~ParameterValue(void){}

		ParameterValue(const ParameterValue& rhs)
			:IParameterValue(rhs){
			this->mValue = rhs.mValue;
		}

		ParameterValue& operator=(const ParameterValue& rhs){
			if (this != &rhs){
				IParameterValue::operator=(rhs);
				this->mValue = rhs.mValue;
			}
			return *this;
		}

		T getValue() const {
			return this->mValue;
		}

		void setValue(const T& value){
			this->mValue = value;
		}

		virtual std::string getTypeStr() const{
			return typeid(T).name();
		}

	protected:
		T mValue;

	};

}
#endif // !_SSF_CORE_PARAMETER_VALUE_HPP_