///
/// @file  cmdoptions.hpp
///
/// Copyright (C) 2014 Kim Walisch, <kim.walisch@gmail.com>
///
/// This file is distributed under the BSD License. See the COPYING
/// file in the top level directory.
///

#ifndef PRIMECOUNT_CMDOPTIONS_HPP
#define PRIMECOUNT_CMDOPTIONS_HPP

#include <primecount.hpp>
#include <stdint.h>

namespace primecount {

enum OptionValues
{
  OPTION_HELP,
  OPTION_DELEGLISE_RIVAT,
  OPTION_DELEGLISE_RIVAT1,
  OPTION_DELEGLISE_RIVAT2,
  OPTION_DELEGLISE_RIVAT_PARALLEL1,
  OPTION_DELEGLISE_RIVAT_PARALLEL2,
  OPTION_LEGENDRE,
  OPTION_LEHMER,
  OPTION_LEHMER2,
  OPTION_LMO,
  OPTION_LMO1,
  OPTION_LMO2,
  OPTION_LMO3,
  OPTION_LMO4,
  OPTION_LMO5,
  OPTION_LMO6,
  OPTION_LMO_PARALLEL1,
  OPTION_LMO_PARALLEL2,
  OPTION_LMO_PARALLEL3,
  OPTION_LI,
  OPTION_LIINV,
  OPTION_MEISSEL,
  OPTION_NTHPRIME,
  OPTION_NUMBER,
  OPTION_PHI,
  OPTION_PI,
  OPTION_PRIMESIEVE,
  OPTION_TEST,
  OPTION_THREADS,
  OPTION_VERSION
};

struct PrimeCountOptions
{
  int64_t x;
  int64_t a;
  int64_t option;
  int threads;
  PrimeCountOptions() :
    x(-1),
    a(-1),
    option(OPTION_PI),
    threads(primecount::MAX_THREADS)
  { }
};

PrimeCountOptions parseOptions(int, char**);

} // namespace primecount

#endif
