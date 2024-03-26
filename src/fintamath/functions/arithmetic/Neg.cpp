#include "fintamath/functions/arithmetic/Neg.hpp"

#include <memory>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Neg::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<IArithmetic>(argVect.front().get());

  return -rhs;
}

}
