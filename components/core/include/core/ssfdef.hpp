#ifndef _SSF_CORE_UTIL_HPP_
#define _SSF_CORE_UTIL_HPP_

namespace ssf{

#if !defined _CRT_SECURE_NO_DEPRECATE && defined _MSC_VER && _MSC_VER > 1300
#  define _CRT_SECURE_NO_DEPRECATE /* to avoid multiple Visual Studio warnings */
#endif


#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
	#if defined SSFAPI_EXPORTS
		#define  SSF_EXPORT __declspec(dllexport)
	#else
		#define  SSF_EXPORT __declspec(dllimport)
	#endif
#else
	#define SSF_EXPORT
#endif

}

#endif // !_SSF_CORE_UTIL_HPP_