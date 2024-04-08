#include "fintamath/functions/trigonometry/Sin.hpp"

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

FINTAMATH_CLASS_IMPLEMENTATION(Sin)

using namespace detail;

std::unique_ptr<IMathObject> Sin::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiSinSimplify(rhs);
}

std::unique_ptr<IMathObject> Sin::multiSinSimplify(const INumber &rhs) {
  static const auto multiSin = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSin;

    outMultiSin.add<Integer>([](const Integer &inRhs) {
      return multiSinSimplify(Real(inRhs));
    });

    outMultiSin.add<Rational>([](const Rational &inRhs) {
      return multiSinSimplify(Real(inRhs));
    });

    outMultiSin.add<Real>([](const Real &inRhs) {
      return sin(inRhs).clone();
    });

    return outMultiSin;
  }();

  return multiSin(rhs);
}

}
