#root/3rdparty/CMakeLists.txt

###############################################################################
# 3RDPARTY SUBDIRECTORIES
###############################################################################

#Google Tests
#Include Google Tests if only BUILD_TESTS was checked by user
if(BUILD_TESTS)
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	add_subdirectory (gtest-1.7.0)
	set_target_properties(gtest PROPERTIES FOLDER 3RDPARTY)
	set_target_properties(gtest_main PROPERTIES FOLDER 3RDPARTY)
endif()