/*
 * The Mersenne Twister pseudo-random number generator (PRNG)
 * Copyright 2015-2017 Christian Stigen Larsen, Modified BSD license
 *
 * This is an implementation of fast PRNG called MT19937, meaning it has a
 * period of 2^19937-1, which is a Mersenne prime.
 *
 * This PRNG is fast and suitable for non-cryptographic code.  For instance, it
 * would be perfect for Monte Carlo simulations, etc.
 */

#ifndef MAKOCODE_MT19937_HPP
#define MAKOCODE_MT19937_HPP

#include <cstdint>
#include <cstddef>

// TODO: Extend to >32-bit, use big integers

/*
 * Extract a pseudo-random unsigned 32-bit integer in the range 0 ... UINT32_MAX
 */
uint32_t rand_u32();

/*
 * Initialize Mersenne Twister with given seed value.
 */
void seed(uint32_t seed_value);

#endif //MAKOCODE_MT19937_HPP