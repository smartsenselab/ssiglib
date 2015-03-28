#ifndef _SSF_CORE_RESOURCE_SETUP_HPP_
#define _SSF_CORE_RESOURCE_SETUP_HPP_

#include <core/params.hpp>

namespace ssf{

	class ResourceSetup{
	
	public:
		ResourceSetup(const std::string& resourceName = "");
		virtual ~ResourceSetup(void);
		ResourceSetup(const ResourceSetup& rhs);
		ResourceSetup& operator=(const ResourceSetup& rhs);
		
		template < class T>
		void setParam(const std::string& paramName, const ParamType& paramType, const T& value){
			if (!this->mParams.exists(paramName))
				this->mParams.addParameter(paramType, paramName, "");
			this->mParams.setValue<T>(paramName, value);
		}

	private:
		std::string mResourceName;
		Params mParams;

	};

}

#endif // !_SSF_CORE_RESOURCE_SETUP_HPP_