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
		SSF_EXPORT Parameters(void);
		SSF_EXPORT virtual ~Parameters(void);
		SSF_EXPORT Parameters(const Parameters& rhs);
		SSF_EXPORT Parameters& operator=(const Parameters& rhs);

		SSF_EXPORT void addParameter(const ParamType& type, const std::string& name, const std::string& description);

		SSF_EXPORT ParamType getType(const std::string& paramName);
		SSF_EXPORT std::string getName(const std::string& paramName);
		SSF_EXPORT std::string getDescription(const std::string& paramName);

		SSF_EXPORT bool isNumeric(const std::string& paramName);
		SSF_EXPORT bool isIntegral(const std::string& paramName);
		SSF_EXPORT bool isFloating(const std::string& paramName);
		SSF_EXPORT bool isBoolean(const std::string& paramName);
		SSF_EXPORT bool isString(const std::string& paramName);
		SSF_EXPORT bool exists(const std::string& paramName);

		SSF_EXPORT void setRequired(const std::string& paramName, const bool& required = true);
		SSF_EXPORT bool isRequired(const std::string& paramName);

		SSF_EXPORT long getMaxValue(const std::string& paramName);
		SSF_EXPORT void setMaxValue(const std::string& paramName, const long& maxValue);
		SSF_EXPORT long getMinValue(const std::string& paramName);
		SSF_EXPORT void setMinValue(const std::string& paramName, const long& minValue);


		template < class T>
		SSF_EXPORT void setValue(const std::string& paramName, const T& value){
			this->getParamByName(paramName).setValue<T>(value);
		}

		template < class T>
		SSF_EXPORT void setDefaultValue(const std::string& paramName, const T& value){
			this->getParamByName(paramName).setDefaultValue<T>(value);
		}

		template < class T>
		SSF_EXPORT T getValue(const std::string& paramName){
			return this->getParamByName(paramName).getValue<T>();
		}




		SSF_EXPORT const std::map<std::string, Parameter>& getParameters() const;
		SSF_EXPORT void setup(std::map<std::string, Parameter>& paramsSetup);


	private:
		SSF_EXPORT Parameter& getParamByName(const std::string& paramName);
		std::map<std::string, Parameter> mParameters;

	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_