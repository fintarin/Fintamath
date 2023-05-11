#include "fintamath/numbers/IntegerFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/exceptions/UndefinedUnaryOperatorException.hpp"

using namespace boost::multiprecision;

namespace fintamath {

Integer abs(const Integer &rhs) {
  return rhs < 0 ? -rhs : rhs;
}

Integer gcd(const Integer &lhs, const Integer &rhs) {
  return Integer(gcd(lhs.getBackend(), rhs.getBackend()));
}

Integer lcm(const Integer &lhs, const Integer &rhs) {
  return Integer(lcm(lhs.getBackend(), rhs.getBackend()));
}

Integer intSqrt(const Integer &rhs) {
  Integer remainder;
  return intSqrt(rhs, remainder);
}

Integer intSqrt(const Integer &rhs, Integer &remainder) {
  cpp_int remainderBackend;

  try {
    Integer res = Integer(sqrt(rhs.getBackend(), remainderBackend));
    remainder = Integer(std::move(remainderBackend));
    return res;
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("sqrt", {rhs.toString()});
  }
}

Integer pow(const Integer &lhs, uint32_t rhs) {
  if (lhs == 0 && rhs == 0) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), std::to_string(rhs));
  }

  return Integer(pow(lhs.getBackend(), rhs));
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

  Integer mid( (left + right) / 2);
  return factorialRec(left, mid) * factorialRec(mid + 1, right);
}

Integer factorial(const Integer &rhs) {
  if (rhs < 0) {
    throw UndefinedUnaryOperatorException("!", rhs.toString(), UndefinedUnaryOperatorException::Type::Postfix);
  }

  if (rhs < 2) {
    return 1;
  }

  return factorialRec(2, rhs);
}

Integer factorial(const Integer &rhs, size_t order) {
  assert(order > 0);

  if (rhs < 0) {
    throw UndefinedUnaryOperatorException(std::string(order, '!'), rhs.toString(),
                                          UndefinedUnaryOperatorException::Type::Postfix);
  }

  if (order == 1) {
    return factorial(rhs);
  }

  // Use generalized factorial formula.
  // https://en.wikipedia.org/wiki/Double_factorial.

  Integer res = 1;
  for (Integer i = rhs; i > 0; i -= int64_t(order)) {
    res *= i;
  }

  return res;
}

// Use number of combinations formula.
// https://en.wikipedia.org/wiki/Combination#Number_of_k-combinations.
Integer combinations(const Integer &totalNumber, const Integer &choosedNumber) {
  if (choosedNumber > totalNumber) {
    throw UndefinedFunctionException("combinations", {totalNumber.toString()});
  }

  return factorial(totalNumber) / (factorial(choosedNumber) * factorial(totalNumber - choosedNumber));
}

// Use multinomial coefficients formula.
// https://en.wikipedia.org/wiki/Multinomial_theorem#Multinomial_coefficients.
Integer multinomialCoefficient(const Integer &totalNumber, const std::vector<Integer> &groupNumbers) {
  Integer checkValue;

  for (const auto &groupNumber : groupNumbers) {
    checkValue += groupNumber;
  }

  if (checkValue != totalNumber) {
    throw UndefinedFunctionException("split", {totalNumber.toString()});
  }

  Integer res = factorial(totalNumber);
  for (const auto &groupNumber : groupNumbers) {
    res /= factorial(groupNumber);
  }

  return res;
}

}
