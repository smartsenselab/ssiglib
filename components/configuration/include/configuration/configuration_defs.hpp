#ifndef _SSF_CONFIGURATION_DEFS_HPP_
#define _SSF_CONFIGURATION_DEFS_HPP_

namespace ssf{

#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
	#if defined CONFIG_API_EXPORTS
		#define  CONFIG_EXPORT __declspec(dllexport)
	#else
		#define  CONFIG_EXPORT __declspec(dllimport)
	#endif
#else
		#define CONFIG_EXPORT
#endif

}

#endif // !_SSF_CONFIGURATION_DEFS_HPP_