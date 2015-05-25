#include <gtest/gtest.h>

#include "core/plugin_loader.hpp"
#include "core/resource.hpp"

#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
#define PLUGIN_NAME "subtest_plugin_instance.dll"
#else
#define PLUGIN_NAME "libsubtest_plugin_instance.so"
#endif

TEST(Plugin, load) {
	
	std::string pluginPath(PLUGIN_NAME);
	
	ssf::PluginLoader<ssf::Resource> loader(pluginPath);
	ssf::Resource* plugin = nullptr;

	bool isLoaded = loader.load();
	EXPECT_TRUE(isLoaded);

	plugin = loader.getPluginInstance();

	EXPECT_STREQ("RESOURCE_SPECIALIZATION", plugin->getName().c_str());
	EXPECT_STREQ("TYPE_RESOURCE_SPECIALIZATION", plugin->getType().c_str());
	/*EXPECT_STREQ("Antonio", plugin->getInfo().getAuthor().c_str());
	EXPECT_STREQ("2.0.0", plugin->getInfo().getRequiredVersion().toString().c_str());*/
	
}
