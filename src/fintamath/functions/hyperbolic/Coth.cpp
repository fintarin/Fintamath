#include "fintamath/functions/hyperbolic/Coth.hpp"

#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Coth::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  return multiCothSimplify(rhs);
}

std::unique_ptr<IMathObject> Coth::multiCothSimplify(const INumber &rhs) {
  static const auto multiCoth = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCoth;

    outMultiCoth.add<Integer>([](const Integer &inRhs) {
      return multiCothSimplify(Real(inRhs));
    });

    outMultiCoth.add<Rational>([](const Rational &inRhs) {
      return multiCothSimplify(Real(inRhs));
    });

    outMultiCoth.add<Real>([](const Real &inRhs) {
      return coth(inRhs).toMinimalObject();
    });

    return outMultiCoth;
  }();

  return multiCoth(rhs);
}

}
