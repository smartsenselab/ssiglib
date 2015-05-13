#ifndef _SSF_CORE_PLUGIN_LOADER_HPP_
#define _SSF_CORE_PLUGIN_LOADER_HPP_

#include "core/core_defs.hpp"
#include "plugin_defs.hpp"


#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif


namespace ssf{

	template<class T>
	class PluginLoader{

	public:

		explicit PluginLoader(const std::string& pluginName = "")
			: mPluginName(pluginName), mPlugin(nullptr), mHandle(0){
		}

		virtual ~PluginLoader(){
			this->unload();
		}

		bool load(){
			if (this->isLoaded())
				this->unload();
			if (this->mPluginName.empty())
				return false;
			return this->loadLibrary();
		}

		bool unload(){
			bool res = true;
			if (this->isLoaded()){
				if (this->mPlugin){
					this->callFunction<void>(PLUGIN_FACTORY_DESTROY);
					this->mPlugin = nullptr;
				}
				res = this->unloadLibrary();
				if (res)
					mHandle = 0;
			}
			return res;
		}

		bool isLoaded() const{
			return (this->mHandle != 0);
		}


		T* getPluginInstance(){
			if (!isLoaded())
				return nullptr;
			if (!this->mPlugin)
				this->mPlugin = callFunction<T*>(PLUGIN_FACTORY_CREATE);
			return this->mPlugin;
		}

		std::string getErrorMessage() const{
			return this->errorMessage;
		}

		const std::string& getPluginName() const{
			return this->mPluginName;
		}

		void setPluginName(const std::string& pluginName){
			this->mPluginName = pluginName;
		}



	private:

#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
		typedef HMODULE LibraryHandle;
		typedef FARPROC GenericFunction;
#else
		typedef void * LibraryHandle;
		typedef void * GenericFunction;
#endif

#ifdef _MSC_VER
# pragma warning (push)
# pragma warning (disable: 4191)
#endif

		template<class R>
		R callFunction(const char* function_name){
			R(*func)();
			func = reinterpret_cast<R(*)()>(getFunction(function_name));
			assert(func);
			return (*func)();
		}

#ifdef _MSC_VER
# pragma warning (pop)
#endif

#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
		bool loadLibrary(){
			mHandle = LoadLibraryA(mPluginName.c_str());
			return mHandle != 0;
		}

		bool unloadLibrary(){
			return FreeLibrary(mHandle) != 0;
		}

		GenericFunction getFunction(const char *functionName){
			return GetProcAddress(mHandle, functionName);
		}
#else
		bool loadLibrary(){
			mHandle = dlopen(mPluginName.c_str(), RTLD_LAZY);
			if (!mHandle)
				saveErrorMsg();
			return mHandle != NULL;
		}

		bool unloadLibrary(){
			int res = dlclose(mHandle);
			if (res != 0)
				saveErrorMsg();
			return res == 0;
		}

		GenericFunction getFunction(const char* functionName){
			void* result = dlsym(mHandle, functionName);
			if (!result)
				saveErrorMsg();
			return result;
		}

		void saveErrorMsg(){
			// Save error message
			char* str = dlerror();
			if (str)
				errorMessage = str;
			// dlerror() must be called twice
			// in order to avoid memory leaks
			str = dlerror();
			assert(!str);
		}

#endif
		
		std::string mPluginName;
		T* mPlugin;
		LibraryHandle mHandle;
		std::string errorMessage;

	};

}


#endif // !_SSF_CORE_PLUGIN_LOADER_HPP_