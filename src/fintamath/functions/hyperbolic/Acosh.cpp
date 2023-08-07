#include "fintamath/functions/hyperbolic/Acosh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acosh::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiAcoshSimpl(rhs);
}

std::unique_ptr<IMathObject> Acosh::multiAcoshSimpl(const INumber &rhs) {
  static const auto multiAcosh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcosh;

    outMultiAcosh.add<Integer>([](const Integer &inRhs) {
      return multiAcoshSimpl(Real(inRhs));
    });

    outMultiAcosh.add<Rational>([](const Rational &inRhs) {
      return multiAcoshSimpl(Real(inRhs));
    });

    outMultiAcosh.add<Real>([](const Real &inRhs) {
      return acosh(inRhs).toMinimalObject();
    });

    return outMultiAcosh;
  }();

  return multiAcosh(rhs);
}

}
