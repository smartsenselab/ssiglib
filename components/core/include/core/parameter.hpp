#ifndef _SSF_CORE_PARAMETER_HPP_
#define _SSF_CORE_PARAMETER_HPP_

#include <string>
#include <memory>

#include "core/parameter_exception.hpp"
#include "core/file_handle.hpp"
#include "core/directory_handle.hpp"

// TODO Set Parameters constructors as protected
// TODO Type Check

namespace ssf{

	enum class ParamType{
		INVALID_PARAMTYPE, INT, LONG, FLOAT, DOUBLE, BOOL, STRING, FILE, DIRECTORY
	};

	

	class IParameter{

	public:

		IParameter(const std::string& name = DEFAULT_NAME, const std::string& description = DEFAULT_DESCRIPTION, 
				const bool& required = false){
			this->mName = std::make_shared<std::string>(name);
			this->mDescription = std::make_shared<std::string>(description);
			this->mRequired = std::make_shared<bool>(required);
			this->mChanged = std::make_shared<bool>(false);
		}

		virtual ~IParameter(void){
			//destructor
		}

		IParameter(const IParameter& rhs){
			this->mName = rhs.mName;
			this->mDescription = rhs.mDescription;
			this->mRequired = rhs.mRequired;
			this->mChanged = rhs.mChanged;
		}

		IParameter& operator=(const IParameter& rhs){
			if (this != &rhs){
				this->mName = rhs.mName;
				this->mDescription = rhs.mDescription;
				this->mRequired = rhs.mRequired;
				this->mChanged = rhs.mChanged;
			}
			return *this;
		}

		std::string getName() const {
			return *(this->mName);
		}

		void setName(const std::string val) {
			*(this->mName) = val;
		}

		std::string getDescription() const {
			return *(this->mDescription);
		}

		void setDescription(std::string description) {
			*(this->mDescription) = description;
		}

		bool getRequired() const {
			return *(this->mRequired);
		}

		void setRequired(const bool& required) {
			*(this->mRequired) = required;
		}

		bool changed() const {
			return *(this->mChanged);
		}

		virtual ParamType getParamType() const = 0;
		
	protected:
		std::shared_ptr<std::string> mName;
		std::shared_ptr<std::string> mDescription;
		std::shared_ptr<bool> mRequired;
		std::shared_ptr<bool> mChanged;

		static const std::string DEFAULT_NAME;
		static const std::string DEFAULT_DESCRIPTION;

	};

	const std::string IParameter::DEFAULT_NAME = "Unnamed Parameter";
	const std::string IParameter::DEFAULT_DESCRIPTION = "No description has been for this parameter";


	template<class T>
	class Parameter : public IParameter {

	public:

		Parameter(void)
			:IParameter(){
			this->mValue = nullptr;
			if (!this->checkType()){
				std::string message = "Invalid type: " + std::string(typeid(T).name()) +
					" (The parameter type must be: int, long, float, double, bool, string, ssf::FileHandle, ssf::DirectoryHandle).";
					throw ParameterException("Undefined Parameter", message);
			}
		}

		Parameter(const T& defaultValue, const std::string& name = DEFAULT_NAME,
			const std::string& description = DEFAULT_DESCRIPTION, const bool& required = false)
			: IParameter(name, description, required){

			this->mValue = std::make_shared<T>(defaultValue);
		}

		virtual ~Parameter(void){
		}

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
			return *(this->mValue);
		}

		void setValue(const T& value) {
			*(this->mValue) = value;
			*(this->mChanged) = true;
		}

		virtual ParamType getParamType() const{
			if (std::is_same<T, int>::value) return ParamType::INT;
			if (std::is_same<T, long>::value) return ParamType::LONG;
			if (std::is_same<T, float>::value) return ParamType::FLOAT;
			if (std::is_same<T, double>::value) return ParamType::DOUBLE;
			if (std::is_same<T, bool>::value) return ParamType::BOOL;
			if (std::is_same<T, std::string>::value) return ParamType::STRING;
			if (std::is_same<T, FileHandle>::value) return ParamType::FILE;
			if (std::is_same<T, DirectoryHandle>::value) return ParamType::DIRECTORY;
			
			return ParamType::INVALID_PARAMTYPE;
		}

	private:
		bool checkType() const{
			return (this->getParamType() != ParamType::INVALID_PARAMTYPE);
		}

	protected:
		std::shared_ptr<ParamType> mValue;

	};

}

#endif // !_SSF_CORE_PARAMETER_HPP_