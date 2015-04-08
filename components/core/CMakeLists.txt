#root/components/core/CMakeLists.txt

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB CORE_EXCEPTION_FILES 		"${CORE_PATH}/include/core/exception.hpp" 
									"${CORE_PATH}/src/exception.cpp"
									"${CORE_PATH}/include/core/file_exception.hpp" 
									"${CORE_PATH}/src/file_exception.cpp"
									"${CORE_PATH}/include/core/param_exception.hpp" 
									"${CORE_PATH}/src/param_exception.cpp"
									)

file(GLOB CORE_FILEHANDLE_FILES 	"${CORE_PATH}/include/core/file_handle.hpp" 
									"${CORE_PATH}/src/file_handle.cpp"
									"${CORE_PATH}/include/core/directory_handle.hpp" 
									"${CORE_PATH}/src/directory_handle.cpp"
									)

file(GLOB CORE_PARAMETERS_FILES 	"${CORE_PATH}/include/core/param_value.hpp"
									"${CORE_PATH}/include/core/param.hpp"
									"${CORE_PATH}/src/param.cpp"									
									"${CORE_PATH}/include/core/params.hpp"
									"${CORE_PATH}/src/params.cpp"									
									)

file(GLOB CORE_BASEOBJECT_FILES		"${CORE_PATH}/include/core/base_object.hpp"
									"${CORE_PATH}/src/base_object.cpp"
									)

file(GLOB CORE_RESOURCE_FILES	 	"${CORE_PATH}/include/core/resource.hpp"
									"${CORE_PATH}/src/resource.cpp"
									#"${CORE_PATH}/include/core/resource_info.hpp"
									#"${CORE_PATH}/src/resource_info.cpp"
									)



file(GLOB CORE_LOG_FILES			"${CORE_PATH}/include/core/log.hpp"
									"${CORE_PATH}/src/log.cpp"
									)



file(GLOB CORE_INCLUDES				"${CORE_PATH}/include/core/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("Exception"	FILES ${CORE_EXCEPTION_FILES})
source_group("Files"		FILES ${CORE_FILEHANDLE_FILES})
source_group("Parameters"	FILES ${CORE_PARAMETERS_FILES})
source_group("Base Ojbect"	FILES ${CORE_BASEOBJECT_FILES})
source_group("Resources"	FILES ${CORE_RESOURCE_FILES})
source_group("Log"			FILES ${CORE_LOG_FILES})


###############################################################################
# ADD LIBRARY CORE
###############################################################################

#Add library core into SSF project with its project
add_library(ssf_core 	${CORE_EXCEPTION_FILES}
						${CORE_FILEHANDLE_FILES} 
						${CORE_PARAMETERS_FILES}
						${CORE_BASEOBJECT_FILES}
						${CORE_RESOURCE_FILES}
						${CORE_LOG_FILES}
			)
						
#Configure folder to core library
set_target_properties(ssf_core PROPERTIES FOLDER COMPONENTS)

#Install configuration
install (TARGETS ssf_core DESTINATION bin)
install (FILES ${CORE_INCLUDES} DESTINATION include)

#Link Library core with Boost
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
target_link_libraries(ssf_core ${Boost_LIBRARIES})

###############################################################################
# SET TESTS FOR LIBRARY CORE
###############################################################################

if(BUILD_TESTS)

	#Create set of core tests files
	file(GLOB CORE_TEST_FILES "${CORE_PATH}/test/*.cpp")
	
	add_executable(test_core ${CORE_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(test_core gtest gtest_main)

	# Extra linking for the project.
	target_link_libraries(test_core ssf_core)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_core to see those specific tests.
	add_test(NAME test_core COMMAND test_core WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/core")
	
	#Configure folder to core library
	set_target_properties(test_core PROPERTIES FOLDER TESTS)

endif()