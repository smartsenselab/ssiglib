#ifndef _SSF_CORE_RESOURCE_SETUP_HPP_
#define _SSF_CORE_RESOURCE_SETUP_HPP_

#include <map>

#include "core/base.hpp"
#include "core/parameter.hpp"

namespace ssf{

	class ResourceSetup{
	
	public:
		SSF_EXPORT ResourceSetup(const std::string& resourceName = "");
		SSF_EXPORT virtual ~ResourceSetup(void);
		SSF_EXPORT ResourceSetup(const ResourceSetup& rhs);
		SSF_EXPORT ResourceSetup& operator=(const ResourceSetup& rhs);
		
		template < class T>
		SSF_EXPORT void setParam(const std::string& paramName, const ParamType& paramType, const T& value){
			if (this->mParams.find(paramName) == this->mParams.end())
				this->mParams[paramName] = Parameter(paramType, paramName, "");
			this->mParams[paramName].setValue<T>(value);
		}

		SSF_EXPORT const std::map<std::string, Parameter>& getParams() const;

	private:
		std::string mResourceName;
		std::map<std::string, Parameter> mParams;

	};

}

#endif // !_SSF_CORE_RESOURCE_SETUP_HPP_