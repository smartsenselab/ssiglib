project(hayai CXX C)
cmake_minimum_required(VERSION 2.6.2)

if(POLICY CMP0054)
	cmake_policy(SET CMP0054 OLD)
endif()

add_library(hayai STATIC "src/hayai_posix_main.cpp")

# if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#   set_target_properties(hayai PROPERTIES COMPILE_FLAGS "/WX- /W0")
# endif()

target_include_directories(hayai PUBLIC ${hayai_SOURCE_DIR}/include)

set_target_properties(hayai PROPERTIES FOLDER 3RDPARTY)
