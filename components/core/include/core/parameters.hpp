#ifndef _SSF_CORE_PARAMETER_LIST_HPP_
#define _SSF_CORE_PARAMETER_LIST_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "core/parameter.hpp"

namespace ssf{

	class Parameters{

	public:
		CORE_EXPORT Parameters(void);
		CORE_EXPORT virtual ~Parameters(void);
		CORE_EXPORT Parameters(const Parameters& rhs);
		CORE_EXPORT Parameters& operator=(const Parameters& rhs);

		CORE_EXPORT void addParameter(const ParamType& type, const std::string& name, const std::string& description);

		CORE_EXPORT ParamType getType(const std::string& paramName);
		CORE_EXPORT std::string getName(const std::string& paramName);
		CORE_EXPORT std::string getDescription(const std::string& paramName);

		CORE_EXPORT bool isNumeric(const std::string& paramName);
		CORE_EXPORT bool isIntegral(const std::string& paramName);
		CORE_EXPORT bool isFloating(const std::string& paramName);
		CORE_EXPORT bool isBoolean(const std::string& paramName);
		CORE_EXPORT bool isString(const std::string& paramName);
		CORE_EXPORT bool exists(const std::string& paramName);

		CORE_EXPORT void setRequired(const std::string& paramName, const bool& required = true);
		CORE_EXPORT bool isRequired(const std::string& paramName);

		CORE_EXPORT long getMaxValue(const std::string& paramName);
		CORE_EXPORT void setMaxValue(const std::string& paramName, const long& maxValue);
		CORE_EXPORT long getMinValue(const std::string& paramName);
		CORE_EXPORT void setMinValue(const std::string& paramName, const long& minValue);


		template < class T>
		CORE_EXPORT void setValue(const std::string& paramName, const T& value){
			this->getParamByName(paramName).setValue<T>(value);
		}

		template < class T>
		CORE_EXPORT void setDefaultValue(const std::string& paramName, const T& value){
			this->getParamByName(paramName).setDefaultValue<T>(value);
		}

		template < class T>
		CORE_EXPORT T getValue(const std::string& paramName){
			return this->getParamByName(paramName).getValue<T>();
		}




		CORE_EXPORT const std::map<std::string, Parameter>& getParameters() const;
		CORE_EXPORT void setup(std::map<std::string, Parameter>& paramsSetup);


	private:
		CORE_EXPORT Parameter& getParamByName(const std::string& paramName);
		std::map<std::string, Parameter> mParameters;

	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_