include(CMakeParseArguments)

set(ssf_opencv_minimal_version 2.8)

macro(ssf_find_opencv)
	set(ssf_options REQUIRED)
	set(ssf_multiValueArgs COMPONENTS)
	cmake_parse_arguments(SSF_FIND_OPENCV "${ssf_options}" "${ssf_oneValueArgs}" "${ssf_multiValueArgs}" ${ARGN} )	
	
	set(ssf_options "")
	if(${SSF_FIND_OPENCV_REQUIRED})
		set(ssf_options "REQUIRED")
	endif()
	
	find_package(OpenCV ${ssf_opencv_minimal_version} COMPONENTS ${SSF_FIND_OPENCV_COMPONENTS} ${ssf_options})
	
endmacro()

macro(ssf_link_opencv TARGET)
	ssf_find_opencv(COMPONENTS ${ARGN} REQUIRED)
			
	find_path(OpenCV_INCLUDE_DIR "opencv/cv.h" PATHS "${OpenCV_DIR}" PATH_SUFFIXES "include" DOC "")
	target_include_directories(${TARGET} PUBLIC ${OpenCV_INCLUDE_DIR})
	
	target_link_libraries(ssf_core ${OpenCV_LIBS})

endmacro()