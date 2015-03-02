#root/components/CMakeLists.txt

#Set alias to components paths
set (CORE_PATH ${PROJECT_SOURCE_DIR}/components/core) #core

#Include CORE component to project
include_directories (${CORE_PATH}/include/core)
add_subdirectory (core)