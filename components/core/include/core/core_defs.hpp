#ifndef _SSF_CORE_DEFS_HPP_
#define _SSF_CORE_DEFS_HPP_

namespace ssf{

//#if !defined _CRT_SECURE_NO_DEPRECATE && defined _MSC_VER && _MSC_VER > 1300
//#  define _CRT_SECURE_NO_DEPRECATE /* to avoid multiple Visual Studio warnings */
//# define _SCL_SECURE_NO_WARNINGS
//#endif

#if (defined _MSC_VER)
	#pragma warning(disable:4996) // disable deprecated warning 
#endif


#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
	#if defined  CORE_API_EXPORTS
		#define  CORE_EXPORT __declspec(dllexport)
	#else
		#define  CORE_EXPORT __declspec(dllimport)
	#endif
#else
	#define CORE_EXPORT
#endif

}

#endif // !_SSF_CORE_DEFS_HPP_