# cmake_minimum_required(VERSION <specify CMake version here>)
project(PAA)

set(CMAKE_CXX_STANDARD 17)

add_executable(PAA main.cpp bucket.cpp bucket.h)