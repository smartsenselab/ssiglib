macro(ssf_add_module _name)

	set(module_options REQUIRED)
	set(module_oneValueArgs "")
	set(module_multiValueArgs DEPENDENCIES BOOST OPENCV)
	cmake_parse_arguments(ADD_MODULE_ARGS "${module_options}" "${module_oneValueArgs}" "${module_multiValueArgs}" ${ARGN} )
		
	set(MODULE_NAME "ssf_${_name}")
	set(MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/${_name}")
		
	if(NOT ${ADD_MODULE_ARGS_REQUIRED})
		option(MODULES_${MODULE_NAME} "Build ${MODULE_NAME}" ON)
		if(NOT MODULES_${MODULE_NAME})
			return()
		endif()
	endif()

	message(STATUS " ")
	message(STATUS "Add SSF Module: ${_name}")
	if(NOT EXISTS ${MODULE_PATH})
		message(FATAL_ERROR "Directory ${MODULE_PATH} not found!")	
	endif()
	
	# files glob
	file(GLOB MODULE_INCLUDE_FILES	"${MODULE_PATH}/include/${MODULE_NAME}/*.hpp")
	file(GLOB MODULE_SOURCE_FILES	"${MODULE_PATH}/src/*.cpp")
	
	# add library
	add_library(${MODULE_NAME} ${MODULE_SOURCE_FILES} ${MODULE_INCLUDE_FILES})
	target_include_directories(${MODULE_NAME} PUBLIC ${MODULE_PATH}/include/)
	set_target_properties(${MODULE_NAME} PROPERTIES FOLDER MODULES)
	
	string(TOUPPER "${MODULE_NAME}_API_EXPORTS" EXPORTS_MACRO)
	target_compile_definitions(${MODULE_NAME} PUBLIC ${EXPORTS_MACRO})
	
	list(LENGTH ADD_MODULE_ARGS_DEPENDENCIES list_size)
	if(NOT ${list_size} STREQUAL "0")
		message(STATUS "Link to Dependents SSF Modules:")
		foreach(lib ${ADD_MODULE_ARGS_DEPENDENCIES})
			message(STATUS "    - ${lib}")
		endforeach()
		target_link_libraries(${MODULE_NAME} ${ADD_MODULE_ARGS_DEPENDENCIES})
	endif()
	
	list(LENGTH ADD_MODULE_ARGS_BOOST list_size)
	if(NOT ${list_size} STREQUAL "0")
		message(STATUS "Link to Boost Libraries:")
		foreach(lib ${ADD_MODULE_ARGS_BOOST})
			message(STATUS "    - ${lib}")
		endforeach()
		ssf_link_boost(${MODULE_NAME} ${ADD_MODULE_ARGS_BOOST} REQUIRED QUIET)
	endif()
	
	list(LENGTH ADD_MODULE_ARGS_OPENCV list_size)
	if(NOT ${list_size} STREQUAL "0")
		message(STATUS "Link to OpenCV Libraries:")
		foreach(lib ${ADD_MODULE_ARGS_OPENCV})
			message(STATUS "    - ${lib}")
		endforeach()
		ssf_link_opencv(${MODULE_NAME} ${ADD_MODULE_ARGS_OPENCV} REQUIRED QUIET)
	endif()
	
	install (TARGETS ${MODULE_NAME} DESTINATION bin)
	install (FILES ${MODULE_INCLUDE_FILES} DESTINATION include)
	
	if(BUILD_TESTS)	
		
		# Create set of core tests files
		file(GLOB MODULE_TEST_FILES "${MODULE_PATH}/test/test*.cpp")
		
		# Create test executable
		set(TEST_NAME test_${MODULE_NAME})
		add_executable(${TEST_NAME} ${MODULE_TEST_FILES})

		# Standard linking to gtest stuff.
		target_link_libraries(${TEST_NAME} gtest gtest_main)
		target_include_directories(${TEST_NAME} PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
		target_include_directories(${TEST_NAME} PUBLIC ${MODULE_PATH}/include/)

		target_link_libraries(${TEST_NAME} ${MODULE_NAME})
	
		# create test directory if it does not exists
		set(DATA_TEST_PATH "${PROJECT_SOURCE_DIR}/data/tests/${MODULE_NAME}")
		file(MAKE_DIRECTORY ${DATA_TEST_PATH})

		# This is so you can do 'make test' to see all your tests run, instead of
		# manually running the executable ssf_test_core to see those specific tests.
		add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${DATA_TEST_PATH})
	
		file(GLOB MODULE_TEST_FILES "${DATA_TEST_PATH}/*")
		file(COPY ${CORE_TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	
		# Configure folder to core library
		set_target_properties(${TEST_NAME} PROPERTIES FOLDER TESTS)
		unset(TEST_NAME)
		unset(DATA_TEST_PATH)
		
	endif()
	unset(MODULE_NAME)
	unset(MODULE_PATH)
	message(STATUS " ")
endmacro()