cmake_minimum_required(VERSION 3.23)
project(makocode)

set(CMAKE_CXX_STANDARD 23)

enable_testing()

add_subdirectory(tests)

add_executable(makocode main.cpp encoder.h decoder.h)