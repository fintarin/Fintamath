#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

#include <memory>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(UnaryPlus)

std::unique_ptr<IMathObject> UnaryPlus::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<IArithmetic>(argVect.front().get());

  return +rhs;
}

}
