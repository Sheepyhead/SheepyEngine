# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("SheepyEngine")

set (CMAKE_CXX_STANDARD 17)
set (SOURCE_DIRECTORY Source)
set (HEADER_FILES 
    ${SOURCE_DIRECTORY}/Game.h 
    ${SOURCE_DIRECTORY}/GameObject.h
    ${SOURCE_DIRECTORY}/Transform.h
)
set (SOURCE_FILES 
    ${SOURCE_DIRECTORY}/Game.cpp 
    ${SOURCE_DIRECTORY}/GameObject.cpp 
    ${SOURCE_DIRECTORY}/Transform.cpp 
)

# Include sub-projects.
add_subdirectory (${SOURCE_DIRECTORY})

# Include libraries
set (CIMG_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/3rdParty/CImg)
add_library (CImg INTERFACE)
target_include_directories (CImg INTERFACE ${CIMG_INCLUDE_DIR})

set (TROMPELOEIL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/3rdParty/trompeloeil/include)
add_library (TrompeLoeil INTERFACE)
target_include_directories (TrompeLoeil INTERFACE ${TROMPELOEIL_INCLUDE_DIR})


add_library (SheepyEngine STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries (SheepyEngine CImg TrompeLoeil)

# Tests
set (CATCH_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/3rdParty/Catch2/single_include)
set (TEST_DIRECTORY Test)
set (TEST_SOURCES
	${TEST_DIRECTORY}/test.h
	${TEST_DIRECTORY}/GameTest.cpp
    ${TEST_DIRECTORY}/Stubs/GameLoopTestGameObject.h
    ${TEST_DIRECTORY}/Stubs/GameLoopTestGameObject.cpp
)

add_subdirectory (${TEST_DIRECTORY})
add_library (Catch INTERFACE)
target_include_directories (
	Catch INTERFACE ${CATCH_INCLUDE_DIR}
	SheepyEngine INTERFACE ${SOURCE_DIRECTORY}
)

link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable (SheepyEngineTest ${TEST_SOURCES})

target_link_libraries (SheepyEngineTest SheepyEngine Catch)
#TODO: Consider if automatic testing can be integrated better
#if(${RUN_TESTS})
#	ADD_CUSTOM_COMMAND(
#		TARGET SheepyEngineTest
#		POST_BUILD
#		COMMAND ${CMAKE_CURRENT_LIST_DIR}/Build/Debug/SheepyEngineTest.exe
#	)
#endif()