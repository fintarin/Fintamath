#include "fintamath/functions/hyperbolic/Tanh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Tanh::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiTanhSimplify(rhs);
}

std::unique_ptr<IMathObject> Tanh::multiTanhSimplify(const INumber &rhs) {
  static const auto multiTanh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiTanh;

    outMultiTanh.add<Integer>([](const Integer &inRhs) {
      return multiTanhSimplify(Real(inRhs));
    });

    outMultiTanh.add<Rational>([](const Rational &inRhs) {
      return multiTanhSimplify(Real(inRhs));
    });

    outMultiTanh.add<Real>([](const Real &inRhs) {
      return tanh(inRhs).toMinimalObject();
    });

    return outMultiTanh;
  }();

  return multiTanh(rhs);
}

}
