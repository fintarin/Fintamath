#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sinh::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiSinhSimpl(rhs);
}

std::unique_ptr<IMathObject> Sinh::multiSinhSimpl(const INumber &rhs) {
  static const auto multiSinh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSinh;

    outMultiSinh.add<Integer>([](const Integer &inRhs) {
      return multiSinhSimpl(Real(inRhs));
    });

    outMultiSinh.add<Rational>([](const Rational &inRhs) {
      return multiSinhSimpl(Real(inRhs));
    });

    outMultiSinh.add<Real>([](const Real &inRhs) {
      return sinh(inRhs).toMinimalObject();
    });

    return outMultiSinh;
  }();

  return multiSinh(rhs);
}

}
