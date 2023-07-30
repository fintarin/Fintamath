#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Pow::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<INumber>(argsVect.front().get());
  const auto &rhs = cast<INumber>(argsVect.back().get());

  if (lhs == Integer(0) && rhs == Integer(0)) {
    return Undefined().clone();
  }

  if (rhs < Integer(0)) {
    return multiPowSimpl(*(Rational(1) / lhs), *(-rhs));
  }

  return multiPowSimpl(lhs, rhs);
}

std::unique_ptr<IMathObject> Pow::multiPowSimpl(const INumber &lhs, const INumber &rhs) {
  static const auto multiPow = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const INumber &)> outMultiPow;

    outMultiPow.add<Integer, Integer>([](const Integer &lhs, const Integer &rhs) {
      return powSimpl(lhs, rhs);
    });

    outMultiPow.add<Rational, Rational>([](const Rational &lhs, const Rational &rhs) {
      return powSimpl(lhs, rhs);
    });

    outMultiPow.add<Real, Real>([](const Real &lhs, const Real &rhs) {
      return powSimpl(lhs, rhs);
    });

    return outMultiPow;
  }();

  if (auto rhsConv = cast<INumber>(convert(lhs, rhs))) {
    return multiPow(lhs, *rhsConv);
  }

  auto lhsConv = cast<INumber>(convert(rhs, lhs));
  return multiPow(*lhsConv, rhs);
}

std::unique_ptr<IMathObject> Pow::powSimpl(const Integer &lhs, const Integer &rhs) {
  return pow(lhs, rhs).toMinimalObject();
}

std::unique_ptr<IMathObject> Pow::powSimpl(const Rational &lhs, const Rational &rhs) {
  const Integer &lhsNumerator = lhs.numerator();
  const Integer &lhsDenominator = lhs.denominator();

  const Integer &rhsNumerator = rhs.numerator();
  const Integer &rhsDenominator = rhs.denominator();

  if (rhsDenominator == 1) {
    if (lhsDenominator == 1) {
      return pow(lhsNumerator, rhsNumerator).toMinimalObject();
    }

    return pow(lhs, rhsNumerator).toMinimalObject();
  }

  if (lhs < Integer(0)) {
    throw UndefinedBinaryOperatorException(Pow().toString(), lhs.toString(), rhs.toString());
  }

  if (lhsDenominator == 1) {
    return Root()(*multiPowSimpl(lhsNumerator, rhsNumerator), rhsDenominator);
  }

  return Root()(*multiPowSimpl(lhs, rhsNumerator), rhsDenominator);
}

std::unique_ptr<IMathObject> Pow::powSimpl(const Real &lhs, const Real &rhs) {
  return pow(lhs, rhs).toMinimalObject();
}

}
