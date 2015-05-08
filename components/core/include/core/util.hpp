#ifndef _SSF_CORE_UTIL_HPP_
#define _SSF_CORE_UTIL_HPP_

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>

namespace ssf{

	class Util{

	public:

		// trim from start
		static std::string &ltrim(std::string &str);

		// trim from end
		static std::string &rtrim(std::string &str);

		// trim from both ends
		static std::string &trim(std::string &str);

	};

}

#endif // !_SSF_CORE_UTIL_HPP_