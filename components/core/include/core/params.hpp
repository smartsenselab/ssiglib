#ifndef _SSF_CORE_PARAMETER_LIST_HPP_
#define _SSF_CORE_PARAMETER_LIST_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "core/param.hpp"

namespace ssf{

	class Params{

	public:
		Params(void);
		virtual ~Params(void);
		Params(const Params& rhs);
		Params& operator=(const Params& rhs);

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


		template < class T>
		void setValue(const std::string& paramName, const T& value){
			this->getParamByName(paramName).setValue<T>(value);
		}

		template < class T>
		T getValue(const std::string& paramName){
			return this->getParamByName(paramName).getValue<T>();
		}

		std::map<std::string, Param> getParameters() const;

	private:
		Param& getParamByName(const std::string& paramName);
		std::map<std::string, Param> mParameters;

	};

}

#endif // !_SSF_CORE_PARAMETER_LIST_HPP_