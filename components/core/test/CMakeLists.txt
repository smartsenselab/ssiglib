#root/components/core/test/CMakeLists.txt

if(BUILD_TESTS)

	#Create set of core tests files
	file(GLOB CORE_TEST_FILES "${CORE_PATH}/test/test*.cpp")
	
	add_executable(test_core ${CORE_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(test_core gtest gtest_main)
	target_include_directories(test_core PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	target_include_directories(test_core PUBLIC ${CORE_PATH}/include/)

	# Extra linking for the project.
	target_link_libraries(test_core ssf_core)
	ssf_link_opencv(test_core opencv_core opencv_imgproc opencv_highgui)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_core to see those specific tests.
	add_test(NAME test_core COMMAND test_core WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/core")
	
	#Configure folder to core librarya
	set_target_properties(test_core PROPERTIES FOLDER TESTS)

	add_subdirectory( test_plugins )
	
endif()