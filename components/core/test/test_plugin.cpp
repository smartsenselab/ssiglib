#include <gtest/gtest.h>

#include "core/plugin_loader.hpp"
#include "core/plugin.hpp"

#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
#define PLUGIN_NAME "plugin_instance.dll"
#else
#define PLUGIN_NAME "plugin_instance.so"
#endif

TEST(Plugin, load) {
	
	std::string pluginPath(PLUGIN_NAME);
	
	ssf::PluginLoader<ssf::Plugin> loader(pluginPath);
	ssf::Plugin* plugin = nullptr;

	bool isLoaded = loader.load();
	EXPECT_TRUE(isLoaded);


	plugin = loader.getPluginInstance();


	EXPECT_STREQ("Example", plugin->getName().c_str());
	EXPECT_STREQ("1.3.4", plugin->getVersion().toString().c_str());		
	
}
