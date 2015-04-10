#root/components/CMakeLists.txt

###############################################################################
# CONFIGURE PATHS
###############################################################################
set (CORE_PATH ${PROJECT_SOURCE_DIR}/components/core) #core
set (STATISTICS_PATH ${PROJECT_SOURCE_DIR}/components/statistics) #statistics
set (MATH_PATH ${PROJECT_SOURCE_DIR}/components/math) #math


###############################################################################
# INCLUDE DIRECTORIES
###############################################################################
include_directories (${CORE_PATH}/include/)
include_directories (${STATISTICS_PATH}/include/)
include_directories (${MATH_PATH}/include/)


if(BUILD_TESTS)
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

###############################################################################
# COMPONENTS SUBDIRECTORIES
###############################################################################
add_subdirectory (core)
add_subdirectory (statistics)
add_subdirectory (math)