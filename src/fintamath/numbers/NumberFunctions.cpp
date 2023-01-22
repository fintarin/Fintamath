#include "fintamath/numbers/NumberFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

NumberPtr abs(const INumber &rhs) {
  if (rhs < ZERO) {
    return castPtr<INumber>(-rhs);
  }
  return castPtr<INumber>(rhs.clone());
}

NumberPtr naturalPow(const INumber &lhs, Integer rhs) {
  NumberPtr res = std::make_unique<Integer>(ONE);
  NumberPtr tmp = castPtr<INumber>(lhs.clone());

  while (rhs != ZERO) {
    if ((*(rhs.toString().end() - 1) - '0') % 2 == 0) {
      rhs /= 2;
      tmp = (*tmp) * (*tmp);
    } else {
      --rhs;
      res = (*res) * (*tmp);
    }
  }

  return castPtr<INumber>(res->simplify());
}

NumberPtr pow(const INumber &inLhs, const INumber &inRhs) {
  auto lhsPtr = inLhs.simplify();
  auto rhsPtr = inRhs.simplify();

  const auto &lhs = lhsPtr->to<INumber>();
  const auto &rhs = rhsPtr->to<INumber>();

  if (rhs.instanceOf<Integer>() && lhs.isPrecise()) {
    const auto &intRhs = rhs.to<Integer>();

    if (intRhs == ZERO && lhs == ZERO) {
      throw UndefinedBinaryOpearatorException("^", lhs.toString(), rhs.toString());
    }

    if (intRhs < ZERO) {
      return naturalPow(*(ONE / lhs), -intRhs);
    }

    return naturalPow(lhs, intRhs);
  }

  return castPtr<INumber>(pow(Converter::convert<Real>(lhs), Converter::convert<Real>(rhs)).simplify());
}

}
