#include "fintamath/functions/hyperbolic/Asinh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asinh::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiAsinhSimpl(rhs);
}

std::unique_ptr<IMathObject> Asinh::multiAsinhSimpl(const INumber &rhs) {
  static const auto multiAsinh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAsinh;

    outMultiAsinh.add<Integer>([](const Integer &inRhs) {
      return multiAsinhSimpl(Real(inRhs));
    });

    outMultiAsinh.add<Rational>([](const Rational &inRhs) {
      return multiAsinhSimpl(Real(inRhs));
    });

    outMultiAsinh.add<Real>([](const Real &inRhs) {
      return asinh(inRhs).toMinimalObject();
    });

    return outMultiAsinh;
  }();

  return multiAsinh(rhs);
}

}
