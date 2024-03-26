#include "fintamath/functions/trigonometry/Acsc.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

using namespace detail;

std::unique_ptr<IMathObject> Acsc::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(-1)) {
    return negExpr(divExpr(Pi{}, Integer(2)))->toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return ComplexInf{}.clone();
  }

  if (rhs == Integer(1)) {
    return divExpr(Pi{}, Integer(2))->toMinimalObject();
  }

  return multiAcscSimplify(rhs);
}

std::unique_ptr<IMathObject> Acsc::multiAcscSimplify(const INumber &rhs) {
  static const auto multiAcsc = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcsc;

    outMultiAcsc.add<Integer>([](const Integer &inRhs) {
      return multiAcscSimplify(Real(inRhs));
    });

    outMultiAcsc.add<Rational>([](const Rational &inRhs) {
      return multiAcscSimplify(Real(inRhs));
    });

    outMultiAcsc.add<Real>([](const Real &inRhs) {
      return acsc(inRhs).clone();
    });

    return outMultiAcsc;
  }();

  return multiAcsc(rhs);
}

}
