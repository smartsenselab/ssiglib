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

		template<class ParamType> bool registerParameter(Parameter<ParamType>& parameter){
			this->mParameters[parameter.getName()] = std::make_shared<Parameter<ParamType>>(parameter);
			std::string a = this->mParameters[parameter.getName()]->getName();
			return true;
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