#root/components/math/CMakeLists.txt

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB MATH_MATH_FILES		"${MATH_PATH}/include/math/math.hpp" 
								"${MATH_PATH}/src/math.cpp"
								)

file(GLOB MATH_INCLUDES				"${MATH_PATH}/include/math/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("MATH"	FILES ${MATH_MATH_FILES})


###############################################################################
# ADD LIBRARY MATH
###############################################################################

#Add library math into SSF project with its project
add_library(ssf_math 	${MATH_MATH_FILES}
			)
						
#Configure folder to math library
set_target_properties(ssf_math PROPERTIES FOLDER COMPONENTS)

#Install configuration
install (TARGETS ssf_math DESTINATION bin)
install (FILES ${_INCLUDES} DESTINATION include)

#Link Library math with Boost
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#target_link_libraries(ssf_math ${Boost_LIBRARIES})

###############################################################################
# SET TESTS FOR LIBRARY MATH
###############################################################################

if(BUILD_TESTS)

	#Create set of math tests files
	file(GLOB MATH_TEST_FILES "${MATH_PATH}/test/*.cpp")
	
	add_executable(test_math ${MATH_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(test_math gtest gtest_main)

	# Extra linking for the project.
	target_link_libraries(test_math ssf_math)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_math to see those specific tests.
	add_test(NAME test_math COMMAND test_math WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/math")
	
	#Configure folder to math library
	set_target_properties(test_math PROPERTIES FOLDER TESTS)

endif()