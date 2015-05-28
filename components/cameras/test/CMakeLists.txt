#root/components/cameras/test/CMakeLists.txt

if(BUILD_TESTS)

	#Create set of cameras tests files
	file(GLOB CAMERAS_TEST_FILES "${CAMERAS_PATH}/test/test*.cpp")
	
	add_executable(test_cameras ${CAMERAS_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(test_cameras gtest gtest_main)
	target_include_directories(test_cameras PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	target_include_directories(test_cameras PUBLIC ${CAMERAS_PATH}/include/)

	# Extra linking for the project.
	target_link_libraries(test_cameras ssf_cameras)
	
	#create test directory if it does not exists\
	file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/cameras")

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_cameras to see those specific tests.
	add_test(NAME test_cameras COMMAND test_cameras WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/cameras")
	
	#Configure folder to cameras library
	set_target_properties(test_cameras PROPERTIES FOLDER TESTS)

	
endif()