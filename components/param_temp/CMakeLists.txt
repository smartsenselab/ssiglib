#root/components/param_temp/CMakeLists.txt

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB PARAM_TEMP_PARAM_TEMP_FILES	"${PARAM_TEMP_PATH}/include/param_temp/param_temp.hpp" 
										"${PARAM_TEMP_PATH}/src/param_temp.cpp"
										)

file(GLOB PARAM_TEMP_INCLUDES			"${PARAM_TEMP_PATH}/include/param_temp/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("PARAM_TEMP"	FILES ${PARAM_TEMP_PARAM_TEMP_FILES})


###############################################################################
# ADD LIBRARY PARAM_TEMP
###############################################################################

#Add library param_temp into SSF project with its project
add_library(ssf_param_temp 	${PARAM_TEMP_PARAM_TEMP_FILES}
			)
						
#Configure folder to param_temp library
set_target_properties(ssf_param_temp PROPERTIES FOLDER COMPONENTS)

#Install configuration
install (TARGETS ssf_param_temp DESTINATION bin)
install (FILES ${_INCLUDES} DESTINATION include)

#Link Library param_temp with Boost
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#target_link_libraries(ssf_param_temp ${Boost_LIBRARIES})

###############################################################################
# SET TESTS FOR LIBRARY PARAM_TEMP
###############################################################################

if(BUILD_TESTS)

	#Create set of param_temp tests files
	file(GLOB PARAM_TEMP_TEST_FILES "${PARAM_TEMP_PATH}/test/*.cpp")
	
	add_executable(test_param_temp ${PARAM_TEMP_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(test_param_temp gtest gtest_main)

	# Extra linking for the project.
	target_link_libraries(test_param_temp ssf_param_temp)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_param_temp to see those specific tests.
	add_test(NAME test_param_temp COMMAND test_param_temp WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/param_temp")
	
	#Configure folder to param_temp library
	set_target_properties(test_param_temp PROPERTIES FOLDER TESTS)

endif()