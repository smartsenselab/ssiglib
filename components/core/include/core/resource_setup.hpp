#ifndef _SSF_CORE_RESOURCE_SETUP_HPP_
#define _SSF_CORE_RESOURCE_SETUP_HPP_

#include <map>

#include "core/parameter.hpp"

namespace ssf{

	class ResourceSetup{
	
	public:
		ResourceSetup(const std::string& resourceName = "");
		virtual ~ResourceSetup(void);
		ResourceSetup(const ResourceSetup& rhs);
		ResourceSetup& operator=(const ResourceSetup& rhs);
		
		template < class T>
		void setParam(const std::string& paramName, const ParamType& paramType, const T& value){
			if (this->mParams.find(paramName) == this->mParams.end())
				this->mParams[paramName] = Parameter(paramType, paramName, "");
			this->mParams[paramName].setValue<T>(value);
		}

		const std::map<std::string, Parameter>& getParams() const;

	private:
		std::string mResourceName;
		std::map<std::string, Parameter> mParams;

	};

}

#endif // !_SSF_CORE_RESOURCE_SETUP_HPP_