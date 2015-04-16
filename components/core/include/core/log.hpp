#ifndef _SSF_CORE_LOG_HPP_
#define _SSF_CORE_LOG_HPP_

#include <string>

namespace ssf{

	class Log{
	public:

		static void init();
		/*static void setFilter(std::string filter);*/
		static void INFO(std::string message);
		static void ERROR(std::string message);
		static void DEBUG(std::string message);
		static void WARNING(std::string message);


	};

}

#endif // !_SSF_CORE_LOG_HPP_