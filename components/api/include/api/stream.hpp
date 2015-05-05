#ifndef _SSF_API_STREAM_HPP_
#define _SSF_API_STREAM_HPP_

#include <string>

namespace ssf{

	class Stream{
	
	public:
        Stream(const std::string& moduleIDProvider, const std::string& outputProvider, const std::string& moduleIDReceiver, const std::string inputReceiver);
		virtual ~Stream(void);
		Stream(const Stream& rhs);
		Stream& operator=(const Stream& rhs);
        
        std::string getModuleIDProvider();
        std::string getModuleIDReceiver();
        std::string getOutputProvider();
        std::string getInputReceiver();

	private:
        std::string mModuleIDProvider;
        std::string mModuleIDReceiver;
        std::string mOutputProvider;
        std::string mInputReceiver;
	};

}

#endif // !_SSF_API_STREAM_HPP_