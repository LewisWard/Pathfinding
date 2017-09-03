cmake_minimum_required (VERSION 2.6)
project (AIDemo)

# the version number.
set (AIDemo_VERSION_MAJOR 1)
set (AIDemo_VERSION_MINOR 0)
set (AIDemo_ASSET_DIR "${PROJECT_SOURCE_DIR}/AIDemo/assets/")

# if Visual Studio
if(MSVC)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GF")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()
 
# add paths for include files
include_directories("${PROJECT_SOURCE_DIR}/AIDemo/include")

# set up defines in Config.h the be used within the program
configure_file (
  "${PROJECT_SOURCE_DIR}/AIDemo/include/Config.h.in"
  "${PROJECT_SOURCE_DIR}/AIDemo/include/Config.h"
  )

# set output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set up lib's
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/lib")

# add the executable
add_executable(AIDemo ${PROJECT_SOURCE_DIR}/AIDemo/src/Main.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/Actor.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/Demo.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/NPC.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/PathfindingAStar.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/Player.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/Ray.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/Texture.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/Wall.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/Window.cpp
                      ${PROJECT_SOURCE_DIR}/AIDemo/src/World.cpp

                      ${PROJECT_SOURCE_DIR}/AIDemo/include/AABB.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Actor.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Config.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Demo.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/NPC.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/PathfindingAStar.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Player.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Ray.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Texture.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Vec2.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Wall.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/Window.h
                      ${PROJECT_SOURCE_DIR}/AIDemo/include/World.h
                )

TARGET_LINK_LIBRARIES(AIDemo SDL2.lib SDL2main.lib)