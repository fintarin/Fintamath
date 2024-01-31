#include "fintamath/functions/hyperbolic/Acosh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/literals/constants/I.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acosh::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(-1)) {
    static const auto res = mulExpr(I(), Pi())->toMinimalObject();
    return res->clone();
  }

  if (rhs == Integer(0)) {
    static const auto res = divExpr(mulExpr(I(), Pi()), Integer(2).clone())->toMinimalObject();
    return res->clone();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiAcoshSimplify(rhs);
}

std::unique_ptr<IMathObject> Acosh::multiAcoshSimplify(const INumber &rhs) {
  static const auto multiAcosh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcosh;

    outMultiAcosh.add<Integer>([](const Integer &inRhs) {
      return multiAcoshSimplify(Real(inRhs));
    });

    outMultiAcosh.add<Rational>([](const Rational &inRhs) {
      return multiAcoshSimplify(Real(inRhs));
    });

    outMultiAcosh.add<Real>([](const Real &inRhs) {
      return acosh(inRhs).clone();
    });

    return outMultiAcosh;
  }();

  return multiAcosh(rhs);
}

}
