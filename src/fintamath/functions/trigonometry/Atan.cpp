#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Atan::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(-1)) {
    return makeExpr(Neg(), makeExpr(Div(), Pi(), Integer(4)))->toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return Integer(0).clone();
  }

  if (rhs == Integer(1)) {
    return makeExpr(Div(), Pi(), Integer(4))->toMinimalObject();
  }

  return multiAtanSimpl(rhs);
}

std::unique_ptr<IMathObject> Atan::multiAtanSimpl(const INumber &rhs) {
  static const auto multiAtan = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAtan;

    outMultiAtan.add<Integer>([](const Integer &inRhs) {
      return multiAtanSimpl(Real(inRhs));
    });

    outMultiAtan.add<Rational>([](const Rational &inRhs) {
      return multiAtanSimpl(Real(inRhs));
    });

    outMultiAtan.add<Real>([](const Real &inRhs) {
      return atan(inRhs).toMinimalObject();
    });

    return outMultiAtan;
  }();

  return multiAtan(rhs);
}

}
