#root/components/cameras/app/CMakeLists.txt

if(BUILD_APPS)

	#Create set of cameras tests files
	file(GLOB CAMERAS_APP_FILES "${CAMERAS_PATH}/app/main.cpp")
	
	add_executable(app_cameras ${CAMERAS_APP_FILES})
	ssf_link_boost(app_cameras system filesystem log log_setup thread date_time)

	# Standard linking to gtest stuff.
	target_include_directories(app_cameras PUBLIC ${CAMERAS_PATH}/include/)

	# Extra linking for the project.
	target_link_libraries(app_cameras ssf_cameras)
	
	#Configure folder to cameras library
	set_target_properties(app_cameras PROPERTIES FOLDER APPS)

	
endif()