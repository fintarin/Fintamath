#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Pow::call(const ArgumentsRefVector &argsVect) const {
  static const auto multiPow = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const INumber &)> outMultiPow;

    outMultiPow.add<Integer, Integer>([](const Integer &lhs, const Integer &rhs) {
      if (rhs < 0) {
        return (Rational(1) / pow(lhs, -rhs)).toMinimalObject();
      }

      return pow(lhs, rhs).toMinimalObject();
    });

    outMultiPow.add<Rational, Rational>([](const Rational &lhs, const Rational &rhs) {
      const Integer &numerator = rhs.numerator();
      const Integer &denominator = rhs.denominator();

      if (denominator == 1) {
        return pow(lhs, numerator).toMinimalObject();
      }

      if (denominator == 2) { // TODO: implement nth root
        return Pow()(*Sqrt()(lhs), numerator);
      }

      return pow(convert<Real>(lhs), convert<Real>(rhs)).toMinimalObject();
    });

    outMultiPow.add<Real, Real>([](const Real &lhs, const Real &rhs) {
      return pow(lhs, rhs).toMinimalObject();
    });

    return outMultiPow;
  }();

  const auto &lhs = cast<INumber>(argsVect.front().get());
  const auto &rhs = cast<INumber>(argsVect.back().get());

  if (auto rhsConv = cast<INumber>(convert(lhs, rhs))) {
    return multiPow(lhs, *rhsConv);
  }

  auto lhsConv = cast<INumber>(convert(rhs, lhs));
  return multiPow(*lhsConv, rhs);
}

}
