include(CMakeParseArguments)

set(ssf_boost_minimal_version 1.47)

macro(ssf_find_boost)
	set(ssf_options REQUIRED QUIET)
	set(ssf_multiValueArgs COMPONENTS)
	cmake_parse_arguments(SSF_FIND_BOOST "${ssf_options}" "${ssf_oneValueArgs}" "${ssf_multiValueArgs}" ${ARGN} )	
	
	set(ssf_options "")
	if(${SSF_FIND_BOOST_REQUIRED})
		set(ssf_options "REQUIRED")
	endif()	
	
	if(${SSF_FIND_BOOST_QUIET})
		set(ssf_options "QUIET")
	endif()	
	
	find_package(Boost ${ssf_boost_minimal_version} COMPONENTS ${SSF_FIND_BOOST_COMPONENTS} ${ssf_options})
	set(Boost_USE_STATIC_LIBS OFF)
	set(Boost_USE_STATIC OFF)
	set(Boost_USE_MULTITHREAD ON)
	
endmacro()

macro(ssf_link_boost TARGET)
	ssf_find_boost(COMPONENTS ${ARGN} REQUIRED)
	
	target_compile_definitions(${TARGET} PUBLIC BOOST_ALL_NO_LIB)
	target_compile_definitions(${TARGET} PUBLIC BOOST_ALL_DYN_LINK)

	target_include_directories(${TARGET} PUBLIC ${Boost_INCLUDE_DIR})
	
	target_link_libraries(${TARGET} ${Boost_LIBRARIES})

endmacro()