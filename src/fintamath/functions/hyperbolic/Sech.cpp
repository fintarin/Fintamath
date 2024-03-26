#include "fintamath/functions/hyperbolic/Sech.hpp"

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

std::unique_ptr<IMathObject> Sech::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return multiSechSimplify(rhs);
}

std::unique_ptr<IMathObject> Sech::multiSechSimplify(const INumber &rhs) {
  static const auto multiSech = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSech;

    outMultiSech.add<Integer>([](const Integer &inRhs) {
      return multiSechSimplify(Real(inRhs));
    });

    outMultiSech.add<Rational>([](const Rational &inRhs) {
      return multiSechSimplify(Real(inRhs));
    });

    outMultiSech.add<Real>([](const Real &inRhs) {
      return sech(inRhs).clone();
    });

    return outMultiSech;
  }();

  return multiSech(rhs);
}

}
