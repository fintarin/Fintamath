#include "fintamath/functions/trigonometry/Acot.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Acot)

using namespace detail;

std::unique_ptr<IMathObject> Acot::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(-1)) {
    return negExpr(divExpr(Pi{}, Integer(4)))->toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return divExpr(Pi{}, Integer(2))->toMinimalObject();
  }

  if (rhs == Integer(1)) {
    return divExpr(Pi{}, Integer(4))->toMinimalObject();
  }

  return multiAcotSimplify(rhs);
}

std::unique_ptr<IMathObject> Acot::multiAcotSimplify(const INumber &rhs) {
  static const auto multiAcot = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcot;

    outMultiAcot.add<Integer>([](const Integer &inRhs) {
      return multiAcotSimplify(Real(inRhs));
    });

    outMultiAcot.add<Rational>([](const Rational &inRhs) {
      return multiAcotSimplify(Real(inRhs));
    });

    outMultiAcot.add<Real>([](const Real &inRhs) {
      return acot(inRhs).clone();
    });

    return outMultiAcot;
  }();

  return multiAcot(rhs);
}

}
