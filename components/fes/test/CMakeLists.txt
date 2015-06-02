#root/components/fes/test/CMakeLists.txt

if(BUILD_TESTS)

	#Create set of fes tests files
	file(GLOB FES_TEST_FILES "${FES_PATH}/test/test*.cpp")
	
	add_executable(test_fes ${FES_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(test_fes gtest gtest_main)
	target_include_directories(test_fes PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	target_include_directories(test_fes PUBLIC ${FES_PATH}/include/)

	# Extra linking for the project.
	target_link_libraries(test_fes ssf_fes)
	
	#create test directory if it does not exists\
	file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/fes")

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_fes to see those specific tests.
	add_test(NAME test_fes COMMAND test_fes WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/fes")
	
	#Configure folder to fes library
	set_target_properties(test_fes PROPERTIES FOLDER TESTS)

	
endif()