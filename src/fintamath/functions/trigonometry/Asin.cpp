#include "fintamath/functions/trigonometry/Asin.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

using namespace detail;

std::unique_ptr<IMathObject> Asin::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(-1)) {
    return negExpr(divExpr(Pi{}, Integer(2)))->toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return Integer(0).clone();
  }

  if (rhs == Integer(1)) {
    return divExpr(Pi{}, Integer(2))->toMinimalObject();
  }

  return multiAsinSimplify(rhs);
}

std::unique_ptr<IMathObject> Asin::multiAsinSimplify(const INumber &rhs) {
  static const auto multiAsin = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAsin;

    outMultiAsin.add<Integer>([](const Integer &inRhs) {
      return multiAsinSimplify(Real(inRhs));
    });

    outMultiAsin.add<Rational>([](const Rational &inRhs) {
      return multiAsinSimplify(Real(inRhs));
    });

    outMultiAsin.add<Real>([](const Real &inRhs) {
      return asin(inRhs).clone();
    });

    return outMultiAsin;
  }();

  return multiAsin(rhs);
}

}
