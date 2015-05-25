#ifndef _SSF_CORE_PARAMETER_INFO_HPP_
#define _SSF_CORE_PARAMETER_INFO_HPP_

#include <string>
#include "core/parameter.hpp"

namespace ssf{

	class ParameterInfo{

	public:
		CORE_EXPORT ParameterInfo(void);
		CORE_EXPORT ParameterInfo(const Parameter& parameter);
		CORE_EXPORT virtual ~ParameterInfo(void);
		CORE_EXPORT ParameterInfo(const ParameterInfo& rhs);
		CORE_EXPORT ParameterInfo& operator=(const ParameterInfo& rhs);

		CORE_EXPORT std::string getName() const;
		CORE_EXPORT std::string getDescription() const;
		CORE_EXPORT ParamType getExpectedType() const;
		CORE_EXPORT bool isRequired() const;

		CORE_EXPORT std::string getDefaultValue() const;
		CORE_EXPORT std::string getValue() const;
		CORE_EXPORT std::vector<std::string> getDefaultVectorValue() const;
		CORE_EXPORT std::vector<std::string> getVectorValue() const;

	private:
		Parameter mParameter;

	};

}

#endif // !_SSF_CORE_PARAMETER_INFO_HPP_