#include "fintamath/functions/arithmetic/Sign.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Sign)

using namespace detail;

std::unique_ptr<IMathObject> Sign::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  return multiSignSimplify(rhs);
}

std::unique_ptr<IMathObject> Sign::multiSignSimplify(const INumber &rhs) {
  static const auto multiSign = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSign;

    outMultiSign.add<Integer>([](const Integer &inRhs) {
      return Integer(inRhs.sign()).clone();
    });

    outMultiSign.add<Rational>([](const Rational &inRhs) {
      return Integer(inRhs.sign()).clone();
    });

    outMultiSign.add<Real>([](const Real &inRhs) {
      if (inRhs == 0) {
        return Integer(1).clone();
      }

      return Integer(inRhs.sign()).clone();
    });

    outMultiSign.add<Complex>([](const Complex &inRhs) {
      if (inRhs.imag() == Integer(0)) {
        return multiSignSimplify(inRhs.real());
      }

      // https://en.wikipedia.org/wiki/Sign_function#Complex_signum
      return Div{}(inRhs, *Abs{}(inRhs));
    });

    return outMultiSign;
  }();

  return multiSign(rhs);
}

}
