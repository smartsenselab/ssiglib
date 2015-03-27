#root/components/statistics/CMakeLists.txt

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB STATISTICS_PLS_FILES		"${STATISTICS_PATH}/include/statistics/pls.hpp" 
									"${STATISTICS_PATH}/src/pls.cpp"
									)

file(GLOB STATISTICS_INCLUDES				"${STATISTICS_PATH}/include/statistics/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("PLS"	FILES ${STATISTICS_PLS_FILES})


###############################################################################
# ADD LIBRARY STATISTICS
###############################################################################

#Add library statistics into SSF project with its project
add_library(ssf_statistics 	${STATISTICS_PLS_FILES}
			)
						
#Configure folder to statistics library
set_target_properties(ssf_statistics PROPERTIES FOLDER COMPONENTS)

#Install configuration
install (TARGETS ssf_statistics DESTINATION bin)
install (FILES ${_INCLUDES} DESTINATION include)

#Link Library statistics with Boost
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#target_link_libraries(ssf_statistics ${Boost_LIBRARIES})

###############################################################################
# SET TESTS FOR LIBRARY STATISTICS
###############################################################################

if(BUILD_TESTS)

	#Create set of statistics tests files
	file(GLOB STATISTICS_TEST_FILES "${STATISTICS_PATH}/test/*.cpp")
	
	add_executable(test_statistics ${STATISTICS_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(test_statistics gtest gtest_main)

	# Extra linking for the project.
	target_link_libraries(test_statistics ssf_statistics)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_statistics to see those specific tests.
	add_test(NAME test_statistics COMMAND test_statistics WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/statistics")
	
	#Configure folder to statistics library
	set_target_properties(test_statistics PROPERTIES FOLDER TESTS)

endif()