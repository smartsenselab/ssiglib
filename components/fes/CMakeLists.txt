#root/components/fes/CMakeLists.txt

###############################################################################
# CONFIGURE FES PATH
###############################################################################
set (FES_PATH ${PROJECT_SOURCE_DIR}/components/fes)

###############################################################################
# CREATE FILES SET
###############################################################################


file(GLOB FES_FILTER1_FILES		"${FES_PATH}/include/fes/fes_defs.hpp"
								"${FES_PATH}/src/fes_source_dummy.cpp"									
								)
									
file(GLOB FES_INCLUDES				"${FES_PATH}/include/fes/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("Filter 01"	FILES ${FES_FILTER1_FILES})

###############################################################################
# ADD LIBRARY FES
###############################################################################

#Add library core into SSF project with its project
add_library(ssf_fes 		${FES_FILTER1_FILES}
							)
							
target_include_directories(ssf_fes PUBLIC ${FES_PATH}/include/)

target_link_libraries(ssf_fes ssf_core)
						
#Configure folder to core library
set_target_properties(ssf_fes PROPERTIES FOLDER COMPONENTS)

target_compile_definitions(ssf_fes PUBLIC FES_API_EXPORTS)

#Install configuration
install (TARGETS ssf_fes DESTINATION bin)
install (FILES ${FES_INCLUDES} DESTINATION include)

#Link External Libraries
#ssf_link_boost(ssf_fes system filesystem log log_setup thread date_time)


###############################################################################
# SET TESTS FOR LIBRARY FES
###############################################################################

if(BUILD_TESTS)	
	add_subdirectory(test)
endif()