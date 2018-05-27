# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("SheepyEngine")

set (CMAKE_CXX_STANDARD 17)

set (HEADER_FILES 3rdParty/CImg/CImg.h)

set (SOURCE_DIRECTORY Source)

set (TEST_DIRECTORY Test)

# Include sub-projects.
add_subdirectory ("Source")
add_subdirectory ("Test")

# Include libraries
include_directories (
    "${CMAKE_CURRENT_LIST_DIR}/3rdParty/CImg"
    "${CMAKE_CURRENT_LIST_DIR}/3rdParty/Catch2/single_include"
)


add_library (SheepyEngine STATIC 
    "${SOURCE_DIRECTORY}/Game.cpp" 
    "${SOURCE_DIRECTORY}/Game.h" 
    "${SOURCE_DIRECTORY}/GameObject.h"
    ${HEADER_FILES})

target_include_directories(SheepyEngine PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdParty/CImg/)

add_executable(SheepyEngineTest "${TEST_DIRECTORY}/test.cpp" "3rdParty/Catch2/single_include/catch.hpp")

target_include_directories(SheepyEngineTest PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdParty/Catch2/)

# TODO: Add tests and install targets if needed.

if(${RUN_TESTS})
	ADD_CUSTOM_COMMAND(
		TARGET SheepyEngineTest SheepyEngine
		POST_BUILD
		COMMAND ${CMAKE_CURRENT_LIST_DIR}/Build/Debug/SheepyEngineTest.exe
	)
endif()