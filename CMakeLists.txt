#CMake Version Minimum Required
cmake_minimum_required (VERSION 2.6)

#Set Global Project Name
set(PROJECT_NAME_STR SSF)
project(${PROJECT_NAME_STR} CXX)

#Option to check if 'test' will be available
option(OPT_TEST "Build tests" ON)

#Add components
add_subdirectory(components)

#Add 3rdparty
add_subdirectory(3rdparty)


if(OPT_TEST)
	enable_testing()
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()