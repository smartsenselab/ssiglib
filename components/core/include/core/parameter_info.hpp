#ifndef _SSF_CORE_PARAMETER_INFO_HPP_
#define _SSF_CORE_PARAMETER_INFO_HPP_

#include "core/parameter.hpp"

namespace ssf{

	class ParameterInfo{
	
	public:
		ParameterInfo(void);
		virtual ~ParameterInfo(void);
		ParameterInfo(const ParameterInfo& rhs);
		ParameterInfo& operator=(const ParameterInfo& rhs);

		ParamType getType() const;
		std::string getName() const;
		std::string getDescription() const;
		bool isRequired() const;
		long getMaxValue() const;
		long getMinValue() const;

	private:
		Parameter mParameter;

	};

}

#endif // !_SSF_CORE_PARAMETER_INFO_HPP_