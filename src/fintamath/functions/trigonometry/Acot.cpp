#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acot::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

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
