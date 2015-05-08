#include "core/util.hpp"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace ssf{

	std::string & Util::ltrim(std::string &str){
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return str;
	}

	std::string & Util::rtrim(std::string &str){
		str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
		return str;
	}

	std::string & Util::trim(std::string &str){
		return ltrim(rtrim(str));
	}

}

