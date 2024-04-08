#include "fintamath/functions/hyperbolic/Tanh.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Tanh)

using namespace detail;

std::unique_ptr<IMathObject> Tanh::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiTanhSimplify(rhs);
}

std::unique_ptr<IMathObject> Tanh::multiTanhSimplify(const INumber &rhs) {
  static const auto multiTanh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiTanh;

    outMultiTanh.add<Integer>([](const Integer &inRhs) {
      return multiTanhSimplify(Real(inRhs));
    });

    outMultiTanh.add<Rational>([](const Rational &inRhs) {
      return multiTanhSimplify(Real(inRhs));
    });

    outMultiTanh.add<Real>([](const Real &inRhs) {
      return tanh(inRhs).clone();
    });

    return outMultiTanh;
  }();

  return multiTanh(rhs);
}

}
