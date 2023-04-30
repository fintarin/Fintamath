#pragma once

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

template <typename Rhs, typename = std::enable_if_t<std::is_base_of_v<INumber, Rhs> && !std::is_same_v<INumber, Rhs>>>
inline Rhs abs(const Rhs &rhs) {
  if (rhs < ZERO) {
    return -rhs;
  }

  return rhs;
}

inline std::unique_ptr<INumber> abs(const INumber &rhs) {
  static const auto multiAbs = [] {
    static MultiMethod<std::unique_ptr<INumber>(const INumber &rhs)> outMultiAbs;

    outMultiAbs.add<Integer>([](const Integer &intRhs) {
      return std::make_unique<Integer>(abs(intRhs));
    });

    outMultiAbs.add<Rational>([](const Rational &ratRhs) {
      return std::make_unique<Rational>(abs(ratRhs));
    });

    outMultiAbs.add<Real>([](const Real &realRhs) {
      return std::make_unique<Real>(abs(realRhs));
    });

    return outMultiAbs;
  }();

  return multiAbs(rhs);
}

inline std::unique_ptr<INumber> sqrt(const Integer &rhs) {
  Integer remainder;

  auto res = std::make_unique<Integer>(intSqrt(rhs, remainder));
  if (remainder == ZERO) {
    return res;
  }

  return cast<INumber>(sqrt(convert<Real>(rhs)).toMinimalObject());
}

inline std::unique_ptr<INumber> sqrt(const Rational &rhs) {
  Integer remainder;

  Integer numerator = intSqrt(rhs.getNumerator(), remainder);
  if (remainder != ZERO) {
    return cast<INumber>(sqrt(convert<Real>(rhs)).toMinimalObject());
  }

  Integer denominator = intSqrt(rhs.getDenominator(), remainder);
  if (remainder != ZERO) {
    return cast<INumber>(sqrt(convert<Real>(rhs)).toMinimalObject());
  }

  return std::make_unique<Rational>(numerator, denominator);
}

inline std::unique_ptr<INumber> sqrt(const INumber &rhs) {
  static const auto multiSqrt = [] {
    static MultiMethod<std::unique_ptr<INumber>(const INumber &rhs)> outMultiSqrt;

    outMultiSqrt.add<Integer>([](const Integer &intRhs) {
      return sqrt(intRhs);
    });

    outMultiSqrt.add<Rational>([](const Rational &ratRhs) {
      return sqrt(ratRhs);
    });

    outMultiSqrt.add<Real>([](const Real &realRhs) {
      return std::make_unique<Real>(sqrt(realRhs));
    });

    return outMultiSqrt;
  }();

  return multiSqrt(rhs);
}

template <typename Lhs, typename Rhs,
          typename = std::enable_if_t<std::is_base_of_v<INumber, Lhs> && std::is_base_of_v<INumber, Rhs>>>
std::unique_ptr<INumber> pow(const Lhs &lhs, const Rhs &rhs) {
  auto lhsSimpl = cast<INumber>(lhs.toMinimalObject());
  auto rhsSimpl = cast<INumber>(rhs.toMinimalObject());

  if (lhsSimpl->isPrecise()) {
    if (const auto *rhsInt = cast<Integer>(rhsSimpl.get())) {
      return pow(*lhsSimpl, *rhsInt);
    }
  }

  return cast<INumber>(pow(convert<Real>(*lhsSimpl), convert<Real>(*rhsSimpl)).toMinimalObject());
}

// Use exponentiation by squaring with constant auxiliary memory (iterative version).
// https://en.wikipedia.org/wiki/Exponentiation_by_squaring#With_constant_auxiliary_memory.
template <typename Lhs, typename = std::enable_if_t<std::is_base_of_v<INumber, Lhs>>>
std::unique_ptr<INumber> pow(const Lhs &lhs, Integer rhs) {
  if (lhs == ZERO && rhs == ZERO) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }

  if (rhs < ZERO) {
    return pow(*(ONE / cast<INumber>(lhs)), -rhs);
  }

  std::unique_ptr<INumber> res = std::make_unique<Integer>(ONE);
  std::unique_ptr<INumber> sqr = cast<INumber>(lhs.clone());

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
