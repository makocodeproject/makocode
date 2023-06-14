add_executable(
        encode_decode_test
        makocode/encode_decode_test.cpp
        ../src/makocode/decoder.hpp
        ../src/makocode/encoder.hpp
        ../src/pcg/pcg_random.hpp
        ../src/pcg/pcg_extras.hpp
        ../src/pcg/pcg_uint128.hpp
)

add_executable(
        cmd_test
        makocode/cmd_test.cpp
        ../src/makocode/cmd.hpp
        ../src/makocode/cmd.cpp
        ../src/pcg/pcg_random.hpp
        ../src/pcg/pcg_extras.hpp
        ../src/pcg/pcg_uint128.hpp
)

add_test(NAME encode_decode_test COMMAND encode_decode_test)
add_test(NAME cmd_test COMMAND cmd_test)