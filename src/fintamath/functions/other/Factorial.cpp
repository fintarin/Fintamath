#include "fintamath/functions/other/Factorial.hpp"

#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Factorial::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiFactorialSimpl(rhs, order);
}

std::unique_ptr<IMathObject> Factorial::multiFactorialSimpl(const INumber &lhs, size_t order) {
  static const auto multiFactorial = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const Integer &)> outMultiAbs;

    outMultiAbs.add<Integer, Integer>([](const Integer &inRhs, const Integer &inOrder) {
      return factorialSimpl(inRhs, size_t(inOrder));
    });

    outMultiAbs.add<Rational, Integer>([](const Rational &inRhs, const Integer &inOrder) {
      return factorialSimpl(inRhs, size_t(inOrder));
    });

    outMultiAbs.add<Real, Integer>([](const Real &inRhs, const Integer &inOrder) {
      return factorialSimpl(inRhs, size_t(inOrder));
    });

    return outMultiAbs;
  }();

  return multiFactorial(lhs, Integer(order));
}

std::unique_ptr<IMathObject> Factorial::factorialSimpl(const Integer &rhs, size_t order) {
  if (rhs < 0) {
    if (order != 1) {
      return {};
    }

    return ComplexInf().clone();
  }

  return factorial(rhs, order).toMinimalObject();
}

std::unique_ptr<IMathObject> Factorial::factorialSimpl(const Rational &rhs, size_t order) {
  if (rhs.denominator() == 1) {
    return factorialSimpl(rhs.numerator(), order);
  }

  if (order != 1) {
    return {};
  }

  return factorialSimpl(Real(rhs), order);
}

std::unique_ptr<IMathObject> Factorial::factorialSimpl(const Real &rhs, size_t order) {
  if (order != 1) {
    return {};
  }

  try {
    return tgamma(rhs + 1).toMinimalObject();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
