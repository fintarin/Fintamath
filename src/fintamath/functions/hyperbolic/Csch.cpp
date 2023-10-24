#include "fintamath/functions/hyperbolic/Csch.hpp"

#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Csch::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  return multiCschSimplify(rhs);
}

std::unique_ptr<IMathObject> Csch::multiCschSimplify(const INumber &rhs) {
  static const auto multiCsch = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCsch;

    outMultiCsch.add<Integer>([](const Integer &inRhs) {
      return multiCschSimplify(Real(inRhs));
    });

    outMultiCsch.add<Rational>([](const Rational &inRhs) {
      return multiCschSimplify(Real(inRhs));
    });

    outMultiCsch.add<Real>([](const Real &inRhs) {
      return csch(inRhs).toMinimalObject();
    });

    return outMultiCsch;
  }();

  return multiCsch(rhs);
}

}
