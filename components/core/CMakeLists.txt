#root/components/core/CMakeLists.txt

###############################################################################
# CONFIGURE CORE PATH
###############################################################################
set (CORE_PATH ${PROJECT_SOURCE_DIR}/components/core)

###############################################################################
# CREATE FILES SET
###############################################################################							
file(GLOB CORE_INCLUDES				"${CORE_PATH}/include/core/*.hpp")
file(GLOB CORE_SOURCE				"${CORE_PATH}/src/*.cpp")

###############################################################################
# ADD LIBRARY CORE
###############################################################################

#Add library core into SSF project with its project
add_library(ssf_core 	${CORE_SOURCE} ${CORE_INCLUDES})
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