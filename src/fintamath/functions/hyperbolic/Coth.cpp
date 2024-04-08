#include "fintamath/functions/hyperbolic/Coth.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Coth)

using namespace detail;

std::unique_ptr<IMathObject> Coth::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf{}.clone();
  }

  return multiCothSimplify(rhs);
}

std::unique_ptr<IMathObject> Coth::multiCothSimplify(const INumber &rhs) {
  static const auto multiCoth = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCoth;

    outMultiCoth.add<Integer>([](const Integer &inRhs) {
      return multiCothSimplify(Real(inRhs));
    });

    outMultiCoth.add<Rational>([](const Rational &inRhs) {
      return multiCothSimplify(Real(inRhs));
    });

    outMultiCoth.add<Real>([](const Real &inRhs) {
      return coth(inRhs).clone();
    });

    return outMultiCoth;
  }();

  return multiCoth(rhs);
}

}
