#root/components/configuration/CMakeLists.txt

###############################################################################
# CONFIGURE CORE PATH
###############################################################################
set (CONFIGURATION_PATH ${PROJECT_SOURCE_DIR}/components/configuration)

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB CONFIGURATION_MAIN_FILES				"${CONFIGURATION_PATH}/include/configuration/setup.hpp" 
												"${CONFIGURATION_PATH}/src/setup.cpp"
												)
										
file(GLOB CONFIGURATION_STREAM_SETUP_FILES		"${CONFIGURATION_PATH}/include/configuration/stream_setup.hpp"
												"${CONFIGURATION_PATH}/src/stream_setup.cpp"
												)
										
file(GLOB CONFIGURATION_MODULE_SETUP_FILES		"${CONFIGURATION_PATH}/src/module_setup.cpp"
												"${CONFIGURATION_PATH}/include/configuration/module_setup.hpp"
												)

file(GLOB CONFIGURATION_SETUP_EXCEPTION_FILES	"${CONFIGURATION_PATH}/src/setup_exception.cpp"
												"${CONFIGURATION_PATH}/include/configuration/setup_exception.hpp"
												)
											
file(GLOB CONFIGURATION_UTIL_FILES				"${CONFIGURATION_PATH}/include/configuration/setup_defs.hpp"
												)											

file(GLOB CONFIGURATION_INCLUDES				"${CONFIGURATION_PATH}/include/configuration/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("Setup"				FILES ${CONFIGURATION_MAIN_FILES})
source_group("Stream_Setup"			FILES ${CONFIGURATION_STREAM_SETUP_FILES})
source_group("Module_Setup"			FILES ${CONFIGURATION_MODULE_SETUP_FILES})
source_group("Setup_Exception"		FILES ${CONFIGURATION_SETUP_EXCEPTION_FILES})
source_group("Util"					FILES ${CONFIGURATION_UTIL_FILES})

###############################################################################
# ADD LIBRARY CONFIGURATION
###############################################################################

#Add library configuration into SSF project with its project
add_library(ssf_configuration 	${CONFIGURATION_MAIN_FILES}
								${CONFIGURATION_STREAM_SETUP_FILES}
								${CONFIGURATION_MODULE_SETUP_FILES}
								${CONFIGURATION_SETUP_EXCEPTION_FILES}
								${CONFIGURATION_UTIL_FILES}
								)
								
target_include_directories (ssf_configuration PUBLIC ${CONFIGURATION_PATH}/include/)

#Link core to configuration
#target_include_directories(ssf_configuration PUBLIC ${CORE_PATH}/include/)
target_link_libraries(ssf_configuration ssf_core)
						
#Configure folder to configuration library
set_target_properties(ssf_configuration PROPERTIES FOLDER COMPONENTS)
target_compile_definitions(ssf_core PUBLIC CONFIG_API_EXPORTS)

#Install configuration
install (TARGETS ssf_configuration DESTINATION bin)
install (FILES ${CONFIGURATION_INCLUDES} DESTINATION include)

#Link External Libraries
ssf_link_opencv(ssf_configuration opencv_core opencv_imgproc opencv_highgui)

###############################################################################
# SET TESTS FOR LIBRARY CONFIGURATIONS
###############################################################################

if(BUILD_TESTS)
	add_subdirectory(test)
endif()