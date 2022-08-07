cmake_minimum_required(VERSION 3.16)
project(x)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding Raylib
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

# Adding clix
include_directories(clix)
FILE(GLOB clixSources clix/*.cc)
add_library(clix ${clixSources})

# for other programs substitute .cc file down below like:
# examples/clickerGame.cc
# examples/tictactoe.cc
# examples/hunter.cc

add_executable(${PROJECT_NAME} examples/snake.cc)

target_link_libraries(${PROJECT_NAME} PRIVATE clix PRIVATE raylib)


