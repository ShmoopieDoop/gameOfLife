cmake_minimum_required(VERSION 3.24)
project(gameOfLife)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
add_executable(gameOfLife
        src/Game.cpp src/Game.h src/Cell.cpp src/Cell.h src/main.cpp src/Display.cpp src/Display.h src/Coordinate.h)
target_link_libraries(gameOfLife PRIVATE SDL2::SDL2)
