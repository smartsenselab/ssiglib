#ifndef _SSF_CORE_PLUGIN_HPP_
#define _SSF_CORE_PLUGIN_HPP_

#include "core/version_info.hpp"
#include <string>

namespace ssf{

	class IPlugin {

	public:	
		virtual const std::string& getName() const = 0;
		virtual const ssf::VersionInfo& getVersion() const = 0;

	protected:
		virtual ~IPlugin() {}

	};

}

#endif // !_SSF_CORE_PLUGIN_HPP_