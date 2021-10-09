cmake_minimum_required(VERSION 3.20)
project(terminal_player)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(terminal_player src/Player.cpp)

target_link_libraries(terminal_player ${OpenCV_LIBS} pthread)