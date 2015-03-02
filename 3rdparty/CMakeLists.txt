#root/3rdparty/CMakeLists.txt

#Include gtest if OPT_TEST is checked by user
if(BUILD_TESTS)
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	add_subdirectory (gtest-1.7.0)
endif()