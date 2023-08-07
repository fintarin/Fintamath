#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Ln::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return NegInf().clone();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiLnSimpl(rhs);
}

std::unique_ptr<IMathObject> Ln::multiLnSimpl(const INumber &rhs) {
  static const auto multiLn = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiLn;

    outMultiLn.add<Integer>([](const Integer &inRhs) {
      return multiLnSimpl(Real(inRhs));
    });

    outMultiLn.add<Rational>([](const Rational &inRhs) {
      return multiLnSimpl(Real(inRhs));
    });

    outMultiLn.add<Real>([](const Real &inRhs) {
      return ln(inRhs).toMinimalObject();
    });

    return outMultiLn;
  }();

  return multiLn(rhs);
}

}
