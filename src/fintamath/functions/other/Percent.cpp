#include "fintamath/functions/other/Percent.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Percent)

std::unique_ptr<IMathObject> Percent::call(const ArgumentRefVector &argVect) const {
  static const Rational percentVal = 100;
  const auto &rhs = cast<INumber>(argVect.front().get());

  return (rhs / percentVal)->toMinimalObject();
}

}
