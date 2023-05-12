#include "fintamath/numbers/NumberFunctions.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RationalFunctions.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<INumber> abs(const INumber &rhs) {
  static const auto multiAbs = [] {
    static MultiMethod<std::unique_ptr<INumber>(const INumber &)> outMultiAbs;

    outMultiAbs.add<Integer>([](const Integer &inRhs) {
      return std::make_unique<Integer>(abs(inRhs));
    });

    outMultiAbs.add<Rational>([](const Rational &inRhs) {
      return std::make_unique<Rational>(abs(inRhs));
    });

    outMultiAbs.add<Real>([](const Real &inRhs) {
      return std::make_unique<Real>(abs(inRhs));
    });

    return outMultiAbs;
  }();

  return multiAbs(rhs);
}

std::unique_ptr<INumber> sqrt(const Integer &rhs) {
  Integer remainder;

  auto res = std::make_unique<Integer>(intSqrt(rhs, remainder));
  if (remainder == 0) {
    return res;
  }

  return cast<INumber>(sqrt(convert<Real>(rhs)).toMinimalObject());
}

std::unique_ptr<INumber> sqrt(const Rational &rhs) {
  Integer remainder;

  Integer numerator = intSqrt(rhs.numerator(), remainder);
  if (remainder != 0) {
    return cast<INumber>(sqrt(convert<Real>(rhs)).toMinimalObject());
  }

  Integer denominator = intSqrt(rhs.denominator(), remainder);
  if (remainder != 0) {
    return cast<INumber>(sqrt(convert<Real>(rhs)).toMinimalObject());
  }

  return std::make_unique<Rational>(numerator, denominator);
}

std::unique_ptr<INumber> sqrt(const INumber &rhs) {
  static const auto multiSqrt = [] {
    static MultiMethod<std::unique_ptr<INumber>(const INumber &)> outMultiSqrt;

    outMultiSqrt.add<Integer>([](const Integer &inRhs) {
      return sqrt(inRhs);
    });

    outMultiSqrt.add<Rational>([](const Rational &inRhs) {
      return sqrt(inRhs);
    });

    outMultiSqrt.add<Real>([](const Real &inRhs) {
      return std::make_unique<Real>(sqrt(inRhs));
    });

    return outMultiSqrt;
  }();

  return multiSqrt(rhs);
}

template <typename Lhs, typename = std::enable_if_t<std::is_base_of_v<INumber, Lhs>>>
std::unique_ptr<INumber> pow(const Lhs &lhs, const Rational &rhs) {
  const Integer &numerator = rhs.numerator();
  const Integer &denominator = rhs.denominator();

  if (denominator == 1) {
    return cast<INumber>(pow(lhs, numerator).toMinimalObject());
  }

  if (denominator == 2) {
    return sqrt(pow(lhs, numerator));
  }

  return cast<INumber>(pow(convert<Real>(lhs), convert<Real>(rhs)).toMinimalObject());
}

std::unique_ptr<INumber> pow(const INumber &lhs, const INumber &rhs) {
  static const auto multiPow = [] {
    static MultiMethod<std::unique_ptr<INumber>(const INumber &, const INumber &)> outMultiPow;

    outMultiPow.add<Integer, Integer>([](const Integer &inLhs, const Integer &inRhs) {
      return cast<INumber>(pow(inLhs, inRhs).toMinimalObject());
    });

    outMultiPow.add<Rational, Rational>([](const Rational &inLhs, const Rational &inRhs) {
      return cast<INumber>(pow(inLhs, inRhs)->toMinimalObject());
    });

    outMultiPow.add<Real, Real>([](const Real &inLhs, const Real &inRhs) {
      return cast<INumber>(pow(inLhs, inRhs).toMinimalObject());
    });

    return outMultiPow;
  }();

  if (auto rhsConv = cast<INumber>(convert(lhs, rhs))) {
    return multiPow(lhs, *rhsConv);
  }

  auto lhsConv = cast<INumber>(convert(rhs, lhs));
  return multiPow(*lhsConv, rhs);
}

}
