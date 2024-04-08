#include "fintamath/functions/hyperbolic/Acsch.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Acsch)

using namespace detail;

std::unique_ptr<IMathObject> Acsch::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf{}.clone();
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
      return acsch(inRhs).clone();
    });

    return outMultiAcsch;
  }();

  return multiAcsch(rhs);
}

}
