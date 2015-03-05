#root/CMakeLists.txt

#CMake Version Minimum Required
cmake_minimum_required (VERSION 2.6)

###############################################################################
# CMake OPTIONS
###############################################################################

#Remove Warning CMP0054 from gtest cmake build

if(POLICY CMP0054)
	cmake_policy(SET CMP0054 OLD)
endif() 

#Allows the solution folder utilization (for MSVC) 
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Set Global Project Name
set(PROJECT_NAME_STR SSF)
project(${PROJECT_NAME_STR} CXX)

###############################################################################
# EXTERNAL LIBRARIES
###############################################################################
find_package(Boost 1.40.0 QUIET REQUIRED)

###############################################################################
# USER OPTIONS
###############################################################################

#Option to check if 'test' will be available
option(BUILD_TESTS "Build tests" ON)

# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

###############################################################################
# SUBDIRECTORIES
###############################################################################

#Add 3rdparty
add_subdirectory(3rdparty)

#Enable tests if BUILD_TEST was checked by user 
if(BUILD_TESTS)
	enable_testing()
endif()

#Add components
add_subdirectory(components)
