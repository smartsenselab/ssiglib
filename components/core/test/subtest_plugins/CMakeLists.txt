#root/components/configuration/test/test_plugin/CMakeLists.txt

if(BUILD_TESTS)

    add_library(subtest_plugin_instance
        SHARED
        ${CORE_PATH}/test/subtest_plugins/plugin_instance.cpp
        ${CORE_PATH}/test/subtest_plugins/plugin_instance.hpp
    )
	
	target_link_libraries(subtest_plugin_instance ssf_core)
	
	set_target_properties(subtest_plugin_instance PROPERTIES FOLDER TESTS)

endif()