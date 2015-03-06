#root/CMakeLists.txt

#CMake Version Minimum Required
cmake_minimum_required (VERSION 2.8)

###############################################################################
# CMake OPTIONS
###############################################################################
#Set Global Project Name
set(PROJECT_NAME_STR SSF)
project(${PROJECT_NAME_STR} CXX)

#Remove Warning CMP0054 from gtest cmake build
if(POLICY CMP0054)
	cmake_policy(SET CMP0054 OLD)
endif() 

#Allows the solution folder utilization (for MSVC) 
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# If install location is default, set new default to "build/install"
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "default install path" FORCE )
endif()


###############################################################################
# EXTERNAL LIBRARIES
###############################################################################
find_package(Boost 1.47 COMPONENTS system filesystem REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC OFF)
set(Boost_USE_MULTITHREAD ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_ALL_DYN_LINK -DBOOST_ALL_NO_LIB")

#add_definitions(-DBOOST_ALL_NO_LIB)  # tell the compiler to undefine this boost macro

#SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")
#SET(CMAKE_CXX_FLAGS_RELEASE "/MTd")

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
