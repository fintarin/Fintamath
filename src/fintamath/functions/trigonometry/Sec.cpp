#include "fintamath/functions/trigonometry/Sec.hpp"

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

std::unique_ptr<IMathObject> Sec::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return multiSecSimplify(rhs);
}

std::unique_ptr<IMathObject> Sec::multiSecSimplify(const INumber &rhs) {
  static const auto multiSec = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSec;

    outMultiSec.add<Integer>([](const Integer &inRhs) {
      return multiSecSimplify(Real(inRhs));
    });

    outMultiSec.add<Rational>([](const Rational &inRhs) {
      return multiSecSimplify(Real(inRhs));
    });

    outMultiSec.add<Real>([](const Real &inRhs) {
      return sec(inRhs).clone();
    });

    return outMultiSec;
  }();

  return multiSec(rhs);
}

}
