#ifndef _SSF_CORE_PARAMETER_HPP_
#define _SSF_CORE_PARAMETER_HPP_

#include <string>
#include <memory>

#include "core/parameter_exception.hpp"
#include "core/file_handle.hpp"
#include "core/directory_handle.hpp"

namespace ssf{

	enum class ParameterType{
		INVALID_PARAMTYPE, INT, LONG, FLOAT, DOUBLE, BOOL, STRING, FILE_HANDLE, DIRECTORY_HANDLE
	};


	class IParameter{
		friend class ParameterBook;

	public:
		IParameter(void){
			this->mName = std::make_shared<std::string>(DEFAULT_NAME);
			this->mDescription = std::make_shared<std::string>(DEFAULT_DESCRIPTION);
			this->mRequired = std::make_shared<bool>(false);
			this->mRegistered = std::make_shared<bool>(false);
		}

		virtual ~IParameter(void){}

		IParameter(const IParameter& rhs){
			this->mName = rhs.mName;
			this->mDescription = rhs.mDescription;
			this->mRequired = rhs.mRequired;
			this->mRegistered = rhs.mRegistered;
		}

		IParameter& operator=(const IParameter& rhs){
			if (this != &rhs){
				this->mName = rhs.mName;
				this->mDescription = rhs.mDescription;
				this->mRequired = rhs.mRequired;
				this->mRegistered = rhs.mRegistered;
			}
			return *this;
		}

		std::string getName() const {
			if (!*(this->mRegistered))
				throw ParameterException("Undefined Parameter", "This parameter must be registered");
			return *(this->mName);
		}

		std::string getDescription() const {
			if (!*(this->mRegistered))
				throw ParameterException("Undefined Parameter", "This parameter must be registered");
			return *(this->mDescription);
		}

		bool getRequired() const {
			if (!*(this->mRegistered))
				throw ParameterException("Undefined Parameter", "This parameter must be registered");
			return *(this->mRequired);
		}

		virtual ParameterType getType() const = 0;

	protected:
		std::shared_ptr<std::string> mName;
		std::shared_ptr<std::string> mDescription;
		std::shared_ptr<bool> mRequired;
		std::shared_ptr<bool> mRegistered;

		static const std::string DEFAULT_NAME;
		static const std::string DEFAULT_DESCRIPTION;

	};



	template<class T>
	class Parameter : public IParameter {
		friend class ParameterBook;

	public:
		Parameter(void) : IParameter(){
			this->mValue = std::make_shared<T>();
			if (!this->checkType()){
				std::string message = "Invalid type: " + std::string(typeid(T).name()) +
					" (The parameter type must be: int, long, float, double, bool, string, ssf::FileHandle, ssf::DirectoryHandle).";
				throw ParameterException("Undefined Parameter", message);
			}
		}
		
		virtual ~Parameter(void){}

		Parameter(const Parameter& rhs)
			:IParameter(rhs){
			this->mValue = rhs.mValue;
		}

		Parameter& operator=(const Parameter& rhs){
			if (this != &rhs){
				IParameter::operator=(rhs);
				this->mValue = rhs.mValue;
			}
			return *this;
		}

		T getValue() const {
			if (!*(this->mRegistered))
				throw ParameterException("Undefined Parameter", "This parameter must be registered");
			return *(this->mValue);
		}

		virtual ParameterType getType() const{
			if (std::is_same<T, int>::value) return ParameterType::INT;
			if (std::is_same<T, long>::value) return ParameterType::LONG;
			if (std::is_same<T, float>::value) return ParameterType::FLOAT;
			if (std::is_same<T, double>::value) return ParameterType::DOUBLE;
			if (std::is_same<T, bool>::value) return ParameterType::BOOL;
			if (std::is_same<T, std::string>::value) return ParameterType::STRING;
			if (std::is_same<T, FileHandle>::value) return ParameterType::FILE_HANDLE;
			if (std::is_same<T, DirectoryHandle>::value) return ParameterType::DIRECTORY_HANDLE;

			return ParameterType::INVALID_PARAMTYPE;
		}

	private:
		bool checkType() const{
			return (this->getType() != ParameterType::INVALID_PARAMTYPE);
		}

	protected:
		std::shared_ptr<T> mValue;

	};

}

#endif // !_SSF_CORE_PARAMETER_HPP_