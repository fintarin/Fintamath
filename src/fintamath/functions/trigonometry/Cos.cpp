#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cos::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return multiCosSimplify(rhs);
}

std::unique_ptr<IMathObject> Cos::multiCosSimplify(const INumber &rhs) {
  static const auto multiCos = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCos;

    outMultiCos.add<Integer>([](const Integer &inRhs) {
      return multiCosSimplify(Real(inRhs));
    });

    outMultiCos.add<Rational>([](const Rational &inRhs) {
      return multiCosSimplify(Real(inRhs));
    });

    outMultiCos.add<Real>([](const Real &inRhs) {
      return cos(inRhs).toMinimalObject();
    });

    return outMultiCos;
  }();

  return multiCos(rhs);
}

}
