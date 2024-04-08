#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Cosh)

using namespace detail;

std::unique_ptr<IMathObject> Cosh::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return multiCoshSimplify(rhs);
}

std::unique_ptr<IMathObject> Cosh::multiCoshSimplify(const INumber &rhs) {
  static const auto multiCosh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCosh;

    outMultiCosh.add<Integer>([](const Integer &inRhs) {
      return multiCoshSimplify(Real(inRhs));
    });

    outMultiCosh.add<Rational>([](const Rational &inRhs) {
      return multiCoshSimplify(Real(inRhs));
    });

    outMultiCosh.add<Real>([](const Real &inRhs) {
      return cosh(inRhs).clone();
    });

    return outMultiCosh;
  }();

  return multiCosh(rhs);
}

}
