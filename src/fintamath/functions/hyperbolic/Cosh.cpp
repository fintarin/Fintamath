#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cosh::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiCoshSimpl(rhs);
}

std::unique_ptr<IMathObject> Cosh::multiCoshSimpl(const INumber &rhs) {
  static const auto multiCosh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCosh;

    outMultiCosh.add<Integer>([](const Integer &inRhs) {
      return multiCoshSimpl(Real(inRhs));
    });

    outMultiCosh.add<Rational>([](const Rational &inRhs) {
      return multiCoshSimpl(Real(inRhs));
    });

    outMultiCosh.add<Real>([](const Real &inRhs) {
      return cosh(inRhs).toMinimalObject();
    });

    return outMultiCosh;
  }();

  return multiCosh(rhs);
}

}
