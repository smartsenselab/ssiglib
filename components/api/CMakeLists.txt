#root/components/api/CMakeLists.txt

###############################################################################
# CONFIGURE CORE PATH
###############################################################################
set (API_PATH ${PROJECT_SOURCE_DIR}/components/api)

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB API_API_FILES		"${API_PATH}/include/api/ssf_configuration.hpp" 
							"${API_PATH}/src/ssf_configuration.cpp"
                            "${API_PATH}/include/api/stream.hpp"
                            "${API_PATH}/src/stream.cpp"
                            "${API_PATH}/src/module.cpp"
                            "${API_PATH}/include/api/module.hpp"
                            "${API_PATH}/include/api/api_exception.hpp"
                            "${API_PATH}/src/api_exception.cpp"

							)

file(GLOB API_INCLUDES				"${API_PATH}/include/api/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("API"	FILES ${API_API_FILES})


###############################################################################
# ADD LIBRARY API
###############################################################################

#Add library api into SSF project with its project
add_library(ssf_api 	${API_API_FILES})
target_include_directories (ssf_api PUBLIC ${API_PATH}/include/)

#Link core to api
include_directories (${CORE_PATH}/include/)
target_link_libraries(ssf_api ssf_core)
						
#Configure folder to api library
set_target_properties(ssf_api PROPERTIES FOLDER COMPONENTS)

#Install configuration
install (TARGETS ssf_api DESTINATION bin)
install (FILES ${_INCLUDES} DESTINATION include)

#Link Library api with Boost
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#target_link_libraries(ssf_api ${Boost_LIBRARIES})

###############################################################################
# SET TESTS FOR LIBRARY API
###############################################################################

#if(BUILD_TESTS)

	#Create set of api tests files
    file(GLOB API_TEST_FILES "${API_PATH}/test/*.cpp")
	
    add_executable(test_api ${API_TEST_FILES})

	# Standard linking to gtest stuff.
    target_link_libraries(test_api gtest gtest_main)

	# Extra linking for the project.
    target_link_libraries(test_api ssf_api)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_api to see those specific tests.
    add_test(NAME test_api COMMAND test_api WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/api")
	
	#Configure folder to api library
    set_target_properties(test_api PROPERTIES FOLDER TESTS)

#endif()