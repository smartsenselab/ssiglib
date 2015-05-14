cmake_minimum_required(VERSION 2.8)

option(Plugin_BUILD_PLUGINLOADER_EXAMPLE "Build PluginLoaderExample" ${BUILD_ALL})

if(Plugin_BUILD_PLUGINLOADER_EXAMPLE)

    project(PluginLoaderExample CXX)

    ##################
    #  Dependencies  #
    ##################

    if(NOT TARGET plugin_example)
        message(FATAL_ERROR "Target not found: PluginExample")
    endif()


    ############
    #  Target  #
    ############

    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/src/main.cpp)

    target_link_libraries(${PROJECT_NAME}
        plugin_example
    )

	target_link_libraries(${PROJECT_NAME}
        ssf_core
    )

    add_dependencies(${PROJECT_NAME} PluginExample)

endif()
