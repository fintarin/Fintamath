#include "fintamath/functions/hyperbolic/Asinh.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asinh::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiAsinhSimplify(rhs);
}

std::unique_ptr<IMathObject> Asinh::multiAsinhSimplify(const INumber &rhs) {
  static const auto multiAsinh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAsinh;

    outMultiAsinh.add<Integer>([](const Integer &inRhs) {
      return multiAsinhSimplify(Real(inRhs));
    });

    outMultiAsinh.add<Rational>([](const Rational &inRhs) {
      return multiAsinhSimplify(Real(inRhs));
    });

    outMultiAsinh.add<Real>([](const Real &inRhs) {
      return asinh(inRhs).clone();
    });

    return outMultiAsinh;
  }();

  return multiAsinh(rhs);
}

}
