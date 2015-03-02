#root/CMakeLists.txt

#CMake Version Minimum Required
cmake_minimum_required (VERSION 2.6)

#CMake options
cmake_policy(SET CMP0054 NEW)

#Set Global Project Name
set(PROJECT_NAME_STR SSF)
project(${PROJECT_NAME_STR} CXX)

#Option to check if 'test' will be available
option(BUILD_TESTS "Build tests" ON)

#Add components
add_subdirectory(components)

#Add 3rdparty
add_subdirectory(3rdparty)

if(BUILD_TESTS)
	enable_testing()
endif()