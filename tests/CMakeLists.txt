add_executable(makocode_test encode_decode_test.cpp ../mt19937/mt19937.cpp ../mt19937/mt19937.h)

add_test(NAME main COMMAND makocode_test)