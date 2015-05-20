#root/components/cameras/CMakeLists.txt

###############################################################################
# CONFIGURE CORE PATH
###############################################################################
set (CAMERAS_PATH ${PROJECT_SOURCE_DIR}/components/cameras)

###############################################################################
# CREATE FILES SET
###############################################################################


file(GLOB CAMERAS_CAMERA_FILES		"${CAMERAS_PATH}/include/cameras/camera.hpp"
									"${CAMERAS_PATH}/src/camera.cpp"
									"${CAMERAS_PATH}/include/cameras/video_camera.hpp"
									"${CAMERAS_PATH}/src/video_camera.cpp"
									)
									
file(GLOB CAMERAS_TEMP_FILES		"${CAMERAS_PATH}/include/cameras/SMCamCMD.hpp"
									"${CAMERAS_PATH}/src/SMCamCMD.cpp"
									"${CAMERAS_PATH}/include/cameras/SMData.hpp"
									"${CAMERAS_PATH}/src/SMData.cpp"
									"${CAMERAS_PATH}/include/cameras/video_camera_PTZ.hpp"
									"${CAMERAS_PATH}/src/video_camera_PTZ.cpp"
									"${CAMERAS_PATH}/include/cameras/video_camera_PTZ_Trend_Net7865.hpp"
									"${CAMERAS_PATH}/src/video_camera_PTZ_Trend_Net7865.cpp"
									)
							
file(GLOB CORE_INCLUDES				"${CAMERAS_PATH}/include/cameras/*.hpp")

###############################################################################
# CREATE SOURCE GROUPS
###############################################################################
source_group("Cameras"	FILES ${CAMERAS_CAMERA_FILES})
source_group("Temp"		FILES ${CAMERAS_TEMP_FILES})

###############################################################################
# ADD LIBRARY CORE
###############################################################################

#Add library core into SSF project with its project
add_library(ssf_cameras 	${CAMERAS_CAMERA_FILES}
							${CAMERAS_TEMP_FILES}
							)
							
target_include_directories(ssf_cameras PUBLIC ${CAMERAS_PATH}/include/)

target_link_libraries(ssf_cameras ssf_core)
						
#Configure folder to core library
set_target_properties(ssf_cameras PROPERTIES FOLDER COMPONENTS)

target_compile_definitions(ssf_cameras PUBLIC CAMERAS_API_EXPORTS)

#Install configuration
install (TARGETS ssf_cameras DESTINATION bin)
install (FILES ${CAMERAS_INCLUDES} DESTINATION include)

#Link External Libraries
ssf_link_boost(ssf_cameras system filesystem log log_setup thread date_time)


###############################################################################
# SET TESTS FOR LIBRARY CORE
###############################################################################

if(BUILD_TESTS)	
	add_subdirectory(test)
endif()