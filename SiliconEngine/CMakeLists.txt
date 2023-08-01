##
# CMakeList.txt
# 
# CMake project for SiliconEngine.
##

##
# Sub-project name
##

set(SILICON_ENGINE SiliconEngine)

##
# Sub-project files
##

file(GLOB_RECURSE engine_files "src/*")

##
# Visual Studio project generation
##

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${engine_files})

##
# Add files to executable
##

add_library(${SILICON_ENGINE} STATIC ${engine_files})

##
# Include directories
##

target_include_directories(${SILICON_ENGINE} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${SILICON_ENGINE} PUBLIC "${CMAKE_SOURCE_DIR}/SiliconCommon/src") # SiliconCommon

##
# Link libraries
##

target_link_libraries(${SILICON_ENGINE}
	#SiliconCommon # DISABLED - Header-only.
)
