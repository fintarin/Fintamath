#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sinh::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  return multiSinhSimplify(rhs);
}

std::unique_ptr<IMathObject> Sinh::multiSinhSimplify(const INumber &rhs) {
  static const auto multiSinh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSinh;

    outMultiSinh.add<Integer>([](const Integer &inRhs) {
      return multiSinhSimplify(Real(inRhs));
    });

    outMultiSinh.add<Rational>([](const Rational &inRhs) {
      return multiSinhSimplify(Real(inRhs));
    });

    outMultiSinh.add<Real>([](const Real &inRhs) {
      return sinh(inRhs).clone();
    });

    return outMultiSinh;
  }();

  return multiSinh(rhs);
}

}
