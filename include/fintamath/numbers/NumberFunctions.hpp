#pragma once

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

inline NumberPtr abs(const INumber &rhs) {
  if (rhs < ZERO) {
    return cast<INumber>(-rhs);
  }
  return cast<INumber>(rhs.clone());
}

template <typename Lhs, typename Rhs,
          typename = std::enable_if_t<std::is_base_of_v<INumber, Lhs> && std::is_base_of_v<INumber, Rhs> &&
                                      !std::is_same_v<Real, Lhs> && !std::is_same_v<Real, Rhs>>>
NumberPtr pow(const Lhs &inLhs, const Rhs &inRhs) {
  auto lhsPtr = inLhs.simplify();
  auto rhsPtr = inRhs.simplify();

  const auto *lhs = cast<INumber>(lhsPtr.get());
  const auto *rhs = cast<INumber>(rhsPtr.get());

  if (const auto *rhsInt = cast<Integer>(rhs)) {
    if (*rhsInt < ZERO) {
      return pow(*(ONE / *lhs), -(*rhsInt));
    }

    return pow(*lhs, *rhsInt);
  }

  return cast<INumber>(pow(convert<Real>(*lhs), convert<Real>(*rhs)).simplify());
}

template <typename Lhs, typename = std::enable_if_t<std::is_base_of_v<INumber, Lhs> && !std::is_same_v<Real, Lhs>>>
NumberPtr pow(const Lhs &lhs, Integer rhs) {
  if (lhs == ZERO && rhs == ZERO) {
    throw UndefinedBinaryOpearatorException("^", lhs.toString(), rhs.toString());
  }

  NumberPtr res = std::make_unique<Integer>(ONE);
  NumberPtr sqr = cast<INumber>(lhs.clone());

  while (rhs != ZERO) {
    if ((*(rhs.toString().end() - 1) - '0') % 2 == 0) {
      rhs /= 2;
      sqr = (*sqr) * (*sqr);
    } else {
      --rhs;
      res = (*res) * (*sqr);
    }
  }

  return cast<INumber>(res->simplify());
}

}
