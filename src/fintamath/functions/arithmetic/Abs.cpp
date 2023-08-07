#include "fintamath/functions/arithmetic/Abs.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RationalFunctions.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Abs::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiAbsSimpl(rhs);
}

std::unique_ptr<IMathObject> Abs::multiAbsSimpl(const INumber &rhs) {
  static const auto multiAbs = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAbs;

    outMultiAbs.add<Integer>([](const Integer &inRhs) {
      return abs(inRhs).toMinimalObject();
    });

    outMultiAbs.add<Rational>([](const Rational &inRhs) {
      return abs(inRhs).toMinimalObject();
    });

    outMultiAbs.add<Real>([](const Real &inRhs) {
      return abs(inRhs).toMinimalObject();
    });

    return outMultiAbs;
  }();

  return multiAbs(rhs);
}

}
