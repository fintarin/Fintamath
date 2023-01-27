#include "fintamath/numbers/NumberFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

NumberPtr abs(const INumber &rhs) {
  if (rhs < ZERO) {
    return cast<INumber>(-rhs);
  }
  return cast<INumber>(rhs.clone());
}

NumberPtr naturalPow(const INumber &lhs, Integer rhs) {
  NumberPtr res = std::make_unique<Integer>(ONE);
  NumberPtr tmp = cast<INumber>(lhs.clone());

  while (rhs != ZERO) {
    if ((*(rhs.toString().end() - 1) - '0') % 2 == 0) {
      rhs /= 2;
      tmp = (*tmp) * (*tmp);
    } else {
      --rhs;
      res = (*res) * (*tmp);
    }
  }

  return cast<INumber>(res->simplify());
}

NumberPtr pow(const INumber &inLhs, const INumber &inRhs) {
  auto lhsPtr = inLhs.simplify();
  auto rhsPtr = inRhs.simplify();

  const auto *lhs = cast<INumber>(lhsPtr.get());
  const auto *rhs = cast<INumber>(rhsPtr.get());

  if (const auto *rhsInt = cast<Integer>(rhs); rhsInt && lhs->isPrecise()) {
    if (*lhs == ZERO && *rhsInt == ZERO) {
      throw UndefinedBinaryOpearatorException("^", lhs->toString(), rhs->toString());
    }

    if (*rhsInt < ZERO) {
      return naturalPow(*(ONE / *lhs), -(*rhsInt));
    }

    return naturalPow(*lhs, *rhsInt);
  }

  return cast<INumber>(pow(convert<Real>(*lhs), convert<Real>(*rhs)).simplify());
}

}
