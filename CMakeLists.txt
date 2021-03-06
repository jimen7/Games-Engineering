cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

######## Add External Dependencies ############
##SFML
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

##B2B Physics Library
# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D")
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")


## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

# Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

#ECM lib
#file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp engine/lib_ecm/*.h)
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

##RESOURCES
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

#### Practical 2 ####
file(GLOB_RECURSE SOURCES practical_2/*.cpp practical_2/*.h)
add_executable(PRACTICAL_2 ${SOURCES})
target_include_directories(PRACTICAL_2 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_2 sfml-graphics)
add_dependencies(PRACTICAL_2 copy_resources)


#### Practical 3 ####
file(GLOB_RECURSE SOURCES practical_3/*.cpp practical_3/*.h)
add_executable(PRACTICAL_3 ${SOURCES})
target_include_directories(PRACTICAL_3 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_3 sfml-graphics lib_tile_level_loader sfml-graphics)
add_dependencies(PRACTICAL_3 copy_resources)


set_target_properties(PRACTICAL_2 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

set_target_properties(PRACTICAL_3
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)


#### Practical 4 ####
file(GLOB_RECURSE SOURCES practical_4/*.cpp practical_4/*.h)
add_executable(PRACTICAL_4 ${SOURCES})
target_include_directories(PRACTICAL_4 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_4 sfml-graphics lib_tile_level_loader sfml-graphics lib_ecm)
add_dependencies(PRACTICAL_4 copy_resources)


set_target_properties(PRACTICAL_4
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)


#### Practical 5 ####
file(GLOB_RECURSE SOURCES practical_5/*.cpp practical_5/*.h)
add_executable(PRACTICAL_5 ${SOURCES})
target_include_directories(PRACTICAL_5 SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(PRACTICAL_5 sfml-graphics Box2D)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_5_PHYSICS)


set_target_properties(PRACTICAL_5
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
