#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acos::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(-1)) {
    return Pi().toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return makeExpr(Div(), Pi(), Integer(2))->toMinimalObject();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiAcosSimplify(rhs);
}

std::unique_ptr<IMathObject> Acos::multiAcosSimplify(const INumber &rhs) {
  static const auto multiAcos = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcos;

    outMultiAcos.add<Integer>([](const Integer &inRhs) {
      return multiAcosSimplify(Real(inRhs));
    });

    outMultiAcos.add<Rational>([](const Rational &inRhs) {
      return multiAcosSimplify(Real(inRhs));
    });

    outMultiAcos.add<Real>([](const Real &inRhs) {
      return acosSimplify(inRhs);
    });

    return outMultiAcos;
  }();

  return multiAcos(rhs);
}

std::unique_ptr<IMathObject> Acos::acosSimplify(const Real &rhs) {
  try {
    return acos(rhs).toMinimalObject();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
