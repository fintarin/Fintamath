#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Atan::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiAtanSimpl(rhs);
}

std::unique_ptr<IMathObject> Atan::multiAtanSimpl(const INumber &rhs) {
  static const auto multiAtan = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAtan;

    outMultiAtan.add<Integer>([](const Integer &inRhs) {
      return multiAtanSimpl(Real(inRhs));
    });

    outMultiAtan.add<Rational>([](const Rational &inRhs) {
      return multiAtanSimpl(Real(inRhs));
    });

    outMultiAtan.add<Real>([](const Real &inRhs) {
      return atan(inRhs).toMinimalObject();
    });

    return outMultiAtan;
  }();

  return multiAtan(rhs);
}

}
