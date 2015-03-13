#ifndef _SSF_CORE_PARAMETER_MANAGER_HPP_
#define _SSF_CORE_PARAMETER_MANAGER_HPP_

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

		template<class T> Parameter<T> makeParameter(const T& defaultValue, const std::string& name,
			const std::string& description = IParameter::DEFAULT_DESCRIPTION, const bool& required = false){
			
			Parameter<T> newParameter;
			*(newParameter.mValue) = defaultValue;
			*(newParameter.mName) = name;
			*(newParameter.mDescription) = description;
			*(newParameter.mRequired) = required;
			
			this->mParameters[newParameter.getName()] = std::make_shared<Parameter<T>>(newParameter);
			*(newParameter.mRegistered) = true;

			return newParameter;

		}

		/*template<class ParamType> bool setParameterValue(const std::string& parameterName, const ParamType& value){
			auto tempParameter = this->mParameters[parameterName];
			()tempParameter
		}*/

	private:
		std::map<std::string, std::shared_ptr<IParameter>> mParameters;

	};

}

#endif // !_SSF_CORE_PARAMETER_MANAGER_HPP_