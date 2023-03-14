#include "fintamath/numbers/IntegerFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/NumberImpls.hpp"

namespace fintamath {

Integer abs(const Integer &rhs) {
  if (rhs < 0) {
    return -rhs;
  }

  return rhs;
}

Integer sqrt(const Integer &rhs) {
  if (rhs < 0) {
    throw UndefinedFunctionException("sqrt", {rhs.toString()});
  }

  return IntegerImpl(sqrt(rhs.getImpl()->v));
}

Integer pow(const Integer &lhs, uint64_t rhs) {
  if (lhs == 0 && rhs == 0) {
    throw UndefinedBinaryOpearatorException("^", lhs.toString(), std::to_string(rhs));
  }

  return IntegerImpl(pow(lhs.getImpl()->v, rhs));
}

Integer factorialRec(const Integer &left, const Integer &right) {
  if (left == right) {
    return left;
  }

  if (right - left == 1) {
    return left * right;
  }

  Integer mid = (left + right) / 2;
  return factorialRec(left, mid) * factorialRec(mid + 1, right);
}

Integer factorial(const Integer &rhs) {
  if (rhs < 0) {
    throw UndefinedUnaryOpearatorException("!", rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
  }

  if (rhs < 2) {
    return 1;
  }

  return factorialRec(2, rhs);
}

Integer factorial(const Integer &rhs, int64_t order) {
  assert(order > 0);

  if (rhs < 0) {
    throw UndefinedUnaryOpearatorException(string(order, '!'), rhs.toString(),
                                           UndefinedUnaryOpearatorException::Type::Postfix);
  }

  if (order == 1) {
    return factorial(rhs);
  }

  Integer res = 1;
  for (Integer i = rhs; i > 0; i -= order) {
    res *= i;
  }

  return res;
}

Integer split(const Integer &n, const vector<Integer> &k_values) {
  Integer checkValue;
  for (auto &k : k_values) {
    checkValue += k;
  }
  if (checkValue != n) {
    throw UndefinedFunctionException("split", {n.toString()});
  }
  auto result = factorial(n);
  for (const auto &k : k_values) {
    result /= factorial(k);
  }
  return result;
}

Integer combinations(const Integer &n, const Integer &k) {
  if (k > n) {
    throw UndefinedFunctionException("combinations", {n.toString()});
  }
  return factorial(n) / (factorial(k) * factorial(n - k));
}

}
