#ifndef _SSF_CORE_LOG_HPP_
#define _SSF_CORE_LOG_HPP_

#include <string>

namespace ssf{

	enum class LogFilter{
		DEBUG, INFO, WARNING, ERROR
	};

	class Log{
	public:

		//Log::setFilter(LogFilter::INFO)

		static void init();
		static void setFilter(LogFilter filter);
		static void INFO(std::string message);
		static void ERROR(std::string message);
		static void DEBUG(std::string message);
		static void WARNING(std::string message);


	};

}

#endif // !_SSF_CORE_LOG_HPP_