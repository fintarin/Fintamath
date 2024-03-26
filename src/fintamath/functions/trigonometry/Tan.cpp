#include "fintamath/functions/trigonometry/Tan.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

using namespace detail;

std::unique_ptr<IMathObject> Tan::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiTanSimplify(rhs);
}

std::unique_ptr<IMathObject> Tan::multiTanSimplify(const INumber &rhs) {
  static const auto multiTan = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiTan;

    outMultiTan.add<Integer>([](const Integer &inRhs) {
      return multiTanSimplify(Real(inRhs));
    });

    outMultiTan.add<Rational>([](const Rational &inRhs) {
      return multiTanSimplify(Real(inRhs));
    });

    outMultiTan.add<Real>([](const Real &inRhs) {
      return tan(inRhs).clone();
    });

    return outMultiTan;
  }();

  return multiTan(rhs);
}

}
