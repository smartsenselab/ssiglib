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

	#Create set of configuration tests files
    file(GLOB CONFIGURATION_TEST_FILES "${CONFIGURATION_PATH}/test/*.cpp")
	
    add_executable(test_configuration ${CONFIGURATION_TEST_FILES})

	# Standard linking to gtest stuff.
    target_link_libraries(test_configuration gtest gtest_main)
	target_include_directories(test_configuration PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	target_include_directories(test_configuration PUBLIC ${CONFIGURATION_PATH}/include/)

	# Extra linking for the project.
    target_link_libraries(test_configuration ssf_configuration)

	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable ssf_test_configuration to see those specific tests.
    add_test(NAME test_configuration COMMAND test_configuration WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data/tests/configuration")
	
	#Configure folder to configuration library
    set_target_properties(test_configuration PROPERTIES FOLDER TESTS)

endif()