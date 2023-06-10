cmake_minimum_required(VERSION 3.23)
project(makocode)

set(CMAKE_CXX_STANDARD 23)

enable_testing()

add_subdirectory(tst)

add_executable(
        makocode
        src/makocode/cmd.cpp
        src/makocode/encoder.hpp
        src/makocode/decoder.hpp
        src/mt19937/mt19937.hpp
        src/mt19937/mt19937.cpp
        src/cxxopts/cxxopts.hpp)