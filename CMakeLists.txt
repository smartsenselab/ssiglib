#root/CMakeLists.txt

#CMake Version Minimum Required
cmake_minimum_required (VERSION 2.8.11)

###############################################################################
# DEFINITION
###############################################################################

set(PROJECT_ACRONYM_STR "SSF")
set(PROJECT_NAME_STR "Smart Surveillance Framework")
project(${PROJECT_ACRONYM_STR} CXX)


###############################################################################
# OPTIONS
###############################################################################

set(VERSION_MAJOR   2   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")

# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

#Option to check if 'test' will be available
option(BUILD_TESTS "Build tests" ON)

#Option to check if 'docs' will be build
option(BUILD_DOCS "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

MARK_AS_ADVANCED(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

###############################################################################
# INCLUDE CMake Files
###############################################################################
include(cmake/SSFConfig.cmake)
include(cmake/SSFBoostUtil.cmake)

###############################################################################
# SUBDIRECTORIES
###############################################################################

#Add 3rdparty
add_subdirectory(3rdparty)

#Add components
add_subdirectory(components)

#Add documentation
add_subdirectory(doc)
