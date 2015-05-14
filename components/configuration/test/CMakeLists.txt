#root/components/configuration/test/CMakeLists.txt

if(BUILD_TESTS)

	#Create set of configuration tests files
    file(GLOB CONFIGURATION_TEST_FILES "${CONFIGURATION_PATH}/test/test*.cpp")
	
    add_executable(test_configuration ${CONFIGURATION_TEST_FILES})

	# Standard linking to gtest stuff.
    target_link_libraries(test_configuration gtest gtest_main)
	target_include_directories(test_configuration PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	target_include_directories(test_configuration PUBLIC ${CONFIGURATION_PATH}/include/)

	# Extra linking for the project.
    target_link_libraries(test_configuration ssf_configuration)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_configuration to see those specific tests.
    add_test(NAME test_configuration COMMAND test_configuration WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/configuration")
	
	#Configure folder to configuration library
    set_target_properties(test_configuration PROPERTIES FOLDER TESTS)

endif()