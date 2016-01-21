include(CMakeParseArguments)

set(ssig_cuda_minimal_version 5.0)

macro(ssig_find_cuda)
	find_package(CUDA ${ssig_cuda_minimal_version})
	mark_as_advanced(CUDA_FOUND)
endmacro()

macro(ssig_link_cuda SSIGLIB_MODULE)
	ssig_find_cuda()

	if(CUDA_FOUND)
		set(MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/${SSIGLIB_MODULE}")
		file(GLOB CUDA_INCLUDE_FILES	"${MODULE_PATH}/include/${SSIGLIB_MODULE}/*.cuh")
		file(GLOB CUDA_SOURCE_FILES	"${MODULE_PATH}/cuda/*.cu")


		list(LENGTH CUDA_SOURCE_FILES source_files_size)
		if(NOT ${source_files_size} STREQUAL "0")
			message(STATUS "Link to CUDA Library:")
			include_directories("${MODULE_PATH}/include/")
			CUDA_ADD_LIBRARY(cuda_${SSIGLIB_MODULE} STATIC ${CUDA_SOURCE_FILES} ${CUDA_INCLUDE_FILES})
			target_link_libraries(${SSIGLIB_MODULE} cuda_${SSIGLIB_MODULE})
		else()
			message(WARNING "This module does not have cuda files!")
		endif()
	else()
		message(WARNING "Cuda not found!")
	endif()

endmacro()
