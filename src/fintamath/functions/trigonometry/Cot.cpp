#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cot::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiCotSimpl(rhs);
}

std::unique_ptr<IMathObject> Cot::multiCotSimpl(const INumber &rhs) {
  static const auto multiCot = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCot;

    outMultiCot.add<Integer>([](const Integer &inRhs) {
      return multiCotSimpl(Real(inRhs));
    });

    outMultiCot.add<Rational>([](const Rational &inRhs) {
      return multiCotSimpl(Real(inRhs));
    });

    outMultiCot.add<Real>([](const Real &inRhs) {
      return cot(inRhs).toMinimalObject();
    });

    return outMultiCot;
  }();

  return multiCot(rhs);
}

}
