#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acos::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiAcosSimpl(rhs);
}

std::unique_ptr<IMathObject> Acos::multiAcosSimpl(const INumber &rhs) {
  static const auto multiAcos = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcos;

    outMultiAcos.add<Integer>([](const Integer &inRhs) {
      return multiAcosSimpl(Real(inRhs));
    });

    outMultiAcos.add<Rational>([](const Rational &inRhs) {
      return multiAcosSimpl(Real(inRhs));
    });

    outMultiAcos.add<Real>([](const Real &inRhs) {
      return acos(inRhs).toMinimalObject();
    });

    return outMultiAcos;
  }();

  return multiAcos(rhs);
}

}
