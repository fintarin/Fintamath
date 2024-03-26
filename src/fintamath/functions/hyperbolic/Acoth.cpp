#include "fintamath/functions/hyperbolic/Acoth.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/literals/constants/I.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

using namespace detail;

std::unique_ptr<IMathObject> Acoth::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(-1)) {
    return NegInf{}.clone();
  }

  if (rhs == Integer(0)) {
    static const auto res = divExpr(mulExpr(I{}, Pi{}), Integer(2).clone())->toMinimalObject();
    return res->clone();
  }

  if (rhs == Integer(1)) {
    return Inf{}.clone();
  }

  return multiAcothSimplify(rhs);
}

std::unique_ptr<IMathObject> Acoth::multiAcothSimplify(const INumber &rhs) {
  static const auto multiAcoth = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcoth;

    outMultiAcoth.add<Integer>([](const Integer &inRhs) {
      return multiAcothSimplify(Real(inRhs));
    });

    outMultiAcoth.add<Rational>([](const Rational &inRhs) {
      return multiAcothSimplify(Real(inRhs));
    });

    outMultiAcoth.add<Real>([](const Real &inRhs) {
      return acoth(inRhs).clone();
    });

    return outMultiAcoth;
  }();

  return multiAcoth(rhs);
}

}
