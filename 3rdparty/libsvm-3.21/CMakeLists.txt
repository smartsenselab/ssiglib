project(libsvm CXX C)
cmake_minimum_required(VERSION 2.6.2)

if(POLICY CMP0054)
	cmake_policy(SET CMP0054 OLD)
endif()

add_library(libsvm STATIC "src/libsvm.cpp")

target_include_directories(libsvm PUBLIC ${libsvm_SOURCE_DIR}/include)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_target_properties(libsvm PROPERTIES COMPILE_FLAGS "/openmp" FOLDER 3RDPARTY)
else()
    set_target_properties(libsvm PROPERTIES COMPILE_FLAGS "-fopenmp -fPIC" FOLDER 3RDPARTY)
endif()
