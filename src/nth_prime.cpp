///
/// @file  nth_prime.cpp
/// @brief Find the nth prime.
///
/// Copyright (C) 2021 Kim Walisch, <kim.walisch@gmail.com>
///
/// This file is distributed under the BSD License. See the COPYING
/// file in the top level directory.
///

#include <primecount.hpp>
#include <primecount-internal.hpp>
#include <primesieve.hpp>

#include <stdint.h>
#include <string>
#include <array>

namespace {

// Number of primes < 2^63
const int64_t max_n = 216289611853439384ll;

// primes[1] = 2, primes[2] = 3, ...
const std::array<int16_t, 170> primes =
{
    0,   2,   3,   5,   7,  11,  13,  17,  19,  23, 
   29,  31,  37,  41,  43,  47,  53,  59,  61,  67, 
   71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 
  113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 
  173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 
  229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 
  281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 
  349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 
  409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 
  463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 
  541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 
  601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 
  659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 
  733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 
  809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 
  863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 
  941, 947, 953, 967, 971, 977, 983, 991, 997, 1009
};

} // namespace

namespace primecount {

/// Find the nth prime using the prime counting function
/// and the segmented sieve of Eratosthenes.
/// Run time: O(x^(2/3) / (log x)^2)
/// Memory usage: O(x^(1/2))
///
int64_t nth_prime(int64_t n, int threads)
{
  if (n < 1)
    throw primecount_error("nth_prime(n): n must be >= 1");

  if (n > max_n)
    throw primecount_error("nth_prime(n): n must be <= " + std::to_string(max_n));

  if (n < (int64_t) primes.size())
    return primes[n];

  // For small n use the segmented sieve of Eratosthenes
  if (n < 100000)
    return primesieve::nth_prime(n, 0);

  // For large n use the prime counting function
  // and the segmented sieve of Eratosthenes.
  int64_t prime_approx = Ri_inverse(n);
  int64_t count_approx = pi(prime_approx, threads);

  if (count_approx < n)
    return primesieve::nth_prime(n - count_approx, prime_approx);
  else // count_approx >= n
    return primesieve::nth_prime(n - count_approx - 1, prime_approx + 1);
}

} // namespace
