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
        src/pcg/pcg_random.hpp
        src/pcg/pcg_extras.hpp
        src/pcg/pcg_uint128.hpp
        src/cxxopts/cxxopts.hpp
        src/makocode/main.cpp
        src/makocode/cmd.hpp)