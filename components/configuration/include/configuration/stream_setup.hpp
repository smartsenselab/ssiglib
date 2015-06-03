#ifndef _SSF_API_STREAM_SETUP_HPP_
#define _SSF_API_STREAM_SETUP_HPP_

#include <string>
#include "configuration/setup_defs.hpp"

namespace ssf{

	class StreamSetup{
	
	public:
        CONFIG_EXPORT StreamSetup();
		CONFIG_EXPORT StreamSetup(const std::string& moduleIDProvider, const std::string& outputProvider, const std::string& moduleIDReceiver, const std::string inputReceiver);
		CONFIG_EXPORT virtual ~StreamSetup(void);
		CONFIG_EXPORT StreamSetup(const StreamSetup& rhs);
		CONFIG_EXPORT StreamSetup& operator=(const StreamSetup& rhs);
        
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

#endif // !_SSF_API_STREAM_SETUP_HPP_