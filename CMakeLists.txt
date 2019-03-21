cmake_minimum_required(VERSION 3.13)
project(C_MinMax)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(C_MinMax
        minmax.cpp)
