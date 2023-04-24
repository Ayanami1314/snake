cmake_minimum_required(VERSION 3.24)
project(untitled18)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled18 main.cpp 123.h score.h snake.h apple.h)


target_link_libraries(${PROJECT_NAME} PRIVATE PDCurses)

include_directories(include)
link_directories(libs)
