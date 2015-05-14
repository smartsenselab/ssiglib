#ifndef _SSF_CORE_RESOURCE_SETUP_HPP_
#define _SSF_CORE_RESOURCE_SETUP_HPP_

#include <map>

#include "core/core_defs.hpp"
#include "core/parameter.hpp"

namespace ssf{

	class ResourceSetup{
	
	public:
		CORE_EXPORT ResourceSetup(const std::string& resourceName = "");
		CORE_EXPORT virtual ~ResourceSetup(void);
		CORE_EXPORT ResourceSetup(const ResourceSetup& rhs);
		CORE_EXPORT ResourceSetup& operator=(const ResourceSetup& rhs);
		
		template < class T>
		CORE_EXPORT void setParam(const std::string& paramName, const ParamType& paramType, const T& value){
			if (this->mParams.find(paramName) == this->mParams.end())
				this->mParams[paramName] = Parameter(paramType, paramName, "");
			this->mParams[paramName].setValue<T>(value);
		}

		CORE_EXPORT const std::map<std::string, Parameter>& getParams() const;

	private:
		std::string mResourceName;
		std::map<std::string, Parameter> mParams;

	};

}

#endif // !_SSF_CORE_RESOURCE_SETUP_HPP_