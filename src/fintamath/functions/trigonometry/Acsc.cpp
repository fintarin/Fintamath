#include "fintamath/functions/trigonometry/Acsc.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acsc::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(-1)) {
    return negExpr(divExpr(Pi(), Integer(2)))->toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  if (rhs == Integer(1)) {
    return divExpr(Pi(), Integer(2))->toMinimalObject();
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
      return acscSimplify(inRhs);
    });

    return outMultiAcsc;
  }();

  return multiAcsc(rhs);
}

std::unique_ptr<IMathObject> Acsc::acscSimplify(const Real &rhs) {
  try {
    return acsc(rhs).toMinimalObject();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
