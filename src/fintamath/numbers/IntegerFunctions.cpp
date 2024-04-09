#include "fintamath/numbers/IntegerFunctions.hpp"

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include <boost/multiprecision/detail/default_ops.hpp>

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace boost::multiprecision;

namespace fintamath {

Integer abs(const Integer &rhs) {
  return rhs < 0 ? -rhs : rhs;
}

Integer gcd(const Integer &lhs, const Integer &rhs) {
  return {gcd(lhs.getBackend(), rhs.getBackend())};
}

Integer lcm(const Integer &lhs, const Integer &rhs) {
  return {lcm(lhs.getBackend(), rhs.getBackend())};
}

Integer sqrt(const Integer &rhs) {
  Integer remainder;
  return sqrt(rhs, remainder);
}

Integer sqrt(const Integer &rhs, Integer &remainder) {
  if (rhs < 0) {
    throw UndefinedException(fmt::format(
        R"(sqrt({}) is undefined (expected argument >= 0))",
        rhs.toString()));
  }

  Integer::Backend remainderBackend;
  Integer res(sqrt(rhs.getBackend(), remainderBackend));
  remainder = Integer(std::move(remainderBackend));
  return res;
}

// Use binary splitting.
// http://numbers.computation.free.fr/Constants/Algorithms/splitting.html.
Integer factorialRec(const Integer &left, const Integer &right) {
  if (left == right) {
    return left;
  }

  if (right - left == 1) {
    return left * right;
  }

  const Integer mid((left + right) / 2);
  return factorialRec(left, mid) * factorialRec(mid + 1, right);
}

Integer factorial(const Integer &rhs) {
  if (rhs < 0) {
    throw UndefinedException(fmt::format(
        R"(factorial({}) is undefined (expected argument >= 0))",
        rhs.toString()));
  }

  if (rhs < 2) {
    return 1;
  }

  return factorialRec(2, rhs);
}

Integer factorial(const Integer &rhs, const size_t order) {
  assert(order > 0);

  if (rhs < 0) {
    throw UndefinedException(fmt::format(
        R"(factorial({}, {}) is undefined (expected first argument >= 0))",
        rhs.toString(),
        order));
  }

  if (order == 1) {
    return factorial(rhs);
  }

  // Use generalized factorial formula.
  // https://en.wikipedia.org/wiki/Double_factorial.

  Integer res = 1;
  for (Integer i = rhs; i > 0; i -= order) {
    res *= i;
  }

  return res;
}

FactorToCountMap factors(Integer rhs, Integer limit) {
  if (rhs < 2) {
    throw UndefinedException(fmt::format(
        R"(factors({}) is undefined (expected argument >= 2))",
        rhs.toString()));
  }

  FactorToCountMap factorToCountMap;

  while (rhs % 2 == 0) {
    ++factorToCountMap[2];
    rhs /= 2;
  }

  {
    const Integer rhsSqrt = sqrt(rhs);

    if (limit < 0 || limit > rhsSqrt) {
      limit = rhsSqrt;
    }
  }

  for (Integer i = 3; i <= limit; i += 2) {
    while (rhs % i == 0) {
      ++factorToCountMap[i];
      rhs = rhs / i;
    }
  }

  if (rhs > 1) {
    ++factorToCountMap[rhs];
  }

  return factorToCountMap;
}

// Use number of combinations formula.
// https://en.wikipedia.org/wiki/Combination#Number_of_k-combinations.
Integer combinations(const Integer &totalNumber, const Integer &choosedNumber) {
  if (totalNumber <= choosedNumber) {
    throw UndefinedException(fmt::format(
        R"(combinations({}, {}) is undefined (expected totalNumber > choosedNumber))",
        totalNumber.toString(),
        choosedNumber.toString()));
  }

  try {
    return factorial(totalNumber) / (factorial(choosedNumber) * factorial(totalNumber - choosedNumber));
  }
  catch (const UndefinedException &) {
    throw UndefinedException(fmt::format(
        R"(combinations({}, {}) is undefined (expected totalNumber >= 0 and choosedNumber >= 0))",
        totalNumber.toString(),
        choosedNumber.toString()));
  }
}

// Use multinomial coefficients formula.
// https://en.wikipedia.org/wiki/Multinomial_theorem#Multinomial_coefficients.
Integer multinomialCoefficient(const std::vector<Integer> &groupNumbers) {
  Integer totalNumber;
  for (const auto &groupNumber : groupNumbers) {
    totalNumber += groupNumber;
  }

  Integer res = factorial(totalNumber);
  for (const auto &groupNumber : groupNumbers) {
    res /= factorial(groupNumber);
  }

  return res;
}

}
