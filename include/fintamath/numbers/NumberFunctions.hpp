#pragma once

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

inline unique_ptr<INumber> abs(const INumber &rhs) {
  if (rhs < ZERO) {
    return -rhs;
  }

  return cast<INumber>(rhs.clone());
}

inline unique_ptr<INumber> inv(const INumber &rhs) {
  return ONE / rhs;
}

template <typename Lhs, typename Rhs,
          typename = std::enable_if_t<std::is_base_of_v<INumber, Lhs> && std::is_base_of_v<INumber, Rhs>>>
unique_ptr<INumber> pow(const Lhs &lhs, const Rhs &rhs) {
  auto lhsSimpl = cast<INumber>(lhs.toMinimalObject());
  auto rhsSimpl = cast<INumber>(rhs.toMinimalObject());

  if (lhsSimpl->isPrecise()) {
    if (const auto *rhsInt = cast<Integer>(rhsSimpl.get())) {
      return pow(*lhsSimpl, *rhsInt);
    }
  }

  return cast<INumber>(pow(convert<Real>(*lhsSimpl), convert<Real>(*rhsSimpl)).toMinimalObject());
}

// Use exponentiation by squaring with constant auxiliary memory (iterative version)
// https://en.wikipedia.org/wiki/Exponentiation_by_squaring
template <typename Lhs, typename = std::enable_if_t<std::is_base_of_v<INumber, Lhs>>>
unique_ptr<INumber> pow(const Lhs &lhs, Integer rhs) {
  if (lhs == ZERO && rhs == ZERO) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }

  if (rhs < ZERO) {
    return pow(*(ONE / cast<INumber>(lhs)), -rhs);
  }

  unique_ptr<INumber> res = make_unique<Integer>(ONE);
  unique_ptr<INumber> sqr = cast<INumber>(lhs.clone());

  while (rhs != ZERO) {
    if ((*(rhs.toString().end() - 1) - '0') % 2 == 0) {
      rhs /= 2;
      sqr = (*sqr) * (*sqr);
    }
    else {
      --rhs;
      res = (*res) * (*sqr);
    }
  }

  return cast<INumber>(res->toMinimalObject());
}

}
