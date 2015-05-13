#root/components/configuration/CMakeLists.txt

###############################################################################
# CONFIGURE CORE PATH
###############################################################################
set (CONFIGURATION_PATH ${PROJECT_SOURCE_DIR}/components/configuration)

###############################################################################
# CREATE FILES SET
###############################################################################

file(GLOB CONFIGURATION_MAIN_FILES			"${CONFIGURATION_PATH}/include/configuration/configuration.hpp" 
											"${CONFIGURATION_PATH}/src/configuration.cpp"
											)
										
file(GLOB CONFIGURATION_STREAM_FILES		"${CONFIGURATION_PATH}/include/configuration/stream.hpp"
											"${CONFIGURATION_PATH}/src/stream.cpp"
											)
										
file(GLOB CONFIGURATION_MODULE_FILES		"${CONFIGURATION_PATH}/src/module.cpp"
											"${CONFIGURATION_PATH}/include/configuration/module.hpp"
											)

file(GLOB CONFIGURATION_EXCEPTIONS_FILES	"${CONFIGURATION_PATH}/src/configuration_exception.cpp"
											"${CONFIGURATION_PATH}/include/configuration/configuration_exception.hpp"
											)
											
file(GLOB CONFIGURATION_UTIL_FILES			"${CONFIGURATION_PATH}/include/configuration/configuration_defs.hpp"
											)											

file(GLOB CONFIGURATION_INCLUDES			"${CONFIGURATION_PATH}/include/configuration/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("Configuration"	FILES ${CONFIGURATION_MAIN_FILES})
source_group("Stream"			FILES ${CONFIGURATION_STREAM_FILES})
source_group("Module"			FILES ${CONFIGURATION_MODULE_FILES})
source_group("Exceptions"		FILES ${CONFIGURATION_EXCEPTIONS_FILES})
source_group("Util"				FILES ${CONFIGURATION_UTIL_FILES})

###############################################################################
# ADD LIBRARY CONFIGURATION
###############################################################################

#Add library configuration into SSF project with its project
add_library(ssf_configuration 	${CONFIGURATION_MAIN_FILES}
								${CONFIGURATION_STREAM_FILES}
								${CONFIGURATION_MODULE_FILES}
								${CONFIGURATION_EXCEPTIONS_FILES}
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

###############################################################################
# SET TESTS FOR LIBRARY CONFIGURATIOS
###############################################################################

if(BUILD_TESTS)
	add_subdirectory(test)
endif()