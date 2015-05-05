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
		Parameters(void);
		virtual ~Parameters(void);
		Parameters(const Parameters& rhs);
		Parameters& operator=(const Parameters& rhs);

		void addParameter(const ParamType& type, const std::string& name, const std::string& description);

		ParamType getType(const std::string& paramName);
		std::string getName(const std::string& paramName);
		std::string getDescription(const std::string& paramName);

		bool isNumeric(const std::string& paramName);
		bool isIntegral(const std::string& paramName);
		bool isFloating(const std::string& paramName);
		bool isBoolean(const std::string& paramName);
		bool isString(const std::string& paramName);
		bool exists(const std::string& paramName);

		void setRequired(const std::string& paramName, const bool& required = true);
		bool isRequired(const std::string& paramName);

		long getMaxValue(const std::string& paramName);
		void setMaxValue(const std::string& paramName, const long& maxValue);
		long getMinValue(const std::string& paramName);
		void setMinValue(const std::string& paramName, const long& minValue);


		template < class T>
		void setValue(const std::string& paramName, const T& value){
			this->getParamByName(paramName).setValue<T>(value);
		}

		template < class T>
		void setDefaultValue(const std::string& paramName, const T& value){
			this->getParamByName(paramName).setDefaultValue<T>(value);
		}

		template < class T>
		T getValue(const std::string& paramName){
			return this->getParamByName(paramName).getValue<T>();
		}

		const std::map<std::string, Parameter>& getParameters() const;
        
		void setup(std::map<std::string, Parameter>& paramsSetup);

	private:
		Parameter& getParamByName(const std::string& paramName);
		std::map<std::string, Parameter> mParameters;

	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_