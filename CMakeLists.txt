cmake_minimum_required(VERSION 3.10)
project(raylibECS)

set(CMAKE_CXX_STANDARD 17)

SET(BUILD_EXAMPLES OFF CACHE BOOL "Build the examples.")
SET(BUILD_GAMES OFF CACHE BOOL "Build the example games.")
add_subdirectory(ext/raylib)
add_subdirectory(ext/entt)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

include_directories(src ext src/controllers src/components src/systems)
add_executable(${PROJECT_NAME} src/main.cpp src/systems/CollisionSystem.cpp src/systems/RenderSystem.cpp src/systems/PlayerInputSystem.cpp)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib EnTT)
