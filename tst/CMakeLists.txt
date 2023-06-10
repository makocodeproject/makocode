add_executable(makocode_test encode_decode_test.cpp ../src/mt19937/mt19937.cpp ../src/mt19937/mt19937.hpp)

add_test(NAME main COMMAND makocode_test)