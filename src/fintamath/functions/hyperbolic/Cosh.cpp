#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cosh::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return multiCoshSimplify(rhs);
}

std::unique_ptr<IMathObject> Cosh::multiCoshSimplify(const INumber &rhs) {
  static const auto multiCosh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCosh;

    outMultiCosh.add<Integer>([](const Integer &inRhs) {
      return multiCoshSimplify(Real(inRhs));
    });

    outMultiCosh.add<Rational>([](const Rational &inRhs) {
      return multiCoshSimplify(Real(inRhs));
    });

    outMultiCosh.add<Real>([](const Real &inRhs) {
      return cosh(inRhs).clone();
    });

    return outMultiCosh;
  }();

  return multiCosh(rhs);
}

}
