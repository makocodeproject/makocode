//
// Created by Justin Bass on 6/15/2023.
//

#define PCG_FORCE_EMULATED_128BIT_MATH 1

#include "../../src/pcg/pcg_random.hpp"

#include <array>

void pcg64_uint128_consistent() {
    pcg64 rng(0);

    std::array<uint64_t, 5> expected {
        74029666500212977u,
        8088122161323000979u,
        16521829690994476282u,
        10814004662382438494u,
        9052198920789078554u};

    std::array<uint64_t, 5> actual = {};
    for (int i = 0; i < 5; i++) {
        actual[i] = rng();
    }

    assert(actual == expected);
}

int main() {
    pcg64_uint128_consistent();
}