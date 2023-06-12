add_executable(
        makocode_test
        makocode/encode_decode_test.cpp
        ../src/mt19937/mt19937.hpp
        ../src/mt19937/mt19937.cpp
        ../src/makocode/cmd.cpp)

add_test(NAME main COMMAND makocode_test)