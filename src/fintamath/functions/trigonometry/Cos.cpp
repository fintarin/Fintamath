#include "fintamath/functions/trigonometry/Cos.hpp"

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

std::unique_ptr<IMathObject> Cos::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return multiCosSimplify(rhs);
}

std::unique_ptr<IMathObject> Cos::multiCosSimplify(const INumber &rhs) {
  static const auto multiCos = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCos;

    outMultiCos.add<Integer>([](const Integer &inRhs) {
      return multiCosSimplify(Real(inRhs));
    });

    outMultiCos.add<Rational>([](const Rational &inRhs) {
      return multiCosSimplify(Real(inRhs));
    });

    outMultiCos.add<Real>([](const Real &inRhs) {
      return cos(inRhs).clone();
    });

    return outMultiCos;
  }();

  return multiCos(rhs);
}

}
