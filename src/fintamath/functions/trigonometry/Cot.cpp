#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cot::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  return multiCotSimplify(rhs);
}

std::unique_ptr<IMathObject> Cot::multiCotSimplify(const INumber &rhs) {
  static const auto multiCot = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCot;

    outMultiCot.add<Integer>([](const Integer &inRhs) {
      return multiCotSimplify(Real(inRhs));
    });

    outMultiCot.add<Rational>([](const Rational &inRhs) {
      return multiCotSimplify(Real(inRhs));
    });

    outMultiCot.add<Real>([](const Real &inRhs) {
      return cot(inRhs).toMinimalObject();
    });

    return outMultiCot;
  }();

  return multiCot(rhs);
}

}
