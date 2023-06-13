add_executable(
        encode_decode_test
        encode_decode_test.cpp
        ../src/makocode/decoder.hpp
        ../src/makocode/encoder.hpp
        ../src/mt19937/mt19937.hpp
        ../src/mt19937/mt19937.cpp
)

add_executable(
        cmd_test
        cmd_test.cpp
        ../src/makocode/cmd.hpp
        ../src/makocode/cmd.cpp
        ../src/mt19937/mt19937.hpp
        ../src/mt19937/mt19937.cpp
)

add_test(NAME encode_decode_test COMMAND encode_decode_test)
add_test(NAME cmd_test COMMAND cmd_test)