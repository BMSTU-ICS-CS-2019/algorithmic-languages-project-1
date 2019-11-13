cmake_minimum_required(VERSION 3.15)
project(lab_11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -fPIC)

add_definitions(-DDEBUG)

add_executable(
        lab_11 main.cpp
        encode/encoder.cpp encode/encoder.h
        encode/shift_side.cpp encode/shift_side.h
        encode/string_utils.cpp encode/string_utils.h
        encode/base16encoder.cpp encode/base16encoder.h
        encode/debug.h
)