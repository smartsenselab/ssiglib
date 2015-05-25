#ifndef _SSF_API_STREAM_HPP_
#define _SSF_API_STREAM_HPP_

#include <string>

#include "configuration/configuration_defs.hpp"

namespace ssf{

	class Stream{
	
	public:
        CONFIG_EXPORT Stream();
		CONFIG_EXPORT Stream(const std::string& moduleIDProvider, const std::string& outputProvider, const std::string& moduleIDReceiver, const std::string inputReceiver);
		CONFIG_EXPORT virtual ~Stream(void);
		CONFIG_EXPORT Stream(const Stream& rhs);
		CONFIG_EXPORT Stream& operator=(const Stream& rhs);
        
		CONFIG_EXPORT std::string getModuleIDProvider();
		CONFIG_EXPORT std::string getModuleIDReceiver();
		CONFIG_EXPORT std::string getOutputProvider();
		CONFIG_EXPORT std::string getInputReceiver();

	private:
        std::string mModuleIDProvider;
        std::string mModuleIDReceiver;
        std::string mOutputProvider;
        std::string mInputReceiver;
	};

}

#endif // !_SSF_API_STREAM_HPP_