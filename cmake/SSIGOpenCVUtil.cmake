include(CMakeParseArguments)

set(ssig_opencv_minimal_version 3.0)

macro(ssig_find_opencv)
	set(ssig_multiValueArgs COMPONENTS)
	cmake_parse_arguments(SSIG_FIND_OPENCV  "${ssig_multiValueArgs}" ${ARGN} )

	find_package(OpenCV ${ssig_opencv_minimal_version} COMPONENTS ${SSIG_FIND_OPENCV_COMPONENTS} REQUIRED QUIET)
	mark_as_advanced(OPENCV_FOUND)
endmacro()

macro(ssig_link_opencv SSIGLIB_MODULE)
	ssig_find_opencv(COMPONENTS ${ARGN})
	
	message(STATUS "Link to OpenCV Libraries:")
	find_path(OpenCV_INCLUDE_DIRS "opencv/cv.h" PATHS "${OpenCV_DIR}" PATH_SUFFIXES "include" DOC "")
	target_include_directories(${SSIGLIB_MODULE} PUBLIC ${OpenCV_INCLUDE_DIR})

	target_link_libraries(${SSIGLIB_MODULE} ${OpenCV_LIBS})

endmacro()
