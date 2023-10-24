#include "fintamath/functions/hyperbolic/Acsch.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acsch::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  return multiAcschSimplify(rhs);
}

std::unique_ptr<IMathObject> Acsch::multiAcschSimplify(const INumber &rhs) {
  static const auto multiAcsch = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcsch;

    outMultiAcsch.add<Integer>([](const Integer &inRhs) {
      return multiAcschSimplify(Real(inRhs));
    });

    outMultiAcsch.add<Rational>([](const Rational &inRhs) {
      return multiAcschSimplify(Real(inRhs));
    });

    outMultiAcsch.add<Real>([](const Real &inRhs) {
      return acsch(inRhs).toMinimalObject();
    });

    return outMultiAcsch;
  }();

  return multiAcsch(rhs);
}

}
