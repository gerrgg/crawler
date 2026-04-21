cmake_minimum_required(VERSION 3.16)
project(raylib_starter LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

include_directories(include)

add_executable(raylib_starter
  src/main.cpp
  src/Game.cpp
  src/Player.cpp
)

target_link_libraries(raylib_starter PRIVATE raylib)