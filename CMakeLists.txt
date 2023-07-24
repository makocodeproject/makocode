cmake_minimum_required(VERSION 3.23)
project(makocode)

set(CMAKE_CXX_STANDARD 23)

enable_testing()

add_subdirectory(tst)

add_executable(
        makocode
        src/cxxopts/cxxopts.hpp
        src/makocode/cmd.cpp
        src/makocode/cmd.hpp
        src/makocode/constants.hpp
        src/makocode/decoder.cpp
        src/makocode/decoder.hpp
        src/makocode/encoder.cpp
        src/makocode/encoder.hpp
        src/makocode/encoder_parameters.cpp
        src/makocode/encoder_parameters.hpp
        src/makocode/main.cpp
        src/pcg/pcg_extras.hpp
        src/pcg/pcg_random.hpp
        src/pcg/pcg_uint128.hpp
)
