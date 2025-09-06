#pragma once

#include <concepts>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

using FactorToCountMap = std::unordered_map<Integer, Integer>;

template <std::derived_from<INumber> Lhs>
Lhs pow(const Lhs &lhs, Integer rhs) {
  if (lhs == 0 && rhs == 0) {
    throw UndefinedException("pow({}, {}) is undefined (zero to the power of zero)");
  }

  if (rhs < 0) {
    return pow(1 / lhs, -rhs);
  }

  // Use exponentiation by squaring with constant auxiliary memory (iterative version).
  // https://en.wikipedia.org/wiki/Exponentiation_by_squaring#With_constant_auxiliary_memory.

  Lhs res(1);
  Lhs sqr = lhs;

  while (rhs != 0) {
    if (rhs % 2 == 0) {
      rhs /= 2;
      sqr = sqr * sqr;
    }
    else {
      --rhs;
      res = res * sqr;
    }
  }

  return res;
}

Integer abs(const Integer &rhs);

Integer gcd(const Integer &lhs, const Integer &rhs);

Integer lcm(const Integer &lhs, const Integer &rhs);

Integer sqrt(const Integer &rhs);

Integer sqrt(const Integer &rhs, Integer &remainder);

Integer factorial(const Integer &rhs);

Integer factorial(const Integer &rhs, size_t order);

FactorToCountMap factors(Integer rhs, Integer limit = -1);

Integer combinations(const Integer &totalNumber, const Integer &choosedNumber);

Integer multinomialCoefficient(const std::vector<Integer> &groupNumbers);

}
