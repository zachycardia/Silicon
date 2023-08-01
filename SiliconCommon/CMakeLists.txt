##
# CMakeList.txt
# 
# CMake project for SiliconCommon.
##

##
# Sub-project name
##

set(SILICON_COMMON SiliconCommon)

##
# Sub-project files
##

file(GLOB_RECURSE common_files "src/*")


##
# Visual Studio project generation
##

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${common_files})

##
# Add files to executable
##

add_library(${SILICON_COMMON} STATIC ${common_files})

##
# Linker properties
##

set_target_properties(${SILICON_COMMON} PROPERTIES LINKER_LANGUAGE CXX)

##
# Include directories
##

target_include_directories(${SILICON_COMMON} PUBLIC "${PROJECT_SOURCE_DIR}/include")