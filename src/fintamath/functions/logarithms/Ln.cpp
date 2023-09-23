#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Ln::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return NegInf().clone();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiLnSimplify(rhs);
}

std::unique_ptr<IMathObject> Ln::multiLnSimplify(const INumber &rhs) {
  static const auto multiLn = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiLn;

    outMultiLn.add<Integer>([](const Integer &inRhs) {
      return multiLnSimplify(Real(inRhs));
    });

    outMultiLn.add<Rational>([](const Rational &inRhs) {
      return multiLnSimplify(Real(inRhs));
    });

    outMultiLn.add<Real>([](const Real &inRhs) {
      try {
        return ln(inRhs).toMinimalObject();
      }
      catch (const UndefinedException &) {
        return std::unique_ptr<IMathObject>{};
      }
    });

    return outMultiLn;
  }();

  return multiLn(rhs);
}

}
