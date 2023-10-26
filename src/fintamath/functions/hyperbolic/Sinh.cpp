#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sinh::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiSinhSimplify(rhs);
}

std::unique_ptr<IMathObject> Sinh::multiSinhSimplify(const INumber &rhs) {
  static const auto multiSinh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSinh;

    outMultiSinh.add<Integer>([](const Integer &inRhs) {
      return multiSinhSimplify(Real(inRhs));
    });

    outMultiSinh.add<Rational>([](const Rational &inRhs) {
      return multiSinhSimplify(Real(inRhs));
    });

    outMultiSinh.add<Real>([](const Real &inRhs) {
      return sinh(inRhs).clone();
    });

    return outMultiSinh;
  }();

  return multiSinh(rhs);
}

}
