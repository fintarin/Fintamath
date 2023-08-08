#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acot::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(-1)) {
    return makeExpr(Neg(), makeExpr(Div(), Pi(), Integer(4)))->toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return makeExpr(Div(), Pi(), Integer(2))->toMinimalObject();
  }

  if (rhs == Integer(1)) {
    return makeExpr(Div(), Pi(), Integer(4))->toMinimalObject();
  }

  return multiAcotSimpl(rhs);
}

std::unique_ptr<IMathObject> Acot::multiAcotSimpl(const INumber &rhs) {
  static const auto multiAcot = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcot;

    outMultiAcot.add<Integer>([](const Integer &inRhs) {
      return multiAcotSimpl(Real(inRhs));
    });

    outMultiAcot.add<Rational>([](const Rational &inRhs) {
      return multiAcotSimpl(Real(inRhs));
    });

    outMultiAcot.add<Real>([](const Real &inRhs) {
      return acot(inRhs).toMinimalObject();
    });

    return outMultiAcot;
  }();

  return multiAcot(rhs);
}

}
