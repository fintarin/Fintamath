#include "fintamath/functions/other/Factorial.hpp"

#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Factorial::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiFactorialSimplify(rhs, order);
}

std::unique_ptr<IMathObject> Factorial::multiFactorialSimplify(const INumber &lhs, size_t order) {
  static const auto multiFactorial = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const Integer &)> outMultiAbs;

    outMultiAbs.add<Integer, Integer>([](const Integer &inRhs, const Integer &inOrder) {
      return factorialSimplify(inRhs, size_t(inOrder));
    });

    outMultiAbs.add<Rational, Integer>([](const Rational &inRhs, const Integer &inOrder) {
      return factorialSimplify(inRhs, size_t(inOrder));
    });

    outMultiAbs.add<Real, Integer>([](const Real &inRhs, const Integer &inOrder) {
      return factorialSimplify(inRhs, size_t(inOrder));
    });

    return outMultiAbs;
  }();

  return multiFactorial(lhs, Integer(order));
}

std::unique_ptr<IMathObject> Factorial::factorialSimplify(const Integer &rhs, size_t order) {
  if (rhs < 0) {
    if (order != 1) {
      return {};
    }

    return ComplexInf().clone();
  }

  return factorial(rhs, order).clone();
}

std::unique_ptr<IMathObject> Factorial::factorialSimplify(const Rational &rhs, size_t order) {
  if (rhs.denominator() == 1) {
    return factorialSimplify(rhs.numerator(), order);
  }

  if (order != 1) {
    return {};
  }

  return factorialSimplify(Real(rhs), order);
}

std::unique_ptr<IMathObject> Factorial::factorialSimplify(const Real &rhs, size_t order) {
  if (order != 1) {
    return {};
  }

  return tgamma(rhs + 1).clone();
}

}
