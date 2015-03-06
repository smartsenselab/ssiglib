#root/components/core/CMakeLists.txt

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB CORE_EXCEPTION_FILES 	"${CORE_PATH}/include/core/exception.hpp" 
								"${CORE_PATH}/src/exception.cpp"
								)

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("Exception" FILES ${CORE_EXCEPTION_FILES})


###############################################################################
# ADD LIBRARY CORE
###############################################################################

#Add library core into SSF project with its project
add_library(ssf_core ${CORE_EXCEPTION_FILES})

#Configure folder to core library
set_target_properties(ssf_core PROPERTIES FOLDER COMPONENTS)

###############################################################################
# CONFIGURE TESTS FOR LIBRARY CORE
###############################################################################

if(BUILD_TESTS)

	#Fix GTest link to test project
	#See more details here: https://airfang.wordpress.com/2008/10/04/gtest-cmake-visual-studio/
	#SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")

	#Create set of core tests files
	file(GLOB CORE_TEST_FILES "${CORE_PATH}/test/*.cpp")
	
	add_executable(ssf_test_core ${CORE_TEST_FILES})

	# Standard linking to gtest stuff.
	target_link_libraries(ssf_test_core gtest gtest_main)

	# Extra linking for the project.
	target_link_libraries(ssf_test_core ssf_core)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_core to see those specific tests.
	add_test(NAME ssf_test_core COMMAND ssf_test_core)
	
	#Configure folder to core library
	set_target_properties(ssf_test_core PROPERTIES FOLDER TESTS)

endif()