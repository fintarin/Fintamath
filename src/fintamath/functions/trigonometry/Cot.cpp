#include "fintamath/functions/trigonometry/Cot.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Cot)

using namespace detail;

std::unique_ptr<IMathObject> Cot::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf{}.clone();
  }

  return multiCotSimplify(rhs);
}

std::unique_ptr<IMathObject> Cot::multiCotSimplify(const INumber &rhs) {
  static const auto multiCot = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCot;

    outMultiCot.add<Integer>([](const Integer &inRhs) {
      return multiCotSimplify(Real(inRhs));
    });

    outMultiCot.add<Rational>([](const Rational &inRhs) {
      return multiCotSimplify(Real(inRhs));
    });

    outMultiCot.add<Real>([](const Real &inRhs) {
      return cot(inRhs).clone();
    });

    return outMultiCot;
  }();

  return multiCot(rhs);
}

}
