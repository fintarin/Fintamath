#include "fintamath/functions/hyperbolic/Acoth.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acoth::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiAcothSimpl(rhs);
}

std::unique_ptr<IMathObject> Acoth::multiAcothSimpl(const INumber &rhs) {
  static const auto multiAcoth = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcoth;

    outMultiAcoth.add<Integer>([](const Integer &inRhs) {
      return multiAcothSimpl(Real(inRhs));
    });

    outMultiAcoth.add<Rational>([](const Rational &inRhs) {
      return multiAcothSimpl(Real(inRhs));
    });

    outMultiAcoth.add<Real>([](const Real &inRhs) {
      return acoth(inRhs).toMinimalObject();
    });

    return outMultiAcoth;
  }();

  return multiAcoth(rhs);
}

}
