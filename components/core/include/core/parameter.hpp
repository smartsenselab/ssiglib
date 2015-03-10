#ifndef _SSF_CORE_PARAMETER_HPP_
#define _SSF_CORE_PARAMETER_HPP_

#include <string>
#include <memory>

#include "core/parameter_exception.hpp"

// TODO Set Parameters constructors as protected

namespace ssf{

	enum class ParamTypeID{
		INTEGER, REAL, STRING, FILE, DIRECTORY, BOOL
	};

	class IParameter{

	public:

		IParameter(const std::string& name = "", const std::string& description = "", const bool& required = false){
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

		virtual ParamTypeID getParamType() const = 0;

	protected:
		std::shared_ptr<std::string> mName;
		std::shared_ptr<std::string> mDescription;
		std::shared_ptr<bool> mRequired;
		std::shared_ptr<bool> mChanged;

	};


	template<class ParamType>
	class Parameter : public IParameter {

	public:

		Parameter(void)
			:IParameter(){
			this->mValue = nullptr;
		}

		Parameter(const ParamType& defaultValue, const std::string& name = "", 
			const std::string& description = "", const bool& required = false)
			: IParameter(name, description, required){
			this->mValue = std::make_shared<ParamType>(defaultValue);
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

		ParamType getValue() const {
			return *(this->mValue);
		}

		void setValue(const ParamType& value) {
			*(this->mValue) = value;
			*(this->mChanged) = true;
		}

	protected:
		std::shared_ptr<ParamType> mValue;

	};

}

#endif // !_SSF_CORE_PARAMETER_HPP_