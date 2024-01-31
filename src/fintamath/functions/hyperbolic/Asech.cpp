#include "fintamath/functions/hyperbolic/Asech.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/literals/constants/I.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asech::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(-1)) {
    static const auto res = mulExpr(I(), Pi())->toMinimalObject();
    return res->clone();
  }

  if (rhs == Integer(0)) {
    return Inf().clone();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiAsechSimplify(rhs);
}

std::unique_ptr<IMathObject> Asech::multiAsechSimplify(const INumber &rhs) {
  static const auto multiAsech = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAsech;

    outMultiAsech.add<Integer>([](const Integer &inRhs) {
      return multiAsechSimplify(Real(inRhs));
    });

    outMultiAsech.add<Rational>([](const Rational &inRhs) {
      return multiAsechSimplify(Real(inRhs));
    });

    outMultiAsech.add<Real>([](const Real &inRhs) {
      return asech(inRhs).clone();
    });

    return outMultiAsech;
  }();

  return multiAsech(rhs);
}

}
