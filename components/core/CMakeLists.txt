#root/components/core/CMakeLists.txt

#Create exception files group
file(GLOB core_exception "${CORE_PATH}/include/core/exception.h" "${CORE_PATH}/src/exception.cpp")

#Create Filters
source_group("exception" FILES ${core_exception}) #exception

#Add Library core
add_library(core ${core_exception})

set_target_properties(core PROPERTIES FOLDER components)