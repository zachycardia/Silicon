##
# CMakeList.txt
# 
# CMake project for SiliconGraphics.
##

##
# Sub-project name
##

set(SILICON_GRAPHICS SiliconGraphics)

##
# Sub-project files
##

file(GLOB_RECURSE graphics_files "src/*")

##
# Visual Studio project generation
##

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${graphics_files})

##
# Add files to executable
##

add_library(${SILICON_GRAPHICS} STATIC ${graphics_files})

##
# Include directories
##

target_include_directories(${SILICON_GRAPHICS} PRIVATE "${PROJECT_SOURCE_DIR}/SiliconCommon/src") # SiliconCommon
target_include_directories(${SILICON_GRAPHICS} PUBLIC "${PROJECT_SOURCE_DIR}/lib") # Common libraries
target_include_directories(${SILICON_GRAPHICS} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib") # Libraries

##
# External libraries
##

file(GLOB_RECURSE graphics_ext_shared_libs "lib/*.lib")

##
# Link libraries
##

target_link_libraries(${SILICON_GRAPHICS}
	#SiliconCommon # DISABLED - Header-only.
	${common_ext_static_libs}
	${graphics_ext_shared_libs}
)
