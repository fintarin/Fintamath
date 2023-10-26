#include "fintamath/functions/hyperbolic/Sech.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sech::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return multiSechSimplify(rhs);
}

std::unique_ptr<IMathObject> Sech::multiSechSimplify(const INumber &rhs) {
  static const auto multiSech = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSech;

    outMultiSech.add<Integer>([](const Integer &inRhs) {
      return multiSechSimplify(Real(inRhs));
    });

    outMultiSech.add<Rational>([](const Rational &inRhs) {
      return multiSechSimplify(Real(inRhs));
    });

    outMultiSech.add<Real>([](const Real &inRhs) {
      return sech(inRhs).clone();
    });

    return outMultiSech;
  }();

  return multiSech(rhs);
}

}
