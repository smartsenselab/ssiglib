#ifndef _SSF_CORE_LOG_HPP_
#define _SSF_CORE_LOG_HPP_

#include <string>

#include "core/ssfdef.hpp"

namespace ssf{

	enum class SSF_EXPORT LogFilter{
		DEBUG, INFO, WARNING, ERROR
	};

	class Log{
	public:

		//Log::setFilter(LogFilter::INFO)
		SSF_EXPORT static void outputConsole(const bool& option);
		
		SSF_EXPORT static void outputFile(const bool& option, const std::string& fileName = "output.log");

		//static void init();
		SSF_EXPORT static void setFilter(const LogFilter& filter);
		SSF_EXPORT static void INFO(const std::string& message);
		SSF_EXPORT static void ERROR(const std::string& message);
		SSF_EXPORT static void DEBUG(const std::string& message);
		SSF_EXPORT static void WARNING(const std::string& message);


	};

}

#endif // !_SSF_CORE_LOG_HPP_