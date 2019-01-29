cmake_minimum_required(VERSION 2.8.12)
project(raylibECS)

set(CMAKE_CXX_STANDARD 17)

SET(BUILD_EXAMPLES OFF CACHE BOOL "Build the examples.")
SET(BUILD_GAMES OFF CACHE BOOL "Build the example games.")
add_subdirectory(ext/raylib)
add_subdirectory(ext/entt)

add_executable(${PROJECT_NAME} src/main.cpp)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib EnTT)

# That's it! You should have an example executable that you can run. Have fun!
