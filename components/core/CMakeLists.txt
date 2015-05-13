#root/components/core/CMakeLists.txt

###############################################################################
# CONFIGURE CORE PATH
###############################################################################
set (CORE_PATH ${PROJECT_SOURCE_DIR}/components/core)

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB CORE_EXCEPTION_FILES 		"${CORE_PATH}/include/core/exception.hpp" 
									"${CORE_PATH}/src/exception.cpp"
									"${CORE_PATH}/include/core/file_exception.hpp" 
									"${CORE_PATH}/src/file_exception.cpp"
									"${CORE_PATH}/include/core/param_exception.hpp" 
									"${CORE_PATH}/src/param_exception.cpp"
									)

file(GLOB CORE_FILEHANDLE_FILES 	"${CORE_PATH}/include/core/file_handle.hpp" 
									"${CORE_PATH}/src/file_handle.cpp"
									"${CORE_PATH}/include/core/directory_handle.hpp" 
									"${CORE_PATH}/src/directory_handle.cpp"
									)

file(GLOB CORE_PARAMETERS_FILES 	"${CORE_PATH}/include/core/parameter.hpp"
									"${CORE_PATH}/src/parameter.cpp"
									"${CORE_PATH}/include/core/parameters.hpp"
									"${CORE_PATH}/src/parameters.cpp"
									)

file(GLOB CORE_BASEOBJECT_FILES		"${CORE_PATH}/include/core/base_object.hpp"
									"${CORE_PATH}/src/base_object.cpp"
									)

file(GLOB CORE_RESOURCE_FILES	 	"${CORE_PATH}/include/core/resource.hpp"
									"${CORE_PATH}/src/resource.cpp"
									"${CORE_PATH}/include/core/resource_info.hpp"
									"${CORE_PATH}/src/resource_info.cpp"
									"${CORE_PATH}/include/core/resource_setup.hpp"
									"${CORE_PATH}/src/resource_setup.cpp"
									)

file(GLOB CORE_STRUCTURES_FILES	 	"${CORE_PATH}/include/core/matrix.hpp"
									"${CORE_PATH}/src/matrix.cpp"
									"${CORE_PATH}/include/core/cube.hpp"
									"${CORE_PATH}/include/core/point2d.hpp"
									"${CORE_PATH}/src/point2d.cpp"
									"${CORE_PATH}/include/core/point3d.hpp"
									"${CORE_PATH}/src/point3d.cpp"
									"${CORE_PATH}/include/core/rect.hpp"
									"${CORE_PATH}/src/scale_info.cpp"
									"${CORE_PATH}/include/core/scale_info.hpp"
									)

file(GLOB CORE_UTIL_FILES			"${CORE_PATH}/include/core/core_defs.hpp"
									"${CORE_PATH}/include/core/version_info.hpp"
									"${CORE_PATH}/src/version_info.cpp"	
									"${CORE_PATH}/include/core/util.hpp"
									"${CORE_PATH}/src/util.cpp"
									)

file(GLOB CORE_LOG_FILES			"${CORE_PATH}/include/core/log.hpp"
									"${CORE_PATH}/src/log.cpp"
									)

file(GLOB CORE_PLUGIN_FILES			"${CORE_PATH}/include/core/plugin_loader.hpp"
									"${CORE_PATH}/include/core/plugin_defs.hpp"
									"${CORE_PATH}/include/core/plugin.hpp"
									)

file(GLOB CORE_INCLUDES				"${CORE_PATH}/include/core/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("Exception"	FILES ${CORE_EXCEPTION_FILES})
source_group("Files"		FILES ${CORE_FILEHANDLE_FILES})
source_group("Parameters"	FILES ${CORE_PARAMETERS_FILES})
source_group("Base Ojbect"	FILES ${CORE_BASEOBJECT_FILES})
source_group("Resources"	FILES ${CORE_RESOURCE_FILES})
source_group("Log"			FILES ${CORE_LOG_FILES})
source_group("Util"			FILES ${CORE_UTIL_FILES})
source_group("Structures"	FILES ${CORE_STRUCTURES_FILES})
source_group("Plugin"		FILES ${CORE_PLUGIN_FILES})


###############################################################################
# ADD LIBRARY CORE
###############################################################################

#Add library core into SSF project with its project
add_library(ssf_core 	${CORE_EXCEPTION_FILES}
						${CORE_FILEHANDLE_FILES} 
						${CORE_PARAMETERS_FILES}
						${CORE_BASEOBJECT_FILES}
						${CORE_RESOURCE_FILES}
						${CORE_LOG_FILES}
						${CORE_UTIL_FILES}
						${CORE_STRUCTURES_FILES}
						${CORE_PLUGIN_FILES}
			)
target_include_directories(ssf_core PUBLIC ${CORE_PATH}/include/)
						
#Configure folder to core library
set_target_properties(ssf_core PROPERTIES FOLDER COMPONENTS)

target_compile_definitions(ssf_core PUBLIC CORE_API_EXPORTS)

#Install configuration
install (TARGETS ssf_core DESTINATION bin)
install (FILES ${CORE_INCLUDES} DESTINATION include)

#Link External Libraries
ssf_link_boost(ssf_core system filesystem log log_setup thread date_time)
ssf_link_opencv(ssf_core opencv_core opencv_imgproc opencv_highgui)


###############################################################################
# SET TESTS FOR LIBRARY CORE
###############################################################################

if(BUILD_TESTS)	
	add_subdirectory(test)
endif()