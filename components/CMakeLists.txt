#root/components/CMakeLists.txt

###############################################################################
# CONFIGURE PATHS
###############################################################################
set (CORE_PATH ${PROJECT_SOURCE_DIR}/components/core) #core

###############################################################################
# INCLUDE DIRECTORIES
###############################################################################
include_directories (${CORE_PATH}/include/)

if(BUILD_TESTS)
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

###############################################################################
# COMPONENTS SUBDIRECTORIES
###############################################################################
add_subdirectory (core)