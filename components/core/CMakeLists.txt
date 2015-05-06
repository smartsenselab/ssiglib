#root/components/core/CMakeLists.txt

###############################################################################
# CONFIGURE CORE PATH
###############################################################################
set (CORE_PATH ${PROJECT_SOURCE_DIR}/components/core)

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

file(GLOB CORE_PARAMETERS_FILES 	"${CORE_PATH}/include/core/parameter.hpp"
									"${CORE_PATH}/src/parameter.cpp"
									"${CORE_PATH}/include/core/parameters.hpp"
									"${CORE_PATH}/src/parameters.cpp"
									)

file(GLOB CORE_BASEOBJECT_FILES		"${CORE_PATH}/include/core/base_object.hpp"
									"${CORE_PATH}/src/base_object.cpp"
									)

file(GLOB CORE_RESOURCE_FILES	 	"${CORE_PATH}/include/core/resource.hpp"
									"${CORE_PATH}/src/resource.cpp"
									"${CORE_PATH}/include/core/resource_info.hpp"
									"${CORE_PATH}/src/resource_info.cpp"
									"${CORE_PATH}/include/core/resource_setup.hpp"
									"${CORE_PATH}/src/resource_setup.cpp"
									)

file(GLOB CORE_STRUCTURES_FILES	 	"${CORE_PATH}/include/core/matrix.hpp"
									"${CORE_PATH}/src/matrix.cpp"
									"${CORE_PATH}/include/core/cube.hpp"
									"${CORE_PATH}/include/core/point2d.hpp"
									"${CORE_PATH}/include/core/point3d.hpp"
									)

file(GLOB CORE_UTIL_FILES			"${CORE_PATH}/include/core/ssfdef.hpp"
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
source_group("Util"			FILES ${CORE_UTIL_FILES})
source_group("Structures"	FILES ${CORE_STRUCTURES_FILES})


###############################################################################
# ADD LIBRARY CORE
###############################################################################

#Add library core into SSF project with its project
add_library(ssf_core 	${CORE_EXCEPTION_FILES}
						${CORE_FILEHANDLE_FILES} 
						${CORE_PARAMETERS_FILES}
						${CORE_BASEOBJECT_FILES}
						${CORE_RESOURCE_FILES}
						${CORE_UTIL_FILES}
						${CORE_STRUCTURES_FILES}
			)
target_include_directories(ssf_core PUBLIC ${CORE_PATH}/include/)
						
#Configure folder to core library
set_target_properties(ssf_core PROPERTIES FOLDER COMPONENTS)

target_compile_definitions(ssf_core PUBLIC SSFAPI_EXPORTS)

#Install configuration
install (TARGETS ssf_core DESTINATION bin)
install (FILES ${CORE_INCLUDES} DESTINATION include)

#Link External Libraries
ssf_link_boost(ssf_core system filesystem)
ssf_link_opencv(ssf_core opencv_core opencv_imgproc opencv_highgui)


###############################################################################
# SET TESTS FOR LIBRARY CORE
###############################################################################

if(BUILD_TESTS)

	#Create set of core tests files
	file(GLOB CORE_TEST_FILES "${CORE_PATH}/test/*.cpp")
	
	add_executable(test_core ${CORE_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(test_core gtest gtest_main)
	target_include_directories(test_core PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	target_include_directories(test_core PUBLIC ${CORE_PATH}/include/)

	# Extra linking for the project.
	target_link_libraries(test_core ssf_core)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_core to see those specific tests.
	add_test(NAME test_core COMMAND test_core WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/core")
	
	#Configure folder to core library
	set_target_properties(test_core PROPERTIES FOLDER TESTS)

endif()