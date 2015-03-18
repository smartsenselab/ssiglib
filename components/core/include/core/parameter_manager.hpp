#ifndef _SSF_CORE_PARAMETER_MANAGER_HPP_
#define _SSF_CORE_PARAMETER_MANAGER_HPP_

#include <string>
#include <map>
#include <memory>

#include "core/parameter.hpp"

namespace ssf{

	class ParameterManager{
	
	public:
		ParameterManager(void);
		virtual ~ParameterManager(void);
		ParameterManager(const ParameterManager& rhs);
		ParameterManager& operator=(const ParameterManager& rhs);

		template<class T> void registerParameter(Parameter<T>& parameter, std::string name,
			const std::string& description = IParameter::DEFAULT_DESCRIPTION,
			const bool& required = false, const T& defaultValue = T()
			){
			if (this->mParameters.find(name) != mParameters.end()){
				std::string message = "A parameter with name \"" + name + "\"was already registered.";
				throw ParameterException(name, message);
			}
			if (*(parameter.mRegistered))
				throw ParameterException(parameter.getName(), "This parameter was already registered.");
			*(parameter.mName) = name;
			*(parameter.mDescription) = description;
			*(parameter.mRequired) = required;
			*(parameter.mValue) = defaultValue;
			*(parameter.mRegistered) = true;
			std::shared_ptr<Parameter<T>> paramTemp = std::make_shared<Parameter<T>>(parameter);
			this->mParameters[name] = paramTemp;
		}

		template<class T> bool setValue(const std::string& parameterName, const T& value){
			if (this->mParameters.find(parameterName) == mParameters.end()){
				std::string message = "There isn't a parameter with such name: \"" + parameterName + 
					"\". Please, verify the correct parameter name.";
				throw ParameterException(parameterName, message);
			}
			auto ptrValue = std::dynamic_pointer_cast<Parameter<T>, IParameter>(this->mParameters[parameterName])->mValue;
			*ptrValue = value;
			return true;
		}

	private:
		std::map<std::string, std::shared_ptr<IParameter>> mParameters;

	};

}

#endif // !_SSF_CORE_PARAMETER_MANAGER_HPP_