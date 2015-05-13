cmake_minimum_required(VERSION 2.8)

option(Plugin_BUILD_PLUGIN_EXAMPLE "Build PluginExample" ${BUILD_ALL})

if(Plugin_BUILD_PLUGIN_EXAMPLE)

    project(PluginExample CXX)

    add_library(plugin_instance
        SHARED
        ${CORE_PATH}/test/test_plugins/plugin_instance.cpp
        ${CORE_PATH}/test/test_plugins/plugin_instance.hpp
    )
	
	target_link_libraries(plugin_example ssf_core)



endif()
