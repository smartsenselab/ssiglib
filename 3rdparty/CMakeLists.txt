#Include gtest if OPT_TEST is checked by user
if(OPT_TEST)
	add_subdirectory (gtest-1.7.0)
endif()