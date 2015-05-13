#ifndef _SSF_CORE_PLUGIN_DEFS_HPP_
#define _SSF_CORE_PLUGIN_DEFS_HPP_


#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
	#define PLUGIN_EXPORT __declspec(dllexport)
#else
	#define PLUGIN_EXPORT
#endif

#define PLUGIN_CREATE_FUNCTION	"createPluginFacade"
#define PLUGIN_DESTROY_FUNCTION	"destroyPluginFacade"

#define PLUGIN_FACTORY_DECLARATION(T)               \
extern "C"{                                         \
PLUGIN_EXPORT T* createPluginFacade();                 \
PLUGIN_EXPORT void destroyPluginFacade();              \
}

#define PLUGIN_FACTORY_DEFINITION(T)    \
T* globalInstance = NULL;               \
T* createPluginFacade()                 \
    if (!globalInstance)                \
        globalInstance = new T();       \
    return globalInstance;              \
}                                       \
void destroyPluginFacade()              \
    if (globalInstance){                \
        delete globalInstance;          \
        globalInstance = NULL;          \
    }                                   \
}

#endif // !_SSF_CORE_PLUGIN_DEFS_HPP_