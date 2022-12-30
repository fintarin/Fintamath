#include "fintamath/numbers/IntegerFunctions.hpp"

#include "NumberImpls.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"

namespace fintamath {
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

  Integer doubleFactorial(const Integer &rhs) {
    if (rhs < 0) {
      throw UndefinedUnaryOpearatorException("!!", rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
    }

    Integer res = 1;
    for (Integer i = rhs; i > 0; i -= 2) {
      res *= i;
    }

    return res;
  }
}
