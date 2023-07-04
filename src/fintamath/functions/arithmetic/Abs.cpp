#include "fintamath/functions/arithmetic/Abs.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RationalFunctions.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Abs::call(const ArgumentsRefVector &argsVect) const {
  static const auto multiAbs = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAbs;

    outMultiAbs.add<Integer>([](const Integer &inRhs) {
      return std::make_unique<Integer>(abs(inRhs));
    });

    outMultiAbs.add<Rational>([](const Rational &inRhs) {
      return std::make_unique<Rational>(abs(inRhs));
    });

    outMultiAbs.add<Real>([](const Real &inRhs) {
      return std::make_unique<Real>(abs(inRhs));
    });

    return outMultiAbs;
  }();

  return multiAbs(cast<INumber>(argsVect.front().get()));
}

}
