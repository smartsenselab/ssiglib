/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                              License Agreement
*                      For Smart Surveillance Framework
*                        http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, 
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright 
*       notice, this list of conditions and the following disclaimer in the 
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its 
*       contributors may be used to endorse or promote products derived from 
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
*  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#ifndef _SSF_CORE_PLUGIN_LOADER_HPP_
#define _SSF_CORE_PLUGIN_LOADER_HPP_

#include "core/core_defs.hpp"
#include "plugin_defs.hpp"

#include <cassert>
#include <cstddef>
#include <string>



#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif


namespace ssf{

	template<class T>
	class PluginLoader{

	public:

		PluginLoader(const std::string& pluginName = "")
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
					this->callFunction<void>(PLUGIN_DESTROY_FUNCTION);
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
				this->mPlugin = callFunction<T*>(PLUGIN_CREATE_FUNCTION);
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


#endif // !_SSF_CORE_PLUGIN_LOADER_HPP_PP_