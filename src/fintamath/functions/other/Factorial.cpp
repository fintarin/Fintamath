#include "fintamath/functions/other/Factorial.hpp"

#include <cstddef>
#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Factorial)

using namespace detail;

std::unique_ptr<IMathObject> Factorial::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  return multiFactorialSimplify(rhs, order);
}

std::unique_ptr<IMathObject> Factorial::multiFactorialSimplify(const INumber &lhs, const size_t order) {
  static const auto multiFactorial = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const Integer &)> outMultiAbs;

    outMultiAbs.add<Integer, Integer>([](const Integer &inRhs, const Integer &inOrder) {
      return factorialSimplify(inRhs, static_cast<size_t>(inOrder));
    });

    outMultiAbs.add<Rational, Integer>([](const Rational &inRhs, const Integer &inOrder) {
      return factorialSimplify(inRhs, static_cast<size_t>(inOrder));
    });

    outMultiAbs.add<Real, Integer>([](const Real &inRhs, const Integer &inOrder) {
      return factorialSimplify(inRhs, static_cast<size_t>(inOrder));
    });

    return outMultiAbs;
  }();

  return multiFactorial(lhs, Integer(order));
}

std::unique_ptr<IMathObject> Factorial::factorialSimplify(const Integer &rhs, const size_t order) {
  if (rhs < 0) {
    if (order != 1) {
      return {};
    }

    return ComplexInf{}.clone();
  }

  return factorial(rhs, order).clone();
}

std::unique_ptr<IMathObject> Factorial::factorialSimplify(const Rational &rhs, const size_t order) {
  if (rhs.denominator() == 1) {
    return factorialSimplify(rhs.numerator(), order);
  }

  if (order != 1) {
    return {};
  }

  return factorialSimplify(Real(rhs), order);
}

std::unique_ptr<IMathObject> Factorial::factorialSimplify(const Real &rhs, const size_t order) {
  if (order != 1) {
    return {};
  }

  return tgamma(rhs + 1).clone();
}

}
