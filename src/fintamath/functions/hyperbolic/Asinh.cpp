#include "fintamath/functions/hyperbolic/Asinh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asinh::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiAsinhSimplify(rhs);
}

std::unique_ptr<IMathObject> Asinh::multiAsinhSimplify(const INumber &rhs) {
  static const auto multiAsinh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAsinh;

    outMultiAsinh.add<Integer>([](const Integer &inRhs) {
      return multiAsinhSimplify(Real(inRhs));
    });

    outMultiAsinh.add<Rational>([](const Rational &inRhs) {
      return multiAsinhSimplify(Real(inRhs));
    });

    outMultiAsinh.add<Real>([](const Real &inRhs) {
      return asinh(inRhs).toMinimalObject();
    });

    return outMultiAsinh;
  }();

  return multiAsinh(rhs);
}

}
