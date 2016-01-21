include(CMakeParseArguments)

set(ssig_opencv_minimal_version 3.0)

macro(ssig_find_opencv)
	set(ssig_options REQUIRED QUIET)
	set(ssig_multiValueArgs COMPONENTS)
	cmake_parse_arguments(SSIG_FIND_OPENCV "${ssig_options}" "${ssig_oneValueArgs}" "${ssig_multiValueArgs}" ${ARGN} )

	set(ssig_options "")
	if(${SSIG_FIND_OPENCV_REQUIRED})
		set(ssig_options "REQUIRED")
	endif()

	if(${SSIG_FIND_OPENCV_QUIET})
		set(ssig_options "QUIET")
	endif()

	find_package(OpenCV ${ssig_opencv_minimal_version} COMPONENTS ${SSIG_FIND_OPENCV_COMPONENTS} ${ssig_options})
	mark_as_advanced(OPENCV_FOUND)
endmacro()

macro(ssig_link_opencv SSIGLIB_MODULE)
	ssig_find_opencv(COMPONENTS ${ARGN} REQUIRED)

	find_path(OpenCV_INCLUDE_DIR "opencv/cv.h" PATHS "${OpenCV_DIR}" PATH_SUFFIXES "include" DOC "")
	target_include_directories(${SSIGLIB_MODULE} PUBLIC ${OpenCV_INCLUDE_DIR})

	target_link_libraries(${SSIGLIB_MODULE} ${OpenCV_LIBS})

endmacro()
