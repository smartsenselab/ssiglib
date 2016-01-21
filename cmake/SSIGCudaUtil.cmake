include(CMakeParseArguments)

set(ssig_cuda_minimal_version 5.0)

macro(ssig_find_cuda)
	find_package(CUDA ${ssig_cuda_minimal_version} REQUIRED)
	mark_as_advanced(CUDA_FOUND)
endmacro()

macro(ssig_link_cuda SSIGLIB_MODULE)
	ssig_find_cuda()

	set(MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/${SSIGLIB_MODULE}")
	file(GLOB CUDA_INCLUDE_FILES	"${MODULE_PATH}/include/${SSIGLIB_MODULE}/*.cuh")
	file(GLOB CUDA_SOURCE_FILES	"${MODULE_PATH}/cuda/*.cu")

	include_directories("${MODULE_PATH}/include/")
	CUDA_ADD_LIBRARY(cuda_${SSIGLIB_MODULE} STATIC ${CUDA_SOURCE_FILES} ${CUDA_INCLUDE_FILES})

	#target_link_libraries(${_module} cuda_${_module})

endmacro()
