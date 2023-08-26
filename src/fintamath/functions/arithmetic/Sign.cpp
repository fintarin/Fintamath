#include "fintamath/functions/arithmetic/Sign.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sign::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiSignSimplify(rhs);
}

std::unique_ptr<IMathObject> Sign::multiSignSimplify(const INumber &rhs) {
  static const auto multiSign = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSign;

    outMultiSign.add<Integer>([](const Integer &inRhs) {
      return Integer(inRhs.sign()).clone();
    });

    outMultiSign.add<Rational>([](const Rational &inRhs) {
      return Integer(inRhs.sign()).clone();
    });

    outMultiSign.add<Real>([](const Real &inRhs) {
      return Integer(inRhs.sign()).clone();
    });

    return outMultiSign;
  }();

  return multiSign(rhs);
}

}
