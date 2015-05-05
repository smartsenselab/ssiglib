###############################################################################
# CMake Policies
###############################################################################

#Remove Warning CMP0054 from gtest cmake build
if(POLICY CMP0054)
	cmake_policy(SET CMP0054 OLD)
endif()

###############################################################################
# Check Compilers
###############################################################################

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE TEMP_COMPILER_VERSION)
	if(TEMP_COMPILER_VERSION VERSION_LESS 4.7)
		message(FATAL_ERROR "${PROJECT_NAME_STR} requires g++ 4.7 or greater. Installed version: ${CMAKE_CXX_COMPILER_VERSION}")
	endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE TEMP_COMPILER_VERSION)
	if (TEMP_COMPILER_VERSION VERSION_LESS 3.4)
		message(FATAL_ERROR "${PROJECT_NAME_STR} requires Clang 3.4 or greater. Installed version: ${CMAKE_CXX_COMPILER_VERSION}")
	endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")	
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17)
		message(FATAL_ERROR "${PROJECT_NAME_STR} requires MSVC 1700 (MSVC 2012) or greater. Installed version: ${CMAKE_CXX_COMPILER_VERSION}")
	endif()
else()
    message(WARNING "You are using an unsupported compiler! ${PROJECT_NAME_STR} has only been tested with Clang, GCC and MSVC.")
endif()

###############################################################################
# Compilers Definitions
###############################################################################

set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL}")
set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
	set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -std=gnu++11")#
	set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
	set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL} -Os -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE} -O4 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS}")
	set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG}")
	set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL}")
	set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE}")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
endif()

###############################################################################
# Enable Tests
###############################################################################

if(BUILD_TESTS)
	enable_testing()
endif()

###############################################################################
# Other Configs
###############################################################################

#Allows the solution folder utilization (for MSVC)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# If install location is default, set new default to "build/install"
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "default install path" FORCE )
endif()