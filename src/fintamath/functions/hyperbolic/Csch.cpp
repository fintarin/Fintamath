#include "fintamath/functions/hyperbolic/Csch.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Csch::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf{}.clone();
  }

  return multiCschSimplify(rhs);
}

std::unique_ptr<IMathObject> Csch::multiCschSimplify(const INumber &rhs) {
  static const auto multiCsch = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCsch;

    outMultiCsch.add<Integer>([](const Integer &inRhs) {
      return multiCschSimplify(Real(inRhs));
    });

    outMultiCsch.add<Rational>([](const Rational &inRhs) {
      return multiCschSimplify(Real(inRhs));
    });

    outMultiCsch.add<Real>([](const Real &inRhs) {
      return csch(inRhs).clone();
    });

    return outMultiCsch;
  }();

  return multiCsch(rhs);
}

}
