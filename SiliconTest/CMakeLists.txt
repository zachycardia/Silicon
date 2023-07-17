##
# CMakeList.txt
# 
# CMake project for SiliconTest.
##

##
# Sub-project name
##

set(SILICON_TEST SiliconTest)

##
# Sub-project files
##

file(GLOB_RECURSE test_files "src/*")

##
# Visual Studio project generation
##

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${test_files})

##
# Add files to executable
##

add_executable (${SILICON_TEST} "src/main.cpp" ${test_files})

##
# Include directories
##

target_include_directories(${SILICON_TEST} PRIVATE "${CMAKE_SOURCE_DIR}/SiliconEngine/src")

##
# Link libraries
##

target_link_libraries(${SILICON_TEST}
	SiliconEngine
)
