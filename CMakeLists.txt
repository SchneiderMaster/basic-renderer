cmake_minimum_required(VERSION 3.10)
project(BasicRenderer)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include)

add_executable(basic_renderer main.cpp)
