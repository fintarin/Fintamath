#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asin::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(-1)) {
    return makeExpr(Neg(), makeExpr(Div(), Pi(), Integer(2)))->toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return Integer(0).clone();
  }

  if (rhs == Integer(1)) {
    return makeExpr(Div(), Pi(), Integer(2))->toMinimalObject();
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
      return asinSimplify(inRhs);
    });

    return outMultiAsin;
  }();

  return multiAsin(rhs);
}

std::unique_ptr<IMathObject> Asin::asinSimplify(const Real &rhs) {
  try {
    return asin(rhs).toMinimalObject();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
