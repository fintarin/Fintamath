#include "fintamath/functions/hyperbolic/Atanh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Atanh::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiAtanhSimpl(rhs);
}

std::unique_ptr<IMathObject> Atanh::multiAtanhSimpl(const INumber &rhs) {
  static const auto multiAtanh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAtanh;

    outMultiAtanh.add<Integer>([](const Integer &inRhs) {
      return multiAtanhSimpl(Real(inRhs));
    });

    outMultiAtanh.add<Rational>([](const Rational &inRhs) {
      return multiAtanhSimpl(Real(inRhs));
    });

    outMultiAtanh.add<Real>([](const Real &inRhs) {
      return atanh(inRhs).toMinimalObject();
    });

    return outMultiAtanh;
  }();

  return multiAtanh(rhs);
}

}
