///
/// @file   BinaryIndexedTree.hpp
/// @brief  The BinaryIndexedTree class is a binary indexed
///         tree (a.k.a. Fenwick tree) that keeps track of
///         the number of unsieved elements (sieve[i] = 1)
///         in the sieve array. Whenever an element is
///         crossed-off for the first time in the sieve array
///         we update the counters data structure. Both
///         updating and querying the counters data structure
///         uses O(log n) operations.
///
///         The implementation is based on the paper:
///
///         Tomás Oliveira e Silva, Computing pi(x): the combinatorial method,
///         Revista do DETUA, vol. 4, no. 6, March 2006, pp. 767-768.
///         http://sweet.ua.pt/tos/bib/5.4.pdf
///
/// Copyright (C) 2017 Kim Walisch, <kim.walisch@gmail.com>
///
/// This file is distributed under the BSD License. See the COPYING
/// file in the top level directory.
///

#ifndef BINARYINDEXEDTREE_HPP
#define BINARYINDEXEDTREE_HPP

#include <stdint.h>
#include <vector>

namespace {

class BinaryIndexedTree
{
public:
  BinaryIndexedTree() { }

  /// Initialize binary indexed tree from sieve array
  template <typename T>
  void init(const T& sieve)
  {
    size_ = sieve.size() / 2;
    tree_.resize(size_);

    for (int64_t i = 0; i < size_; i++)
    {
      tree_[i] = sieve[i * 2];
      int64_t k = (i + 1) & ~i;
      for (int64_t j = i; k >>= 1; j &= j - 1)
        tree_[i] += tree_[j - 1];
    }
  }

  /// Update (decrement by 1) the counters after
  /// that an element has been crossed-off for the
  /// first time in the sieve array.
  /// Runtime: O(log N)
  ///
  void update(int64_t pos)
  {
    pos >>= 1;
    do
    {
      tree_[pos]--;
      pos |= pos + 1;
    }
    while (pos < size_);
  }

  /// Get the number of unsieved elements <= pos
  /// in the current segment (sieve array).
  /// Runtime: O(log N)
  ///
  int64_t count(int64_t low, int64_t high)
  {
    int64_t pos = (high - low) >> 1;
    int64_t sum = tree_[pos++];
    for (; pos &= pos - 1; sum += tree_[pos - 1]);
    return sum;
  }

private:
  std::vector<int32_t> tree_;
  int64_t size_;
};

} // namespace

#endif
