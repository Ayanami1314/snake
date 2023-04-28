cmake_minimum_required(VERSION 3.24)
project(untitled18)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled18 main.cpp apple.h snake&graph.h graph_initialize.h score&time.h all_global.h UI.h)


target_link_libraries(${PROJECT_NAME} PRIVATE PDCurses)
include_directories(include)
link_directories(libs)
