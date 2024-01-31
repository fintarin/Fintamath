#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Tan::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiTanSimplify(rhs);
}

std::unique_ptr<IMathObject> Tan::multiTanSimplify(const INumber &rhs) {
  static const auto multiTan = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiTan;

    outMultiTan.add<Integer>([](const Integer &inRhs) {
      return multiTanSimplify(Real(inRhs));
    });

    outMultiTan.add<Rational>([](const Rational &inRhs) {
      return multiTanSimplify(Real(inRhs));
    });

    outMultiTan.add<Real>([](const Real &inRhs) {
      return tan(inRhs).clone();
    });

    return outMultiTan;
  }();

  return multiTan(rhs);
}

}
