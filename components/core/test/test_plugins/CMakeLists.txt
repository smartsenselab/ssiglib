#root/components/configuration/test/test_plugin/CMakeLists.txt

if(BUILD_TESTS)

    add_library(plugin_instance
        SHARED
        ${CORE_PATH}/test/test_plugins/plugin_instance.cpp
        ${CORE_PATH}/test/test_plugins/plugin_instance.hpp
    )
	
	target_link_libraries(plugin_instance ssf_core)

endif()