##
# CMakeList.txt
# 
# Top level CMake project file.
##

cmake_minimum_required (VERSION 3.18)

# C++ config
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Silicon")

##
# External libraries
##

file(GLOB_RECURSE common_ext_static_libs "lib/*.lib")

# Include sub-projects.
add_subdirectory ("SiliconCommon")
add_subdirectory ("SiliconGraphics")
add_subdirectory ("SiliconEngine")
add_subdirectory ("SiliconTest")
