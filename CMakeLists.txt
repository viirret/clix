cmake_minimum_required(VERSION 3.16)
project(clix)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding Raylib
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)


# TODO there has to be a smarter way to do this.

# for other programs substitute, first .cc file
# clix/clickerGame.cc
# clix/clickerGame2.cc
# clix/tictactoe.cc
# clix/hunter.cc

add_executable(${PROJECT_NAME} examples/clickerGame2.cc clix/Image.cc clix/Core.cc clix/Gun.cc clix/Audio.cc clix/Player.cc clix/Object.cc clix/Controls.cc clix/Crosshair.cc clix/Config.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("You're on Mac OS !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("You're on Linux !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("You're on Windows !")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
