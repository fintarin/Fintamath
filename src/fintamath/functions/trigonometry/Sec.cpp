#include "fintamath/functions/trigonometry/Sec.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sec::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return multiSecSimplify(rhs);
}

std::unique_ptr<IMathObject> Sec::multiSecSimplify(const INumber &rhs) {
  static const auto multiSec = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSec;

    outMultiSec.add<Integer>([](const Integer &inRhs) {
      return multiSecSimplify(Real(inRhs));
    });

    outMultiSec.add<Rational>([](const Rational &inRhs) {
      return multiSecSimplify(Real(inRhs));
    });

    outMultiSec.add<Real>([](const Real &inRhs) {
      return sec(inRhs).toMinimalObject();
    });

    return outMultiSec;
  }();

  return multiSec(rhs);
}

}
