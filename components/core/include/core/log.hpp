#ifndef _SSF_CORE_LOG_HPP_
#define _SSF_CORE_LOG_HPP_

#include <string>

#include "core/core_defs.hpp"

namespace ssf{

	enum class CORE_EXPORT LogFilter{
		DEBUG, INFO, WARNING, ERROR
	};

	class Log{
	public:

		//Log::setFilter(LogFilter::INFO)
		CORE_EXPORT static void outputConsole(const bool& option);
		
		CORE_EXPORT static void outputFile(const bool& option, const std::string& fileName = "output.log");

		//static void init();
		CORE_EXPORT static void setFilter(const LogFilter& filter);
		CORE_EXPORT static void INFO(const std::string& message);
		CORE_EXPORT static void ERROR(const std::string& message);
		CORE_EXPORT static void DEBUG(const std::string& message);
		CORE_EXPORT static void WARNING(const std::string& message);


	};

}

#endif // !_SSF_CORE_LOG_HPP_