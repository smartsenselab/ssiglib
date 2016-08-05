project(libflann CXX C)
cmake_minimum_required(VERSION 2.6.2)

if(POLICY CMP0054)
	cmake_policy(SET CMP0054 OLD)
endif()

add_library(libflann STATIC "include/flann/flann_cpp.cpp")

target_include_directories(libflann PUBLIC ${libflann_SOURCE_DIR}/include)

set_target_properties(libflann PROPERTIES FOLDER 3RDPARTY)