#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asin::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiAsinSimpl(rhs);
}

std::unique_ptr<IMathObject> Asin::multiAsinSimpl(const INumber &rhs) {
  static const auto multiAsin = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAsin;

    outMultiAsin.add<Integer>([](const Integer &inRhs) {
      return multiAsinSimpl(Real(inRhs));
    });

    outMultiAsin.add<Rational>([](const Rational &inRhs) {
      return multiAsinSimpl(Real(inRhs));
    });

    outMultiAsin.add<Real>([](const Real &inRhs) {
      return asin(inRhs).toMinimalObject();
    });

    return outMultiAsin;
  }();

  return multiAsin(rhs);
}

}
