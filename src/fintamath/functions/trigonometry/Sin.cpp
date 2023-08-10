#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sin::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiSinSimplify(rhs);
}

std::unique_ptr<IMathObject> Sin::multiSinSimplify(const INumber &rhs) {
  static const auto multiSin = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSin;

    outMultiSin.add<Integer>([](const Integer &inRhs) {
      return multiSinSimplify(Real(inRhs));
    });

    outMultiSin.add<Rational>([](const Rational &inRhs) {
      return multiSinSimplify(Real(inRhs));
    });

    outMultiSin.add<Real>([](const Real &inRhs) {
      return sin(inRhs).toMinimalObject();
    });

    return outMultiSin;
  }();

  return multiSin(rhs);
}

}
