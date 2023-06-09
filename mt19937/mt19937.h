/*
 * The Mersenne Twister pseudo-random number generator (PRNG)
 *
 * This is an implementation of fast PRNG called MT19937, meaning it has a
 * period of 2^19937-1, which is a Mersenne prime.
 *
 * This PRNG is fast and suitable for non-cryptographic code.  For instance, it
 * would be perfect for Monte Carlo simulations, etc.
 *
 * Written by Christian Stigen Larsen
 * Distributed under the modified BSD license.
 * 2015-02-17, 2017-12-06
 */

#ifndef MAKOCODE_MT19937_H
#define MAKOCODE_MT19937_H

#include <cstdint>

// TODO: Extend to >32-bit, use big integers

/*
 * Extract a pseudo-random unsigned 32-bit integer in the range 0 ... UINT32_MAX
 */
uint32_t rand_u32();

/*
 * Initialize Mersenne Twister with given seed value.
 */
void seed(uint32_t seed_value);

#endif //MAKOCODE_MT19937_H